DESTDIR?=/usr
DEST_LIB:=$(DESTDIR)/lib
DEST_INC:=$(DESTDIR)/include

COMPILE_FLAG := -std=c++23 -Wextra -Wno-implicit-fallthrough -fconcepts-diagnostics-depth=2
INCLUDE_FLAG := -Iinclude
TEST_LINK_FLAG := -lCatch2Main -lCatch2 -L. -lspkutils -lscrypt -luuid
COMPILE := g++ $(COMPILE_FLAG) $(INCLUDE_FLAG)
TST_COMPILE := g++ $(COMPILE_FLAG) -Iinclude

.PHONY: install
install: all
	mkdir -p "$(DEST_LIB)" "$(DEST_INC)"
	cp libspkutils.a "$(DEST_LIB)"
	cp -r include/spk_utils "$(DEST_INC)"

.PHONY: uninstall
uninstall:
	rm -f "$(DEST_LIB)/libspkutils.a"
	rm -rf "$(DEST_INC)/spk_utils"

.PHONY: all
all: libspkutils.a error.spec hash.spec uuid.spec

.PHONY: build
build: libspkutils.a

%.o: src/%.cpp include/spk_utils/%.hpp
	$(COMPILE) -c $< -o $@

libspkutils.a: error.o hash.o uuid.o
	ar r $@ $^
	ranlib $@

spk_log.o: test/spk_log.cpp
	$(COMPILE) -c $< -o $@

%.spec: test/%.spec.cpp libspkutils.a spk_log.o
	$(TST_COMPILE) $< spk_log.o -o $@ $(TEST_LINK_FLAG)
	./$@ -s

.PHONY: clean
clean:
	rm *.o libspkutils.a *.spec
