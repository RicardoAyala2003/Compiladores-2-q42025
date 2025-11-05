#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Token {
    std::string value;
    std::string type;
};

class Lexer
{
private:
    std::vector<char> characters;
    int index = 0;
    std::string buffer = "";

public:
    Lexer(std::vector<char> input) : characters(input) {}

    char getNextChar()
    {
        if (index >= characters.size()) return '\0';
        return characters[index++];
    }

    char checkNextChar()
    {
        if (index >= characters.size()) return '\0';
        return characters[index];
    }

    std::string getBuffer() {
        return buffer;
    }

    std::string getNextToken()
    {
        int currentState = 0;
        buffer = "";

        char currentChar = getNextChar();
        if (currentChar == '\0') return "EOF";

        while (true)
        {
            switch (currentState)
            {
            case 0:
                if ((currentChar >= 9 && currentChar <= 10) || currentChar == 13 || currentChar == 32)
                {
                    currentChar = getNextChar();
                    if (currentChar == '\0') return "EOF";
                    currentState = 1;
                }
                else if (std::isdigit(currentChar))
                {
                    buffer += currentChar;
                    currentChar = getNextChar();
                    if (currentChar == '\0') return "INTEGER";
                    currentState = 2;
                }
                else if ((std::isalpha(currentChar) || currentChar == '_') && currentChar != 'i')
                {
                    buffer += currentChar;
                    currentChar = getNextChar();
                    if (currentChar == '\0') return "IDENTIFIER";
                    currentState = 3;
                }
                else if (currentChar == '*')
                {
                    buffer += currentChar;
                    currentChar = getNextChar();
                    if (currentChar == '\0') return "OP_MUL";
                    currentState = 4;
                }
                else if (currentChar == '"') 
                {
                    currentChar = getNextChar();
                    if (currentChar == '\0') return "ERROR";
                    currentState = 5;
                }
                else if (currentChar == 'i') 
                {
                    buffer += currentChar;
                    currentChar = getNextChar();
                    if (currentChar == '\0') return "IDENTIFIER";
                    currentState = 7;
                }
                else if (currentChar == '/')
                {
                    buffer += currentChar;
                    currentChar = getNextChar();
                    if (currentChar == '\0') return "OP_DIV";
                    currentState = 8;
                }
                else
                {
                    buffer += currentChar;
                    return "ERROR";
                }
                break;

            case 1:
                currentState = 0;
                break;

            case 2:
                if (std::isdigit(currentChar))
                {
                    buffer += currentChar;
                    currentChar = getNextChar();
                    if (currentChar == '\0') return "INTEGER";
                    currentState = 2;
                }
                else
                {
                    index--;
                    return "INTEGER";
                }
                break;

            case 3:
                if (std::isalnum(currentChar) || currentChar == '_')
                {
                    buffer += currentChar;
                    currentChar = getNextChar();
                    if (currentChar == '\0') return "IDENTIFIER";
                    currentState = 3;
                }
                else
                {
                    index--;
                    return "IDENTIFIER";
                }
                break;

            case 4:
                index--;
                return "OP_MUL";
                break;

            case 5:
                if (currentChar == '"') 
                {
                    currentState = 6;
                }
                else if (currentChar == '\\')
                {
                    buffer += currentChar;
                    currentChar = getNextChar();
                    if (currentChar == '\0') return "ERROR";
                    buffer += currentChar;
                    currentChar = getNextChar();
                    if (currentChar == '\0') return "ERROR";
                    currentState = 5;
                }
                else
                {
                    buffer += currentChar;
                    currentChar = getNextChar();
                    if (currentChar == '\0') return "ERROR";
                    currentState = 5;
                }
                break;

            case 6:
                return "STRING_LITERAL";
                break;

            case 7:
                if (currentChar == 'f') 
                {
                    buffer += currentChar;
                    currentChar = getNextChar();
                    if (currentChar == '\0') return "KW_IF";
                    if (std::isalnum(currentChar) || currentChar == '_')
                    {
                        currentState = 3;
                    }
                    else
                    {
                        index--;
                        return "KW_IF";
                    }
                }
                else
                {
                    currentState = 3;
                }
                break;

            case 8:
                if (currentChar == '/')
                {
                    buffer = "";
                    currentState = 9;
                    currentChar = getNextChar();
                    if (currentChar == '\0') return "EOF";
                }
                else if (currentChar == '*')
                {
                    buffer = "";
                    currentState = 10;
                    currentChar = getNextChar();
                    if (currentChar == '\0') return "ERROR";
                }
                else
                {
                    index--;
                    return "OP_DIV";
                }
                break;

            case 9:
                if (currentChar == '\n' || currentChar == '\r')
                {
                    currentChar = getNextChar();
                    if (currentChar == '\0') return "EOF";
                    buffer = "";
                    currentState = 0;
                }
                else
                {
                    currentChar = getNextChar();
                    if (currentChar == '\0') return "EOF";
                    currentState = 9;
                }
                break;

            case 10:
                if (currentChar == '*')
                {
                    currentChar = getNextChar();
                    if (currentChar == '\0') return "ERROR";
                    currentState = 11;
                }
                else
                {
                    currentChar = getNextChar();
                    if (currentChar == '\0') return "ERROR";
                    currentState = 10;
                }
                break;

            case 11:
                if (currentChar == '/')
                {
                    currentChar = getNextChar();
                    if (currentChar == '\0') return "EOF";
                    buffer = "";
                    currentState = 0;
                }
                else if (currentChar == '*')
                {
                    currentChar = getNextChar();
                    if (currentChar == '\0') return "ERROR";
                    currentState = 11;
                }
                else
                {
                    currentChar = getNextChar();
                    if (currentChar == '\0') return "ERROR";
                    currentState = 10;
                }
                break;
            }
        }
    }
};

std::vector<char> loadFileContent(const std::string &filename)
{
    std::ifstream file(filename);
    std::vector<char> content;

    if (!file)
    {
        std::cerr << "Cannot open file.\n";
        return content;
    }

    char ch;
    while (file.get(ch))
    {
        content.push_back(ch);
    }

    return content;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./program <filename>\n";
        return 1;
    }

    std::vector<char> fileChars = loadFileContent(argv[1]);

    Lexer lexer(fileChars);

    std::string tokenType;

    while ((tokenType = lexer.getNextToken()) != "EOF") 
    {
        std::cout  << tokenType << " >> " << lexer.getBuffer() << "\n";
    }

    return 0;
}