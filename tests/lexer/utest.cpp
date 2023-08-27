#include "mu_test.h"

#include "lexer.hpp"



BEGIN_TEST(var_int_test)
    Lexer lexer;
    std::string sourceCode = "sleep 1000";

    std::vector<Token> tokens = lexer.tokenize(sourceCode);

    for (Token const& token : tokens) {
        std::string tokenType;
        if (token.type == TokenType::IDENTIFIER) {
            tokenType = "IDENTIFIER";
        } else if (token.type == TokenType::NUMBER) {
            tokenType = "NUMBER";
        } else if (token.type == TokenType::SYMBOL) {
            tokenType = "SYMBOL";
        }

        std::cout << "Token Type: " << tokenType << ", Value: " << token.value << std::endl;
    }
    ASSERT_PASS();
END_TEST

BEGIN_TEST(script_test)
    Lexer lexer;
    std::string sourceCode = "sleep 1000 magnetos = 3 throttle = 0.2 \
    mixture = 0.949 masterbat = 1 masterlat = 1 \
    masteravionics = 1 brakeparking = 0 primer = 3 starter = 1 autostart = 1\
    print rpm rpm = 800 sleep 250 while rpm < 750 { print rpm sleep 250}\
    var h0 = heading\
    breaks = 0\
    sleep 10000\
    throttle = 1 while alt < 1500 {\
    rudder = (h0 - heading)/20\
    aileron = - roll / 70\
    elevator = pitch/50\
    print alt\
    sleep 250\
}"; 

    std::vector<Token> tokens = lexer.tokenize(sourceCode);

    for (Token const& token : tokens) {
        std::string tokenType;
        if (token.type == TokenType::IDENTIFIER) {
            tokenType = "IDENTIFIER";
        } else if (token.type == TokenType::NUMBER) {
            tokenType = "NUMBER";
        } else if (token.type == TokenType::SYMBOL) {
            tokenType = "SYMBOL";
        }

        std::cout << "Token Type: " << tokenType << ", Value: " << token.value << std::endl;
    }
    ASSERT_PASS();
END_TEST


TEST_SUITE(因果応報 [inga ōhō: bad causes bring bad results])
    TEST(var_int_test)
    TEST(script_test)

END_SUITE