# ClickFix v0.1.0-alpha.1 — source prototype

Target: Geometry Dash Android 2.2081, Geode Loader 5.11.2, ARM64.

## What this prototype contains
- Geode settings: master enable switch.
- Separate Input Buffer and Click Correction toggles.
- Tolerance slider from 0 to 100 ms (default 100 ms).
- All game modes compatibility preference.

## Important limitation
This is **not an installable `.geode` package**. It is source code for the settings/loading prototype. The gameplay input hooks, input buffering, and early-click correction are not implemented yet. The settings are saved by Geode but do not alter gameplay in this alpha.

## Build on a computer
Install Geode CLI, the matching Geode SDK binaries, Android NDK, and Ninja. From this project directory:

```sh
geode sdk install-binaries -p android64
geode build -p android64
```

The Android package should be produced in `build-android64` if the build succeeds. Copy the resulting `.geode` to:

`/storage/emulated/0/Android/media/com.geode.launcher/game/geode/mods/`

Then restart Geometry Dash/Geode. Do not install this ZIP directly as a mod.
