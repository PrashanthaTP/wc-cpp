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

const string HELP_STR =
    "Usage: ccwc [OPTION] [FILE]\n"
    "\n"
    "Options:\n"
    "  -c     print the byte counts\n"
    "  -w     print the word counts\n"
    "  -l     print the newline counts\n"
    "\n"
    "More Information: https://github.com/PrashanthaTP/wc-cpp\n";

int main(int argc, char* argv[]) {
    if (string(argv[1]) == "-h" || string(argv[1]) == "--help") {
        cout << HELP_STR;
        exit(EXIT_SUCCESS);
    }
    if (argc < 3) {
        cerr << "Wrong number of arguments\n";
        cerr << "See help : ccwc.exe --help\n";
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
    } else if (string(argv[1]) == "-l") {
        try {
            uint32_t nLines = getLineCount(filePath);
            cout << nLines << " " << getBaseName(filePath) << "\n";
        } catch (const std::exception& e) {
            cerr << e.what();
            exit(EXIT_FAILURE);
        }
    } else if (string(argv[1]) == "-w") {
        try {
            uint32_t nWords = getWordCount(filePath);
            cout << nWords << " " << getBaseName(filePath) << "\n";
        } catch (const std::exception& e) {
            cerr << e.what();
            exit(EXIT_FAILURE);
        }
    } else {
        cerr << "Unknown argument: " << "'" << argv[1] << "'" << "\n";
        cerr << "See --help\n";
        exit(EXIT_FAILURE);
    }
}
