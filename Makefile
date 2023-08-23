ifeq ($(strip $(PVSNESLIB_HOME)),)
$(error "Please create an environment variable PVSNESLIB_HOME with path to its folder and restart application. (you can do it on windows with <setx PVSNESLIB_HOME "/c/snesdev">)")
endif

# BEFORE including snes_rules :
# list in AUDIOFILES all your .it files in the right order. It will build to generate soundbank file
AUDIODIR :=	res
export AUDIOFILES :=	$(foreach dir, $(AUDIODIR), \
	$(dir)/*.it)

# then define the path to generate soundbank data. The name can be different but do not forget to update your include in .c file !
export SOUNDBANK := soundbank

include ${PVSNESLIB_HOME}/devkitsnes/snes_rules

.PHONY: bitmaps all

#---------------------------------------------------------------------------------
# ROMNAME is used in snes_rules file
export ROMNAME := logo

# to build musics, define SMCONVFLAGS with parameters you want
SMCONVFLAGS	:= -s -o $(SOUNDBANK) -V -b 5
musics: $(SOUNDBANK).obj

all: musics logo $(ROMNAME).sfc

cleanGfxLogo:
	@echo clean Rare graphics data
	@rm -f res/*.pic res/*.pal res/*.map res/*.mp7 res/*.pc7

clean: cleanBuildRes cleanRom cleanGfx cleanGfxLogo cleanAudio

#---------------------------------------------------------------------------------

mode3bg1.pic: res/mode3bg1.bmp
	@echo convert mode3bg1 image ... $(notdir $@)
	$(GFXCONV) -pc256 -n -gs8 -pe0 -fbmp  $<

mode3bg2.pic: res/mode3bg2.bmp
	@echo convert mode3bg2 image ... $(notdir $@)
	$(GFXCONV) -pc16 -n -gs8 -pe0 -fbmp  $<

mode5.pic: res/mode5.bmp
	@echo convert mode5 image ... $(notdir $@)
	$(GFXCONV) -pc16 -n -gs8 -pe0 -fbmp  $<

mode7.pc7: res/mode7.png
	@echo convert mode7 image ... $(notdir $@)
	$(GFXCONV) -n -fpng -m7 $<

logo: mode3bg1.pic mode3bg2.pic mode5.pic mode7.pc7
