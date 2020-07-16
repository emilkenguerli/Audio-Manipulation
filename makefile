CXX=g++ --std=c++11
RM=rm -f
CPPFLAGS=-g $(--cflags)
LDFLAGS=-g $(--ldflags)
LDLIBS=$(--libs)

SRCSTST=Audio.cpp AudioUnitTests.cpp
SRCS=main.cpp Audio.cpp 
OBJSTST=$(subst .cpp,.o,$(SRCSTST))
OBJS=$(subst .cpp,.o,$(SRCS))

all: samp test

samp: $(OBJS)
	$(CXX) $(LDFLAGS) -o samp $(OBJS) $(LDLIBS)

samp.o: main.cpp Audio.cpp

test: $(OBJSTST)
	$(CXX) $(LDFLAGS) -o test $(OBJSTST) $(LDLIBS)

test.o: Audio.cpp

clean:  
	$(RM) $(OBJS) samp test
	$(RM) *.o
