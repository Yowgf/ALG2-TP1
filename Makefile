# MakeT project Makefile
# Main Makefile
# ===============================================================
#
# This makefile tries to cover the options of normal compilation
#   (not really useful in this case), and test compilation, which
#   runs all the tests especified for each class.
# ---------------------------------------------------------------
#
# Options:
#
# "TARGET=..." -------------- lets you specify file names
#
# clean --------------------- cleaning built files rule
# ---------------------------------------------------------------
SHELL := /bin/bash

# Auxiliary makefiles addresses
ALL_FILES_VARS     := F_CUSTOM_FUNCTIONS F_GLOBAL_VARS F_VAR_EXPANSION \
                      F_RULES
AUX_MAKE_DIR       := src/make
F_CUSTOM_FUNCTIONS := $(AUX_MAKE_DIR)/custom-functions.mk
F_GLOBAL_VARS      := $(AUX_MAKE_DIR)/global-var.mk
F_VAR_EXPANSION    := $(AUX_MAKE_DIR)/var-expansions.mk
F_RULES            := $(AUX_MAKE_DIR)/rules.mk

# This function is defined here due to its most essential character.
define i_check_files =
	for file_var in $(foreach file, $(1), $($(file))); do
		if [[ ! -e "$$file_var" ]]; then
			echo "$$file_var 1";
			exit 1;
		fi
	done;
	echo 0
endef

FILE_VAR_STATUS := $(shell $(call i_check_files, $(ALL_FILES_VARS)))
ifneq "$(lastword $(FILE_VAR_STATUS))" "0"
  $(error Essential file "$(word 1, $(FILE_VAR_STATUS))" not found.)
endif

# Informs custom functions
include $(F_CUSTOM_FUNCTIONS)
# Informs global variables
include $(F_GLOBAL_VARS)

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

# Expands variables
include $(F_VAR_EXPANSION)
# Informs rules
include $(F_RULES)
