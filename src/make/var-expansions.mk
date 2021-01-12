# MakeT project Makefile
# Variable expansions Makefile
# ==============================================================

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

# To be used in compilation rules
ifeq "$(origin, TARGET)" "undefined"
  TARGET := $(BUILD)/Main.$(EXECUTABLE_EXTENSION)

endif

# Main file source
MAIN_FILE = $(patsubst $(BUILD)%$(EXECUTABLE_EXTENSION),$(APPLIANCE)%$(APP_EXTENSION), build/Main.exe)

# Command for compiling each object
COMPIL_OBJECT_CODE = $(CXX) $(FLAGS) -I $(HEADER) -c $< -o $@
# Links objects
LINK_CODE = $(CXX) $(FLAGS) -I $(HEADER) $(OBJECT_FILES) $(MAIN_FILE) -o $@

# For use in creating directories rule
#-- Do not use "/" in the end!
#-- Otherwise it won't recognize the directory's existance.
OBJECT_MOD_DIRS  := $(foreach mod, $(MODULES), $(patsubst %, %/$(mod), $(OBJECT_DIRS)))
BUILD_MODS       := $(patsubst %, $(BUILD)/%, $(MODULES))
