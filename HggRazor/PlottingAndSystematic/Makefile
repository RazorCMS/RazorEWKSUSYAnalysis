CXX = $(shell root-config --cxx)
LD = $(shell root-config --ld)

INC = $(shell pwd)
Repo = $(shell git rev-parse --show-toplevel)
Aux = $(Repo)/Aux
HggRazor = $(Repo)/HggRazor
Selection = $(HggRazor)/Selection
CommonTools = $(HggRazor)/CommonTools

CPPFLAGS := $(shell root-config --cflags) -I$(INC)/include -I$(CommonTools)/include -I$(Aux)/include -I$(Selection)/include
LDFLAGS := $(shell root-config --glibs) $(STDLIBDIR)

CPPFLAGS += -g -std=c++11

TARGET  = PlotCustomMrRsq
TARGET2 = PlotFromTree
TARGET3 = PlotFromInclusiveTree
TARGET4 = GetHggRazorSystematics

SRC = app/PlotCustomMrRsq.cc $(CommonTools)/src/HggAux.cc $(Aux)/src/CommandLineInput.cc $(Aux)/src/TChainTools.cc $(Aux)/src/PlotCosmetics.cc

SRC2 = app/PlotFromTree.cc $(CommonTools)/src/HggTree.cc $(Selection)/src/HggRazorClass.cc $(CommonTools)/src/HggAux.cc $(Aux)/src/CommandLineInput.cc $(Aux)/src/TChainTools.cc $(Aux)/src/PlotCosmetics.cc

SRC3 = app/PlotFromInclusiveTree.cc $(CommonTools)/src/HggTree.cc $(Selection)/src/HggRazorClass.cc $(CommonTools)/src/HggAux.cc $(Aux)/src/CommandLineInput.cc $(Aux)/src/TChainTools.cc $(Aux)/src/PlotCosmetics.cc

SRC4 = app/GetHggRazorSystematics.cc $(CommonTools)/src/HggRazorSystematics.cc $(CommonTools)/src/HggTree.cc $(CommonTools)/src/HggAux.cc $(Aux)/src/CommandLineInput.cc

OBJ  = $(SRC:.cc=.o)
OBJ2 = $(SRC2:.cc=.o)
OBJ3 = $(SRC3:.cc=.o)
OBJ4 = $(SRC4:.cc=.o)

all : $(TARGET) $(TARGET2) $(TARGET3) $(TARGET4)

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

$(TARGET3) : $(OBJ3)
	$(LD) $(CPPFLAGS) -o $(TARGET3) $(OBJ3) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

$(TARGET4) : $(OBJ4)
	$(LD) $(CPPFLAGS) -o $(TARGET4) $(OBJ4) $(LDFLAGS)
	@echo $@
	@echo $<
	@echo $^

%.o : %.cc
	$(CXX) $(CPPFLAGS) -o $@ -c $<
	@echo $@
	@echo $<
clean :
	rm -f *.o app/*.o src/*.o $(Selection)/src/*.o $(CommonTools)/src/*.o $(Aux)/src/*.o $(TARGET) $(TARGET2) $(TARGET3) $(TARGET4) *~
