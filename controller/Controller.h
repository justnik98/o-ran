//
// Created by justnik on 02.12.2020.
//

#ifndef O_RAN_CONTROLLER_H
#define O_RAN_CONTROLLER_H

#include <string>
#include <optional>
#include "../writer/IWriter.h"
#include "../reader/IReader.h"

class Controller {
private:
    IWriter &w;
    IReader &r;
    std::string url;
    uint32_t port = 6379;
    const timespec time{0, 500000L};
public:
    Controller(IWriter &w, IReader &r, const std::string &url);

    Controller(IWriter &w, IReader &r, const std::string &url, uint32_t port);

    void run() const;
};


#endif //O_RAN_CONTROLLER_H
