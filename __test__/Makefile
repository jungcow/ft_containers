.PHONY		:	all re fclean clean

NAME		=	container_tester
INC			=	-I./global \
				-I./containers/base\
				-I./containers/vector\
				-I./containers/vector/method\
				-I./containers/map

CXX			=	clang++

CXXFLAGS	=	-pedantic\
				-std=c++11 #-D TYPE=1

LFLAGS		=	#-lgtest -lgtest_main

EXTRA_SRCS	=	$(addprefix ./srcs/, \
					type.cpp \
				)

SRCS		=	./main.cpp\
				$(EXTRA_SRCS)

OBJS		=	$(SRCS:.cpp=.o)

DEPS		=	$(OBJS:.o=.d)

%.o			:	%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@ -MD

all			:	$(NAME)

$(NAME)		:	$(OBJS)
	$(CXX) $(INC) $(CXXFLAGS) -o $@ $^

clean		:
	rm -rf $(OBJS) $(DEPS)

fclean		:	clean
	rm -rf $(NAME)

re			:
	make fclean
	make all

test		:
	make && ./container_tester

-include $(DEPS)
