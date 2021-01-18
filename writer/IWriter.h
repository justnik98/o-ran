//
// Created by justnik on 21.11.2020.
//

#ifndef O_RAN_IWRITER_H
#define O_RAN_IWRITER_H

#include <iostream>
#include <string>
#include <thread>
#include <ctime>

class IWriter {
public:
    virtual void write(const std::string &str) const = 0;

    virtual ~IWriter() = default;;

    IWriter &operator=(const IWriter &) = delete;
};

inline void IWriter::write(const std::string &str) const {
    std::cout << str;
}

#endif //O_RAN_IWRITER_H
