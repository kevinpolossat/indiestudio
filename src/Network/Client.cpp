//
// Created by florian on 29/05/17.
//

#include "Client.hh"

Client &Client::getClient() {
    static Client cl;
    return cl;
}

Client::~Client() {

}

Client::Client() {
    this->callback = [](udp_server &){throw std::runtime_error("No callback set");};
}

bool Client::connectMainServer() {
    if (nullptr == this->tcp) {
        try {
            this->tcp_io_service = std::make_unique<boost::asio::io_service>();
            this->tcp = std::make_unique<tcp_client>(*tcp_io_service, "127.0.0.1");
            std::thread tmp([&](){
                tcp_io_service->run();
            });
            tmp.detach();
        }
        catch (...) {
            this->tcp = nullptr;
        }
    }
    return nullptr != this->tcp;
}

bool Client::connectPlayer() const {
    return nullptr != this->udp;
}

bool Client::launchServer() {
    auto ip = this->getIp();

    if (ip.empty() == true){
        return false;
    }
    try{
        this->udp_io_service = std::make_unique<boost::asio::io_service>();
        this->udp = std::make_unique<udp_client>(*udp_io_service, ip);
        std::thread tmp([&](){
            udp_io_service->run();
        });
        tmp.detach();
    }
    catch (...){
        this->udp = nullptr;
    }
    return connectPlayer();
}

std::string Client::get() {
    return this->udp->read();
}

void Client::send(std::string const &msg) {
    this->udp->send(msg);
}

std::string Client::getIp() {
    auto ip = (nullptr == this->tcp) ? "master\n127.0.0.1" : this->tcp->read();

    if (ip.empty() == true){
        return "";
    }

    std::vector<std::string> vec;
    boost::split(vec, ip, boost::is_any_of("\n"));

    if (vec.size() == 2){
        this->udp_server_io_service = std::make_unique<boost::asio::io_service>();
        this->server = std::make_unique<udp_server>(*udp_server_io_service);
        std::thread tmp([&](){
            udp_server_io_service->run();
        });
        tmp.detach();
        std::thread tmpCallback([&](){
            this->callback(*this->server);
        });
        tmpCallback.detach();
        return vec[1];
    }
    return vec[0];
}

void Client::stop() {
    if (nullptr != tcp_io_service)
        tcp_io_service->stop();
    if (nullptr != udp_io_service)
        udp_io_service->stop();
    if (nullptr != udp_server_io_service)
        udp_server_io_service->stop();
}

void Client::setCallback(std::function<void(udp_server &)> callback) {
    this->callback = callback;
}


/*
int main()
{
    bool stop = false;
    Client &client = Client::getClient();
    client.setCallback([&](udp_server &server){
        while (false == stop){
            auto msg = server.read();
            if (msg.empty() == false){
                std::cout << "recu: " << msg << std::endl;
            }
        }
    });
    client.connectMainServer();

    for (int i = 0; i < 10 && client.launchServer() == false; ++i) {

        sleep(3);
    }
    for (int i = 0; i < 5; ++i) {
        client.send("coucou" + std::to_string(getpid()));
        sleep(2);
    }
    stop = true;
    client.stop();
    return 0;
}*/