# ~PROJECT~ project Makefile
# Variable expansions Makefile
# ==============================================================

# List of all global variables that are expected to be
#   customized according to the use of the user.
GLOBAL_VAR_LIST := CXX FLAGS HEADER APPLIANCE BUILD \
  MODULES HEADER_EXTENSION APP_EXTENSION OBJECT_EXTENSION \
  EXECUTABLE_EXTENSION MAIN_FILE TARGET

# Set defaults of some variables (format DEFAULT_<VAR_NAME>)
DEFAULT_CXX   := g++
DEFAULT_FLAGS := -std=c++11 -Wall

DEFAULT_SOURCE           := src
DEFAULT_SOURCE_VAL_NAMES := HEADER APPLIANCE

DEFAULT_HEADER    := header
DEFAULT_APPLIANCE := appliance
DEFAULT_BUILD     := build

DEFAULT_MODULES :=

DEFAULT_HEADER_EXTENSION     := hpp
DEFAULT_APP_EXTENSION        := cpp
DEFAULT_OBJECT_EXTENSION     := o
DEFAULT_EXECUTABLE_EXTENSION := exe

DEFAULT_MAIN_FILE := $(SOURCE)/$(APPLIANCE)/main.$(APP_EXTENSION)
DEFAULT_TARGET    := $(BUILD)/main.$(EXECUTABLE_EXTENSION)

# This call only affects those variables that have a default
#   value defined.
$(call lp_apply_defaults, $(GLOBAL_VAR_LIST))

# Checks definition of global variables.
# Function from inspection-functions file ~i_check_vars~ used here.
GLOBAL_VAR_STATUS :=  $(shell $(call i_check_vars, $(GLOBAL_VAR_LIST)))
temp_status := $(lastword $(GLOBAL_VAR_STATUS))
ifneq "$(temp_status)" "0"
  $(call e_fatal, $(temp_status) undefined global variables: \
    $(wordlist 1, $(temp_status), $(GLOBAL_VAR_STATUS)). \
    Verify file $(F_GLOBAL_VARS))
endif
undefine temp_status

# An empty space character
define C_SP =
 
endef

# A newline character
define C_NL :=


endef

# Adding prefix to directories inside ~$(SOURCE)~
$(eval \
$(foreach src_dir, $(SOURCE_VAL_NAMES),\
override $(src_dir) := $(SOURCE)/$($(src_dir))$(C_NL)) \
)

vpath %.$(APP_EXTENSION) $(patsubst %, $(APPLIANCE)/%, $(MODULES))

# Header files list
HEADER_FILES := $(wildcard $(patsubst %, $(HEADER)/%/*.$(HEADER_EXTENSION), $(MODULES)))
# Appliance files list
APPLIANCE_FILES := $(wildcard $(patsubst %, $(APPLIANCE)/%/*.$(APP_EXTENSION), $(MODULES)))

# Searches for files with ~$(OBJECT_EXTENSION)~ extension
OBJECT_FILES := $(patsubst $(APPLIANCE)%$(APP_EXTENSION), $(BUILD)%$(OBJECT_EXTENSION), $(APPLIANCE_FILES))

# Compiled files directory list
OBJECT_DIRS := $(BUILD)

# Command for compiling each object
COMPIL_OBJECT_CODE = $(CXX) $(FLAGS) -I $(HEADER) -c $< -o $@
# Links objects
LINK_CODE = $(CXX) $(FLAGS) -I $(HEADER) $(OBJECT_FILES) $(MAIN_FILE) -o $@

# For use in creating directories rule
#-- Do not use "/" in the end!
#-- Otherwise it won't recognize the directory's existance.
OBJECT_MOD_DIRS  := $(foreach mod, $(MODULES), $(patsubst %, %/$(mod), $(OBJECT_DIRS)))
BUILD_MODS       := $(patsubst %, $(BUILD)/%, $(MODULES))
