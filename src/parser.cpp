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
    std::vector<Token> tokens = m_lexer.tokenize(m_script_code);
    std::vector<std::unique_ptr<ASTNode>> parsed_nodes;

    while (m_pos < tokens.size()) {
        std::unique_ptr<ASTNode> statement_node = parse_statement(tokens);
        parsed_nodes.push_back(std::move(statement_node));
    }
    return parsed_nodes;
}

std::unique_ptr<ASTNode> Parser::parse_statement(std::vector<Token> const& a_tokens) 
{
    if (m_pos < a_tokens.size()) {
        Token current_token = a_tokens[m_pos];
        if (current_token.m_type == TokenType::VAR) {
            m_pos++; 
            return parse_variable(a_tokens);

        } else if(current_token.m_type == TokenType::PRINT) {
            m_pos++; 
            return parse_print(a_tokens);

        } else if(current_token.m_type == TokenType::SLEEP) {
            m_pos++; 
            return parse_sleep(a_tokens);
            
        } else if(current_token.m_type == TokenType::WHILE) {
            m_pos++; 
            return parse_while(a_tokens);
        }


        //TODO handle other types of statements here
    }
    return nullptr;
}

std::unique_ptr<VariableNode> Parser::parse_variable(std::vector<Token> const& a_tokens)
{
    if (m_pos < a_tokens.size()) {
        Token current_token = a_tokens[m_pos];
        std::unique_ptr<VariableNode> variable_node ;
        if (current_token.m_type == TokenType::IDENTIFIER) {
            std::string variable_name = current_token.m_value;
            
            m_pos++;
            
            if (m_pos < a_tokens.size() && a_tokens[m_pos].m_type == TokenType::ASSIGNMENT) {
                m_pos++; 
                if (m_pos < a_tokens.size() && a_tokens[m_pos].m_type == TokenType::NUMBER) {
                    m_pos++; 
                     std::string number = current_token.m_value;
                     variable_node = std::make_unique<VariableNode>(variable_name , number);
                } 
            }
            return variable_node;
        }
    }
    
    return nullptr;
}

std::unique_ptr<PrintNode> Parser::parse_print(std::vector<Token> const& a_tokens)
{
    if (m_pos < a_tokens.size()) {
        Token current_token = a_tokens[m_pos];
        std::string text;
        if (current_token.m_type == TokenType::STRING_LITERAL) {
            m_pos++;
            text = current_token.m_value;
        }
        return std::make_unique<PrintNode>(text);
    }
    return nullptr;
}

std::unique_ptr<SleepNode> Parser::parse_sleep(std::vector<Token> const& a_tokens)
{
    if (m_pos < a_tokens.size()) {
        Token current_token = a_tokens[m_pos];
        std::string time;
        if (current_token.m_type == TokenType::NUMBER) {
            m_pos++;
            time = current_token.m_value;
        }
        return std::make_unique<SleepNode>(time);
    }
    return nullptr;
}

std::unique_ptr<WhileNode> Parser::parse_while(std::vector<Token> const& a_tokens)
{
    std::string identifier_name;
    std::string symbol;
    std::string number;

    if (m_pos < a_tokens.size()) {
        m_pos++;
        if (m_pos < a_tokens.size() && a_tokens[m_pos].m_type == TokenType::IDENTIFIER) {
            Token current_token = a_tokens[m_pos];
            identifier_name = current_token.m_value;
            m_pos++;
            if (m_pos < a_tokens.size() && (a_tokens[m_pos].m_type ==  TokenType::LESS )) {
                current_token = a_tokens[m_pos];
                symbol = current_token.m_value;
                m_pos++;
                if (m_pos < a_tokens.size() && (a_tokens[m_pos].m_type ==  TokenType::NUMBER)) {
                    current_token = a_tokens[m_pos];
                    number = current_token.m_value;
                    m_pos++;
                }
            }
        }
        if (m_pos < a_tokens.size() && a_tokens[m_pos].m_type == TokenType::OPEN_SCOP) {
            m_pos++;
        } else {
            return nullptr;
        }

        std::vector<std::unique_ptr<ASTNode>> loop_body;
        while (m_pos < a_tokens.size() && a_tokens[m_pos].m_type != TokenType::CLOSE_SCOP) {
            std::unique_ptr<ASTNode> statement = parse_statement(a_tokens);
            if (statement) {
                loop_body.push_back(std::move(statement));
                m_pos++;
            } else {
                return nullptr;
            }
        }

        if (m_pos < a_tokens.size() && a_tokens[m_pos].m_type == TokenType::CLOSE_SCOP) {
            m_pos++;
        } else {
            return nullptr;
        }
        std::unique_ptr<ConditionNode> condition = std::make_unique<ConditionNode>(identifier_name , number ,symbol); 
        return std::make_unique<WhileNode>(std::move(condition), std::move(loop_body));
    }
    return nullptr;
}

// std::unique_ptr<BindNode> Parser::parse_bind() 
// {
//     if (get_command_from_script() != "bind ") {
//         return nullptr;
//     }

//     if (get_command_from_script() != "(") {
//         return nullptr;
//     }

//     std::string property = get_command_from_script();
//     if (property.empty() || property.front() != '\'' || property.back() != '\'') {
//        throw("somethis go wrong");
//         return nullptr;
//     }

//     if (get_command_from_script() != ")") {
//         throw("somethis go wrong");
//         return nullptr;
//     }

//     return std::make_unique<BindNode>(property.substr(1, property.length() - 2));
// }


// std::unique_ptr<AssignmentNode> Parser::parse_assignment() 
// {
//     std::string identifier = get_command_from_script();
//     if (identifier.empty() || get_command_from_script() != "=") {
//         // Handle error: Invalid assignment
//         return nullptr;
//     }

//     auto expression = parse_arithmetic(); 
//     if (!expression) {
//         return nullptr;
//     }

//     return std::make_unique<AssignmentNode>(identifier, std::move(expression));
// }


// std::unique_ptr<IfNode> Parser::parse_if() 
// {
//     // // Parse condition
//     // auto condition = parse_arithmetic();
//     // if (!condition) {
//     //     // Handle error: Invalid condition
//     //     return nullptr;
//     // }

//     // if (get_command_from_script() != ":") {
//     //     // Handle error: Expected ':'
//     //     return nullptr;
//     // }

//     // std::vector<std::unique_ptr<ASTNode>> if_body;
//     // // Parse and populate if_body using a loop
//     // while (...) {
//     //     auto statement = parse_statement();
//     //     if (statement) {
//     //         if_body.push_back(std::move(statement));
//     //     } else {
//     //         // Handle error
//     //     }
//     // }

//     // std::vector<std::unique_ptr<ASTNode>> else_body;
//     // if (get_command_from_script() == "else") {
//     //     // Parse else body in a similar manner
//     //     // ...

//     //     // Parse 'end'
//     //     if (get_command_from_script() != "end") {
//     //         // Handle error: Expected 'end' after if-else
//     //         return nullptr;
//     //     }
//     // } else {
//     //     // Parse 'end'
//     //     if (get_command_from_script() != "end") {
//     //         // Handle error: Expected 'end' after if
//            return nullptr;
//     //     }
//     //}

//     //return std::make_unique<IfNode>(std::move(condition), std::move(if_body), std::move(else_body));
// }

// std::unique_ptr<ArithmeticNode> Parser::parse_arithmetic() 
// {
//     // std::unique_ptr<ASTNode> left_operand = parse_primary();
//     // if (!left_operand) {
//     //     // Handle error: Invalid left operand
//     //     return nullptr;
//     // }

//     // std::string op = get_command_from_script();
//     // if (op != "+" && op != "-" && op != "*" && op != "/") {
//     //     // Not an arithmetic operator
//     //     return nullptr;
//     // }

//     // std::unique_ptr<ASTNode> right_operand = parse_primary();
//     // if (!right_operand) {
//     //     // Handle error: Invalid right operand
//         return nullptr;
//     // }

//     // return std::make_unique<ArithmeticNode>(
//     //     std::move(left_operand), op, std::move(right_operand));
// }


}// namespace fg
