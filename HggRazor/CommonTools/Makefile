CXX = $(shell root-config --cxx)
LD = $(shell root-config --ld)

INC=$(shell pwd)


STDINCDIR :=-I$(INC)/include
STDLIBDIR := 

CPPFLAGS := $(shell root-config --cflags) $(STDINCDIR)
LDFLAGS := $(shell root-config --glibs) $(STDLIBDIR) -lRooFit -lRooFitCore

CPPFLAGS += -g

TARGET  = FitMgg
TARGET1 = TestSystematics
TARGET2 = CloneTChiWH

SRC  = app/FitMgg.cc src/SusyHggMggFit.cc
SRC1 = test/TestHggRazorSystematics.cc src/HggRazorSystematics.cc src/HggTree.cc src/HggAux.cc
SRC2  = app/CloneTChiWH.cc

OBJ = $(SRC:.cc=.o)
OBJ1 = $(SRC1:.cc=.o)
OBJ2 = $(SRC2:.cc=.o)

all : $(TARGET) $(TARGET2)

$(TARGET) : $(OBJ)
	$(LD) $(CPPFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)
	@echo $
	@echo $<
	@echo $^

$(TARGET1) : $(OBJ1)
	$(LD) $(CPPFLAGS) -o $(TARGET1) $(OBJ1) $(LDFLAGS)
	@echo $
	@echo $<
	@echo $^

$(TARGET2) : $(OBJ2)
	$(LD) $(CPPFLAGS) -o $(TARGET2) $(OBJ2) $(LDFLAGS)
	@echo $
	@echo $<
	@echo $^

%.o : %.cc
	$(CXX) $(CPPFLAGS) -o $@ -c $<
	@echo $@	
	@echo $<
clean :
	rm -f *.o app/*.o test/*.o src/*.o $(TARGET) $(TARGET1) $(TARGET2) *~

