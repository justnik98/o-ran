//
// Created by justnik on 21.11.2020.
//

#ifndef O_RAN_IWRITER_H
#define O_RAN_IWRITER_H

#include <string>
#include <iostream>

class IWriter {
public:
    virtual void write(const std::string &str) const = 0;

    virtual ~IWriter() {};

    IWriter &operator=(const IWriter &) = delete;
};

inline void IWriter::write(const std::string &str) const {
    std::cout << str << std::endl;
}

#endif //O_RAN_IWRITER_H
