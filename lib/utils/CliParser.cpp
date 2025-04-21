#include "CliParser.h"

CliParser::CliParser(int argc, char* argv[]) {
    Parse(argc, argv);
}

void CliParser::Parse(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "-i") == 0 || std::strcmp(argv[i], "--input") == 0) {
            if (i + 1 < argc) {
                input_file_ = argv[++i];
            } else {
                std::cerr << "Error: Missing input file argument after " << argv[i] << '\n';
            }
        } else if (std::strcmp(argv[i], "-o") == 0 || std::strcmp(argv[i], "--output") == 0) {
            if (i + 1 < argc) {
                output_dir_ = argv[++i];
            } else {
                std::cerr << "Error: Missing output directory argument after " << argv[i] << '\n';
            }
        } else if (std::strcmp(argv[i], "-m") == 0 || std::strcmp(argv[i], "--max-iter") == 0) {
            if (i + 1 < argc) {
                max_iterations_ = std::stoi(argv[++i]);
            } else {
                std::cerr << "Error: Missing max iterations argument after " << argv[i] << '\n';
            }
        } else if (std::strcmp(argv[i], "-f") == 0 || std::strcmp(argv[i], "--freq") == 0) {
            if (i + 1 < argc) {
                frequency_ = std::stoi(argv[++i]);
            } else {
                std::cerr << "Error: Missing frequency argument after " << argv[i] << '\n';
            }
        } else {
            std::cerr << "Warning: Unknown argument " << argv[i] << '\n';
        }
    }
}

std::string CliParser::GetInputFile() const {
    return input_file_;
}

std::string CliParser::GetOutputDir() const {
    return output_dir_;
}

int64_t CliParser::GetMaxIterations() const {
    return max_iterations_;
}

int64_t CliParser::GetFrequency() const {
    return frequency_;
}
