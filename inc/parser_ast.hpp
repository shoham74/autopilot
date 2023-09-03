#ifndef SCRIPT_PARSER_HPP
#define SCRIPT_PARSER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

namespace poco_script_parser {

class ScriptParser {
public:
    ScriptParser(const std::string& script_file_path);

    bool parse_script();
    void print_parsed_data();

private:
    std::string extract_var_name(const std::string& line);
    bool is_bound_variable(const std::string& var_name);

private:
    std::string script_file_path_;
    std::vector<std::string> bound_variables_;
    std::map<std::string, std::string> assignments_;
    std::vector<std::string> print_statements_;
};

} // namespace poco_script_parser

#endif // SCRIPT_PARSER_HPP
