#include <iostream>
#include <string>

#include "ccwc.hpp"

using std::cerr;
using std::cout;
using std::string;

string getBaseName(const string& filePath) {
    //https://stackoverflow.com/questions/8520560/get-a-file-name-from-a-path
    return filePath.substr(filePath.find_last_of("/\\") + 1);
}

int main(int argc, char* argv[]) {

    if (argc < 3) {
        cerr << "Wrong number of arguments\n";
        cerr << "See help : ./ccwc.exe --help\n";
        exit(EXIT_FAILURE);
    }
    std::string filePath{argv[2]};
    if (string(argv[1]) == "-c") {
        try {
            uint32_t nBytes = getByteCount(filePath);
            cout << nBytes << " " << getBaseName(filePath) << "\n";
        } catch (const std::exception& e) {
            cerr << e.what();
            exit(EXIT_FAILURE);
        }
    } else {
        cerr << "Unknown argument: " << "'" << argv[1] << "'" << "\n";
        exit(EXIT_FAILURE);
    }
}
