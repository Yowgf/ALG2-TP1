# MakeT project Makefile
# Global variables custom definitions.
# ==============================================================

F_ERROR_FUNCTIONS      := $(AUX_MAKE_DIR)/error-functions.mk
F_INSPECTION_FUNCTIONS := $(AUX_MAKE_DIR)/inspection-functions.mk

include $(F_ERROR_FUNCTIONS)
include $(F_INSPECTION_FUNCTIONS)
