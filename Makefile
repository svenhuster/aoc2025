CC      := gcc
AOCPART ?= 1
DEBUG ?= 0

TARGETS := $(patsubst %.c,%,$(wildcard day*.c))
BUILD_FLAGS := .build_flags_$(AOCPART)_$(DEBUG)

ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG
endif

all: $(TARGETS)

$(BUILD_FLAGS):
	@rm -f .build_flags_*
	@touch $@

day%: day%.c $(BUILD_FLAGS)
	$(CC) $(CFLAGS) -DAOCPART=$(AOCPART) $< -o $@ $(LDFLAGS)

run%: day%
	@echo "=================== Day $* ==================="
	@./day$* < input$*.txt

sample%: day%
	@echo "=================== Day $* (SAMPLE) ==================="
	@./day$* < sample$*.txt

clean:
	@rm -f $(TARGETS) .build_flags_*

.PHONY: all clean run% sample%
