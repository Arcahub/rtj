CXX	= g++

AR = ar -rc

NAME = libjzon.a

CXXFLAGS = -W -Wall -Wextra -I./include

SRC = $(shell find src/ -type f -name '*.cpp')

TEST_SRC = $(shell find test/src -type f -name '*.cpp')

OBJ = $(SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $@ $(OBJ)

debug: CXXFLAGS += -g3
debug: all

clean:
	rm -rf $(OBJ)
	rm -rf $(TEST_OBJ)
	rm -rf **/*.gcda
	rm -rf **/*.gcno

fclean: clean
	rm -rf $(NAME)
	rm -rf unit_tests

re: fclean all

tests_run: CXXFLAGS += -lcriterion --coverage
tests_run: re $(TEST_OBJ)
	$(CXX) -o unit_tests $(TEST_OBJ) $(CXXFLAGS) -L./ -ljzon
	./unit_tests