GOOGLE_TEST_LIB = gtest
GOOGLE_TEST_INCLUDE = /usr/local/include

G++ = g++
G++_FLAGS = -c -g -Wall -I $(GOOGLE_TEST_INCLUDE)
LD_FLAGS = -L /usr/local/lib -l $(GOOGLE_TEST_LIB) -l pthread

OBJECTS = main.o Executive.o Data.o Scene.o MXVI.o Correlations.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJECTS)
	g++ -o $(TARGET) $(OBJECTS) $(LD_FLAGS)

%.o : %.cpp
	$(G++) $(G++_FLAGS) $<

clean:
	rm -f $(TARGET) $(OBJECTS)
                    
.PHONY: all clean

# CC=g++
# CFLAGS=-c -Wall
# LDFLAGS=
# SOURCES=main.cpp Executive.cpp Data.cpp Scene.cpp MXVI.cpp
# OBJECTS=$(SOURCES:.cpp=.o)
# EXECUTABLE=exec

# all: $(SOURCES) $(EXECUTABLE)

# $(EXECUTABLE): $(OBJECTS)
# 	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# .cpp.o:
# 	$(CC) $(CFLAGS) $< -o $@
