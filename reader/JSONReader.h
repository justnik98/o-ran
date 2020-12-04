//
// Created by justnik on 21.11.2020.
//

#ifndef O_RAN_JSONREADER_H
#define O_RAN_JSONREADER_H

#include "IReader.h"
#include <fstream>
#include <cstdio>
#include <iostream>

class JSONReader : public IReader {
private:
    std::string filename;
public:
    JSONReader(const std::string &filename);

    std::string getLabel(uint32_t id) const override;

    std::string getQuote() const override;

    virtual ~JSONReader() {};
};


#endif //O_RAN_JSONREADER_H
