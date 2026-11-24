CC          ?= clang
AR          ?= ar
ARFLAGS     := rcs

LIB_NAME    ?= containers
BUILD_DIR   := build
LIB_ARCHIVE := $(BUILD_DIR)/lib$(LIB_NAME).a

LIB_SRCS    := $(shell find src -name '*.c' 2>/dev/null | LC_ALL=C sort)
TEST_SRCS   := $(shell find tests -name '*.c' 2>/dev/null | LC_ALL=C sort)

# Map source paths to build paths, preserving subdirectories
LIB_OBJS    := $(patsubst %.c,$(BUILD_DIR)/%.o,$(LIB_SRCS))
TEST_OBJS   := $(patsubst %.c,$(BUILD_DIR)/%.o,$(TEST_SRCS))
DEPS        := $(LIB_OBJS:.o=.d) $(TEST_OBJS:.o=.d)

TEST_RUNNER := $(BUILD_DIR)/test

STD_FLAGS   := -std=c17 -Wall -Wextra -Wpedantic
CPPFLAGS    := -I. -Iinclude -Isrc -MMD -MP
CFLAGS      ?= $(STD_FLAGS) -O2 -g
LDFLAGS     :=
LDLIBS      :=

.PHONY: all debug test clean

all: $(LIB_ARCHIVE)

debug: CFLAGS := $(STD_FLAGS) -O0 -g3
debug: $(LIB_ARCHIVE)

$(LIB_ARCHIVE): $(LIB_OBJS)
	@mkdir -p $(dir $@)
	$(AR) $(ARFLAGS) $@ $^

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(TEST_RUNNER): $(TEST_OBJS) $(LIB_ARCHIVE)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LDFLAGS) $(TEST_OBJS) $(LIB_ARCHIVE) -o $@ $(LDLIBS)

test: $(TEST_RUNNER)
	./$(TEST_RUNNER)

-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR)