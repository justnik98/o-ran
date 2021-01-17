#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include "controller/Controller.h"
#include "reader/JSONReader.h"
#include "writer/ConsoleWriter.h"
#include "writer/HTTPWriter.h"


using namespace std;

int main() {
    try {
        map<string, string> params;
        ifstream cfg("o-ran.cfg");
        if (cfg.is_open()) {
            string line;
            while (getline(cfg, line)) {
                line.erase(remove_if(line.begin(), line.end(), [](unsigned char x) { return std::isspace(x); }),
                           line.end());
                if (line[0] == '#' || line.empty()) continue;
                auto delimiterPos = line.find('=');
                auto name = line.substr(0, delimiterPos);
                auto value = line.substr(delimiterPos + 1);
                params.insert_or_assign(name, value);
            }
        } else {
            cerr << "Couldn't open config file for reading. \n";
        }
        if (params["output"] == "http") {
            HTTPWriter w(params["ip"], params["port"]);
            JSONReader r(params["filename"]);
            Controller c(w, r, params["redisip"], stoi(params["redisport"]));
            c.run();
        } else {
            ConsoleWriter w;
            JSONReader r("warcraft-3-quotes.json");
            Controller c(w, r, params["redisip"], stoi(params["redisport"]));
            c.run();
        }
    }
    catch(std::exception e){
        cerr << e.what();
    }
    return 0;
}
