//
// Created by florian on 29/05/17.
//

#ifndef INDIESTUDIO_TCP_CLIENT_HH
#define INDIESTUDIO_TCP_CLIENT_HH

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>
#include <mutex>

using boost::asio::ip::tcp;

class tcp_connection_client : public boost::enable_shared_from_this<tcp_connection_client>
{
public:
    typedef boost::shared_ptr<tcp_connection_client> pointer;

    static pointer create(boost::asio::io_service& ios)
    {
        return pointer(new tcp_connection_client(ios));
    }

    tcp::socket& socket()
    {
        return m_socket;
    }

    void readAsync()
    {
        boost::asio::async_read(m_socket, boost::asio::buffer(m_network_buffer),
                                boost::asio::transfer_at_least(3),
                                boost::bind(&tcp_connection_client::handle_read, shared_from_this(),
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred)
        );
    }

    std::string read(){
        std::string res;

        {
            std::lock_guard<std::mutex> l(mtx);

            res = message_;
            message_.clear();
        }
        return res;
    }

    void write(std::string const & str){
        auto msg = str;

        boost::asio::async_write(m_socket, boost::asio::buffer(msg),
                                 boost::bind(&tcp_connection_client::handle_write, shared_from_this(),
                                             boost::asio::placeholders::error)
        );
    }

private:
    tcp_connection_client(boost::asio::io_service& io_service)
            : m_socket(io_service), io_service(io_service)
    {
    }

    void handle_read(const boost::system::error_code& error, size_t /*number_bytes_read*/)
    {
        if (!error) {
            {
                std::lock_guard<std::mutex> l(mtx);

                this->message_.clear();
                this->message_.append(m_network_buffer.begin(), m_network_buffer.end());
            }
            readAsync();
        }
    }

    void handle_write(const boost::system::error_code& error)
    {
        if (error)
        {
            std::cerr << "Error on write" << std::endl;
        }
    }

    tcp::socket				m_socket;
    boost::array<char, BUFSIZ> m_network_buffer;
    boost::asio::io_service&	io_service;
    std::mutex mtx;
    std::string message_;
};


class tcp_client
{
public:
    tcp_client(boost::asio::io_service& io_service, std::string const &ip)
            :m_io_service (io_service)
    {
        tcp::endpoint endpoint(boost::asio::ip::address::from_string(ip), 2000);
        connect(endpoint);
    }

    std::string read(){
        return connection->read();
    }

    void send(std::string const &msg){
        connection->write(msg);
    }
private:
    void connect(tcp::endpoint& endpoint)
    {
        connection = tcp_connection_client::create(m_io_service);
        tcp::socket& socket = connection->socket();
        socket.async_connect(endpoint,
                             boost::bind(&tcp_client::handle_connect, this, connection, boost::asio::placeholders::error)
        );
    }

    void handle_connect(tcp_connection_client::pointer new_connection, const boost::system::error_code& error)
    {
        if (!error)
        {
            new_connection->readAsync();
        }
    }


    boost::asio::io_service&	m_io_service;
    tcp_connection_client::pointer     connection;
};

/*

#include <thread>
int main(){
    boost::asio::io_service io_service;
    tcp_client u(io_service, "127.0.0.1");

    std::thread t([&](){io_service.run();});
    t.detach();
    std::thread t2([&](){
        while (1){
            auto msg = u.read();
            if (msg.empty() == false){
                std::cout << "recu: " << msg << std::endl;
            }
        }
    });
    t2.detach();
    while(1) {
        std::string msg;
        std::cin >> msg;
        if (msg == ""){
            break;
        }
        u.send(msg);
    }

    sleep(3);
    io_service.stop();
    return 0;
}
*/

#endif //INDIESTUDIO_TCP_CLIENT_HH
