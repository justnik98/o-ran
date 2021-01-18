//
// Created by justnik on 21.11.2020.
//

#ifndef O_RAN_CONSOLEWRITER_H
#define O_RAN_CONSOLEWRITER_H

#include "IWriter.h"

class ConsoleWriter : public IWriter {
public:
    void write(const std::string &str) const override;

    ~ConsoleWriter() override = default;
};


#endif //O_RAN_CONSOLEWRITER_H
