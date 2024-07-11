GSRC = ../src
GBIN = bin
GBUILD = build
GTARGET = $(GBIN)\librdv_db_sqlite.a

GTOOLS = C:\Users\tiaka\Downloads\eDocs\eTools

GROOT = ../../..

GINCS =\
	-I$(GTOOLS)/include \
	-I$(GROOT)/common/lib/src \

GOBJS =\
    $(patsubst $(GSRC)/%.cpp, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.cpp)) \

GCFLAGS =\
    -g \
    -std=gnu++17 \

all: clean_exe compile

compile: $(GOBJS)
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	ar rcs -o $(GTARGET) $(GOBJS)
$(GBUILD)/%.o: $(GSRC)/%.cpp
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	g++ $(GCFLAGS) -c $< -o $@ $(GINCS)
clean_exe:
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	@del /q /s $(GBIN)\*
clean:
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	@del /q /s $(GBUILD)\*.o $(GBIN)\*
