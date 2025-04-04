#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

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
const std::filesystem::path inputFilePath_1_unicode{cwd /
                                                    "inputs/test1_unicode.txt"};
const std::filesystem::path inputFilePath_2{cwd / "inputs/test2.txt"};

// template <typename T>
// struct TestConfig {
//     T (*func)(const std::string&);
//     std::string inputFilePath;
//     T expectedResult;
// };

// struct TestConfig<uint32_t> testConfigAsciiInput[] = {
//     {&getByteCount, inputFilePath_1.string(), 453}, {
//         &getByteCount, inputFilePath_2.string(), 990
//     }
// };

//TODO :  Check about Value Parameterized Tests in GoogleTest
struct TestInputParamConfig {
    std::string filePath;
    uint32_t byteCount;
    uint32_t wordCount;
    uint32_t lineCount;
};

struct TestInputConfig {
    std::vector<struct TestInputParamConfig> asciiInput;
    std::vector<struct TestInputParamConfig> unicodeInput;
    std::vector<struct TestInputParamConfig> nonExistentInput;
};

/*
$ wc test/inputs/*
   5   69  453 test/inputs/test1.txt
   6   70  462 test/inputs/test1_unicode.txt
  14  166  990 test/inputs/test2.txt
  25  305 1905 total
  */
static const struct TestInputConfig gTestInputConfig = {
    .asciiInput = {{.filePath = inputFilePath_1.string(),
                    .byteCount = 453,
                    .wordCount = 69,
                    .lineCount = 5},
                   {
                       .filePath = inputFilePath_2.string(),
                       .byteCount = 990,
                       .wordCount = 166,
                       .lineCount = 14,
                   }},
    .unicodeInput = {{
        .filePath = inputFilePath_1_unicode.string(),
        .byteCount = 462,
        .wordCount = 70,
        .lineCount = 6,
    }},
    .nonExistentInput = {{.filePath = inputFilePath_1_notexist.string()}}};

namespace TestUtil {
template <typename T, typename S>
void expect_no_throw(T (*func)(const S& input), const S& input, T expectedRes) {
    EXPECT_NO_THROW({
        uint32_t res = func(input);
        EXPECT_EQ(res, expectedRes);
    });
}
//https://stackoverflow.com/questions/23270078/test-a-specific-exception-type-is-thrown-and-the-exception-has-the-right-propert
template <typename T, typename S, typename E>
void expect_throw(T (*func)(const S& input), const S& input,
                  const std::string& errStr) {
    EXPECT_THROW(
        {
            try {
                (void)func(input);
            } catch (const std::exception& e) {
                EXPECT_STREQ(errStr.c_str(), e.what());
                throw;
            }
        },
        E);
}
}  // namespace TestUtil

TEST(CCWCTest, GetBytesHandleAsciiInput) {
    for (auto input : gTestInputConfig.asciiInput) {
        TestUtil::expect_no_throw<uint32_t, const std::string&>(
            &getByteCount, input.filePath, input.byteCount);
    }
}

TEST(CCWCTest, GetBytesHandleUnicodeInput) {
    for (auto input : gTestInputConfig.unicodeInput) {
        TestUtil::expect_no_throw<uint32_t, const std::string&>(
            &getByteCount, input.filePath, input.byteCount);
    }
}

//https://stackoverflow.com/questions/23270078/test-a-specific-exception-type-is-thrown-and-the-exception-has-the-right-propert
TEST(CCWCTest, GetBytesThrowFileException) {
    const std::string errStr =
        "Error opening file: " + inputFilePath_1_notexist.string() + "\n";
    for (auto input : gTestInputConfig.nonExistentInput) {
        TestUtil::expect_throw<uint32_t, const std::string&,
                               std::runtime_error>(&getByteCount,
                                                   input.filePath, errStr);
    }
}

TEST(CCWCTest, GetLineCountHandleAsciiInput) {
    for (auto input : gTestInputConfig.asciiInput) {
        TestUtil::expect_no_throw<uint32_t, const std::string&>(
            &getLineCount, input.filePath, input.lineCount);
    }
}

TEST(CCWCTest, GetLineCountHandleUnicodeInput) {
    for (auto input : gTestInputConfig.unicodeInput) {
        TestUtil::expect_no_throw<uint32_t, const std::string&>(
            &getLineCount, input.filePath, input.lineCount);
    }
}

TEST(CCWCTest, GetLineCountThrowFileException) {
    const std::string errStr =
        "Error opening file: " + inputFilePath_1_notexist.string() + "\n";
    for (auto input : gTestInputConfig.nonExistentInput) {
        TestUtil::expect_throw<uint32_t, const std::string&,
                               std::runtime_error>(&getLineCount,
                                                   input.filePath, errStr);
    }
}

TEST(CCWCTest, GetWordCountHandleAsciiInput) {
    for (auto input : gTestInputConfig.asciiInput) {
        TestUtil::expect_no_throw<uint32_t, const std::string&>(
            &getWordCount, input.filePath, input.wordCount);
    }
}

TEST(CCWCTest, GetWordCountHandleUnicodeInput) {
    for (auto input : gTestInputConfig.unicodeInput) {
        TestUtil::expect_no_throw<uint32_t, const std::string&>(
            &getWordCount, input.filePath, input.wordCount);
    }
}

TEST(CCWCTest, GetWordCountThrowFileException) {
    const std::string errStr =
        "Error opening file: " + inputFilePath_1_notexist.string() + "\n";
    for (auto input : gTestInputConfig.nonExistentInput) {
        TestUtil::expect_throw<uint32_t, const std::string&,
                               std::runtime_error>(&getWordCount,
                                                   input.filePath, errStr);
    }
}
