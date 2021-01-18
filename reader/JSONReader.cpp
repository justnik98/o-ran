//
// Created by justnik on 21.11.2020.
//

#include "JSONReader.h"

using namespace std;

JSONReader::JSONReader(const string &filename) {
    fstream in;
    in.open("../" + filename);
    uint32_t counter = 0;
    string str;
    string quote;
    while (getline(in, str)) {
        if (str.find("value") != string::npos) {
            auto posEnd = str.rfind('\"');
            auto posBegin = str.rfind('\"', posEnd - 1);
            quote = str.substr(posBegin, posEnd - posBegin + 1);
            quotes[counter++] = quote;
        }
    }
}

string JSONReader::getLabel(uint32_t id) const {
    return string("AAA");
}

string JSONReader::getQuote() {
    auto ind = r.rand() % quotes.size();
    string res = quotes.at(ind);
    return res;
}


