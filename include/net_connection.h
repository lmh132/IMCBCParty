#pragma once

#include "net_common.h"
#include "net_message.h"
#include "net_tsq.h"

template <typename T>
class connection : public std::enable_shared_from_this<connection<T>> {
public:
    connection() {}

    virtual ~connection() {}

    bool connectToServer();
    bool disconnect();
    bool isConnected() const;

    bool sendMsg(const message<T>& msg);

protected:
    asio::ip::tcp::socket m_socket;
    asio::io_context& m_asioContext;

    tsqueue<message<T>> m_qMessagesOut;
    tsqueue<owned_message<T>> m_qMessagesIn;
};