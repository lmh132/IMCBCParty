#include "net_common.h"
#include "net_message.h"
#include "net_tsq.h"
#include "net_connection.h"

template <typename T>
class server_interface {
public:
    server_interface(uint16_t : port) : m_asioAcceptor(m_asioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {

    }

    virtual ~server_interface() {
        stop();
    }

    start() {
        try {
            waitForClientConnection();
            m_threadContext = std::thread([this]() { m_asioContext.run(); });
        } catch (std::exception& e) {
            std::cerr << "[SERVER] Exception: " << e.what() << std::endl;
        }
        std::cout << "[SERVER] Started!" << std::endl;
        return true;
    }

    stop() {
        m_asioContext.stop();
        if (m_threadContext.joinable()) {
            m_threadContext.join();
        }
        std::cout << "[SERVER] Stopped!" << std::endl;
    }

    //ASYNC
    void waitForClientConnection() {
        m_asioAcceptor.async_accept([this](std::error_code ec, asio::ip::tcp::socket socket) {
            if (!ec) {
                std::cout << "[SERVER] New Connection: " << socket.remote_endpoint() << std::endl;
                std::shared_ptr<connection<T>> newConn = 
            } else {
                std::cout << "[SERVER] New Connection Error: " << ec.message() << std::endl;
            }

            waitForClientConnection();
        });
    }

    void messageClient(std::shared_ptr<connection<T>> client, const message<T>& msg) {
        
    }

    void messageAllClients(const message<T>& msg, std::shared_ptr<connection<T>> pIgnoreClient = nullptr) {
        
    }

protected:
    virtual bool onClientConnect(std::shared_ptr<connection<T>> client) {
        return false;
    }

    virtual void onClienDisconnect(std::shared_ptr<connection<T>> client) {
        return false;
    }

    virtual void onMessage(std::shared_ptr<connection<T>> client, message<T>& msg) {
        return false;
    }

    tsqueue<owned_message<T>> m_qMessagesIn;
    asio::io_context m_asioContext;
    std::thread = m_threadContext;

    //get socket for client connections
    asio::ip::tcp::acceptor m_asioAcceptor;

    uint32_t nIDCounter = 10000;
};