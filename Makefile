TARGET=blaatbot2025
PCDEV_ROOT=pcdev

CXX_SRC 	+= main.cpp
CXX_SRC 	+= xmlParser.cpp

include $(PCDEV_ROOT)/build/make/all.mk

