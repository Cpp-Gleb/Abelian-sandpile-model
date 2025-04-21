add_library(Sandpile Sandpile.cpp Sandpile.h
)

target_include_directories(Sandpile PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Sandpile PUBLIC UnorderedMap utils Bmp)