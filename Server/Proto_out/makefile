
CPPFLAGS= -g -O2 -Wall -Werror -fPIC

TARGET	= $(DEBUG_TARGET_DIR)/libProto_out.a

DEBUG_TARGET_DIR = ../Lib/

OBJ_DIR	= ../.objs/Proto_out
SRC = $(wildcard *.cpp)
OBJS = $(addprefix $(OBJ_DIR)/,$(subst .cpp,.o,$(SRC)))


all : $(TARGET)

$(TARGET) : $(OBJS)
	@if [ ! -e $(DEBUG_TARGET_DIR) ]; then \
		mkdir -p $(DEBUG_TARGET_DIR); \
	fi
	ar cr $@ $?

$(OBJ_DIR)/%.o : %.cpp
	@if [ ! -e $(OBJ_DIR) ]; then \
		mkdir $(OBJ_DIR); \
	fi
	$(CXX) $(CPPFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJS) $(TARGET)
