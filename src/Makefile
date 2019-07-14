ROOTCONFIG = root-config

CXX     =$(shell $(ROOTCONFIG) --cxx)
GCC	=$(shell $(ROOTCONFIG) --cc)
CXXFLAGS	= -O2 -Wall -fPIC -Wextra
ROOTCFLAGS:= $(shell $(ROOTCONFIG) --cflags)
ROOTLIBS  := $(shell $(ROOTCONFIG) --libs) -lMinuit
ROOTGLIBS := $(shell $(ROOTCONFIG) --glibs)
ROOTINC :=$(shell $(ROOTCONFIG) --incdir)

CUSTOMDEFINES = -DNOISY
CXXFLAGS+= -g $(CUSTOMDEFINES)
MAKEDEPEND =$(CXX)
INCLUDES = -I$(ROOTINC)

LIBS	:= $(ROOTLIBS)
LDFLAGS := $(shell $(ROOTCONFIG) --ldflags)
LD	:= $(shell $(ROOTCONFIG) --ld)
OBJS	:= \
	TaInput.o TaCollector.o


HDR	:= $(OBJS:.o=.hh) 
DEPS 	:= $(OBJS:.o=.d)

all:  $(OBJS) main.o Collector_Dict collector

Collector_Dict: $(HDR) CollectorLinkDef.h
	rootcint -f $@.cc -c $(INCLUDES) $^;
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $@.cc -o $@.o ;
$(OBJS):
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(@:.o=.cc) -o  $@ ;

main.o: main.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $^ -o $@;

collector:$(OBJS) Collector_Dict.o main.o
	$(LD) $(CXXFLAGS) $(ROOTLIBS) $^ -o $@;
clean:
	rm -f *.o;
	rm -f *Dict*;	

%.d:	%.cc
	@echo Creating dependencies for $<
	@$(SHELL) -ec '$(MAKEDEPEND) -MM $(INCLUDES) -c $< \
	      | sed '\''s%^.*\.o%$*\.o%g'\'' \
	      | sed '\''s%\($*\)\.o[ :]*%\1.o $@ : %g'\'' > $@; \
	      [ -s $@ ] || rm -f $@'

-include $(DEPS)
