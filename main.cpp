#include <iostream>
#include <string>
#include "controller/Controller.h"
#include "writer/ConsoleWriter.h"
#include "writer/HTTPWriter.h"
#include "reader/JSONReader.h"

using namespace std;

int main() {
    HTTPWriter h("127.0.0.1", "8080");
    JSONReader r("warcraft-3-quotes.json");
    ConsoleWriter w;
    Controller c(w, r, "127.0.0.1");
    c.run();
    return 0;
}
