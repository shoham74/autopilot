#ifndef AST_NODE_IF_HPP
#define AST_NODE_IF_HPP

#include "ast_node.hpp"

#include <string> // std::string
#include <vector> // vector
#include <memory> // unique ptr

namespace fgear {

//TODO: if clause
class IfNode : public ASTNode {
public:
    using ptr = std::unique_ptr<ASTNode>;
    using vector = std::vector<std::unique_ptr<ASTNode>>;
    explicit IfNode(ptr&& a_cond, vector&& a_if_body, vector&& a_else_body);
    
    ~IfNode() = default;

    void operator()() override;


private:
    std::unique_ptr<ASTNode> m_condition;
    std::vector<std::unique_ptr<ASTNode>> m_if_body;
    std::vector<std::unique_ptr<ASTNode>> m_else_body;
};

} // namespace fgear 

#endif // AST_NODE_IF_HPP