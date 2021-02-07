# ALG2-TP1 project Makefile
# Global variables custom definitions.
# ==============================================================

# Compiler command and flags
CXX   := 
FLAGS := 

# Source directory
SOURCE := 

# ~SOURCE~ descendants
# If you want to add more directories as children of ~SOURCE~,
#   add them to this variable, then add the variable definitions
#   by themselves.
# For example:
# ------------------------------------------------
# SOURCE_VAL_NAMES := HEADER APPLIANCE THIRD-PARTY
# HEADER := include
# APPLIANCE := app
# THIRD-PARTY := third-party
# ------------------------------------------------
SOURCE_VAL_NAMES :=

# Source directory direct descendants
SOURCE_MAIN := 
SOURCE_UNIT := 

SOURCE_MAIN_VAL_NAMES := 

# Directory of header files
HEADER      := 
# Directory of appliance files (e.g. ~.cpp~)
APPLIANCE   :=

SOURCE_UNIT_VAL_NAMES := 

# Directory of compiled files
BUILD := 

# Project's modules
MODULES := Alg Interface Utils

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
