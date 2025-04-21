add_library(Bmp Bmp.cpp Bmp.h)

target_include_directories(Bmp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Bmp PUBLIC UnorderedMap)