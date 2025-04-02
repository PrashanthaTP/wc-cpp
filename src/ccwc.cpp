#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using std::cerr;
using std::cout;
using std::string;
using std::vector;

string getBaseName(const string& filePath){
    //https://stackoverflow.com/questions/8520560/get-a-file-name-from-a-path
    return filePath.substr(filePath.find_last_of("/\\")+1);
}
string getFileData(const string& filePath){
    FILE* file = fopen(filePath.c_str(), "r");
    if(file==NULL){
        throw std::runtime_error("File could not be opened: " + filePath);
    }
    //https://stackoverflow.com/questions/33588254/are-element-size-and-count-exchangable-in-an-fread-call
    fseek(file, 0, SEEK_END);
    unsigned int fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    vector<char> buffer(fileSize);
    int readChars = fread(buffer.data(), sizeof(char), buffer.size(), file);
    if(readChars==0){
        //https://en.cppreference.com/w/c/io/fread
    }
    fclose(file);
    cout << fileSize << " " << getBaseName(filePath) <<"\n";
    return "";
}
void process(const string& filepath) {
    getFileData(filepath);
}

int main(int argc, char* argv[]) {

    if (argc < 3) {
        cerr << "Wrong number of arguments\n";
        cerr << "See help : ./ccwc.exe --help\n";
        exit(EXIT_FAILURE);
    }

    if (string(argv[1]) == "-c") {
        process(argv[2]);
    }else{
        cerr << "Unknown argument: " << "'" << argv[1] << "'" << "\n";
        exit(EXIT_FAILURE);
    }
}
