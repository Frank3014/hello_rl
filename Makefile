#*****************************************************************************
# Compiler and assembler
#*****************************************************************************
CC=gcc
CXX=g++
LD=g++

#*****************************************************************************
# Object files
#*****************************************************************************
SRCROOT		= .
OBJDIR          = $(SRCROOT)/Release

INCLUDES        += -I$(SRCROOT)

DIRS 		:= $(shell find . -maxdepth 3 -type d)
CSRC 		+= $(foreach dir,$(DIRS),$(wildcard $(dir)/*.c))
CCSRC		+= $(foreach dir,$(DIRS),$(wildcard $(dir)/*.cc))
CPPSRC	 	+= $(foreach dir,$(DIRS),$(wildcard $(dir)/*.cpp))

COBJS=$(CSRC:.c=.o)
CCOBJS=$(CCSRC:.cc=.o)
CPPOBJS=$(CPPSRC:.cpp=.o)

OBJS+=$(COBJS)
OBJS+=$(CCOBJS)
OBJS+=$(CPPOBJS)

CXXFLAG += $(INCLUDES) -std=c++11 -Wall -O2

LIBS +=-lncurses -lstdc++

all: flappy_bird 

flappy_bird : $(OBJS)
	$(CC) -o $(OBJDIR)/$@ $(LDFLAGS) $(addprefix $(OBJDIR)/, $(OBJS)) $(LIBS)

%.o:%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CXXFLAG) -c -o $(OBJDIR)/$@ $<

%.o:%.cc
	@mkdir -p $(OBJDIR)
	$(CC) $(CXXFLAG) -c -o $(OBJDIR)/$@ $<

%.o:%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) $(CXXFLAG) -c -o $(OBJDIR)/$@ $<

clean:
	rm -rf $(addprefix $(OBJDIR)/, $(OBJS)) $(addprefix $(OBJDIR)/, flappy_bird)
