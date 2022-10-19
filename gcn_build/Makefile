#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITPPC)),)
$(error "Please set DEVKITPPC in your environment. export DEVKITPPC=<path to>devkitPPC")
endif

include $(DEVKITPPC)/gamecube_rules

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
#---------------------------------------------------------------------------------
TARGET    := $(notdir $(CURDIR))
BUILD     := build
SOURCES   := src
DATA      := data
INCLUDES  :=

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------

CFLAGS		= -g -O2 -Wall $(MACHDEP) $(INCLUDE)
CXXFLAGS	= $(CFLAGS)

LDFLAGS		= -g $(MACHDEP) -Wl,-Map,$(notdir $@).map 

#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------
# TODO: maybe look into pkgconfig instead? might work
LIBS	:= -lSDL_image -lSDL_ttf -lSDL_mixer `$(DEVKITPRO)/portlibs/gamecube/bin/sdl-config --libs` -ljpeg -lvorbisfile -lvorbis -logg -lmad -lm `$(DEVKITPRO)/portlibs/ppc/bin/freetype-config --libs`

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:= $(PORTLIBS)

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
			$(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

#---------------------------------------------------------------------------------
# automatically build a list of object files for our project
#---------------------------------------------------------------------------------
CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))

# resources
GFX_BINFILES := $(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/gfx/*.*)))
ICONS_BINFILES := $(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/icons/*.*)))
SOUND_BINFILES := $(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/sound/*.ogg)))
FONTS_BINFILES := $(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/fonts/**/*.ttf)))

# No C++, only C, so using CC
export LD := $(CC)

export OFILES_GFX_BIN := $(addprefix gfx_,$(addsuffix .o,$(GFX_BINFILES)))
export OFILES_ICONS_BIN := $(addprefix icons_,$(addsuffix .o,$(ICONS_BINFILES)))
export OFILES_SOUND_BIN := $(addprefix sound_,$(addsuffix .o,$(SOUND_BINFILES)))
export OFILES_FONTS_BIN := $(addprefix fonts_,$(addsuffix .o,$(FONTS_BINFILES)))
export OFILES_BIN	:=	$(OFILES_GFX_BIN) $(OFILES_ICONS_BIN) $(OFILES_SOUND_BIN) $(OFILES_FONT_BINFILES)

export OFILES_SOURCES := $(CFILES:.c=.o)
export OFILES := $(OFILES_BIN) $(OFILES_SOURCES)

# Header files for resources
export GFX_HFILES = $(addprefix gfx_,$(addsuffix .h,$(subst .,_,$(GFX_BINFILES))))
export ICONS_HFILES = $(addprefix icons_,$(addsuffix .h,$(subst .,_,$(ICONS_BINFILES))))
export SOUND_HFILES = $(addprefix sound_,$(addsuffix .h,$(subst .,_,$(SOUND_BINFILES))))
export FONTS_HFILES = $(addprefix fonts_,$(addsuffix .h,$(subst .,_,$(FONTS_BINFILES))))
export HFILES := $(GFX_HFILES) $(ICONS_HFILES)

#---------------------------------------------------------------------------------
# build a list of include paths
#---------------------------------------------------------------------------------
export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
			$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
			-I$(CURDIR)/$(BUILD) \
			-I$(LIBOGC_INC)

#---------------------------------------------------------------------------------
# build a list of library paths
#---------------------------------------------------------------------------------
export LIBPATHS	:=	-L$(LIBOGC_LIB) $(foreach dir,$(LIBDIRS),-L$(dir)/lib)

export OUTPUT	:=	$(CURDIR)/$(TARGET)
.PHONY: $(BUILD) clean

#---------------------------------------------------------------------------------
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/gcn_build/Makefile

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(OUTPUT).elf $(OUTPUT).dol

#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT).dol: $(OUTPUT).elf
$(OUTPUT).elf: $(OFILES)

$(OFILES_SOURCES) : $(HFILES)


# Converts our resources into binary formats that can be packaged together with the executable
gfx_%.png.o gfx_%_png.h : gfx/%.png
	@echo $(notdir $<)
	@bin2s -a 32 -H gfx_`(echo $(<F) | tr . _)`.h $< | $(AS) -o gfx_$(<F).o

gfx_%.bmp.o	gfx_%_bmp.h : gfx/%.bmp
	@echo $(notdir $<)
	@bin2s -a 32 -H gfx_`(echo $(<F) | tr . _)`.h $< | $(AS) -o gfx_$(<F).o

icons_%.png.o icons_%_png.h : icons/%.png
	@echo $(notdir $<)
	@bin2s -a 32 -H icons_`(echo $(<F) | tr . _)`.h $< | $(AS) -o icons_$(<F).o

sound_%.ogg.o sound_%_ogg.h : sound/%.ogg
	@echo $(notdir $<)
	@bin2s -a 32 -H sound_`(echo $(<F) | tr . _)`.h $< | $(AS) -o sound_$(<F).o

fonts_%.ttf.o fonts_%_ttf.h : fonts/**/%.ogg
	@echo $(notdir $<)
	@bin2s -a 32 -H fonts_`(echo $(<F) | tr . _)`.h $< | $(AS) -o fonts_$(<F).o


-include $(DEPENDS)

#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------
