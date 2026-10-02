# Arkham Subtitle Scale

Configurable subtitle size and vertical positioning for **Batman: Arkham Asylum GOTY (Windows, Steam)**.

**Version 0.2.0 is an experimental pre-release.** Subtitle scaling at 3x has been confirmed in gameplay at 3840x2160. The new vertical offset and other subtitle scenes still need in-game verification.

## Install

1. Close the game.
2. Download the ready-to-use ZIP attached to a GitHub Release. The automatically generated source archives do not contain the compiled mod.
3. Copy the three files inside the archive's `Binaries` directory into the game's `Binaries` directory, next to `ShippingPC-BmGame.exe`:
   - `dinput8.dll`
   - `ArkhamSubtitleScale.asi`
   - `ArkhamSubtitleScale.ini`
4. Launch the game normally through Steam. No compilation is required.

If another mod already supplies `dinput8.dll`, do not overwrite it. This minimal loader loads only this mod's ASI. Compatibility with other loaders is not implemented or tested.

## Settings

Edit `Binaries/ArkhamSubtitleScale.ini`, then restart the game:

```ini
[Subtitles]
Enabled=1
Scale=3.0
VerticalOffset=160
```

| Setting | Meaning |
| --- | --- |
| `Enabled` | `0` disables subtitle modifications; `1` enables them. |
| `Scale` | Size multiplier, from `0.5` to `4.0`. Use a decimal point. `1.0` is the original size. |
| `VerticalOffset` | Offset in pixels at the current rendering resolution, from `-1000` to `1000`. Positive moves down; negative moves up; `0` keeps the game's original position. |

The supplied 3x scale and 160-pixel offset are starting values for 3840x2160, not automatic resolution scaling. Large offsets can move text off-screen. Use `Scale=1.0` and `VerticalOffset=0` for the original draw size and position.

## License

The original mod code is provided under the MIT license; see `LICENSE`. Game assets are not included. This is an unofficial community project.
