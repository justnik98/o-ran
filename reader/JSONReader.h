//
// Created by justnik on 21.11.2020.
//

#ifndef O_RAN_JSONREADER_H
#define O_RAN_JSONREADER_H

#include "IReader.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>

#include "../libs/Random.h"

class JSONReader : public IReader {
private:

    std::map<uint32_t, std::string> quotes;

    Random r;
public:
    explicit JSONReader(const std::string &filename);

    [[nodiscard]] std::string getLabel(uint32_t id) const override;

    [[nodiscard]] std::string getQuote() override;

    ~JSONReader() override = default;;
};


#endif //O_RAN_JSONREADER_H
