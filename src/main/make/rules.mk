# ALG2-TP1 project Makefile
# Rules definition Makefile
# ==============================================================

# Links objects. Put first to avoid errors with .DEFAULT_GOAL assignment.
$(TARGET) : $(TARGET_DEPENDENCIES)
	$(info Linking code...)
	$(LINK_CODE)

# The --parents switch here allows to automatically create parent directories when needed.
$(OBJECT_MOD_DIRS) ::
	@-mkdir --parents $@

# Compiles objects.
$(BUILD_MAIN)/%$(OBJECT_EXTENSION) :: $(APPLIANCE_MAIN)/%$(APP_EXTENSION) $(HEADER_MAIN)/%$(HEADER_EXTENSION)
	$(COMPIL_OBJECT_CODE_MAIN)

$(BUILD_UNIT)/%$(OBJECT_EXTENSION) :: $(APPLIANCE_UNIT)/%$(APP_EXTENSION) $(HEADER_UNIT)/%$(HEADER_EXTENSION)
	$(COMPIL_OBJECT_CODE_UNIT)

# Deletes all the directories supposed to contain objects.
.PHONY : clean unit test
clean ::
ifneq "$(origin OBJECT_DIRS)" "file"
		$(info Variable "OBJECT_DIRS" used for "clean" left undefined.)
		$(info Please check the file in $(GLOBAL_VARS))
else
		$(eval OBJECT_DIRS := $(wildcard $(OBJECT_DIRS) $(TARGET)))
ifneq ($(strip $(OBJECT_DIRS)),)
		$(info Deleting all the directories and subfolders:)
		$(info $(OBJECT_DIRS))
		@echo
		@echo Are you sure? \(Y/N\)
		@read choice && \
		if [[ "$$choice" = "y" ]] || [[ "$$choice" = "Y" ]]; then \
		{ ( $(foreach dir, $(OBJECT_DIRS), rm --verbose --preserve-root --recursive --force "$(dir)"; ) ) && \
			echo Cleaning successful.; } || \
			$(call e_prev_cmd, Cleaning of some directory failed.) \
		else \
		echo No cleaning was performed.; \
		fi
endif
endif

# Performs the various unit tests available
unit :: $(UNIT_TARGET_DEPENDENCIES)
	$(UNIT_LINK_CODE)

# Tests the program against set of entries and expected outputs
# Then measures times to local csv file
test ::
ifeq "$(wildcard $(TARGET) $(TARGET).$(EXECUTABLE_EXTENSION))" ""
	$(MAKE)
endif
	@bash $(TEST_SCRIPT) $(TEST_STEM) $(TEST_IN_EXTENSION) $(TEST_OUT_EXTENSION) $(TEST_NUMBER)

# Sink for unidentified patterns.
% ::
	@echo Archive or Pattern "$@" not found!
