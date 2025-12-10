#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "PracticeParser.hpp"

enum class States{
    Initial_Q,
    Semicolon_Q,
    OpenPar_Q,
    ClosePar_Q,
    Open_Bracket,
    Close_Bracket,
    Assign_Q,
    Equal_Q,
    Neg_Transition_Q,
    Diff_Q,
    Less_Q,
    LessEqual_Q,
    Greater_Q,
    GreaterEqual_Q,
    Integer_Q,
    Identifier_Q,
    EOF_Q
};

class Lexer{
    public:
        Lexer(const std::string &file):input(file),ch(0){
            if (!input.is_open()) {
                throw std::runtime_error("No se pudo abrir el archivo: " + file);
            }
            ch = input.get();
        }

        ~Lexer() {
            if (input.is_open()) {
                input.close();
            }
        }

        int getNextToken(spl::Parser::value_type* v);

        std::string getText(){return lexema;}
        int getCharValue(){return ch;}
        void storeValue();
        char convertToChar(){return static_cast<char>(ch);}
        void readAllFile();
        void throwError();
        int checkReserve();

    private:
        int ch;
        std::string lexema;
        std::ifstream input;

};