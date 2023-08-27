CXX = g++
CC = $(CXX)

CXXFLAGS = -pedantic -Wall -Werror -Wextra -g3 -std=c++17
CPPFLAGS = -DDEBUG -I$(INCLUDES_DIR) -I$(SOURCES_DIR) 

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

OBJS = utest.o $(SOURCES_DIR)/lexer.o
TARGET = utest

all: $(TARGET)

check: $(TARGET)
	@./$(TARGET) -v

recheck: clean check

clang_check: CXX = clang++
clang_check: check

clean:
	@$(RM) $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) -lpthread -lpugixml

utest.o: $(INCLUDES_DIR)/mu_test.h $(INCLUDES_DIR)/lexer.hpp 

$(SOURCES_DIR)/lexer.o: $(INCLUDES_DIR)/lexer.hpp 

.PHONY: all check recheck clang_check clean