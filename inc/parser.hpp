#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <iostream> 
#include <memory>

#include "ast_node.hpp"

namespace fg {
class Parser {
public:
    explicit Parser(std::string const& a_script_code);
    ~Parser() = default;
    std::vector<std::unique_ptr<ASTNode>> parse();

private:
    std::unique_ptr<ASTNode> parse_statement();
    std::unique_ptr<VariableNode> parse_variable();
    std::unique_ptr<BindNode> parse_bind();
    std::unique_ptr<ForNode> parse_for();
    std::unique_ptr<IfNode> parse_if();
    std::unique_ptr<WhileNode> parse_while();
    std::unique_ptr<AssignmentNode> parse_assignment();
    std::unique_ptr<ArithmeticNode> parse_arithmetic();
    std::unique_ptr<PrintNode> parse_print();

    std::string get_command_from_script();

private:   
    const std::string m_script_code;
    std::size_t m_pos;
};
} // namespace fg
#endif // PARSER_HPP
