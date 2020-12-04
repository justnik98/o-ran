//
// Created by justnik on 21.11.2020.
//

#ifndef O_RAN_HTTPWRITER_H
#define O_RAN_HTTPWRITER_H

#include "IWriter.h"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/asio/buffer.hpp>

class HTTPWriter : public IWriter {
private:
    std::string host;
    std::string port;
    std::string target = "/index.html";
    int version = 11;
public:
    HTTPWriter(const std::string &ip, const std::string &port);

    void write(const std::string &str) const override;

    bool isReachable() const;

    virtual ~HTTPWriter() {};

};


#endif //O_RAN_HTTPWRITER_H
