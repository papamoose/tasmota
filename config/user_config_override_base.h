/*
  user_config_override_base.h - settings shared by all US time zone variants.

  Applied automatically by .github/workflows/build-and-release.yml. The
  workflow copies this file next to the selected per-timezone file
  (config/user_config_override_<zone>.h) inside tasmota/tasmota/. The
  per-timezone file is copied as user_config_override.h, so Tasmota picks it
  up, and it #includes this file.

  Applies on top of whatever the upstream Tasmota release ships as default:
    - Prometheus /metrics support (xsns_91_prometheus.ino)
    - NTP servers
    - APP_TIMEZONE 99 plus the US DST transition dates (2nd Sunday of March
      at 2am to 1st Sunday of November at 2am), so freshly flashed devices
      get the right time without a manual Console command
  The per-timezone file sets the UTC offsets (TIME_DST_OFFSET /
  TIME_STD_OFFSET) and a reference LATITUDE/LONGITUDE (used for
  Sunrise/Sunset timer entries) for its zone.

  If you want to bake in other settings (WiFi SSID, MQTT broker, extra
  sensors, etc.), add them here so every zone gets them.
*/

#ifndef _USER_CONFIG_OVERRIDE_BASE_H_
#define _USER_CONFIG_OVERRIDE_BASE_H_

#ifndef USE_PROMETHEUS
#define USE_PROMETHEUS          // Enable /metrics HTTP endpoint for Prometheus scraping
#endif

// -- Time - NTP servers -----------------------------------------------
#ifdef NTP_SERVER1
#undef NTP_SERVER1
#endif
#define NTP_SERVER1              "pool.ntp.org"

#ifdef NTP_SERVER2
#undef NTP_SERVER2
#endif
#define NTP_SERVER2              "time.google.com"

#ifdef NTP_SERVER3
#undef NTP_SERVER3
#endif
#define NTP_SERVER3              "time.cloudflare.com"

// -- Time - US DST rules (identical for all four US time zones) --------
// 99 = derive the UTC offset from the TIME_DST/TIME_STD rules below
// instead of a fixed offset.
#ifdef APP_TIMEZONE
#undef APP_TIMEZONE
#endif
#define APP_TIMEZONE              99

// Daylight time starts 2nd Sunday of March at 2am
#ifdef TIME_DST_HEMISPHERE
#undef TIME_DST_HEMISPHERE
#endif
#define TIME_DST_HEMISPHERE       North
#ifdef TIME_DST_WEEK
#undef TIME_DST_WEEK
#endif
#define TIME_DST_WEEK             Second
#ifdef TIME_DST_DAY
#undef TIME_DST_DAY
#endif
#define TIME_DST_DAY              Sun
#ifdef TIME_DST_MONTH
#undef TIME_DST_MONTH
#endif
#define TIME_DST_MONTH            Mar
#ifdef TIME_DST_HOUR
#undef TIME_DST_HOUR
#endif
#define TIME_DST_HOUR             2

// Standard time starts 1st Sunday of November at 2am
#ifdef TIME_STD_HEMISPHERE
#undef TIME_STD_HEMISPHERE
#endif
#define TIME_STD_HEMISPHERE       North
#ifdef TIME_STD_WEEK
#undef TIME_STD_WEEK
#endif
#define TIME_STD_WEEK             First
#ifdef TIME_STD_DAY
#undef TIME_STD_DAY
#endif
#define TIME_STD_DAY              Sun
#ifdef TIME_STD_MONTH
#undef TIME_STD_MONTH
#endif
#define TIME_STD_MONTH            Nov
#ifdef TIME_STD_HOUR
#undef TIME_STD_HOUR
#endif
#define TIME_STD_HOUR             2

// TIME_DST_OFFSET, TIME_STD_OFFSET, LATITUDE, and LONGITUDE are set by the
// per-timezone file (config/user_config_override_<zone>.h).

#endif  // _USER_CONFIG_OVERRIDE_BASE_H_
