#!/usr/bin/env python3
"""
Script pour générer des assets BMP pour Book ADN
"""
from PIL import Image, ImageDraw

def create_sprite_bmp(filename, width, height, color):
    """Crée un sprite BMP simple 16x16 en 8 bits."""
    # Créer en RGB puis convertir en palette 8 bits
    img = Image.new('RGB', (width, height), (255, 0, 255))  # Magenta = transparent
    draw = ImageDraw.Draw(img)
    
    # Rectangle de couleur
    draw.rectangle([2, 2, width - 2, height - 2], fill=color)
    # Petit carré blanc pour identifier le sprite
    draw.rectangle([4, 4, 7, 7], fill=(255, 255, 255))
    
    # Convertir en palette 8 bits (256 couleurs)
    img = img.convert('P', palette=Image.ADAPTIVE, colors=256)
    img.save(filename, 'BMP')
    print(f"Créé: {filename}")

def create_bg_bmp(filename, width, height, color):
    """Crée un background BMP large avec fond de couleur unie en 8 bits."""
    # Créer en RGB puis convertir en palette 8 bits
    img = Image.new('RGB', (width, height), color)
    img = img.convert('P', palette=Image.ADAPTIVE, colors=256)
    img.save(filename, 'BMP')
    print(f"Créé: {filename} ({width}x{height})")

# Créer les sprites (16x16 simples, animation sera gérée différemment)
create_sprite_bmp('graphics/lapin.bmp', 16, 16, (255, 180, 180))
create_sprite_bmp('graphics/leopard.bmp', 16, 16, (255, 200, 100))

# Créer les backgrounds (256x256 standard GBA)
create_bg_bmp('graphics/scene_01.bmp', 256, 256, (100, 150, 255))  # Bleu ciel
create_bg_bmp('graphics/scene_02.bmp', 256, 256, (100, 200, 100))  # Vert
create_bg_bmp('graphics/scene_03.bmp', 256, 256, (255, 150, 100))  # Orange

print("\n✓ Assets BMP générés!")
print("  - Sprites: 16x16")
print("  - Backgrounds: 256x256")
