cmake_minimum_required(VERSION 3.25)
project(TopDownRecursiveParser)

set(CMAKE_CXX_STANDARD 14)

add_executable( TopDownRecursiveParser-lexer.h TopDownRecursiveParser-lexer.cc  inputbuf.cc inputbuf.h )

