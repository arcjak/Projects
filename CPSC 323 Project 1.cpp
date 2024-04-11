#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//Daniel Lee, CPSC 335 Project 1
using namespace std;

enum TokenType 
{
    IDENTIFIER,
    INTEGER,
    OPERATOR,
    SEPARATOR,
    UNKNOWN
};

struct Token 
{
    TokenType type;
    string lexeme;
};

// Function to check if a character is a valid identifier character
bool isIdentifierChar(char c) {
    return isalnum(c) || c == '_';
}

bool isOperatorChar(char c) 
{
    // set of characters considered as operators
    string operators = "+-*/%=><&|^!";

    // Check if the character is in the set of operators
    return operators.find(c) != string::npos;
}
bool isSeparatorChar(char c) 
{
    // set of characters considered as operators
    string separators = ":;(){}";

    // Check if the character is in the set of operators
    return separators.find(c) != string::npos;
}

// Lexer Function to tokenize the input source code
vector<Token> lexer(const string& sourceCode)
{
    vector<Token> tokens;
    string currentLexeme = "";
    TokenType currentType = UNKNOWN;

    for (char c : sourceCode) 
    {
        if (isIdentifierChar(c)) 
        {
            // Append to the current lexeme if it's a valid identifier character
            currentLexeme += c;
            currentType = isdigit(c) ? INTEGER : IDENTIFIER;
        } 
        else if (isOperatorChar(c))
        {
            if (!currentLexeme.empty()) // checks to see if current lexeme is empty. If not, push token to the vector, and reset lexeme to blank with type "Unknown"
            {
                tokens.push_back({currentType, currentLexeme});
                currentLexeme = "";
                currentType = UNKNOWN;
            }
            tokens.push_back({OPERATOR, string(1, c)});
        }
        else if (isSeparatorChar(c))
        {
            if (!currentLexeme.empty()) // checks to see if current lexeme is empty. If not, push token to the vector, and reset lexeme to blank with type "Unknown"
            {
                tokens.push_back({currentType, currentLexeme});
                currentLexeme = "";
                currentType = UNKNOWN;
            }
            tokens.push_back({SEPARATOR, string(1, c)});
        }
        else 
        {
            // If the lexeme is not empty, push the token into the vector
            if (!currentLexeme.empty()) 
            {
                tokens.push_back({currentType, currentLexeme});
                currentLexeme = "";
                currentType = UNKNOWN;
            }
        }
    }

    // Push the last token if there's any
    if (!currentLexeme.empty()) 
    {
        tokens.push_back({currentType, currentLexeme});
    }

    return tokens;
}


// Function to print tokens and lexemes to the terminal
void printTokens(const vector<Token>& tokens) 
{
    cout << "Token\t\tLexeme\n---------------------------------\n";
    for (const Token& token : tokens) {
        string tokenType;
        switch (token.type) {
            case IDENTIFIER:
                tokenType = "Identifier";
                break;
            case INTEGER:
                tokenType = "Integer";
                break;
            case OPERATOR:
                tokenType = "Operator";
                break;
            case SEPARATOR:
                tokenType = "Separator";
                break;
            default:
                tokenType = "Unknown";
                break;
        }
        cout << tokenType << "\t\t" << token.lexeme << endl;
    }
}

int main() 
{
    // Read input source code from a text file
    ifstream inputFile("Input_File.txt");
    if (!inputFile.is_open()) {
        cerr << "Failed to open Input_File.txt" << endl;
        return 1;
    }

    string sourceCode((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());

    // Tokenize the source code
    vector<Token> tokens = lexer(sourceCode);

    // Print tokens and lexemes
    printTokens(tokens);

    // Write output to a text file
    ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        cerr << "Failed to open output.txt" << endl;
        return 1;
    }

    for (const Token& token : tokens) 

        {
            outputFile << (token.type == IDENTIFIER ? "Identifier" : 
               (token.type == INTEGER ? "Integer" : 
               (token.type == OPERATOR ? "Operator" :
               (token.type == SEPARATOR ? "Separator" : "Unknown")))) 
           << "\t" << token.lexeme << endl;
        }

    cout << "Output written to output.txt" << endl;

    return 0;
}
