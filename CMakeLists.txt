cmake_minimum_required(VERSION 3.25)
project(TopDownRecursiveParser)

set(CMAKE_CXX_STANDARD 14)

add_executable(TopDownRecursiveParser-lexer.cc TopDownRecursiveParser-lexer.h  test1.sh tests/test_comments_01.txt tests/test_comments_02.txt tests/test_comments_03.txt tests/test_names_01.txt tests/test_names_02.txt tests/test_names_03.txt tests/test_parsing_error01.txt tests/test_parsing_error02.txt tests/test_parsing_error03.txt tests/test_parsing_ok01.txt tests/test_parsing_ok02.txt tests/test_parsing_ok03.txt inputbuf.cc inputbuf.h
        parser.cc
        symboltable.cpp
        symboltable.h
        parser.h)
