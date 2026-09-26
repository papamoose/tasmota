# tasmota-prometheus

Automatically tracks [Tasmota](https://github.com/arendst/Tasmota) releases
and republishes matching firmware builds with the Prometheus `/metrics`
endpoint (`USE_PROMETHEUS`) enabled — nothing else changed.

It also bakes in NTP servers and a US time zone (with correct DST rules) as
compile-time defaults, so freshly flashed devices get the right time and
don't need a manual `Timezone`/`TimeStd`/`TimeDst` Console command. Each
release builds every environment once per zone - **America/Eastern**,
**America/Central**, **America/Mountain**, and **America/Pacific** - and
labels the binaries with the zone (e.g. `tasmota-eastern.bin`). Pick the
one that matches your wall clock. The zone only changes the time defaults,
so any binary works anywhere.

## How it works

`.github/workflows/build-and-release.yml` runs on a schedule (once a day,
plus manual trigger):

1. Asks the GitHub API for `arendst/Tasmota`'s latest release tag.
2. Checks if this repo already has a release with that same tag. If so, it
   exits — nothing to do.
3. If it's a new tag: it creates a GitHub release in *this* repo tagged
   with the **same version string** as upstream, then runs one build job
   per US time zone in parallel. Each job checks out Tasmota **at that
   exact tag**, copies in the shared override
   ([`config/user_config_override_base.h`](config/user_config_override_base.h)
   - Prometheus and NTP) plus that zone's override
   ([`config/user_config_override_<zone>.h`](config/user_config_override_eastern.h)
   - UTC offsets and reference city), builds every environment with
   PlatformIO, and uploads the `.bin` files labeled with the zone (e.g.
   `tasmota-eastern.bin`) to the release.

So your releases page ends up mirroring Tasmota's, one-for-one, just with
Prometheus baked in.

## Building just the minimal env

**Locally**, from inside a Tasmota checkout (copy in the shared override
plus one zone file first):

```bash
cp config/user_config_override_base.h    tasmota/tasmota/
cp config/user_config_override_eastern.h tasmota/tasmota/user_config_override.h
pio run -e tasmota         # full build
pio run -e tasmota-minimal # stripped-down build
```

**Via this repo's workflow**, without editing any files: go to **Actions →
Track Tasmota releases... → Run workflow**, and fill in:

- `build_envs`: `tasmota-minimal` (overrides the default list for just
  that run)
- `force_rebuild`: check this if a release for the current upstream tag
  already exists and you want to add/replace these binaries on it, rather
  than being skipped because "this tag is already built."

Leaving `build_envs` blank uses the default set
(`tasmota,tasmota-minimal`).

## Customizing

- **Timezones / locations** — shared settings (Prometheus, NTP servers,
  US DST dates) live in `config/user_config_override_base.h`. Each zone's
  UTC offsets (`TIME_DST_OFFSET` / `TIME_STD_OFFSET`) and reference city
  (`LATITUDE` / `LONGITUDE`) live in its
  `config/user_config_override_<zone>.h` (`eastern` = New York,
  `central` = Chicago, `mountain` = Denver, `pacific` = Los Angeles).
  To add a zone, copy an existing zone file, adjust the offsets and
  coordinates, and add the zone name to the `zone` matrix in the workflow.
- **Which boards/envs to build** — edit `BUILD_ENVS` in the workflow (a
  comma-separated list of PlatformIO environment names from Tasmota's
  `platformio.ini`, e.g. `tasmota,tasmota-sensors`). Defaults to
  `tasmota,tasmota-minimal`.
- **Other firmware settings** (WiFi, MQTT, extra sensors, etc.) — add more
  `#define`s to `config/user_config_override.h`.
- **Check frequency** — edit the `cron` schedule in the workflow.

## Known issue this repo works around

PlatformIO Core `6.2.0` has an open regression
([pioarduino/platform-espressif32#529](https://github.com/pioarduino/platform-espressif32/issues/529))
where pioarduino-based platforms (which Tasmota's ESP8266/ESP32 platforms
are) get their `tool-scons` package wiped mid-build due to a version-mismatch
check, producing:

```
ModuleNotFoundError: No module named 'SCons.Tool.FortranCommon'
```

The workflow pins `PLATFORMIO_VERSION` to `6.1.19` (last known-good) to avoid
this. Bump it once upstream ships a fix.

## Flashing

- **New device**: flash a `.bin` over USB with `esptool.py` or the Tasmota
  web installer.
- **Existing Tasmota device**: use the device's web UI → **Firmware Upgrade**
  → upload the matching `.bin` (OTA). Note: OTA does not re-apply the
  baked-in time defaults - the device keeps its current Timezone/NTP/
  location settings (see **Important** below).

Every binary is labeled with its zone (`tasmota-eastern.bin`,
`tasmota-central.bin`, `tasmota-mountain.bin`, `tasmota-pacific.bin`). The
zone only changes the time defaults, so a device in any US time zone can
run any of them, but pick the matching one to skip a manual `Timezone`
setup after a reset.

On flash-constrained boards (e.g. 1MB ESP8266 modules), the full `tasmota`
build may not leave room for every driver once Prometheus is added. Each
release also includes `tasmota-minimal-<zone>.bin` — small stripped-down
builds meant as a two-step path for tight-flash devices:

1. Flash the matching `-minimal` build first (small enough to fit directly).
2. From that device's web UI → **Firmware Upgrade**, OTA it up to the full
   `tasmota-<zone>.bin` build from the same release.

If even the full build is too big for your specific board's flash, add a
lighter env like `tasmota-lite` to `BUILD_ENVS` in the workflow instead.

## Disclaimer

This is an unofficial, community-style rebuild, not affiliated with the
Tasmota project. Firmware is built directly from Tasmota's own tagged source
with one config change on top.

## Important: baked-in defaults only apply to fresh/reset devices

`NTP_SERVER1-3`, `APP_TIMEZONE`, `TIME_STD_*`, `TIME_DST_*`, `LATITUDE`, and
`LONGITUDE` are all "SECTION1" parameters. Tasmota only re-applies these
compiled-in defaults when:

- flashing a device for the first time (never configured before), or
- doing a factory reset, or
- the firmware's `CFG_HOLDER` value has changed since the device's last save

On a device you already have running, OTA-updating to a build from this repo
will **not** silently overwrite your existing Timezone/NTP/location settings
— your device keeps whatever it's currently configured with. To apply the
baked-in defaults on such a device, either do a factory reset (`Reset 1` in
Console, then re-enter your WiFi/MQTT settings) or run the Console command
for your zone:

| Zone | Console command |
| --- | --- |
| Eastern (America/New_York) | `Backlog Timezone 99; TimeStd 0,1,11,1,2,-300; TimeDst 0,2,3,1,2,-240` |
| Central (America/Chicago) | `Backlog Timezone 99; TimeStd 0,1,11,1,2,-360; TimeDst 0,2,3,1,2,-300` |
| Mountain (America/Denver) | `Backlog Timezone 99; TimeStd 0,1,11,1,2,-420; TimeDst 0,2,3,1,2,-360` |
| Pacific (America/Los_Angeles) | `Backlog Timezone 99; TimeStd 0,1,11,1,2,-480; TimeDst 0,2,3,1,2,-420` |

The commands set the DST/STD rules; Tasmota derives the correct offset from
them automatically. The NTP servers are baked into every build, so you only
need them if your device does not sync time at all (`NtpServer1
1.na.pool.ntp.org`).
