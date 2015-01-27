## Process this file with automake to produce Makefile.in
noinst_PROGRAMS = client RadiusServer
client_SOURCES = client.cpp
client_LDADD = ../ace-radius/libace-radius.a \
	       -lssl \
	       ../log4cxx/lib/liblog4cxx.a -llog4cxx \
	       ../apr-util/lib/libaprutil-1.a -laprutil-1 -lexpat \
	       ../apr/lib/libapr-1.a -lapr-1 \
	       -lpthread
client_LDFLAGS = -L ../log4cxx/lib -L ../apr-util/lib -L ../apr/lib
RadiusServer_SOURCES = server.cpp 
RadiusServer_LDADD = ../ace-radius/libace-radius.a \
	       -lssl \
	       ../log4cxx/lib/liblog4cxx.a -llog4cxx \
	       ../apr-util/lib/libaprutil-1.a -laprutil-1 -lexpat \
	       ../apr/lib/libapr-1.a -lapr-1 \
	       -lpthread
AM_CPPFLAGS = -I ../log4cxx/include/ \
	   -I ../apr-util/include/ \
           -I ../apr/include/
RadiusServer_LDFLAGS = -L ../log4cxx/lib -L ../apr-util/lib -L ../apr/lib

