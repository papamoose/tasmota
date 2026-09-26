# tasmota-prometheus

Automatically tracks [Tasmota](https://github.com/arendst/Tasmota) releases
and republishes matching firmware builds with the Prometheus `/metrics`
endpoint (`USE_PROMETHEUS`) enabled — nothing else changed.

## How it works

`.github/workflows/build-and-release.yml` runs on a schedule (every 6 hours,
plus manual trigger):

1. Asks the GitHub API for `arendst/Tasmota`'s latest release tag.
2. Checks if this repo already has a release with that same tag. If so, it
   exits — nothing to do.
3. If it's a new tag: checks out Tasmota **at that exact tag**, copies in
   [`config/user_config_override.h`](config/user_config_override.h) (which
   just adds `#define USE_PROMETHEUS`), builds it with PlatformIO, and
   publishes a GitHub release in *this* repo tagged with the **same version
   string** as upstream, with the resulting `.bin` files attached.

So your releases page ends up mirroring Tasmota's, one-for-one, just with
Prometheus baked in.

## Building just the minimal env

**Locally**, from inside a Tasmota checkout with the override applied:

```bash
pio run -e tasmota-minimal
```

**Via this repo's workflow**, without editing any files: go to **Actions →
Track Tasmota releases... → Run workflow**, and fill in:

- `build_envs`: `tasmota-minimal` (overrides the default list for just
  that run)
- `force_rebuild`: check this if a release for the current upstream tag
  already exists and you want to add/replace these binaries on it, rather
  than being skipped because "this tag is already built."

Leaving `build_envs` blank uses the default set (`tasmota,tasmota-minimal`).

## Customizing

- **Which boards/envs to build** — edit `BUILD_ENVS` in the workflow (a
  comma-separated list of PlatformIO environment names from Tasmota's
  `platformio.ini`, e.g. `tasmota,tasmota-minimal,tasmota-sensors`). Defaults
  to `tasmota,tasmota-minimal`.
- **Other firmware settings** (WiFi, MQTT, extra sensors, etc.) — add more
  `#define`s to `config/user_config_override.h`.
- **Check frequency** — edit the `cron` schedule in the workflow.

## Known issue this repo works around

PlatformIO Core `6.2.0` has an open regression
([pioarduino/platform-espressif32#529](https://github.com/pioarduino/platform-espressif32/issues/529))
where pioarduino-based platforms (Tasmota's ESP32 platforms) get their
`tool-scons` package wiped mid-build due to a version-mismatch check, producing:

```
ModuleNotFoundError: No module named 'SCons.Tool.FortranCommon'
```

The workflow pins `PLATFORMIO_VERSION` to `6.1.19` (last known-good) to avoid
this. Bump it once upstream ships a fix.

## Flashing

- **New device**: flash a `.bin` over USB with `esptool.py` or the Tasmota
  web installer.
- **Existing Tasmota device**: use the device's web UI → **Firmware Upgrade**
  → upload the matching `.bin` (OTA).

On flash-constrained boards (e.g. 1MB ESP8266 modules), the full `tasmota`
build may not leave room for every driver once Prometheus is added. Each
release also includes `tasmota-minimal.bin` — a small stripped-down build
meant as a two-step path for tight-flash devices:

1. Flash the `-minimal` build first (small enough to fit directly).
2. From that device's web UI → **Firmware Upgrade**, OTA it up to the full
   `tasmota` build from the same release.

If even the full build is too big for your specific board's flash, add a
lighter env like `tasmota-lite` to `BUILD_ENVS` in the workflow instead.

## Disclaimer

This is an unofficial, community-style rebuild, not affiliated with the
Tasmota project. Firmware is built directly from Tasmota's own tagged source
with one config change on top.
