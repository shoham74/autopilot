#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "parser.hpp"
#include "ast_node.hpp"
#include "blocking_map.hpp"
#include "var.hpp"

namespace fg {
class Interpreter {
public:
    void execute(std::string const& a_script);
private:
    void execute_AST(std::vector<std::unique_ptr<ASTNode>> const& a_ast_node);
private:
    concurrency::BlockingMap<std::string, std::tuple<std::string, std::string, Var>> m_variables;
};
} //namespace fg
#endif // INTERPRETER_HPP