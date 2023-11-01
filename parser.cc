#include "TopDownRecursiveParser-lexer.h"
#include "TopDownRecursiveParser-lexer.cc"
#include "parser.h"

//Grammar

// program -> global_vars scope
// global_vars -> ε
// global_vars -> var_list SEMICOLON
// var_list -> ID scope
// var_list -> ID COMMA var_list
// scope -> ID LBRACE public_vars private_vars stmt_list RBRACE
// public_vars -> ε
// public_vars -> PUBLIC COLON var_list SEMICOLON
// private_vars -> PRIVATE COLON var_list SEMICOLON
// stmt_list -> stmt
// stmt_list -> stmt stmt_list
// stmt -> var_list SEMICOLON
// stmt -> scope

/* Terminal :
 *
 *  ε, SEMICOLON, ID, LBRACE, RBRACE, PUBLIC, COLON, SEMICOLON,
 *
 * Non-Terminals :
 *
 * program, global_vars, var_list,scope,public_vars, stmt_list, stmt
 *
 * First List
 * (
 *
 *
 *
 * )
 * Follow List
 * (
 *
 *
 *
 *
 * )
 */
/*
//Grammar for Program
void ParserFunctions::parse_program()
{
    parse_globalvars();
    parse_scope();
};

void ParserFunctions::parse_globalvars()
{
    /*if ( lexer.GetToken() == END_OF_FILE)

    else if (var_list )

    else
    {
        void syntax_error();

    }

};



void ParserFunctions::parse_varslist()
{

};



void ParserFunctions::parse_scope()
{

};

void ParserFunctions::parse_publicvars()
{

};



void ParserFunctions::parse_privatevars()
{

};



void ParserFunctions::parse_stmnt_list()
{

};



void ParserFunctions::parse_stmnt()
{

};

void syntax_error()
{
    cout << "Syntax Error\n";
    exit(1);
}


*/



/*int main()
{






}
 */