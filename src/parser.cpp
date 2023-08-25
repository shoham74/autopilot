#include "parser.hpp"
#include <sstream>

namespace fg {

Parser::Parser(std::string const& a_script_code)
: m_script_code(a_script_code)
, m_pos{0} 
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
    } else if (command == "+" || command == "-"  || command == "*" || command == "/" ){  
        return parse_arithmetic();
    } else if (command == "print") {
       return parse_print();
    } else {  
        return nullptr;
    }
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

std::unique_ptr<VariableNode> Parser::parse_variable() 
{
    std::string name = get_command_from_script();
    if (name.empty() || get_command_from_script() != "=") {
        return nullptr;
    }
    std::string property = get_command_from_script();
    return std::make_unique<VariableNode>(name, property);
}

std::unique_ptr<BindNode> Parser::parse_bind() 
{
    if (get_command_from_script() != "bind ") {
        return nullptr;
    }

    if (get_command_from_script() != "(") {
        return nullptr;
    }

    std::string property = get_command_from_script();
    if (property.empty() || property.front() != '\'' || property.back() != '\'') {
       throw("somethis go wrong");
        return nullptr;
    }

    if (get_command_from_script() != ")") {
        throw("somethis go wrong");
        return nullptr;
    }

    return std::make_unique<BindNode>(property.substr(1, property.length() - 2));
}

std::unique_ptr<PrintNode> Parser::parse_print() 
{
    std::string text = get_command_from_script();
    if (text.empty()) {
        return nullptr;
    }
    return std::make_unique<PrintNode>(text);
}

std::unique_ptr<AssignmentNode> Parser::parse_assignment() 
{
    std::string identifier = get_command_from_script();
    if (identifier.empty() || get_command_from_script() != "=") {
        // Handle error: Invalid assignment
        return nullptr;
    }

    auto expression = parse_arithmetic(); 
    if (!expression) {
        return nullptr;
    }

    return std::make_unique<AssignmentNode>(identifier, std::move(expression));
}

std::unique_ptr<ForNode> Parser::parse_for() 
{
    // // Parse initialization, condition, update, and loop body
    // auto initialization = parse_assignment();
    // if (!initialization) {
    //     // Handle error: Invalid initialization
    //     return nullptr;
    // }

    // if (get_command_from_script() != ";") {
    //     // Handle error: Expected ';'
    //     return nullptr;
    // }

    // auto condition = parse_arithmetic();
    // if (!condition) {
    //     // Handle error: Invalid condition
    //     return nullptr;
    // }

    // if (get_command_from_script() != ";") {
    //     // Handle error: Expected ';'
    //     return nullptr;
    // }

    // auto update = parse_assignment();
    // if (!update) {
    //     // Handle error: Invalid update
    //     return nullptr;
    // }

    // if (get_command_from_script() != ":") {
    //     // Handle error: Expected ':'
    //     return nullptr;
    // }

    // std::vector<std::unique_ptr<ASTNode>> loop_body;
    // // Parse and populate loop_body using a loop
    // while (...) {
    //     auto statement = parse_statement();
    //     if (statement) {
    //         loop_body.push_back(std::move(statement));
    //     } else {
    //         // Handle error
    //     }
    // }

    // if (get_command_from_script() != "end") {
    //     // Handle error: Expected 'end' after loop body
        return nullptr;
    // }

    // return std::make_unique<ForNode>(
    //     std::move(initialization), std::move(condition),
    //     std::move(update), std::move(loop_body));
}

std::unique_ptr<IfNode> Parser::parse_if() 
{
    // // Parse condition
    // auto condition = parse_arithmetic();
    // if (!condition) {
    //     // Handle error: Invalid condition
    //     return nullptr;
    // }

    // if (get_command_from_script() != ":") {
    //     // Handle error: Expected ':'
    //     return nullptr;
    // }

    // std::vector<std::unique_ptr<ASTNode>> if_body;
    // // Parse and populate if_body using a loop
    // while (...) {
    //     auto statement = parse_statement();
    //     if (statement) {
    //         if_body.push_back(std::move(statement));
    //     } else {
    //         // Handle error
    //     }
    // }

    // std::vector<std::unique_ptr<ASTNode>> else_body;
    // if (get_command_from_script() == "else") {
    //     // Parse else body in a similar manner
    //     // ...

    //     // Parse 'end'
    //     if (get_command_from_script() != "end") {
    //         // Handle error: Expected 'end' after if-else
    //         return nullptr;
    //     }
    // } else {
    //     // Parse 'end'
    //     if (get_command_from_script() != "end") {
    //         // Handle error: Expected 'end' after if
           return nullptr;
    //     }
    //}

    //return std::make_unique<IfNode>(std::move(condition), std::move(if_body), std::move(else_body));
}

std::unique_ptr<WhileNode> Parser::parse_while() 
{
    // Parse condition
    auto condition = parse_arithmetic();
    if (!condition) {
        // Handle error: Invalid condition
        return nullptr;
    }

    if (get_command_from_script() != ":") {
        // Handle error: Expected ':'
        return nullptr;
    }

    std::vector<std::unique_ptr<ASTNode>> loop_body;
    // Parse and populate loop_body using a loop
    // while (...) {
    //     auto statement = parse_statement();
    //     if (statement) {
    //         loop_body.push_back(std::move(statement));
    //     } else {
    //         // Handle error
    //     }
    // }

    if (get_command_from_script() != "end") {
        // Handle error: Expected 'end' after loop body
        return nullptr;
    }

    return std::make_unique<WhileNode>(std::move(condition), std::move(loop_body));
}

std::unique_ptr<ArithmeticNode> Parser::parse_arithmetic() 
{
    // std::unique_ptr<ASTNode> left_operand = parse_primary();
    // if (!left_operand) {
    //     // Handle error: Invalid left operand
    //     return nullptr;
    // }

    // std::string op = get_command_from_script();
    // if (op != "+" && op != "-" && op != "*" && op != "/") {
    //     // Not an arithmetic operator
    //     return nullptr;
    // }

    // std::unique_ptr<ASTNode> right_operand = parse_primary();
    // if (!right_operand) {
    //     // Handle error: Invalid right operand
        return nullptr;
    // }

    // return std::make_unique<ArithmeticNode>(
    //     std::move(left_operand), op, std::move(right_operand));
}


}// namespace fg
