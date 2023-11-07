#include "parser.h"
#include "algorithm"
//SymbolTABLE  CODE
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
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
*/

//First Sets
std::vector<std::string> First_EmptySet = {""};                                   // Global Var
std::vector<std::string> First_var_list_SEMICOLON = {"ID", ""};                   //Global var
std::vector<string> First_ID= {"ID"};                                               //Var_List
std::vector<string> First_ID_COMMA_var_list = {"ID"};                                  //VAR_LIST
std::vector<string> First_ID_LBRACE_public_vars_private_Vars_stmt_list_RBRACE = {"ID"}; //SCOPE
std::vector<string> First_PUBLIC_COLON_var_list_SEMICOLON  = { "","PUBLIC" };            //PUBLICVAR
std::vector<string> First_PRIVATE_COLON_var_list_SEMICOLON = { "","PRIVATE "};              //PRIVATEVAR
std::vector<string> First_stmt = { "ID" };                                             //stmt_list
std::vector<string> First_stmt_stmt_list = { "ID", ""};                                //stmt_lst
std::vector<string> First_stmt_ID_EQUAL_ID_SEMICOLON = { "ID" };                       //var_list SEMICOLON
std::vector<string> First_scope = { "ID" };                                                // scope

//Follow Sets
std::vector<string> Follow_Program = {"END_OF_FILE"};                                //Correct Terminal Symbol
std::vector<string> Follow_Global_vars = {"ID"};                                     //Correct Terminal Symbol
std::vector<string> Follow_var_list = {"SEMICOLON"};                                 //
std::vector<string> Follow_scope = {"END_OF_FILE"};
std::vector<string> Follow_public_vars = {"", "PRIVATE"};
std::vector<string> Follow_private_vars  = { "ID"};
std::vector<string> Follow_stmt_list= { "RBRACE" };
std::vector<string> Follow_stmt = { "RBRACE", "ID" };

/*
//Follow Sets // Rules where utilized for Follow Sets
FOLLOW_program(0 production rule)
FOLLOW_global_vrs(1 production rule)
FOLLOW_var_list(4 production rule)
FOLLOW_scope(2 production rule)
FOLLOW_public_vars(1 production rule)
FOLLOW_private_vars(1 production rule)
FOLLOW_stmt_list(2 production rule)
FOLLOW_stmt(2 production rule)
*/

std::vector<int>  numlist = {0,1,2,3,4,5,6,7,8,9} ;
std::vector<char> alphalist = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','X','Y','Z'};

// Enum to represent the access specifier
enum class SpecifiedPrivacy
        {
    GLOBAL,
    PUBLIC,
    PRIVATE,
    VARLIST
};

class SymbolTable
        {
public:
    SymbolTable()
    {
        enterScope(SpecifiedPrivacy::GLOBAL);

    }

    // Enter a new scope
    void enterScope(SpecifiedPrivacy access)
    {
        sym_tables.push_back({});
        access_SpecifiedPrivacy.push_back(access);
    }

    // Exit the CurrentScope
    void exitScope()
    {
        if (sym_tables.size() > 1)
        {
            sym_tables.pop_back();
            access_SpecifiedPrivacy.pop_back();
        }
        else {
            std::cerr << "Cannot exit the scope." << std::endl;
        }
    }

    // Add a variable to the current scope
    void addVar(const std::string& name, const std::string& type)
    {
        auto& currentScope = sym_tables.back();
        if (currentScope.find(name) == currentScope.end())
        {
            currentScope[name] = type;
        }
        else
        {
            std::cerr << "Variable '" << name << "' in the current scope." << std::endl;
        }
    }

    // Look up a variable
    std::string lookforVar(const std::string& name)
    {
        for (int i = sym_tables.size() - 1; i >= 0; --i)
        {
            if (sym_tables[i].find(name) != sym_tables[i].end())
            {
                return sym_tables[i][name];
            }
            // Stop searching when a private  specifier occurs
            if (access_SpecifiedPrivacy[i] == SpecifiedPrivacy::PRIVATE)
            {
                break;
            }
        }
        std::cerr << "Variable '" << name << "' is not declared." << std::endl;
        return "undefined";
    }

private:
    std::vector<std::unordered_map<std::string, std::string>> sym_tables;
    std::vector<SpecifiedPrivacy> access_SpecifiedPrivacy;
};


/*
Algorithm Brainstorm:

Compare Lexeme token( this will change every getToken call)
Flag for Certain Tokens to change syntax of lexeme
When Var_list exists
*/

//Create Symbol Table here

//Default Global Scope


//Grammar Check Data Structures
std::vector<string>  program_check = {"global_vars","scope"};
std::vector<string>  global_vars_check = {""};
std::vector<string>  global_vars1_check= {"var_list","SEMICOLON"};
std::vector<string>  var_list_check = {"ID", "scope"};
std::vector<string>  var_list1_check = {"ID", "COMMA", "var_list"};
std::vector<string>  scope_check = {"ID", "LBRACE", "public_vars" ,"private_vars", "stmt_list" ,"RBRACE"};
std::vector<string>  public_vars_check = {""};
std::vector<string>  pubic_vars1_check= {"PUBLIC", "COLON" ,"var_list" ,"SEMICOLON"};
std::vector<string>  private_vars_check = {"PRIVATE" ,"COLON", "var_list", "SEMICOLON"};
std::vector<string>  stmt_list_check = {"stmt"};
std::vector<string>  stmt_list1_check = {"stmt", "stmt_list"};
std::vector<string>  stmt_check = {"var_list", "SEMICOLON"};
std::vector<string>  stmt1_check = {"scope"};

// Store your parser grammar here once complete to dive into the next.
std::vector<string>  program ;
std::vector<string>  global_vars ;
std::vector<string>  global_vars1;
std::vector<string>  var_list ;
std::vector<string>  var_list1 ;
std::vector<string>  scope;
std::vector<string>  public_vars;
std::vector<string>  public_vars1;
std::vector<string>  private_vars ;
std::vector<string>  stmt_list;
std::vector<string>  stmt_list1;
std::vector<string>  stmt;
std::vector<string>  stmt1 ;

//Hold for characters during calls to add them into
std::vector<string> global_vars_syntax = {""};
std::vector<string> public_vars_syntax = {""};
std::vector<string> private_vars_syntax = {""};
std::vector<string> vars_syntax ={""};
std::vector<string> scope_name = {""};


string terms[] = { "END_OF_FILE" ,"PUBLIC","PRIVATE","EQUAL","COLON","COMMA","SEMICOLON","LBRACE","RBRACE","ID", "ERROR"
};

LexicalAnalyzer lexer;
Token token;
Token token1;

//Define Syntax Error
void syntax_error()
{
    cout << "Syntax Error\n";
    exit(1);
}

//Grammar for Program

//Define Parse_Program Grammar parse

void ParserFunctions::parse_program()
{
    token = lexer.GetToken();
    if(std::find (First_var_list_SEMICOLON.begin(), First_var_list_SEMICOLON.end(), terms[token.token_type]) != First_var_list_SEMICOLON.end())
    {
        lexer.UngetToken(token);                            //Split into next Non-terminals
        parse_globalvars();
        parse_scope();

        //Debugger to confirm all tokens have been parsed through
        program.emplace_back("global_vars");
        program.emplace_back("scope");                     //Acts as a Check for the Grammar
        if(program == program_check)
        {
            printf("sucessfully parsed");
        }

    }
    else if(std::find (Follow_Program.begin(), Follow_Program.end(), terms[token.token_type]) != Follow_Program.end())
    {
        lexer.UngetToken(token);                            //End of File
    }
    else
        syntax_error();
};

//Define global_vars Grammar parse

void ParserFunctions::parse_globalvars()
{
   token = lexer.GetToken();                                      //Get Token
    if ((std::find (First_var_list_SEMICOLON.begin(), First_var_list_SEMICOLON.end(), terms[token.token_type])  != First_var_list_SEMICOLON.end()) || (std::find (First_EmptySet.begin(), First_EmptySet.end(), terms[token.token_type])  != First_EmptySet.end()))
    {

        lexer.UngetToken(token);                                         //Unget
        global_vars1.emplace_back("var_list");                          //Qualifies for Var_List
        ParserFunctions::parse_varslist();                              //Parse into Non-Terminal
        global_vars_syntax ;                                 //TODO                      //once var_list done add it to global vars
        token = lexer.GetToken();                                      //Once Done parsing var_list get semicolon
        if(token.token_type == SEMICOLON)
        {
            global_vars1.emplace_back("SEMICOLON");
        }
        else
            syntax_error();

        //Debugger to confirm all tokens have been parsed through
        if(global_vars1 == global_vars1_check)
        {
                printf("sucessfully parsed");
        }

    }
    else if (std::find (Follow_Global_vars.begin(), Follow_Global_vars.end(), terms[token.token_type]) != Follow_Global_vars.end() )
    {
        lexer.UngetToken(token);
        printf("global_vars complete");
    }
    else
         syntax_error();
};

//Define vars_list Grammar parse

void ParserFunctions::parse_varslist()
{
    token = lexer.GetToken();                                             //Get Token
    if((std::find (First_ID.begin(), First_ID.end(), terms[token.token_type]) != First_ID.end() ) || (std::find (First_ID_COMMA_var_list.begin(), First_ID_COMMA_var_list.end(), terms[token.token_type]) != First_ID_COMMA_var_list.end()))
    {
        var_list.emplace_back("ID");                           // Place ID in the tracker
        var_list1.emplace_back("ID");                          // Place ID in the tracker
        vars_syntax.emplace_back(token.lexeme);                // Adding ID token string to list
        token = lexer.GetToken();                              // Get next token
        if (token.token_type == COMMA)
        {
            var_list1.emplace_back("COMMA");                   // Add Comma to tracker
            vars_syntax.emplace_back(token.lexeme);            // Add a Comma after each variable? Maybe in the printout?
            parse_varslist();                                  // Call VarList Again
        }
        else if(token.token_type == ID)
        {
            var_list.emplace_back("scope");                    // Place Scope in Tracker
            lexer.UngetToken(token);                           // UnGetToken
            parse_scope();                                     // Go to scope parsing
        }
        else
            syntax_error();
    }
    else if(std::find (Follow_var_list.begin(), Follow_var_list.end(), terms[token.token_type]) != Follow_var_list.end() )
    {
        lexer.UngetToken(token);
    }
    else
        syntax_error();
};

//Define scope Grammar parse

void ParserFunctions::parse_scope()
{
    token = lexer.GetToken();                                          //Get Token
    if(std::find (First_ID_LBRACE_public_vars_private_Vars_stmt_list_RBRACE.begin(), First_ID_LBRACE_public_vars_private_Vars_stmt_list_RBRACE.end(), terms[token.token_type]) != First_ID_LBRACE_public_vars_private_Vars_stmt_list_RBRACE.end())
    {
            scope.emplace_back("ID");                //Adding ID to checker
            scope_name.emplace_back(token.lexeme);   //Adding Scope name to the Vector
            token = lexer.GetToken();
            if( token.token_type == LBRACE)
            {
                scope.emplace_back("LBRACE");   //ADD LBRACE TO CHECKER
                token = lexer.GetToken();
                if(token.token_type == PUBLIC)
                {
                    scope.emplace_back("PUBLIC");
                    lexer.UngetToken(token);
                    parse_public_vars();                        // go to public pars
                }
                else if(token.token_type == PRIVATE)
                {
                    scope.emplace_back("PRIVATE");

                    lexer.UngetToken(token);
                    parse_private_vars();                       //Go to private pars
                }
                else if(token.token_type == ID)
                {
                    token = lexer.GetToken();                   // Check Additional Token to see
                    if(token.token_type == ID)
                    {
                        lexer.UngetToken(token);                // if an additional ID
                                                                // Call var_list
                        parse_varslist();
                    }
                    else
                        syntax_error();
                }
                else
                    syntax_error();
            }
            else
                syntax_error();
    }
    else if (std::find (Follow_scope.begin(), Follow_scope.end(), terms[token.token_type]) != Follow_scope.end())
    {
        lexer.UngetToken(token);
        printf("parsed_scope");
    }
    else
        syntax_error();
};

//Define public_vars Grammar parse

void ParserFunctions::parse_public_vars()
{
  token = lexer.GetToken();                                                  //Get Token
    if(std::find (First_PUBLIC_COLON_var_list_SEMICOLON.begin(), First_PUBLIC_COLON_var_list_SEMICOLON.end(), terms[token.token_type]) != First_PUBLIC_COLON_var_list_SEMICOLON.end())
    {
        parse_public_vars();
        printf("parse_public_vars");
    }
    else if (std::find (Follow_public_vars.begin(), Follow_public_vars.end(), terms[token.token_type]) != Follow_public_vars.end()  )
    {
        lexer.UngetToken(token);
    }
    else
        syntax_error();
};

//Define parse_vars Grammar parse

void ParserFunctions::parse_private_vars()
{
    token = lexer.GetToken();                                                          //Get Token
    if(std::find (First_PRIVATE_COLON_var_list_SEMICOLON.begin(), First_PRIVATE_COLON_var_list_SEMICOLON.end(), terms[token.token_type]) != First_PRIVATE_COLON_var_list_SEMICOLON.end())
    {

        parse_private_vars();
        printf("parse_private_vars");
    }
    else if (std::find (Follow_private_vars.begin(), Follow_private_vars.end(), terms[token.token_type]) != Follow_private_vars.end()  )
    {
        lexer.UngetToken(token);
    }
    else
        syntax_error();
};

//Define parse_stmt_list Grammar parse

void ParserFunctions::parse_stmnt_list()
{
    token = lexer.GetToken();                                //Get Token
    if(std::find (First_stmt_stmt_list.begin(), First_stmt_stmt_list.end(), terms[token.token_type]) != First_stmt_stmt_list.end())
    {
        lexer.UngetToken(token);                    // UnGetToken to get to the next function
        parse_stmnt();                              // Call stmt funtion
        parse_stmnt_list();                         //recursively call function.
    }
    else if (std::find (Follow_stmt_list.begin(), Follow_stmt_list.end(), terms[token.token_type]) != Follow_stmt_list.end()  )
    {
        lexer.UngetToken(token);
    }
    else
        syntax_error();
};

//Define parse_stmnt Grammar parse

void ParserFunctions::parse_stmnt()
{
    token = lexer.GetToken();                              //Get Token
    if(std::find (First_stmt_ID_EQUAL_ID_SEMICOLON.begin(), First_stmt_ID_EQUAL_ID_SEMICOLON.end(), terms[token.token_type]) != First_stmt_ID_EQUAL_ID_SEMICOLON.end())
    {
        token1 = lexer.GetToken();                          //var_list SEMICOLON
        if (token1.token_type == ID)
        {
            lexer.UngetToken(token1);                       //unget ID
            lexer.UngetToken(token);                        //unget ID
            parse_varslist();                               // get var list
        }
        else if (token1.token_type == LBRACE)
        {

                lexer.UngetToken(token1);
                lexer.UngetToken(token);
                parse_scope();                               // get var list

        }
        else
            syntax_error();
    }
    else if (std::find (Follow_stmt.begin(), Follow_stmt.end(), terms[token.token_type]) != Follow_stmt.end()  )
    {
        lexer.UngetToken(token);
    }
    else
        syntax_error();
};

int main()
{
    SymbolTable symbolTable;
    while (token.token_type != END_OF_FILE)
    {





    }
    ParserFunctions::parse_program();

    /*
    SAMPLE SYMBOLTABLE CODE!

    symbolTable.enterScope(SpecifiedPrivacy::Global);
    symbolTable.addVar(lexer.tmp.lexeme, "globalVar");


    symbolTable.enterScope(SpecifiedPrivacy::Public);
    symbolTable.addVar("pubVar", "float");

    lexer.tmp.lexeme = symbolTable.enterScope(SpecifiedPrivacy::Private);
    symbolTable.addVar("pVar", "char");

    std::cout << "Variable 'pubVar' type: " << symbolTable.lookforVar("pubVar") << std::endl;
    std::cout << "Variable 'pVar' type: " << symbolTable.lookforVar("pVar") << std::endl;

    symbolTable.exitScope();
    symbolTable.exitScope();
    symbolTable.addVar("GVar", "private");

    std::cout << "Variable 'globalVar' type: " << symbolTable.lookforVar("globalVar") << std::endl;
    std::cout << "Variable 'GVar' type: " << symbolTable.lookforVar("GVar") << std::endl;
     */

}
