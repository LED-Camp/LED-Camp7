CROSS		=
CXX		= $(CROSS)g++
TARGET		= ledtank
TARGET_EX   = ledtank_ex
CFLAGS	    = -Wall -O0 -std=c++11
SRCS	    = $(wildcard *.cpp)
OBJS	 = $(SRCS:.cpp=.o)
OBJS_EX = $(SRCS:.cpp=_ex.o)



OBJDIR		= .
SRCDIR		= .

#INCLUDES	= -I..

INCLUDES	= -I../VL53L0X_rasp/platform/inc
INCLUDES	+= -I../VL53L0X_1.0.2/Api/core/inc
LIBS		= -lwiringPi -lpthread -lpaho-mqtt3c
LIBS		+= -lVL53L0X_Rasp

.PHONY: production
production: $(OBJS) $(TARGET)
$(TARGET): $(OBJS)
	$(CXX) -L../VL53L0X_rasp/bin -o $@ $(OBJS) $(LIBS)
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX)  $(CFLAGS) $(INCLUDES) -o $@ -c $< 


.PHONY: experiment
experiment: $(OBJS_EX) $(TARGET_EX)
	rm -rf $(OBJS_EX)
$(TARGET_EX): $(OBJS_EX)
	$(CXX) -L../VL53L0X_rasp/bin -o $@ $(OBJS_EX) $(LIBS)
$(OBJDIR)/%_ex.o: $(SRCDIR)/%.cpp
	$(CXX) -D 'EXPERIMENTAL_USE' $(CFLAGS) $(INCLUDES) -o $@ -c $<  

.PHONY: clean
clean:
	rm -rf $(TARGET) $(TARGET_EX) $(OBJS) $(OBJS_EX)

