//
// Created by florian on 29/05/17.
//

#ifndef INDIESTUDIO_CLIENT_HH
#define INDIESTUDIO_CLIENT_HH

#define _WIN32_WINNT 0x0501

#include <chrono>
#include <thread>
#include <boost/archive/text_oarchive.hpp>

#include "tcp_client.hh"
#include "udp_client.hh"
#include "udp_server.hh"
#include "Map.hh"
#include "Referee.hh"

class Client {
public:
    static Client &getClient();
    ~Client();

    /**
     * Return message send by player server
     * @return
     */
    std::string get();
    /**
     * Send message for player server
     */
    void send(std::string const &);

    /**
     * Return true if connection on main server is ready
     * @return
     */
    bool connectMainServer();
    /**
     * Return true if we are connect on player server
     * @return
     */
    bool connectPlayer() const;
    /**
     * launch server in local, return true if is success
     */
    bool launchServer();

    /**
     * Stop all customer
     */
    void stop();

    void setCallback(std::function<void (udp_server&)>);

private:
    Client();
    Client(Client const &)              = delete;
    Client &operator=(Client const &)   = delete;
    Client(Client &&)                   = delete;
    std::string getIp();

private:
    std::unique_ptr<boost::asio::io_service> tcp_io_service;
    std::unique_ptr<boost::asio::io_service> udp_io_service;
    std::unique_ptr<boost::asio::io_service> udp_server_io_service;

    std::unique_ptr<tcp_client> tcp;
    std::unique_ptr<udp_client> udp;
    std::unique_ptr<udp_server> server;

    std::function<void(udp_server &)> callback;
};


#endif //INDIESTUDIO_CLIENT_HH
