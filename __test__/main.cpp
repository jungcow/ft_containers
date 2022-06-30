#include <iostream>
#include <vector>

#include "containers/vector/vector_tester.hpp"
#include "global/tester.hpp"

using namespace Test;

void hello(void)
{
	system("leaks container_tester");
}

int main(void)
{
#if LEAKS
	atexit(hello);
#endif

	Tester<VectorTester> vtester;
	std::vector<double> vec(10, 8);
	std::vector<double>::iterator vi;
	std::vector<double>::iterator from;
	std::vector<double>::iterator to;

	vi = vec.begin() + 1;
	from = vec.begin() + 2;
	to = vec.end() - 3;

	std::cout << vec.size() << std::endl;

	std::cout << vtester->erase()
					 .given(vec)
					 .when(vi)
					 .info<NANOSECONDS>()
			  << std::endl;

	std::cout << vec.size() << std::endl;

	std::cout << vtester->erase()
					 .given(vec)
					 .when(from, to)
					 .info<NANOSECONDS>()
			  << std::endl;

	std::cout << vec.size() << std::endl;
}

#if 0
.PHONY		: all re clean fclean
NAME			=	ScalarConversion
CXX				=	clang++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98

SRCS			=	main.cpp \
						ScalarType.cpp \
						detectScalarType.cpp \
						convertScalarType.cpp \
						outputScalarType.cpp

OBJS			=	$(SRCS:.cpp=.o)

DEPS			=	$(OBJS:.o=.d)

all				:	$(NAME)

$(NAME)		:	$(OBJS)
					$(CXX) $(CXXFLAGS) $^ -o $@

%.o				:	%.cpp
					$(CXX) $(CXXFLAGS) -c $< -o $@ -MD

clean			:
					rm -rf $(OBJS) $(DEPS)

fclean		:	clean
					rm -rf $(NAME)

re				:	fclean all

-include $(DEPS)

#endif