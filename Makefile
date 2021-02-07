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
AUX_MAKE_DIR       := src/main/make
F_CUSTOM_FUNCTIONS := $(AUX_MAKE_DIR)/custom-functions.mk
F_GLOBAL_VARS      := $(AUX_MAKE_DIR)/global-var.mk
F_VAR_EXPANSION    := $(AUX_MAKE_DIR)/var-expansions.mk
F_RULES            := $(AUX_MAKE_DIR)/rules.mk

# This function is defined here due to its most essential character.
# The idea is not to use "include" unless you are certain all files
#   exist.
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

# Informs global variables
include $(F_GLOBAL_VARS)

# Informs custom functions
include $(F_CUSTOM_FUNCTIONS)

# Expands variables
include $(F_VAR_EXPANSION)
# Informs rules
include $(F_RULES)
