#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#include <string>
#include <cstring>
#include <iostream>
#include <cstdint>

class CliParser {
public:
    CliParser(int argc, char* argv[]);

    std::string GetInputFile() const;
    std::string GetOutputDir() const;
    int64_t GetMaxIterations() const;
    int64_t GetFrequency() const;

private:
    std::string input_file_;
    std::string output_dir_;
    int64_t max_iterations_ = 0;
    int64_t frequency_ = 0;

    void Parse(int argc, char* argv[]);
};

#endif
