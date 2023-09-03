#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace qi = boost::spirit::qi;
namespace fg {
class Parser {
public:
      struct Command {
        enum class CommandType {
            VariableDefinition,
            BindStatement,
            IfStatement,
            WhileStatement,
            Assignment
        };

        CommandType type;
        std::string keyword;
        std::vector<std::string> arguments;
    };
    
    Parser();
    bool parse(const std::string& input, std::vector<Command>& commands);

private:
    void initialize_parser();
    qi::rule<std::string::const_iterator, std::string()> quoted_string;
    qi::rule<std::string::const_iterator, std::string()> identifier;

    qi::rule<std::string::const_iterator, Command(), qi::space_type> variable_definition;
    qi::rule<std::string::const_iterator, Command(), qi::space_type> bind_statement;
    qi::rule<std::string::const_iterator, Command(), qi::space_type> if_statement;
    qi::rule<std::string::const_iterator, Command(), qi::space_type> while_statement;
    qi::rule<std::string::const_iterator, Command(), qi::space_type> assignment;

    qi::rule<std::string::const_iterator, std::string(), qi::space_type> number;

    qi::rule<std::string::const_iterator, std::string(), qi::space_type> primary;
    qi::rule<std::string::const_iterator, std::string(), qi::space_type> factor;
    qi::rule<std::string::const_iterator, std::string(), qi::space_type> term;
    qi::rule<std::string::const_iterator, std::string(), qi::space_type> expression;

    qi::rule<std::string::const_iterator, std::vector<Command>(), qi::space_type> block;
    qi::rule<std::string::const_iterator, Command(), qi::space_type> statement;

    qi::rule<std::string::const_iterator, std::vector<Command>(), qi::space_type> program;
    
};

BOOST_FUSION_ADAPT_STRUCT(
    Parser::Command,
    (Parser::CommandType, type)
    (std::string, keyword)
    (std::vector<std::string>, arguments)
)

}
#endif // PARSER_HPP


