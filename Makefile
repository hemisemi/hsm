CC := g++
CPPFLAGS := -W -Wall --ansi --pedantic -std=c++0x -fPIC -g
LDFLAGS := -shared

SRCDIR := src
DEPDIR := .deps
BUILDDIR := .build
DOCDIR := doc

FREETYPE_PATH = /usr/include/freetype2

INCPATH := -I$(SRCDIR) -I$(FREETYPE_PATH)
LIBS	:= 

TARGET := hsm

SRC := $(shell find $(SRCDIR) -name '*.cpp')
HDR := $(shell find $(SRCDIR) -name '*.h')
DEP := $(SRC:$(SRCDIR)/%.cpp=$(DEPDIR)/%.P)
OBJ := $(SRC:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

################################################################################

release: $(TARGET)

debug: $(TARGET)d

install:
	./install.sh $(SRCDIR) /usr/include/hsm
	! test -s lib${TARGET}.so || cp -p lib${TARGET}.so /usr/lib
	! test -s lib${TARGET}d.so || cp -p lib${TARGET}d.so /usr/lib
	
uninstall:
	./uninstall.sh $(SRCDIR) /usr/include/hsm
	rm -f /usr/lib/lib${TARGET}.so
	rm -f /usr/lib/lib${TARGET}d.so

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o lib$(TARGET).so $^ $(LIBS)

$(TARGET)d: $(OBJ)
	$(CC) $(LDFLAGS) -g -o lib$(TARGET)d.so $^ $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	@mkdir -p $(@D:$(BUILDDIR)%=$(DEPDIR)%)
	
	$(CC) -MMD -MF $(DEPDIR)/$*.d $(CPPFLAGS) $(INCPATH) -o $@ -c $<
	
	@cp $(DEPDIR)/$*.d $(DEPDIR)/$*.P; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(DEPDIR)/$*.d >> $(DEPDIR)/$*.P; \
	rm -f $(DEPDIR)/$*.d

-include $(DEP)

.PHONY: clean mrproper install uninstall

clean:
	rm -r $(DEPDIR) $(BUILDDIR)

mrproper: clean
	rm -rf lib$(TARGET).so lib$(TARGET)d.so

