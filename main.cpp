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
        config(params);
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
    catch (std::runtime_error &e) {
        cerr << e.what();
    }
    catch (std::out_of_range &e) {
        cerr << e.what();
    }
    catch (...) {
        cerr << "smth goes wrong\n";
    }
    return 0;
}
