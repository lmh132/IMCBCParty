#pragma once

#include "net_common.h"
#include "net_message.h"
#include "net_tsq.h"

template <typename T>
class client_interface {
public:
    client_interface() : m_socket(m_context) {}
    virtual ~client_interface() { disconnect(); }


    bool connect(const std::string& host, const uint16_t port) {
        try {
            m_connection = std::make_unique<connection<T>>();

            asio::ip::tcp::resolver resolver(m_context);
            endpoints = resolver.resolve(host, std::to_string(port));

            m_connection->ConnectToServer(endpoints);
            thrContext = std::thread([this]() { m_context.run(); });
        } catch (std::exception& e) {
            std::cerr << "Client Exception: " << e.what() << std::endl;
            return false;
        }
    }

    bool disconnect() {
        if (isConnected()) {
            m_connection->Disconnect();
        }
        m_context.stop();
        if (thrContext.joinable()) {
            thrContext.join();
        }
        m_connection.release();
    }

    bool isConnected() {
        if (m_connection) {
            return m_connection->isConnected();
        } else {
            return false;
        }
    }

    tsqueue<owned_message<T>>& incoming() {
        return m_qMessagesIn;
    }

protected:
    asio::io_context m_context;
    std::thread thrContext;
    asio::ip::tcp::socket m_socket;
    std::unique_ptr<connection<T>> m_connection;
    asio::ip::tcp::resolver::results_type endpoints;

private:
    tsqueue<owned_message<T>> m_qMessagesIn;
};