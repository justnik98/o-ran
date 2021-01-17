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

class JSONReader : public IReader {
private:
    std::string filename;

    std::map<uint32_t, std::string> quotes;
public:
    JSONReader(const std::string &filename);

    std::string getLabel(uint32_t id) const override;

    std::string getQuote() const override;

    virtual ~JSONReader() {};
};


#endif //O_RAN_JSONREADER_H
