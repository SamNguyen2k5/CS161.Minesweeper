#include "context.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

ContextReader::ContextReader() {}

ContextReader::ContextReader(const std::string& filename) {
    load_file(filename);
}

void ContextReader::report_error() {
    std::cerr << "Error reading file.";
    exit(-1);
}

void ContextReader::load_file(const std::string& filename) {
    std::ifstream ifs(filename);
    std::stringstream ss;

    std::cerr << "file = " << filename << std::endl;

    while (not ifs.eof()) {
        std::string line = "";
        while (line.empty()) {
            std::getline(ifs, line, '\n');
            std::cerr << "line = [" << line << "]" << std::endl;
        }

        ss.clear();
        ss.str(line);

        std::string token, var;

        // Variable not declared
        if (not (ss >> var))
            report_error();

        // Comment
        if (var == "#")
            continue;

        // No equal sign found
        if (not (ss >> token))
            report_error();

        if (token != "=")
            report_error();

        while (true) {
//            std::cerr << "peek = " << std::string(1, ss.peek()) << std::endl;

            // HEX Code
            if (ss.peek() == '#') {
                ss.get();
                std::string code;
                ss >> code;
                if (code.size() == 6u)
                    code = code + "FF";

                mp_hex[var] = stoul(code, nullptr, 16);
                std::cerr << var << " := " << get_hex(var) << std::endl;
                break;
            }

            // String
            if (ss.peek() == '"') {
                ss.get();
                std::getline(ss, mp_str[var], '"');
                std::cerr << var << " := " << get_str(var) << std::endl;
                break;
            }

            // Decimal number
            if (ss.peek() >= '0' and ss.peek() <= '9') {
                ss >> mp_int[var];
                std::cerr << var << " := " << get_int(var) << std::endl;
                break;
            }

            ss.get();
        }
    }
    ifs.close();
}

void ContextReader::load_file(const char* filename) {
    load_file(std::string(filename));
}

int ContextReader::get_int(const std::string& token) { return mp_int[token]; }
unsigned int ContextReader::get_hex(const std::string& token) { return mp_hex[token]; }
std::string ContextReader::get_str(const std::string& token) { return mp_str[token]; }

int ContextReader::get_int(const char* token) { return mp_int[std::string(token)]; }
unsigned int ContextReader::get_hex(const char* token) { return mp_hex[std::string(token)]; }
std::string ContextReader::get_str(const char* token) { return mp_str[std::string(token)]; }

