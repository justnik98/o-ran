//
// Created by justnik on 21.11.2020.
//

#include "HTTPWriter.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;


HTTPWriter::HTTPWriter(const std::string &ip, const std::string &port) : host(ip), port(port) {}

void HTTPWriter::write(const std::string &str) const {
    if (isReachable()) {
        try {
            // The io_context is required for all I/O
            net::io_context ioc;

            // These objects perform our I/O
            tcp::resolver resolver(ioc);
            beast::tcp_stream stream(ioc);

            // Look up the domain name
            auto const results = resolver.resolve(host, port);

            // Make the connection on the IP address we get from a lookup
            stream.connect(results);

            // Set up an HTTP GET request message
            http::request<http::string_body> req{http::verb::get, target, version};
            req.set(http::field::host, host);
            req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
            req.set(http::field::message_context, str);

            // Send the HTTP request to the remote host
            http::write(stream, req);

            // This buffer is used for reading and must be persisted
            beast::flat_buffer buffer;

            // Declare a container to hold the response
            http::response<http::dynamic_body> res;

            // Receive the HTTP response
            http::read(stream, buffer, res);

            // Write the message to standard out
            // std::string s = boost::beast::buffers_to_string(res.base().result());
            uint32_t status = res.base().result_int();
            if (status != 200) {
                beast::error_code ec;
                stream.socket().shutdown(tcp::socket::shutdown_both, ec);
                if (ec && ec != beast::errc::not_connected)
                    throw beast::system_error{ec};
            }
            // Gracefully close the socket
            beast::error_code ec;
            stream.socket().shutdown(tcp::socket::shutdown_both, ec);

            // not_connected happens sometimes
            // so don't bother reporting it.
            //
            if (ec && ec != beast::errc::not_connected)
                throw beast::system_error{ec};

            // If we get here then the connection is closed gracefully
        }
        catch (std::exception const &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return;
        }
    }
}

bool HTTPWriter::isReachable() const {
    try {
        // The io_context is required for all I/O
        net::io_context ioc;

        // These objects perform our I/O
        tcp::resolver resolver(ioc);
        beast::tcp_stream stream(ioc);

        // Look up the domain name
        auto const results = resolver.resolve(host, port);

        // Make the connection on the IP address we get from a lookup
        stream.connect(results);

        // Set up an HTTP GET request message
        http::request<http::string_body> req{http::verb::get, target, version};
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        req.set(http::field::message_context, "Hello");

        // Send the HTTP request to the remote host
        http::write(stream, req);

        // This buffer is used for reading and must be persisted
        beast::flat_buffer buffer;

        // Declare a container to hold the response
        http::response<http::dynamic_body> res;

        // Receive the HTTP response
        http::read(stream, buffer, res);

        // Write the message to standard out
        // std::string s = boost::beast::buffers_to_string(res.base().result());
        uint32_t status = res.base().result_int();
        if (status != 200) {
            beast::error_code ec;
            std::clog << "HTTP error with code " << status << std::endl;
            stream.socket().shutdown(tcp::socket::shutdown_both, ec);
            if (ec && ec != beast::errc::not_connected)
                throw beast::system_error{ec};
            return 0;
        }
        std::clog << "Successfully connected" << std::endl;
        // Gracefully close the socket
        beast::error_code ec;
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);

        // not_connected happens sometimes
        // so don't bother reporting it.
        //
        if (ec && ec != beast::errc::not_connected)
            throw beast::system_error{ec};

        // If we get here then the connection is closed gracefully
    }
    catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 0;
    }
    return 1;
}
