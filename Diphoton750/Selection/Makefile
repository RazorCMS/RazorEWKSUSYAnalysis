CXX = $(shell root-config --cxx)
LD = $(shell root-config --ld)

INC = $(shell pwd)
Repo = $(shell git rev-parse --show-toplevel)
Aux = $(Repo)/Aux
Diphoton750 = $(Repo)/Diphoton750
CommonTools = $(Diphoton750)/CommonTools

CPPFLAGS := $(shell root-config --cflags) -I$(INC)/include -I$(CommonTools)/include -I$(Aux)/include
LDFLAGS := $(shell root-config --glibs) $(STDLIBDIR)

CPPFLAGS += -g -std=c++11

TARGET = MakeSelection
TARGET2 = PrintEventInfo

SRC = app/MakeSelection.cc src/HggTree.cc src/HggRazorClass.cc $(CommonTools)/src/HggAux.cc $(Aux)/src/CommandLineInput.cc $(Aux)/src/TChainTools.cc
SRC2 = app/PrintEventInfo.cc $(CommonTools)/src/HggTree.cc src/HggRazorClass.cc $(CommonTools)/src/HggAux.cc $(Aux)/src/CommandLineInput.cc $(Aux)/src/TChainTools.cc

OBJ = $(SRC:.cc=.o)
OBJ2 = $(SRC2:.cc=.o)

all : $(TARGET) $(TARGET2)

$(TARGET) : $(OBJ)
	$(LD) $(CPPFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

$(TARGET2) : $(OBJ2)
	$(LD) $(CPPFLAGS) -o $(TARGET2) $(OBJ2) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

%.o : %.cc
	$(CXX) $(CPPFLAGS) -o $@ -c $<
	@echo $@
	@echo $<
clean :
	rm -f *.o app/*.o src/*.o $(CommonTools)/src/*.o $(Aux)/src/*.o $(TARGET) $(TARGET2) *~
