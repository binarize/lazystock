# Generic Makefile 07-12-2021

C_FILES += $(wildcard ./*.c)
C_FILES += $(wildcard ./**/*.c)
C_OBJECTS += $(addprefix ../build/obj/,$(notdir $(C_FILES:.c=.o)))

# Common flags
VPATH=./
HEADERS += -I./

# Common flags
CFLAGS = -std=c17 -Wall -Wfatal-errors
LFLAGS = -std=c17 -Wall -Wfatal-errors

# PRODUCTION
#CFLAGS += -O3 -g0
#LFLAGS += -O3 -g0

# DEBUGGING
# -Wall  enables all warnings
# -O0    disable all optimisations
# -g3    maximal debug information
CFLAGS += -O0 -g3
LFLAGS += -O0 -g3

# PROFILING
# CFLAGS += -pg
# LFLAGS += -pg


UNAME_S := $(shell uname -s)
UNAME_P := $(shell uname -p)
UNAME_M := $(shell uname -m)
UNAME_V := $(shell uname -v)

# Platform-specific flags

ifeq ($(OS),Windows_NT)
	CFLAGS += -D__USE_MINGW_ANSI_STDIO
	LFLAGS += -Wl,-subsystem,windows -lmingw32 -limm32 -lcomdlg32
	ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
		CFLAGS += -m64
		LFLAGS += -m64
	else
		ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
			CFLAGS += -m64
			LFLAGS += -m64
		endif
		ifeq ($(PROCESSOR_ARCHITECTURE),x86)
			CFLAGS += -m32
			LFLAGS += -m32
		endif
	endif
else

	ifeq ($(UNAME_S),Linux)
		CFLAGS += $(shell sdl2-config --cflags)
		LFLAGS += $(shell sdl2-config --libs)
	endif
	ifeq ($(UNAME_S),Darwin)

		ifeq ($(UNAME_P),arm)
			# Compile SDL from source for now on ARM.
			CFLAGS +=  -D OSX -D OSX_ARM
		else
			# Include SDL library normally on intel.
			CFLAGS += `-D OSX -D OSX_INTEL
		endif
	endif
endif

# Rules

../build/bin: $(C_OBJECTS)
	@echo OS Name: $(UNAME_S) / Machine Name: $(UNAME_M) / Processor Type: $(UNAME_P)
	@gcc $^ $(LFLAGS) -o $@

../build/obj/%.o: %.c
	@mkdir -p ../build/obj
	@gcc $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@rm -rf ../build/*
	@echo "\n\n"

test: clean ../build/bin
	../build/bin

# -include $(C_OBJECTS:.o=.d)