#include "auto_parser.hpp"

namespace fg {


Parser::Parser() 
{
    initialize_parser();
}

void Parser::initialize_parser() 
{
        using namespace qi::labels;
        using namespace qi;

        quoted_string %= qi::lexeme['\'' >> *(qi::char_ - '\'') >> '\''];
        identifier %= qi::lexeme[qi::alpha >> *(qi::alnum | qi::char_('_'))];

        variable_definition = "var" >> identifier >> '=' >> expression;
        //bind_statement = "bind" >> '(' >> quoted_string >> ')';
        if_statement = "if" >> expression >> ':' >> block >> -(qi::lit("else") >> ':' >> block);
        while_statement = "while" >> expression >> ':' >> block;
        assignment = identifier >> '=' >> expression;

        expression = term % (+qi::char_("+-"));

        term = factor % (+qi::char_("*/"));

        factor = primary | identifier | '(' >> expression >> ')';
        primary = number | quoted_string;

        block = '{' >> *statement >> '}';
        statement = variable_definition | bind_statement | if_statement | while_statement | assignment;

        program = *statement;

        qi::phrase_parse_attr = qi::ascii::space;

        qi::lexeme_type %= +(qi::char_ - qi::eol) | qi::eol;
}

bool Parser::parse(std::string const& input, std::vector<Command>& commands) 
{
    using iterator_type = std::string::const_iterator;
    iterator_type begin = input.begin();
    iterator_type end = input.end();

    bool result = qi::phrase_parse(begin, end, program, qi::ascii::space, commands);

    return result && begin == end;
}
}