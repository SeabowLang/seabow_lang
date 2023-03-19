SRC_PATHS	= sources/*.cpp sources/nodes/*.cpp sources/values/*.cpp sources/compiler/interpreter.cpp
INC_PATHS	= -Iincludes
DST_PATH	= build
CMM_CMDS	= -O3 -Wall -Wno-sign-compare -Wno-string-plus-int
OUTPUT		= seabow
ARGS		= # Variable used to pass arguments to seabow compiler.


install:
	cp build/linux/seabow $(DESTDIR)/seabow
	chmod +x $(DESTDIR)/seabow

snp-cmp:
	snapcraft
	mv *.snap $(DST_PATH)/linux/

snp-pkg:
	sudo snap install $(DST_PATH)/linux/*.snap --dangerous --devmode

snp-unpkg:
	sudo snap remove $(OUTPUT)

snp-push:
	snapcraft push $(DST_PATH)/linux/*.snap

snp-release:
	snapcraft release $(OUTPUT) $(ARGS)

snp-download:
	sudo snap install $(OUTPUT) --channel=$(ARGS)

cmp-l:
	g++ $(SRC_PATHS) $(INC_PATHS) -o $(DST_PATH)/linux/$(OUTPUT) $(CMM_CMDS)

cmp-w:
	x86_64-w64-mingw32-g++-posix -D_WIN32=1 $(SRC_PATHS) $(INC_PATHS) -o $(DST_PATH)/windows/$(OUTPUT).exe $(CMM_CMDS) -static-libgcc -static-libstdc++ -static -lwinpthread

cmp-m:
	clang++ -D__APPLE__=1 $(SRC_PATHS) $(INC_PATHS) -o $(DST_PATH)/macos/$(OUTPUT) $(CMM_CMDS)

cmp-all:
	$(MAKE) cmp-l cmp-w cmp-m


run-l:
	./build/linux/$(OUTPUT) $(ARGS)

run-w:
	wine ./build/windows/$(OUTPUT).exe $(ARGS)

run-m:
	./build/macos/$(OUTPUT) $(ARGS)

run-all:
	$(MAKE) run-l run-w run-m


test-l:
	$(MAKE) cmp-l run-l

test-w:
	$(MAKE) cmp-w run-w

test-m:
	$(MAKE) cmp-m run-m

test-all:
	$(MAKE) cmp-all run-all