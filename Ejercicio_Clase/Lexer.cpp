#include "Lexer.hpp"

void Lexer::storeValue(){
    lexema += convertToChar();
    ch = input.get();
}

void Lexer::throwError(){
    std::runtime_error("Se devolvio un error en el caracter "+convertToChar());
}

int Lexer::checkReserve(){
    if(lexema == "if"){
        return spl::Parser::token::KEYWORD_IF;
    }else if(lexema == "else"){
        return spl::Parser::token::KEYWORD_ELSE;
    }else if(lexema == "print"){
        return spl::Parser::token::KEYWORD_PRINT;
    }
    return spl::Parser::token::VARIABLE;
}

int Lexer::getNextToken(spl::Parser::value_type* yylval){
    States state = States::Initial_Q;

    lexema.clear();
    if(ch == EOF){
        return 0;
    }

    while(true){
        switch(state){
            case States::Initial_Q:
                if((ch >= '\t' && ch <= '\n') || ch == '\r' || ch == '\x20'){
                    ch = input.get();
                    lexema.clear();
                }else if(ch == ';'){
                    storeValue();
                    state = States::Semicolon_Q;
                }else if(ch == '('){
                    storeValue();
                    state = States::OpenPar_Q;
                }else if(ch == ')'){
                    storeValue();
                    state = States::ClosePar_Q;
                }else if(ch == '='){
                    storeValue();
                    state = States::Assign_Q;
                }else if(ch == '>'){
                    storeValue();
                    state = States::Greater_Q;
                }else if(ch == '<'){
                    storeValue();
                    state = States::Less_Q;
                }else if(ch == '!'){
                    storeValue();
                    state = States::Neg_Transition_Q;
                }else if(ch == '{'){
                    storeValue();
                    state = States::Open_Bracket;
                }else if(ch == '}'){
                    storeValue();
                    state = States::Close_Bracket;
                }else if(ch >= '0' && ch <= '9'){
                    storeValue();
                    state = States::Integer_Q;
                }else if((ch >= 'A' && ch <= 'Z')
                        || (ch >= 'a' && ch <= 'z')
                        || ch == '_')
                {
                    storeValue();
                    state = States::Identifier_Q;
                }else if(ch == EOF){
                    return 0;
                }
                break;
            case States::Semicolon_Q:
                return ';';
                break;
            case States::OpenPar_Q:
                return '(';
                break;
            case States::ClosePar_Q:
                return ')';
                break;
            case States::Open_Bracket:
                return '{';
                break;
            case States::Close_Bracket:
                return '}';
                break;
            case States::Assign_Q:
                if(ch == '='){
                    storeValue();
                    state = States::Equal_Q;
                }else{
                    return '=';
                }
                break;
            case States::Equal_Q:
                return spl::Parser::token::OP_REL_EQUALS;
                break;
            case States::Greater_Q:
                if(ch == '='){
                    storeValue();
                    state = States::GreaterEqual_Q;
                }else{
                    return '>';
                }
                break;
            case States::GreaterEqual_Q:
                return spl::Parser::token::OP_REL_GREATER_EQUAL;
                break;
            case States::Less_Q:
                if(ch == '='){
                    storeValue();
                    state = States::LessEqual_Q;
                }else{
                    return '<';
                }
                break;
            case States::LessEqual_Q:
                return spl::Parser::token::OP_REL_LESS_EQUAL;
                break;
            case States::Neg_Transition_Q:
                if(ch == '='){
                    storeValue();
                    state = States::Diff_Q;
                }else{
                    throwError();
                }
                break;
            case States::Diff_Q:
                return spl::Parser::token::OP_REL_DIFF;
                break;
            case States::Integer_Q:
                if(ch >= '0' && ch <= '9'){
                    storeValue();
                }else{
                    *yylval= new NumberExpression(stoi(lexema));
                    return spl::Parser::token::NUMBER;
                }
                break;
            case States::Identifier_Q:
                if((ch >= 'A' && ch <= 'Z')
                        || (ch >= 'a' && ch <= 'z')
                        || (ch >= '0' && ch <= '9')
                        || ch == '_')
                {
                    storeValue();
                }else{
                    int token = checkReserve();
                    if(token == spl::Parser::token::VARIABLE){
                        *yylval = new VarExpression(lexema);
                    }
                    return token;
                }
                break;
        }
    }

    return -1;
}

/*
void Lexer::readAllFile(){
    ch = input.get();
    int result = 0;
    while(ch == EOF){
        result = getNextToken();
        if(result ){

        }
    }
}*/