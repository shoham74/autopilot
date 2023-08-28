#include "lexer.hpp"

Lexer::Lexer() 
{

}

namespace {

TokenType get_token_type(std::string const& tokenStr) 
{
    // Keywords
    switch (tokenStr[0]) {
        case 'v':
            if (tokenStr == "var") return TokenType::VAR;
            break;
        case 'b':
            if (tokenStr == "bind") return TokenType::BIND;
            break;
        case 'i':
            if (tokenStr == "if") return TokenType::IF;
            break;
        case 'e':
            if (tokenStr == "else") return TokenType::ELSE;
            break;
        case 'w':
            if (tokenStr == "while") return TokenType::WHILE;
            break;
        case 'p':
            if (tokenStr == "print") return TokenType::PRINT;
            break;
        case 's':
            if (tokenStr == "sleep") return TokenType::SLEEP;
            break;
    }

    // Symbols
    switch (tokenStr[0]) {
        case '=':
            return TokenType::ASSIGNMENT;
        case '+':
            return TokenType::PLUS;
        case '-':
            return TokenType::MINUS;
        case '*':
            return TokenType::ASTERISK;
        case '/':
            return TokenType::SLASH;
        case '(':
            return TokenType::OPEN_PAREN;
        case ')':
            return TokenType::CLOSE_PAREN;
        case '{':
            return TokenType::OPEN_SCOP;
        case '}':
            return TokenType::CLOSE_SCOP;
        case ':':
            return TokenType::COLON;
        case ',':
            return TokenType::COMMA;
        case ';':
            return TokenType::SEMICOLON;
        case '>':
            if (tokenStr == ">=") return TokenType::GREATER_EQUAL;
            return TokenType::GREATER;
        case '<':
            if (tokenStr == "<=") return TokenType::LESS_EQUAL;
            return TokenType::LESS;
        case '!':
        if (tokenStr == "!=") return TokenType::NOT_EQUAL;
        break;
}

    // Identifier recognition
    if (std::isalpha(tokenStr[0]) || tokenStr[0] == '_') {
        bool isIdentifier = true;
        for (char c : tokenStr.substr(1)) {
            if (!std::isalnum(c) && c != '_') {
                isIdentifier = false;
                break;
            }
        }
        if (isIdentifier) return TokenType::IDENTIFIER;
    }

    // Number recognition (simplified for positive integers)
    bool isNumber = true;
    for (char c : tokenStr) {
        if (!std::isdigit(c)) {
            isNumber = false;
            break;
        }
    }
    if (isNumber) return TokenType::NUMBER;

    // String literal recognition (simplified for single-quoted strings)
    if (tokenStr.size() >= 2 && tokenStr.front() == '\'' && tokenStr.back() == '\'')
        return TokenType::STRING_LITERAL;

    // Default to IDENTIFIER for unhandled cases
    return TokenType::IDENTIFIER;
}
}

std::vector<Token> Lexer::tokenize(std::string const& sourceCode) const {
    std::vector<Token> tokens;

    boost::char_separator<char> separator(" \t\r\n");
    boost::tokenizer<boost::char_separator<char>> tokenizer(sourceCode, separator);

    for (const std::string& tokenStr : tokenizer) {
        Token token;
        token.m_type = get_token_type(tokenStr);
        token.m_value = tokenStr;
        tokens.push_back(token);
    }

    return tokens;
}
