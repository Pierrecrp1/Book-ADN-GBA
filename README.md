# Book ADN - GBA Game

Un projet interactif créé pour une créatrice de mode, transformant son identité visuelle en expérience de jeu vidéo rétro pour Game Boy Advance.

## 📖 Description

Book ADN est une expérience interactive qui raconte l'histoire d'une poursuite : un lapin traverse trois univers visuels distincts, suivi de près par un léopard. Le léopard se rapproche progressivement à chaque scène, symbolisant l'évolution d'une identité créative qui se construit et s'affirme.

Ce projet a été conçu sur mesure pour répondre aux besoins d'une étudiante en école de mode souhaitant créer un "book ADN" original pour présenter son univers créatif et son identité visuelle de manière unique et mémorable.

## 🎮 Gameplay

### Objectif
Traversez les trois scènes pour atteindre la fin... mais le léopard finira toujours par vous rattraper !

### Contrôles
- **Flèches directionnelles** : Déplacement (gauche/droite)
- **A** : Valider les sélections dans les menus
- **B** : Retour en arrière dans les menus
- **START** : Ouvrir le menu pause pendant le jeu
- **UP/DOWN** : Navigation dans les menus
- **LEFT/RIGHT** : Ajuster les volumes dans les options

### Fonctionnalités
- **3 scènes distinctes** représentant différents univers visuels
- **Système de caméra dynamique** qui suit les personnages
- **Menu d'options** avec 4 réglages de volume indépendants
- **Sauvegarde automatique** des préférences
- **Menu pause** accessible à tout moment
- **Animations fluides** et atmosphère sonore immersive

## 🛠️ Comment Utiliser le Projet

### Pour jouer directement
Le fichier ROM `Book-ADN-GBA.gba` peut être utilisé avec :
- Un émulateur Game Boy Advance (mGBA, VisualBoy Advance, etc.)
- Une cartouche flash pour jouer sur console GBA réelle

### Pour compiler le projet
Si vous souhaitez modifier et recompiler le projet :

1. Installez [devkitPro](https://devkitpro.org/) avec devkitARM
2. Installez le framework [Butano](https://github.com/GValiente/butano)
3. Placez ce projet dans le dossier `butano/projects/`
4. Compilez avec la commande :
```bash
make
```

Le fichier ROM sera généré : `Book-ADN-GBA.gba`

## � Contexte du Projet

Ce projet a été développé pour répondre à une demande spécifique : créer un support de présentation original et interactif pour une étudiante en école de mode. Le format jeu vidéo rétro permet de présenter son univers créatif de manière unique et mémorable, en transformant son "book ADN" traditionnel en une expérience interactive immersive.

L'identité visuelle se déploie à travers trois scènes distinctes, chacune avec sa propre ambiance musicale, créant un parcours narratif qui reflète l'évolution et l'affirmation d'une identité artistique personnelle.

---

Projet développé sur mesure pour créer un book ADN interactif et original.  
Réalisé avec le framework [Butano](https://github.com/GValiente/butano) pour Game Boy Advance.
