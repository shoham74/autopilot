#include "parser.hpp"
#include <sstream>

Parser::Parser(std::string const& a_script_code)
: m_script_code(a_script_code)
, m_pos(0) 
{
}

std::vector<std::unique_ptr<ASTNode>> Parser::parse() 
{
    std::vector<std::unique_ptr<ASTNode>> ast;
    while (m_pos < m_script_code.length()) {
        auto statement = parse_statement();
        if (statement) {
            ast.push_back(std::move(statement));
        }
    }
    return ast;
}

std::unique_ptr<ASTNode> Parser::parse_statement() 
{
    std::string command = get_command_from_script();
    if (command == "var") {
        return parse_variable();
    } else if (command == "bind") {
        return parse_bind();
    } else if (command == "if") {
        return parse_if();
    } else if (command == "while") {
        return parse_while();
    } else if (command == "for"){
        return parse_for();
    } else if (command == "="){   
        return parse_assignment();
    } else if (command == "="){   
        return nullptr;
    }
}

std::unique_ptr<VariableNode> Parser::parse_variable() 
{
   
    return nullptr;
}

std::unique_ptr<BindNode> Parser::parse_bind() 
{
    return nullptr;
}

std::unique_ptr<ForNode> Parser::parse_for() 
{
   
    return nullptr;
}

std::unique_ptr<IfNode> Parser::parse_if() 
{
   
    return nullptr;
}

std::unique_ptr<WhileNode> Parser::parse_while() 
{
    
    return nullptr;
}

std::unique_ptr<AssignmentNode> Parser::parse_assignment() 
{
   
    return nullptr;
}

std::unique_ptr<ArithmeticNode> Parser::parse_arithmetic() {
    // Implement parsing for arithmetic expressions
    // Create and return an ArithmeticNode
    return nullptr;
}

std::string Parser::get_command_from_script() 
{
    std::istringstream ss(m_script_code);
    ss.seekg(m_pos);
    
    std::string command;
    ss >> command;
    m_pos = ss.tellg();
    
    return command;
}
