%language "C++"
%require "3.2"

%code requires {
    #include <string>
    #include "spl.hpp"
    class Lexer;
}

%{
    #include "Lexer.hpp"
    #define yylex(v) lexer.getNextToken(v)

    void spl::Parser::error(const std::string& msg) {
        std::cerr << "Error de sintaxis: " << msg << std::endl;
    }
%}

%parse-param {Lexer &lexer}
%parse-param{AstNode* &astN}
%define api.namespace {spl}
%define api.parser.class {Parser}
%define api.value.type {AstNode*}

%token VARIABLE 
%token NUMBER
%token KEYWORD_IF KEYWORD_ELSE KEYWORD_PRINT
%token OP_REL_GREATER_EQUAL OP_REL_LESS_EQUAL OP_REL_EQUALS OP_REL_DIFF

%nonassoc LOWER_THAN_ELSE
%nonassoc KEYWORD_ELSE

%%

program: listStmts {astN = new Program($1);}
;

listStmts: listStmts statement {$$ = $1; reinterpret_cast<StatementList*>($$)-> stmts.push_back($2); }
        |  %empty {$$ = new StatementList({});}
;

statement: printStmt ';' {$$ =$1;}
        | assignStmt ';' {$$ =$1;}
        | ifStmt {$$ =$1;}
;

assignStmt: VARIABLE '=' NUMBER {$$ = new AssignmentStmt($1,$3);}
        | VARIABLE '=' VARIABLE {$$ = new AssignmentStmt($1,$3);}
;

ifStmt: KEYWORD_IF '(' condExpr ')' statement %prec LOWER_THAN_ELSE {$$ = new  IfStmt($3, $5, nullptr ); }
    | KEYWORD_IF '(' condExpr ')' statement KEYWORD_ELSE statement {$$ = new  IfStmt($3, $5, $7 ); }
;

printStmt: KEYWORD_PRINT '(' VARIABLE ')' { $$ = new PrintStmt($3);}
;

condExpr: VARIABLE '<' VARIABLE {$$ = new RelationalExpression($1,RelationalOperator::LESS,$3);}
        |VARIABLE OP_REL_EQUALS VARIABLE {$$ = new RelationalExpression($1,RelationalOperator::EQUAL,$3);}//relacional
        |VARIABLE OP_REL_LESS_EQUAL VARIABLE {$$ = new RelationalExpression($1,RelationalOperator::LESS_EQUAL,$3);}//relacional
        |VARIABLE OP_REL_GREATER_EQUAL VARIABLE {$$ = new RelationalExpression($1,RelationalOperator::GREATER_EQUAL,$3);}//relacional
        |VARIABLE '>' VARIABLE {$$ = new RelationalExpression($1,RelationalOperator::GREATER,$3);}//relacional
        |VARIABLE OP_REL_DIFF VARIABLE {$$ = new RelationalExpression($1,RelationalOperator::NOT_EQUAL,$3);}//relacional
        |VARIABLE {$$ = $1;}// Este new lo va a manejar el lexer;
        |NUMBER {$$ = $1;}// Este new lo va a manejar el lexer, el lexer tiene que retornar el nodo;
;