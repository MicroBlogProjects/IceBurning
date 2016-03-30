
ARFLAGS = cr
CPPFLAGS= -g -O2 -Wall -Werror -fPIC

DEBUG_TARGET_DIR = ../Lib
DEBUG_TARGET = $(DEBUG_TARGET_DIR)/libCommon.a
TARGET	= $(DEBUG_TARGET)

OBJ_DIR	= ../.objs

SRC = $(wildcard *.cpp)
OBJS = $(addprefix $(OBJ_DIR)/,$(subst .cpp,.o,$(SRC)))

all : $(TARGET)

$(TARGET) : $(OBJS)
	@if [ ! -e $(DEBUG_TARGET_DIR) ]; then \
		mkdir -p $(DEBUG_TARGET_DIR); \
	fi
	ar $(ARFLAGS) $@ $?

$(OBJ_DIR)/%.o : %.cpp
	g++ $(CPPFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJS) $(TARGET)
