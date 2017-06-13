//
// Created by florian on 29/05/17.
//

#ifndef INDIESTUDIO_TCP_CONNECTION_HH
#define INDIESTUDIO_TCP_CONNECTION_HH

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;
using boost::asio::ip::udp;

class tcp_connection
        : public boost::enable_shared_from_this<tcp_connection>
{
public:
    typedef boost::shared_ptr<tcp_connection> pointer;

    static pointer create(boost::asio::io_service& io_service)
    {
        return pointer(new tcp_connection(io_service));
    }

    tcp::socket& socket()
    {
        return socket_;
    }

    void send(std::string const &message)
    {
        boost::asio::async_write(socket_, boost::asio::buffer(message),
                                 boost::bind(&tcp_connection::handle_write, shared_from_this()));
    }

    void read(){
        boost::asio::async_read(socket_, boost::asio::buffer(this->buffer),
                                boost::asio::transfer_at_least(3),
                                boost::bind(&tcp_connection::handle_read, shared_from_this(),
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred)
        );
    }

    void handle_read(const boost::system::error_code& error, size_t number_bytes_read){
        if (!error){
            {
                std::cout.write(&buffer[0], number_bytes_read) << std::endl;
                this->message_.append(&buffer[0], number_bytes_read);
                this->read();
            }
        }
    }

private:
    explicit tcp_connection(boost::asio::io_service& io_service)
            : socket_(io_service)
    {
    }

    tcp_connection(tcp_connection const & other)                = delete;
    tcp_connection(tcp_connection && other)                     = delete;
    tcp_connection &operator = (tcp_connection const & other)   = delete;

    void handle_write()
    {
    }

    tcp::socket socket_;
    std::string message_;
    boost::array<char, BUFSIZ> buffer;
};


#endif //INDIESTUDIO_TCP_CONNECTION_HH
