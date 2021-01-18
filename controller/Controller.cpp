//
// Created by justnik on 02.12.2020.
//

#include <cstring>
#include <ctime>
#include <fstream>
#include <hiredis/hiredis.h>
#include <iostream>
#include <thread>

#include "Controller.h"

using namespace std;

[[maybe_unused]] Controller::Controller(IWriter &w, IReader &r, const std::string &url) : w(w), r(r), url(url) {}

void Controller::run() const {
    /*Setting for logfile */
    streambuf *psbuf, *backup;
    ofstream log;
    log.open("log.txt");
    backup = clog.rdbuf();
    psbuf = log.rdbuf();
    clog.rdbuf(psbuf);
    std::clog << "Start" << endl;
    /* Settings for Redis*/
    redisContext *c;
    redisReply *reply;
    struct timeval timeout = {1, 500000}; // 1.5 seconds
    c = redisConnectWithTimeout(url.c_str(), port, timeout);
    redisCommand(c, "SET cmd start");
    if (c == nullptr || c->err) {
        if (c) {
            cerr << "Connection error on " << url << ":" << port << ": " << c->errstr << endl;
            clog << "Connection error: " << c->errstr << endl;
            redisFree(c);
        } else {
            cerr << "Connection error: can't allocate redis context" << endl;
            clog << "Connection error: can't allocate redis context" << endl;
        }
        exit(1);
    }
    while (true) {
        reply = static_cast<redisReply *>(redisCommand(c, "GET cmd"));
        if (!strcmp(reply->str, "stop")) {
            freeReplyObject(reply);
            break;
        }
        if (!strcmp(reply->str, "getquote")) {
            string res = r.getQuote();
            res += '\n';
            thread([&, res](){w.write(res);}).detach();
            //w.write(res);
            redisCommand(c, "SET %s %s", "msg", res.c_str());
            redisCommand(c, "SET cmd ready");
        }
        freeReplyObject(reply);
        this_thread::sleep_for(chrono::microseconds (500));
    }
    redisFree(c);
    clog << "Finish" << endl;
    clog.rdbuf(backup);
    log.close();
}

Controller::Controller(IWriter &w, IReader &r, const string &url, uint32_t port) : w(w), r(r), url(url), port(port) {}

void config(map<std::string, std::string> &params) {

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
    if (!params.contains("filename")) {
        throw std::invalid_argument("No file to read.\n Write filename = yourfile in config file.\n");
    }
    if (params["output"] == "http") {
        if (!params.contains("ip")) {
            params["ip"] = "127.0.0.1";
        }
        if (!params.contains("port")) {
            params["port"] = "8080";
        }
    }
}
