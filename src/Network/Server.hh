//
// Created by florian on 29/05/17.
//

#ifndef INDIESTUDIO_SERVER_HH
#define INDIESTUDIO_SERVER_HH

#define _WIN32_WINNT 0x0501

#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include "tcp_connection.hh"

using boost::asio::ip::tcp;
using boost::asio::ip::udp;

class Server {
public:
    size_t const nb_players = 2;

    explicit Server(boost::asio::io_service& io_service)
            : acceptor_(io_service, tcp::endpoint(tcp::v4(), 2000)), io_service(io_service)
    {
        start_accept();
    }

    ~Server() {}
private:
    Server(Server const & other)                = delete;
    Server(Server && other)                     = delete;
    Server& operator = (Server const & other)   = delete;

    void start_accept()
    {
        tcp_connection::pointer new_connection =
                tcp_connection::create(io_service); // Update

        acceptor_.async_accept(new_connection->socket(),
                               boost::bind(&Server::handle_accept, this, new_connection,
                                           boost::asio::placeholders::error));
    }

    void handle_accept(tcp_connection::pointer new_connection,
                       const boost::system::error_code& error)
    {
        if (!error)
        {
            this->connects.push_back(new_connection);
            new_connection->read();
            if (this->connects.size() == Server::nb_players){
                auto &master = this->connects.back();
                auto masterIp = master->socket().remote_endpoint().address().to_string();
                this->connects.pop_back();
                master->send("master\n" + masterIp);
                for (auto &i: this->connects){
                    i->send(masterIp);
                }
                this->connects.clear();
            }
            start_accept();
        }
    }

    tcp::acceptor acceptor_;
    boost::asio::io_service &io_service;
    std::vector<tcp_connection::pointer> connects;
};

#endif //INDIESTUDIO_SERVER_HH
