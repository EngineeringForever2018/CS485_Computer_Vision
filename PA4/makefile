CC = g++
SRCDIR := src
BUILDDIR := ./build
TARGET := ./main

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -Wall -std=c++11
#CFLAGS += -g`
LIB := -L/opt/local/lib -lopencv_calib3d -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_core
INC := -I include -I /opt/local/include

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $(TARGET) $(LIB) 

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c -o $@ $< $(INC)

clean:
	$(RM) -r $(BUILDDIR) $(TARGET) ./test/output* output.csv
