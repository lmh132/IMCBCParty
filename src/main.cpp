#include <iostream>
#include <string>

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

std::vector<char> vBuffer(1 * 1024);

void getData(asio::ip::tcp::socket &socket) {
    socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()), [&](std::error_code ec, std::size_t length) {
        if (!ec) {
            std::cout << "\n\nRead " << length << " bytes\n\n";

            for (int i = 0; i < length; i++) {
                std::cout << vBuffer[i];
            }

            getData(socket);
        }
    });
}

// int main() {
//     asio::error_code ec;

//     asio::io_context context;

//     asio::io_context::work idleWork(context);

//     std::thread thrContext = std::thread([&]() { context.run(); });

//     asio::ip::tcp::resolver resolver(context);
//     auto endpoint = resolver.resolve("example.com", "80", ec);

//     if (ec) {
//         std::cout << "Failed to resolve: " << ec.message() << std::endl;
//         return -1;
//     }

//     asio::ip::tcp::socket socket(context);

//     std::cout << "Attempting to connect" << std::endl;

//     asio::connect(socket, endpoint, ec);

//     if(!ec) {
//         std::cout << "Connected!" << std::endl;
//     } else {
//         std::cout << "Failed to connect to address:\n" << ec.message() << std::endl;
//     }

//     if (socket.is_open()) {
//         getData(socket);

//         std::string sRequest = "GET /index.html HTTP/1.1\r\n"
//                                "Host: example.com\r\n"
//                                "Connection: close\r\n\r\n";
//         socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);

//         std::this_thread::sleep_for(std::chrono::seconds(2));
//     }

//     std::cin.get();
//     return 0;
// };
