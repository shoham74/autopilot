#ifndef AST_NODE_HPP
#define AST_NODE_HPP

#include <string>
#include <vector>
#include <memory>


class ASTNode {
public:
    virtual ~ASTNode() = default;
};

class VariableNode : public ASTNode {
public:
VariableNode(std::string const& a_name, std::string const& a_property)
: m_name(a_name)
, m_property(a_property) 
{

}

std::string name() const {
        return m_name;
    }

std::string property() const {
        return m_property;
    }

private:
    std::string m_name;
    std::string m_property;
};

class BindNode : public ASTNode {
public:
BindNode(std::string const& a_name, std::string const& a_property)
: m_name(a_name)
, m_property(a_property) 
{

}

std::string name() const {
        return m_name;
    }

std::string property() const {
        return m_property;
    }

private:
    std::string m_name;
    std::string m_property;
};

class PrintNode : public ASTNode {
public:
explicit PrintNode(const std::string& text)
        : m_text(text) {}

std::string text() const {
        return m_text;
    }

private:
    std::string m_text;
};

class IfNode : public ASTNode {
public:
    IfNode(std::unique_ptr<ASTNode> cond,
           std::vector<std::unique_ptr<ASTNode>> if_body,
           std::vector<std::unique_ptr<ASTNode>> else_body)
        : condition(std::move(cond)),
          if_body(std::move(if_body)),
          else_body(std::move(else_body)) {}

private:
    std::unique_ptr<ASTNode> condition;
    std::vector<std::unique_ptr<ASTNode>> if_body;
    std::vector<std::unique_ptr<ASTNode>> else_body;
};

class WhileNode : public ASTNode {
public:
    WhileNode(std::unique_ptr<ASTNode> cond,
              std::vector<std::unique_ptr<ASTNode>> body)
        : condition(std::move(cond)), loop_body(std::move(body)) {}

private:
    std::unique_ptr<ASTNode> condition;
    std::vector<std::unique_ptr<ASTNode>> loop_body;
};

class AssignmentNode : public ASTNode {
public:
    AssignmentNode(const std::string& identifier,
                   std::unique_ptr<ASTNode> expression)
        : identifier(identifier), expression(std::move(expression)) {}

private:
    std::string identifier;
    std::unique_ptr<ASTNode> expression;
};




class ConditionNode : public ASTNode {
public:
    ConditionNode(std::string const& id , std::string const& num , std::string const& symbol)
        : m_condition(symbol) , m_number(num) , m_idtfr(id)
        {

        }

private:
    std::string m_condition;
    std::string m_number; 
    std::string m_idtfr; 

};






class SleepNode : public ASTNode {
public:
SleepNode(std::string const& a_time)
: m_time(a_time) 
{ 
}

int time() const
{
    return std::stoi(m_time);
}

private:
    std::string m_time;
};

class ArithmeticNode : public ASTNode {
public:
    ArithmeticNode(std::unique_ptr<ASTNode> left,
                   const std::string& op,
                   std::unique_ptr<ASTNode> right)
        : left(std::move(left)), op(op), right(std::move(right)) {}

private:
    std::unique_ptr<ASTNode> left;
    std::string op;
    std::unique_ptr<ASTNode> right;
};


#endif // AST_NODE_HPP