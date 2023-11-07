//
// Created by lorenzo on 10/29/23.
//

#ifndef TOPDOWNRECURSIVEPARSER_PARSER_H
#define TOPDOWNRECURSIVEPARSER_PARSER_H
#include "lexer.h"

class ParserFunctions
        {
                public:

                static  void parse_program();
                static  void parse_globalvars();
                static  void parse_varslist();
                static  void parse_scope();
                static  void parse_public_vars();
                static  void parse_private_vars();
                static  void parse_stmnt_list();
                static  void parse_stmnt();
        };

#endif //TOPDOWNRECURSIVEPARSER_PARSER_H

