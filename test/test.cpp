#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <regex>
#include <string>

#include <gtest/gtest.h>

#include "ccwc.hpp"

const std::filesystem::path BASH_EXE = "C:\\Program Files\\Git\\bin\\bash.exe";
const std::filesystem::path WC_EXE = "C:\\Program Files\\Git\\usr\\bin\\wc.exe";
const std::filesystem::path TEMP_DIR = std::filesystem::temp_directory_path();
const std::filesystem::path TEMP_FILENAME = "temp-ccwc.txt";

std::string getCmdStr(std::string cmd) {
    return "\"" + BASH_EXE.string() + "\"" + " -c " + "'" + cmd + "'";
}

std::string redirectCmdToFile(std::string cmd, std::string outFile) {
    return cmd + " 1>" + outFile + " 2>&1";
}

void executeCmd() {
    //https://stackoverflow.com/questions/875249/how-to-get-current-directory
    // std::filesystem::path cwd = std::filesystem::current_path();
    // cwd = std::regex_replace(cwd.string(), std::regex("\\\\"), "/");
    std::filesystem::path srcFilePath{__FILE__};
    std::filesystem::path cwd = srcFilePath.parent_path();
    std::filesystem::path inputFilePath{cwd / "inputs/test1.txt"};
    std::filesystem::path tempFile = TEMP_DIR / TEMP_FILENAME;
    // std::string cmdStr =  BASH_EXE.string() + "-c 'wc -c \"" +
    //                      cwd + "/../../test/inputs/test1.txt\"' 1> " +
    //                      tempFile + " 2>&1";
    // std::string cmdStr =
    //     getCmdStr(std::string("wc -c ") + "\"" + inputFilePath.string() + "\"");
    std::string cmdStr =
        "\"" + WC_EXE.string() + "\"" + " -c " + inputFilePath.string();
    cmdStr = redirectCmdToFile(cmdStr, tempFile.string());
    std::system(cmdStr.c_str());
}

const std::filesystem::path srcFilePath{__FILE__};
const std::filesystem::path cwd{srcFilePath.parent_path()};
const std::filesystem::path inputFilePath_1{cwd / "inputs/test1.txt"};
const std::filesystem::path inputFilePath_1_notexist{cwd / "inputs/test11.txt"};
const std::filesystem::path inputFilePath_1_unicode{cwd / "inputs/test1_unicode.txt"};
const std::filesystem::path inputFilePath_2{cwd / "inputs/test2.txt"};

TEST(CCWCTest, GetBytesHandleAsciiInput) {
    EXPECT_NO_THROW({
        uint32_t res = getByteCount(inputFilePath_1.string());
        EXPECT_EQ(res, 453);
    });

    EXPECT_NO_THROW({
        uint32_t res = getByteCount(inputFilePath_2.string());
        EXPECT_EQ(res, 990);
    });
}

TEST(CCWCTest, GetBytesHandleUnicodeInput){
    EXPECT_NO_THROW({
        uint32_t res = getByteCount(inputFilePath_1_unicode.string());
        EXPECT_EQ(res, 462);
    });
}

//https://stackoverflow.com/questions/23270078/test-a-specific-exception-type-is-thrown-and-the-exception-has-the-right-propert
TEST(CCWCTest, GetBytesThrowFileException) {
    const std::string errStr =
        "Error opening file: " + inputFilePath_1_notexist.string() + "\n";
    EXPECT_THROW(
        {
            try {
                (void)getByteCount(inputFilePath_1_notexist.string());
            } catch (const std::exception& e) {
                EXPECT_STREQ(errStr.c_str(), e.what());
                throw;
            }
        },
        std::runtime_error);
}
