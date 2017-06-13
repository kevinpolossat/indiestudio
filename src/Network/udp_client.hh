//
// Created by florian on 29/05/17.
//

#ifndef INDIESTUDIO_UDP_CLIENT_HH
#define INDIESTUDIO_UDP_CLIENT_HH

#define _WIN32_WINNT 0x0501

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <thread>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <mutex>
#include <queue>
#include <set>

using boost::asio::ip::udp;

class udp_client {
public:
    udp_client(boost::asio::io_service &io_service, std::string ip)
    :  socket(io_service), endpoint_(boost::asio::ip::address::from_string(ip), 2000)
    {
        this->socket.open(udp::v4());
        this->start_receive();
    }

    udp_client(udp_client const & other)                = delete;
    udp_client(udp_client && other)                     = delete;
    udp_client operator = (udp_client const & other)    = delete;

    ~udp_client() {}

    auto extractVecOfString(std::string const &str){
        std::vector<std::string> vec;
        auto iter = str.size() / 4096;

        for (decltype(iter) i = 0; i < str.size(); i += 4096){
            vec.push_back(str.substr(i, 4096));
        }

        return std::move(vec);
    }

    void send(std::string const &msg){
        auto vec = this->extractVecOfString(msg + "\t\r\n");

        std::lock_guard<std::mutex> l(mtx);

        for (auto &i: vec) {
            socket.async_send_to(boost::asio::buffer(i), endpoint_,
                                 [](const boost::system::error_code &/*error*/, std::size_t /*bytes_transferred*/) {

                                 });
        }
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

private:
    void start_receive()
    {
        socket.async_receive_from(
                boost::asio::buffer(recv_buffer_), remote_endpoint_,
                boost::bind(&udp_client::handle_receive, this,
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

private:
    udp::socket socket;
    udp::endpoint endpoint_;
    udp::endpoint remote_endpoint_;
    boost::array<char, 4096> recv_buffer_;
    std::set<udp::endpoint> endpoints;
    std::map<udp::endpoint, std::string> endpoints_data;
    std::mutex mtx;
    std::queue<std::string> messages;
};

#endif //INDIESTUDIO_UDP_CLIENT_HH
