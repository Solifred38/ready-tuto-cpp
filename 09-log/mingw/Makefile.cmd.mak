#================================================
GSRC = ../src
GBIN = bin
GBUILD = build
GTARGET = $(GBIN)\setup.exe
#================================================
GINCS =\

GLIBS =\

GOBJS =\
    $(patsubst $(GSRC)/%.cpp, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.cpp)) \

GCFLAGS =\
    -g \
    -std=gnu++11 \

#================================================
# cpp
#================================================
all: clean_exe compile run
all_g: clean_exe compile run_g

compile: $(GOBJS)
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	g++ $(GCFLAGS) -o $(GTARGET) $(GOBJS) $(GLIBS)
$(GBUILD)/%.o: $(GSRC)/%.cpp
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	g++ $(GCFLAGS) -c $< -o $@ $(GINCS)
run:
	@envs.bat && $(GTARGET) $(argv)
run_g:
	@envs.bat && gdb -ex run --args $(GTARGET) $(argv)
clean_exe:
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	@del /q /s $(GTARGET)
clean:
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	@del /q /s $(GBUILD)\*.o $(GTARGET)
#================================================
