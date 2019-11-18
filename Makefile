CXX ?= g++

CXXFLAGS += -Wall
UPDATESRC = emright_fwupdate.cpp

UPDATEOBJ = $(UPDATESRC:.cpp=.o)
PROGNAME = EMRight_FWupdate
STATIC_BUILD ?= n
ifeq ($(STATIC_BUILD), y)
	LDFLAGS += -static
endif

all: $(PROGNAME)

$(PROGNAME): $(UPDATEOBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(UPDATEOBJ) -o $(PROGNAME)

clean:
	rm -f $(UPDATEOBJ) $(PROGNAME)
