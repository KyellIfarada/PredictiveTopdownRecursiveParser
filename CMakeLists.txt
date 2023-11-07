cmake_minimum_required(VERSION 3.14)

project(TopDownRecursiveParser)

add_executable(TopDownRecursiveParser parser.cc )

add_Library(MyLibrary SHARED parser.h lexer.cc lexer.h inputbuf.cc inputbuf.h)

target_link_libraries(TopDownRecursiveParser PUBLIC MyLibrary)