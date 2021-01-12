# MakeT project Makefile
# Global variables custom definitions.
# ==============================================================

GLOBAL_VAR_LIST := CXX FLAGS HEADER APPLIANCE BUILD \
  MODULES HEADER_EXTENSION APP_EXTENSION OBJECT_EXTENSION \
  EXECUTABLE_EXTENSION TARGET

# Compiler flags
CXX   := g++
FLAGS := -std=c++11 -Wall

# Source directory
SOURCE := src

# ~Source~ descendants
SOURCE_VAL_NAMES := HEADER APPLIANCE
# Directory of header files
HEADER      := header
# Directory of appliance files (e.g. ~.cpp~)
APPLIANCE   := appliance

# Directory of compiled files
BUILD       := build

# Project's modules
MODULES := Containers JPI Utils

# Files extensions
HEADER_EXTENSION     := hpp
APP_EXTENSION        := cpp
OBJECT_EXTENSION     := o
EXECUTABLE_EXTENSION := exe

TARGET := $(BUILD)/Main.exe

# Regarding tests
TEST_SCRIPT        := run-tests.sh
TEST_STEM          := EX
TEST_IN_EXTENSION  := in
TEST_OUT_EXTENSION := out
TEST_NUMBER        := 9
