OBJDIR		= .
SRCDIR		= .

CROSS		=
CXX		= $(CROSS)g++
CC		= $(CROSS)gcc
TARGET		= ledtank
TARGET_EX   = ledtank_ex
CFLAGS	    = -Wall -O0 
CXXFLAGS	    = -Wall -O0 -std=c++11
SRCS := $(shell find $(SRCDIR) -name "*.cpp" -or -name "*.c" )
OBJS := $(SRCS:%=$(OBJDIR)/%.o)
OBJS_EX := $(SRCS:%=$(OBJDIR)/%_ex.o)	


#INCLUDES	= -I..

INCLUDES	= -I../VL53L0X_rasp/platform/inc
INCLUDES	+= -I../VL53L0X_1.0.2/Api/core/inc
LIBS		= -lwiringPi -lpthread 
LIBS		+= -lVL53L0X_Rasp

.PHONY: production
production: $(OBJS) $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) -g -L../VL53L0X_rasp/bin -o $@ $(OBJS) $(LIBS)
$(OBJDIR)/%.cpp.o: $(SRCDIR)/%.cpp
	$(CXX) -g  $(CXXFLAGS) $(INCLUDES) -o $@ -c $<
$(OBJDIR)/%.c.o: $(SRCDIR)/%.c
	$(CC) -g  $(CFLAGS) $(INCLUDES) -o $@ -c $<


.PHONY: experiment
experiment: $(OBJS_EX) $(TARGET_EX)
	rm -rf $(OBJS_EX)
$(TARGET_EX): $(OBJS_EX)
	$(CXX) -g -L../VL53L0X_rasp/bin -o $@ $(OBJS_EX) $(LIBS)
$(OBJDIR)/%.cpp_ex.o: $(SRCDIR)/%.cpp
	$(CXX) -g -D 'EXPERIMENTAL_USE' $(CXXFLAGS) $(INCLUDES) -o $@ -c $<
$(OBJDIR)/%.c_ex.o: $(SRCDIR)/%.c
	$(CC) -g -D 'EXPERIMENTAL_USE' $(CFLAGS) $(INCLUDES) -o $@ -c $<


.PHONY: clean
clean:
	rm -rf $(TARGET) $(TARGET_EX) $(OBJS) $(OBJS_EX)

