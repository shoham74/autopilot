#include "lexer.hpp"

Lexer::Lexer() 
{

}

std::vector<Token> Lexer::tokenize(std::string const& a_code) const 
{
    std::vector<Token> tokens;

    boost::char_separator<char> separator(" \t\r\n", "+-*/=();{},");
    boost::tokenizer<boost::char_separator<char>> tokenizer(a_code, separator);

    for (std::string const& token_str : tokenizer) {
        Token token;
        if (std::isdigit(token_str[0])) {
            token.type =  TokenType::NUMBER;
            token.value = token_str;
        } else if (std::isalpha(token_str[0]) || token_str[0] == '_') {
            token.type =  TokenType::IDENTIFIER;
            token.value = token_str;
        } else {
            token.type =  TokenType::SYMBOL;
            token.value = token_str;
        }
        tokens.push_back(token);
    }

    return tokens;
}
