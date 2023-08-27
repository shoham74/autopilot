// Lexer.hpp
#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include <boost/tokenizer.hpp>

// Define token types
enum class TokenType {
    IDENTIFIER,
    NUMBER,
    SYMBOL
};

// Token structure
struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    Lexer();
    std::vector<Token> tokenize(std::string const& a_code) const;
};

#endif // LEXER_HPP
