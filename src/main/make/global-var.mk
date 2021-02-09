# ALG2-TP1 project Makefile
# Global variables custom definitions.
# ==============================================================

# Compiler command and flags
CXX   := 
FLAGS := 

# Source directory
SOURCE := 

# Source directory direct descendants
SOURCE_MAIN := 
SOURCE_UNIT := 

# Directory of header files
HEADER_MAIN    := 
# Directory of appliance files (e.g. ~.cpp~)
APPLIANCE_MAIN :=

HEADER_UNIT    := 
APPLIANCE_UNIT :=

# Directory of compiled files
BUILD :=

BUILD_MAIN :=
BUILD_UNIT := 

# Project's modules
MODULES := Alg DS Interface Utils

# Files extensions
HEADER_EXTENSION     := 
APP_EXTENSION        := 
OBJECT_EXTENSION     := 
EXECUTABLE_EXTENSION := 

# Leaving these empty will apply the default value
# Check file var_expansions.mk for details
MAIN_FILE := 
TARGET :=

UNIT_MAIN_FILE := 
UNIT_TARGET    := 

# Regarding tests
# These must be manually defined
TEST_SCRIPT        := 
TEST_STEM          := 
TEST_IN_EXTENSION  := 
TEST_OUT_EXTENSION := 
TEST_NUMBER        := 
