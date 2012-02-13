BOARD ?= atmega328
PORT ?= /dev/ttyUSB3
#LIB_DIRS += .
LIB_DIRS += ${PWD}/uTPLib
include Makefile.master
