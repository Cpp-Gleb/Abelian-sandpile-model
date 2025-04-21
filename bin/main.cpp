#include "CliParser.h"
#include "TsvReader.h"
#include "Sandpile.h"
#include "Bmp.h"

int main(int argc, char* argv[]) {
    CliParser parser(argc, argv);

    TsvReader reader(parser.GetInputFile());
    std::string writer(parser.GetOutputDir());
    int64_t max_iteration(parser.GetMaxIterations());
    int64_t frequenc(parser.GetFrequency());

    Sandpile sandpile(reader, max_iteration, writer, frequenc);

    return 0;
}
