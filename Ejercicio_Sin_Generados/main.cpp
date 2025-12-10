#include <iostream>
#include "Lexer.hpp"
#include <vector>
#include <fstream>
#include <unordered_set>

int main(int argc, char* argv[])
{
    if(argc != 2){
        std::cout << "No estan suficientes parametros\n";
    }

    std::string direccion;
    direccion = argv[1];
    std::unordered_set<std::string> s;
    Lexer lexer(direccion);
    AstNode* program;

    try{
        spl::Parser parser(lexer,program);
        parser.parse();
        std::cout <<program->toCpp(s)<<'\n';
    }catch(const std::runtime_error& e){
        std::cerr<<e.what();
    }

	return 0;
}