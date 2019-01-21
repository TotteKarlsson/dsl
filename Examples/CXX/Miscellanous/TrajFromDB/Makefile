SHELL = /bin/sh
BIN_DIR=./../bin/

CLEAN_FILES= *.obj *.o *.exe *.tds *~ *.~* *.lib temp.*

USERLIBS = ./../link_libs/libutils.a
CXX = g++
LIBTOOL = $(SHELL) /usr/bin/libtool
INCLUDES = -I./../utils/ -I./../mysqlpp/ -I/usr/include/mysql/

MYSQLLIB = /usr/lib/libmysqlclient.a
SQLPLUSLIB = ../link_libs/libmysqlpp.a
WARNINGS = -Wall -Wno-deprecated

OBJECTS = dipmysql.o dipmySQLMain.o SQLClient.o 
LDFLAGS = 
#static linking
LDADD =  $(SQLPLUSLIB) $(MYSQLLIB)  -lcrypto -lssl -lz

DEFAULT_INCLUDES =  -I. 

CXXFLAGS = $(WARNINGS)
CXXCOMPILE = $(CXX) $(DEFAULT_INCLUDES) $(INCLUDES) $(CXXFLAGS)
CXXLINK =  $(CXX) $(INCLUDES) $(CXXFLAGS) $(LDFLAGS) -o $@

#.SUFFIXES: .cc .lo .o .obj .cpp
PROJECT = dipmysql

$(PROJECT): $(OBJECTS) 
	$(CXXLINK) $(OBJECTS) $(SQLPLUSLIB) $(USERLIBS) $(LDADD) 

install: prep $(PROJECT)
	cp -f $(PROJECT) $(BIN_DIR)$(PROJECT)

.cc.o:
	$(CXXCOMPILE) -c -o  $@ $<
	
.cpp.o:
	$(CXXCOMPILE) -c -o  $@ $<

clean: 
	rm -f $(CLEAN_FILES) $(BIN_DIR)$(PROJECT) $(PROJECT)

prep:
	mkdir -p $(BIN_DIR)
