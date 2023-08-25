#include "mu_test.h"
#include <iostream>
#include "parser.hpp"

using namespace fg;

BEGIN_TEST(var_int_test)
    std::string script = "var x = 5";
    fg::Parser parser(script);
    auto ast = parser.parse();
    ASSERT_EQUAL(ast.size(), 1);
    ASSERT_THAT(dynamic_cast<VariableNode*>(ast[0].get()) != nullptr);
END_TEST

BEGIN_TEST(bind_test)
try{
    std::string script = "bind (/controls/switches/magnetos)";
    fg::Parser parser(script);
    auto ast = parser.parse();
    ASSERT_EQUAL(ast.size(), 1);
    ASSERT_THAT(dynamic_cast<BindNode*>(ast[0].get()) != nullptr);
}
catch(...)
{ std::cout<<"what?!\n";}
END_TEST


TEST_SUITE(ParserTests)
    TEST(var_int_test)
    TEST(bind_test)
END_SUITE