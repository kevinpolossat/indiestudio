//
// Created by florian on 29/05/17.
//

#ifndef INDIESTUDIO_UDP_SERVER_HH
#define INDIESTUDIO_UDP_SERVER_HH

#include <set>
#include <thread>
#include <mutex>
#include <map>
#include <boost/algorithm/string.hpp>
#include <queue>
#include "tcp_connection.hh"

class udp_server {
public:
    udp_server(boost::asio::io_service& io_service)
            : socket_(io_service, udp::endpoint(udp::v4(), 2000))
    {
        start_receive();
    }

    std::string read(){
        std::lock_guard<std::mutex> l(mtx);

        if (this->messages.size() == 0){
            return "";
        }

        auto msg = std::move(this->messages.front());
        this->messages.pop();

        return msg;
    }

    auto extractVecOfString(std::string const &str){
        std::vector<std::string> vec;
        auto iter = str.size() / 4096;

        for (decltype(iter) i = 0; i < str.size(); i += 4096){
            vec.push_back(str.substr(i, 4096));
        }

        return std::move(vec);
    }

    void send(std::string const &msg){
        std::lock_guard<std::mutex> l(mtx);

        auto vec = this->extractVecOfString(msg + "\t\r\n");

        for (auto &endpoint: endpoints) {
            for (auto &i: vec) {
                socket_.async_send_to(boost::asio::buffer(i), endpoint,
                                     [](const boost::system::error_code &error, std::size_t bytes_transferred) {

                                     });
            }
        }
    }

private:
    void start_receive()
    {
        socket_.async_receive_from(
                boost::asio::buffer(recv_buffer_), remote_endpoint_,
                boost::bind(&udp_server::handle_receive, this,
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
    }

    auto readBuffer(boost::array<char, 4096> &buffer, std::size_t nb_read){
        std::vector<std::string> vec;
        std::string str(buffer.begin(), buffer.begin() + nb_read);

        boost::split(vec, str, boost::is_any_of("\r\n"));

        decltype(vec) res(vec.size());
        std::copy_if(vec.begin(), vec.end(), res.begin(), [](auto const &str){return str.empty() == false;});

        return std::move(res);
    }

    void handle_receive(const boost::system::error_code& error, std::size_t nb_read)
    {
        if (!error || error == boost::asio::error::message_size)
        {
            {
                std::lock_guard<std::mutex> l(mtx);

                endpoints.insert(remote_endpoint_);
                if (this->endpoints_data.end() == this->endpoints_data.find(remote_endpoint_)){
                    this->endpoints_data[remote_endpoint_] = "";
                }
                auto vec = this->readBuffer(recv_buffer_, nb_read);

                this->endpoints_data[remote_endpoint_] += std::move(vec.front());
                vec.erase(vec.begin());

                if (this->endpoints_data[remote_endpoint_].find_first_of("\t") != std::string::npos){
                    this->endpoints_data[remote_endpoint_].pop_back();
                    messages.push(std::move(this->endpoints_data[remote_endpoint_]));
                    this->endpoints_data[remote_endpoint_].clear();
                }
                if (vec.size() > 0 && vec.back().find_first_of("\t") == std::string::npos) {
                    this->endpoints_data[remote_endpoint_] = std::move(vec.back());
                    vec.pop_back();
                }
                if (vec.size() > 0) {
                    std::for_each(vec.begin(), vec.end(), [&](auto &msg) {
                        messages.push(std::move(msg));
                    });
                }
            }

            start_receive();
        }
    }

    void handle_send()
    {
        std::cout << "send ok: " << std::endl;
    }

    udp::socket socket_;
    udp::endpoint remote_endpoint_;
    boost::array<char, 4096> recv_buffer_;
    std::set<udp::endpoint> endpoints;
    std::map<udp::endpoint, std::string> endpoints_data;
    std::mutex mtx;
    std::queue<std::string> messages;
};
/*
int main()
{
    boost::asio::io_service io_service;

    udp_server server(io_service);
    std::thread t([&](){io_service.run();});
        while (1){
            auto msg = server.read();
            if (msg.empty() == false){
                std::cout << "recu: " << msg << std::endl;
                //std::string rep;
                //std::cout << "Envoyer la réponse :";
                //std::cin >> rep;

                //server.send(msg);

            }
        }

}
*/

#endif //INDIESTUDIO_UDP_SERVER_HH
