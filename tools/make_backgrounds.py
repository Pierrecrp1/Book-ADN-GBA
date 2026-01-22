import sys
import subprocess
from pathlib import Path

SRC_DIR = Path("graphics/background_src")
OUT_DIR = Path("graphics")

TILE_SIZE = 160
CANVAS_W = 512
CANVAS_H = 256

IMAGES_PER_SCENE = 2

def run(cmd: list[str]) -> None:
    print(" ".join(cmd))
    subprocess.run(cmd, check=True)

def ensure_magick() -> None:
    try:
        subprocess.run(
            ["magick", "-version"],
            check=True,
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL
        )
    except Exception:
        print("[ERREUR] ImageMagick introuvable (commande 'magick').")
        sys.exit(1)

def write_json_if_missing(json_path: Path) -> None:
    if json_path.exists():
        return
    json_path.write_text(
        '{\n    "type": "regular_bg"\n}\n',
        encoding="utf-8"
    )

def main() -> None:
    ensure_magick()

    if not SRC_DIR.exists():
        print(f"[ERREUR] Dossier introuvable: {SRC_DIR}")
        sys.exit(1)

    OUT_DIR.mkdir(parents=True, exist_ok=True)

    # Récupère tous les PNG triés par numéro
    pngs = sorted(
        SRC_DIR.glob("*.png"),
        key=lambda p: int(p.stem)
    )

    if len(pngs) < 2:
        print("[ERREUR] Il faut au moins 2 images dans background_src.")
        sys.exit(1)

    scene_index = 1
    i = 0

    while i + 1 < len(pngs):
        img1 = pngs[i]
        img2 = pngs[i + 1]

        scene_name = f"scene_{scene_index:02d}"
        out_bmp = OUT_DIR / f"{scene_name}.bmp"
        out_json = OUT_DIR / f"{scene_name}.json"
        tmp_png = OUT_DIR / f"__tmp_{scene_name}.png"

        print(f"[BUILD] {scene_name} <- {img1.name}, {img2.name}")

        # Concat 2 images redimensionnées en 160x160 -> 320x160
        run([
            "magick",
            str(img1), "-resize", f"{TILE_SIZE}x{TILE_SIZE}!",
            str(img2), "-resize", f"{TILE_SIZE}x{TILE_SIZE}!",
            "+append",
            str(tmp_png)
        ])

        # Pad canvas + quantize + BMP3
        run([
            "magick", str(tmp_png),
            "-background", "black",
            "-gravity", "center",
            "-extent", f"{CANVAS_W}x{CANVAS_H}",
            "-colors", "16",
            "-type", "Palette",
            "-depth", "4",
            f"BMP3:{out_bmp}"
        ])

        # Nettoyage
        if tmp_png.exists():
            tmp_png.unlink()

        write_json_if_missing(out_json)

        print(f"[OK] {scene_name}")

        scene_index += 1
        i += IMAGES_PER_SCENE

    print("\n[OK] Tous les backgrounds ont ete generes.")

if __name__ == "__main__":
    main()