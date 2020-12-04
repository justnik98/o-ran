//
// Created by justnik on 21.11.2020.
//

#include "JSONReader.h"

using namespace std;

JSONReader::JSONReader(const string &filename) : filename(filename) {
    srand(time(NULL));
}

string JSONReader::getLabel(uint32_t id) const {
    return string("AAA");
}

string JSONReader::getQuote() const {
    std::fstream in;
    in.open(filename);
    uint32_t num = 1 + (rand() % 100);
    uint32_t pos = 0;
    uint32_t pos2 = 0;
    uint32_t counter = 0;
    string str = "";
    while (counter != num) {
        getline(in, str);
        if (str.find("value") != string::npos) {
            counter++;
        }
    }
    pos = str.find("\"", 11);
    pos2 = str.find(',');
    in.close();

    return str.substr(pos, pos2 - pos);
}


