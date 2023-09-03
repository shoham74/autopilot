#include "parser_ast.hpp"
#include "Poco/CppParser/Parser.h"


namespace poco_script_parser {

ScriptParser::ScriptParser(const std::string& script_file_path) 
: script_file_path_(script_file_path) 
{

}

bool ScriptParser::parse_script() {
    std::ifstream script_file(script_file_path_);
    if (!script_file.is_open()) {
        std::cerr << "Failed to open script file: " << script_file_path_ << std::endl;
        return false;
    }

    Poco::CppParser::Parser parser;
    std::string line;
    while (std::getline(script_file, line)) {
        if (line.find("bind") == 0) {
            std::string var_name = extract_var_name(line);
            if (!var_name.empty()) {
                bound_variables_.push_back(var_name);
            }
        } else if (line.find('=') != std::string::npos) {
            std::string var_name = line.substr(0, line.find('='));
            if (is_bound_variable(var_name)) {
                std::string var_value = line.substr(line.find('=') + 1);
                assignments_[var_name] = var_value;
            }
        } else if (line.find("print") == 0) {
            std::string var_name = line.substr(6);
            if (is_bound_variable(var_name)) {
                print_statements_.push_back(var_name);
            }
        }
    }

    script_file.close();
    return true;
}

void ScriptParser::print_parsed_data() {
    std::cout << "Bound Variables:" << std::endl;
    for (const auto& var : bound_variables_) {
        std::cout << var << std::endl;
    }

    std::cout << "Variable Assignments:" << std::endl;
    for (const auto& assignment : assignments_) {
        std::cout << assignment.first << " = " << assignment.second << std::endl;
    }

    std::cout << "Print Statements:" << std::endl;
    for (const auto& statement : print_statements_) {
        std::cout << "print " << statement << std::endl;
    }
}

std::string ScriptParser::extract_var_name(const std::string& line) {
    std::string var_name;
    size_t start_pos = line.find("\"");
    size_t end_pos = line.find("\"", start_pos + 1);
    if (start_pos != std::string::npos && end_pos != std::string::npos) {
        var_name = line.substr(start_pos + 1, end_pos - start_pos - 1);
    }
    return var_name;
}

bool ScriptParser::is_bound_variable(const std::string& var_name) 
{
    return std::find(bound_variables_.begin(), bound_variables_.end(), var_name) != bound_variables_.end();
}

} // namespace poco_script_parser
