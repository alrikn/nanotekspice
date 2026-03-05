##
## EPITECH PROJECT, 2025
## nanotekspice
## File description:
## Makefile
##

NAME = nanotekspice
SRC = main.cpp	\
	src/circuit_handler/operator.cpp \
	src/circuit_handler/HashMapCache.cpp \
	src/circuit_handler/Circuit.cpp \
	src/components/AComponent.cpp \
	src/components/AGateComponent.cpp \
	src/components/advanced_components/Component2716.cpp \
	src/components/advanced_components/Component4008.cpp \
	src/components/advanced_components/Component4013.cpp \
	src/components/advanced_components/Component4040.cpp \
	src/components/advanced_components/Component4512.cpp \
	src/components/advanced_components/FlipFlopComponent.cpp \
	src/components/elementary_components/AndComponent.cpp \
	src/components/elementary_components/LoggerComponent.cpp \
	src/components/elementary_components/NandComponent.cpp \
	src/components/elementary_components/NotComponent.cpp \
	src/components/elementary_components/NorComponent.cpp \
	src/components/elementary_components/OrComponent.cpp \
	src/components/elementary_components/XorComponent.cpp \
	src/components/input_components/ClockComponent.cpp \
	src/components/input_components/FalseComponent.cpp \
	src/components/input_components/TrueComponent.cpp \
	src/components/input_components/UserInputComponent.cpp \
	src/components/input_components/UserOutputComponent.cpp \
	src/components/gate_components/Component4001.cpp \
	src/components/gate_components/Component4011.cpp \
	src/components/gate_components/Component4030.cpp \
	src/components/gate_components/Component4069.cpp \
	src/components/gate_components/Component4071.cpp \
	src/components/gate_components/Component4081.cpp \
	src/parser/Parser.cpp \
	src/main_loop.cpp \


OBJ = $(SRC:.cpp=.o)
CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -g
CPPFLAGS = -I include -I include/gate_components -I include/input_components -I include/elementary_components -I include/advanced_components

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $(NAME) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
