GSRC = ../src
GBIN = bin
GBUILD = build
GTARGET = $(GBIN)\rdv_db_sqlite_test.exe

GTOOLS = C:\Users\tiaka\Downloads\eDocs\eTools

GROOT = ../../..

GINCS =\
	-I$(GTOOLS)/include \
	-I$(GROOT)/common/lib/src \
	-I$(GROOT)/db_sqlite/lib/src \

GLIBS =\
	-L$(GTOOLS)/lib \
	-L$(GROOT)/common/lib/mingw/bin \
	-L$(GROOT)/db_sqlite/lib/mingw/bin \
	-lrdv_common -lrdv_db_sqlite -lsqlite3 \

GOBJS =\
    $(patsubst $(GSRC)/%.cpp, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.cpp)) \

GCFLAGS =\
    -g \
    -std=gnu++17 \

GDEPENDS :=\
	$(GROOT)/common/lib/mingw \
	$(GROOT)/db_sqlite/lib/mingw \

all: clean_exe depends_lib compile run
all_g: clean_exe depends_lib compile run_g

depends_lib:
	@$(foreach GDIR,$(GDEPENDS),$(MAKE) -C $(GDIR) -f Makefile.cmd.mak all && ) echo.
depends_clean:
	@$(foreach GDIR,$(GDEPENDS),$(MAKE) -C $(GDIR) -f Makefile.cmd.mak clean && ) echo.

compile: $(GOBJS)
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	g++ $(GCFLAGS) -o $(GTARGET) $(GOBJS) $(GLIBS)
$(GBUILD)/%.o: $(GSRC)/%.cpp
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	g++ $(GCFLAGS) -c $< -o $@ $(GINCS)
$(GDEPENDS):
	@$(MAKE) -C $@ -f Makefile.cmd.mak all
run:
	@envs.bat && $(GTARGET) $(argv)
run_g:
	@envs.bat && gdb -ex run --args $(GTARGET) $(argv)
clean_exe:
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	@del /q /s $(GBIN)\*
clean: depends_clean
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	@del /q /s $(GBUILD)\*.o $(GBIN)\*
