CROSS		=
CXX		= $(CROSS)g++
TARGET		= ledtank
CFLAGS		= -Wall -O0
SRCS		= $(wildcard *.cpp)
OBJS		= $(SRCS:.cpp=.o)


OBJDIR		= .
SRCDIR		= .

#INCLUDES	= -I..

INCLUDES	= -I../VL53L0X_rasp/platform/inc
INCLUDES	+= -I../VL53L0X_1.0.2/Api/core/inc
LIBS		= -lwiringPi -lpthread -lpaho-mqtt3c
LIBS		+= -lVL53L0X_Rasp

.PHONY: all
all: $(OBJS) $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -L../VL53L0X_rasp/bin -o $@ $(OBJS) $(LIBS)

#$(OBJS): $(SRCS)
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -o $@ -c $<

.PHONY: clean
clean:
	rm -rf $(TARGET) $(OBJS)

#rctank: rctank.cpp main.cpp
#	g++ -Wall -o rctank rctank.cpp main.cpp -lwiringPi -lpthread
