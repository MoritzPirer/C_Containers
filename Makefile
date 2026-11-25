
CC          ?= clang
AR          ?= ar
ARFLAGS     := rcs

LIB_NAME    ?= containers
BUILD_DIR   := build
LIB_ARCHIVE := $(BUILD_DIR)/lib$(LIB_NAME).a

LIB_SRCS    := $(shell find src -name '*.c' 2>/dev/null | LC_ALL=C sort)
TEST_SRCS   := $(shell find test -name 'test_*.c' 2>/dev/null | LC_ALL=C sort)

# Map source paths to build paths, preserving subdirectories
LIB_OBJS    := $(patsubst %.c,$(BUILD_DIR)/%.o,$(LIB_SRCS))
TEST_OBJS   := $(patsubst %.c,$(BUILD_DIR)/%.o,$(TEST_SRCS))
TEST_BINS   := $(patsubst test/%.c,$(BUILD_DIR)/test/%,$(TEST_SRCS))

DEPS        := $(LIB_OBJS:.o=.d) $(TEST_OBJS:.o=.d)

TEST_RUNNER := $(BUILD_DIR)/testrunner

STD_FLAGS   := -std=c17 -Wall -Wextra -Wpedantic
CPPFLAGS    := -I. -Iinclude -Isrc -MMD -MP
CFLAGS      ?= $(STD_FLAGS) -O2 -g
TEST_CFLAGS := $(CFLAGS) -Werror=unused-function
LDFLAGS     :=
LDLIBS      :=

.PHONY: all debug test clean

all: $(LIB_ARCHIVE)

debug: CFLAGS := $(STD_FLAGS) -O0 -g3
debug: $(LIB_ARCHIVE)

# Library
$(LIB_ARCHIVE): $(LIB_OBJS)
	@mkdir -p $(dir $@)
	$(AR) $(ARFLAGS) $@ $^

$(BUILD_DIR)/src/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Individual test object files
$(BUILD_DIR)/test/%.o: test/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(TEST_CFLAGS) -c $< -o $@

# Individual test executables
$(BUILD_DIR)/test/%: $(BUILD_DIR)/test/%.o $(LIB_ARCHIVE)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LDFLAGS) $< $(LIB_ARCHIVE) -o $@ $(LDLIBS)

# Test runner
$(TEST_RUNNER): testrunner.c
	@mkdir -p $(dir $@)
	$(CC) $(STD_FLAGS) -O2 -g $< -o $@

# Run all tests
test: $(TEST_RUNNER) $(TEST_BINS)
	cd $(BUILD_DIR)/test && ../testrunner

# Dependency files
-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR)
