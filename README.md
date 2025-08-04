# GTA:SA Steam Idler

This tool helps you log hours on Grand Theft Auto: San Andreas (GTA:SA) on Steam while playing Multi Theft Auto: San Andreas (MTA:SA).

Since MTA:SA no longer supports third-party launchers, you need to start MTA:SA first. After that, launch GTA:SA through Steam, which will open this launcher.

You can also use this tool to launch regular GTA:SA.

<img width="374" height="158" alt="image" src="https://github.com/user-attachments/assets/b2b7c2ec-f122-4263-8258-19f14716fc32" />

## Files

- `main.cpp` — Main source code.
- `resource.h` — Resource header.
- `resource.rc` — Resource script.
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

1. Compile the source code or download the latest release.

2. Head over to your GTA:SA Steam folder (`..\Steam\steamapps\common\Grand Theft Auto San Andreas`) and rename `gta-sa.exe` to `gta_sa.exe`.

3. Copy the compiled/downloaded `gta-sa.exe` to your GTA:SA Steam folder.

4. Launch the game via Steam.
