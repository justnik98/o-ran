//
// Created by justnik on 21.11.2020.
//

#ifndef O_RAN_IREADER_H
#define O_RAN_IREADER_H

#include <string>

class IReader {
public:
    virtual std::string getLabel(uint32_t id) const = 0;

    virtual std::string getQuote() const = 0;
    //virtual uint32_t getLabelsNum()const = 0;

    virtual ~IReader() {};
};


#endif //O_RAN_IREADER_H
