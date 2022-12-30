# Il s'agit d'une version modifiée d'un makefile déjà existant
# CREDITS: Scot McPeak, Nicholas Hamilton, et en particulier le tutoriel Makefile
# http://scottmcpeak.com/autodepend/autodepend.html

# Compilateur: G++
CC          := g++

# Le nom de l'exécutable
TARGET      := mgsi

# Les répertoires des fichiers sources, fichiers d'entête, fichiers objets, fichiers binaires et les ressources s'il y en a
SRCDIR      := src
INCDIR      := inc
BUILDDIR    := obj
TARGETDIR   := bin
RESDIR      := shaders

# Extensions des fichiers sources, fichiers d'entête, fichiers objets et fichiers de dépendance
SRCEXT      := cpp
DEPEXT      := d
OBJEXT      := o


# Les options de compilation, les librairies et les dossiers d'inclusion
CFLAGS      := -Wall -g
LIB         := -lm -lGL -lGLU -lGLEW -lSDL
INC         := -I$(INCDIR) -I/usr/local/include
INCDEP      := -I$(INCDIR)

# Cible par défaut, c'est à dire lancée par la commande make
default: all

#---------------------------------------------------------------------------------
# A NE PAS MODIFIER (sinon tout explose et tout le monde meurt (non, pas vraiment)))
#---------------------------------------------------------------------------------

SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

# Make complet
all: directories $(TARGET)

# Remake
remake:	clean all

# Création des dossiers
directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(RESDIR)
	@mkdir -p $(SRCDIR)

# Clean des fichiers objets
cleanobj:
	@$(RM) $(BUILDDIR)/*

# Clean des fichiers binaires
cleanbin:
	@$(RM) $(TARGETDIR)/*

# Clean des fichiers objets et binaires
clean:	cleanobj cleanbin

# Inclure les informations de dépendance pour les fichiers .o existants
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))

# Création de l'exécutable
$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGETDIR)/$(TARGET) $^ $(LIB)

# Création des fichiers objets et en particulier des fichiers de dépendance
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@$(CC) $(CFLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp

# Cible phony, c'est à dire lancée par la commande make <cible>
.PHONY: all remake clean cleaner resources
	