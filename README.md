# GTA SA Steam Idler

This tool helps you log hours on Grand Theft Auto: San Andreas (GTA:SA) on Steam while playing Multi Theft Auto: San Andreas (MTA:SA).

Since MTA:SA no longer supports third-party launchers, you need to start MTA:SA first. After that, launch GTA:SA through Steam, which will activate the idler.

You can also use this tool to launch the regular GTA:SA game directly.

## Files

- `main.cpp` — Main source code.
- `resource.h` — Resource header (defines icon resource ID).
- `resource.rc` — Resource script (embeds the icon).
- `icon.ico` — Application icon.

## How to Build (MinGW/g++)

1. **Install MinGW-w64** (or any g++/windres toolchain for Windows).

2. **Open a terminal in the project folder.**

3. **Compile the resources:**
   ```sh
   windres resource.rc -O coff -o resource.o
   ```

4. **Compile and link the application:**
   ```sh
   g++ main.cpp resource.o -o gta-sa.exe -mwindows -municode -DUNICODE -D_UNICODE
   ```

5. **Run the executable:**
   ```sh
   ./gta-sa.exe
   ```

## How to use

Head over to your GTA:SA Steam folder (`..\Steam\steamapps\common\Grand Theft Auto San Andreas`) and rename `gta-sa.exe` to `gta_sa.exe`.

Copy the compiled `gta-sa.exe` to your GTA:SA Steam folder.

Launch the game via Steam.