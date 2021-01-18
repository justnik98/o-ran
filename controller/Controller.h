//
// Created by justnik on 02.12.2020.
//

#ifndef O_RAN_CONTROLLER_H
#define O_RAN_CONTROLLER_H

#include <map>
#include <optional>
#include <string>
#include "../writer/IWriter.h"
#include "../reader/IReader.h"

class Controller {
private:
    IWriter &w;
    IReader &r;
    std::string url;
    uint32_t port = 6379;
public:
    [[maybe_unused]] Controller(IWriter &w, IReader &r, const std::string &url);

    Controller(IWriter &w, IReader &r, const std::string &url, uint32_t port);

    void run() const;
};

void config(std::map<std::string, std::string> & params);


#endif //O_RAN_CONTROLLER_H
