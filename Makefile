VERBOSE ?= 0
BOARD ?= atmega328
PORT ?= /dev/ttyUSB3
#LIB_DIRS += .
LIB_DIRS += ${PWD}/uTPLib
LIB_DIRS += ${PWD}/dcf77
include Makefile.master
