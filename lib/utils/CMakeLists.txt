add_library(utils CliParser.cpp CliParser.h TsvReader.cpp TsvReader.h)

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
