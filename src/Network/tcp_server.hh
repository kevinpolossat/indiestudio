//
// Created by florian on 29/05/17.
//

#ifndef INDIESTUDIO_TCP_SERVER_HH
#define INDIESTUDIO_TCP_SERVER_HH

#include "tcp_connection.hh"

class tcp_server {
public:
    explicit tcp_server(boost::asio::io_service& io_service)
            : acceptor_(io_service, tcp::endpoint(tcp::v4(), 2000)), io_service(io_service)
    {
        start_accept();
    }

    tcp_server(tcp_server const & other)                = delete;
    tcp_server(tcp_server && other)                     = delete;
    tcp_server &operator = (tcp_server const & other)   = delete;
    ~tcp_server() {}

private:
    void start_accept()
    {
        tcp_connection::pointer new_connection =
                tcp_connection::create(acceptor_.get_io_service()); // Update

        acceptor_.async_accept(new_connection->socket(),
                               boost::bind(&tcp_server::handle_accept, this, new_connection,
                                           boost::asio::placeholders::error));
    }

    void handle_accept(tcp_connection::pointer new_connection,
                       const boost::system::error_code& error)
    {
        if (!error)
        {
            new_connection->read();
            start_accept();
        }
    }

    tcp::acceptor acceptor_;
    boost::asio::io_service &io_service;
};
/*
int main(){
    boost::asio::io_service io_service;
    tcp_server s(io_service);
    io_service.run();
    return (0);
}
*/

#endif //INDIESTUDIO_TCP_SERVER_HH
