#---------------------------------------------------------------------------------------------------------------------
# Project configuration
#---------------------------------------------------------------------------------------------------------------------

# Nom de la ROM (automatique : nom du dossier)
TARGET          :=  $(notdir $(CURDIR))

# Dossier où seront les fichiers compilés
BUILD           :=  build

# Dossier où se trouve le moteur Butano (racine du repo)
LIBBUTANO       :=  ../..

# Python utilisé par les outils internes
PYTHON          :=  python

# Dossiers du projet
SOURCES         :=  src
INCLUDES        :=  include
DATA            :=
GRAPHICS        :=  graphics
AUDIO           :=  audio
AUDIOBACKEND    :=  maxmod
AUDIOTOOL       :=
DMGAUDIO        :=  dmg_audio
DMGAUDIOBACKEND :=  default

# ROM metadata
ROMTITLE        :=  BOOKADN
ROMCODE         :=  SBTP

# Flags optionnels
USERFLAGS       :=
USERCXXFLAGS    :=
USERASFLAGS     :=
USERLDFLAGS     :=
USERLIBDIRS     :=
USERLIBS        :=
DEFAULTLIBS     :=
STACKTRACE      :=
USERBUILD       :=
EXTTOOL         :=

#---------------------------------------------------------------------------------------------------------------------
# Absolute Butano path resolution
#---------------------------------------------------------------------------------------------------------------------

ifndef LIBBUTANOABS
    export LIBBUTANOABS := $(realpath $(LIBBUTANO))/butano
endif

#---------------------------------------------------------------------------------------------------------------------
# Include Butano build system
#---------------------------------------------------------------------------------------------------------------------

include $(LIBBUTANOABS)/butano.mak

#---------------------------------------------------------------------------------------------------------------------
# Run ROM in mGBA
#---------------------------------------------------------------------------------------------------------------------
run:
	"$(shell cygpath -w 'C:\Program Files\mGBA\mGBA.exe')" $(TARGET).gba

#---------------------------------------------------------------------------------------------------------------------
# Build + Run
#---------------------------------------------------------------------------------------------------------------------
br: all run

#---------------------------------------------------------------------------------------------------------------------
# Assets generation
#---------------------------------------------------------------------------------------------------------------------
# Python Windows
ASSETS_PYTHON := /c/Users/pierr/AppData/Local/Programs/Python/Python313/python.exe

# Liste des modules Python requis (séparés par espaces)
PYTHON_REQUIREMENTS := pillow numpy

# Installation des dépendances pip
pipinstall:
	$(ASSETS_PYTHON) -m pip install --upgrade pip
	$(ASSETS_PYTHON) -m pip install $(PYTHON_REQUIREMENTS)

# Script d'assets
# ASSETS_SCRIPT := generate_assets.py
ASSETS_SCRIPT := tools/make_backgrounds.py

# Génération des assets
assets:
	$(ASSETS_PYTHON) $(ASSETS_SCRIPT)

# Génération des assets + build
ab: pipinstall assets all

# Génération des assets + build + run
abr: pipinstall assets all run