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

## Compatibility and limitations

Only the following original Steam GOTY executable is accepted:

```text
ShippingPC-BmGame.exe SHA256
4dac1f5e2ac6710b7378fdce74601f616f4753e3756cb5fda63c7519cc2eb028
```

Other executables, including modified EXEs and Epic/GOG versions, are refused unless they match this exact hash. Other languages, Windows versions, Proton and combinations with other mods have not been validated.

- The mod scales the game's existing bitmap font. It does not introduce a high-resolution or vector font; enlarged letters may look soft or pixelated.
- Text measurement, wrapping and line spacing are scaled together. The original one-pixel outline is retained.
- The hooks target subtitle drawing calls. Menu and general HUD text scaling is outside the mod's scope.
- Extra line breaks can affect how the game's subtitle manager distributes text over time. Check long dialogue, radio dialogue and cutscenes.
- The game executable and packages are not modified on disk. Patches are applied to the running process after version and instruction checks.

## Troubleshooting and removal

`Binaries/ArkhamSubtitleScale.log` is recreated on startup. `Installed 13 hooks` indicates successful patch installation. `Subtitle drawing hook reached` indicates a subtitle draw call was intercepted.

`Unsupported EXE SHA256` or `Hook validation/protection failed` means the mod refused to patch. Do not bypass these checks. For a bug report, include the mod version, storefront, resolution, settings, scene and this mod's log.

To remove the mod, close the game and delete its three installed files. Its log may also be removed. Delete only the loader installed with this mod. Steam file verification may leave additional mod files in place.

## Build from source

Install Visual Studio or Build Tools with MSVC C++ x86 tools and a Windows SDK. Run `build.cmd`; it locates Visual Studio using `vswhere`, builds the two x86 modules with static CRT, and runs the local tests. Output is written to `build`.

Optionally run `build.cmd "X:\path\to\game\Binaries\ShippingPC-BmGame.exe"` to also check the supported executable's hash. No game files are needed for the other tests or included in this repository.

Tests cover drawing arguments, centering, vertical offsets, outline alignment, x86 line-step hooks, refusal on conflicting patch bytes, page-protection restoration, rejection of an unsupported EXE, and forwarding DirectInput8Create to the system library. These tests do not replace visual verification in the game.

## License

The original mod code is provided under the MIT license; see `LICENSE`. Game assets are not included. This is an unofficial community project.
