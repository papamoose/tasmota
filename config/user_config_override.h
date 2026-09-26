/*
  user_config_override.h - applied automatically by .github/workflows/build-and-release.yml

  Adds on top of whatever the upstream Tasmota release ships as default:
    - Prometheus /metrics support (xsns_91_prometheus.ino)
    - NTP servers
    - America/Denver timezone with correct DST rules (baked in, so it's
      set on first boot without needing a manual Console command)
    - Denver lat/long, used for Sunrise/Sunset timer entries

  If you want to bake in other settings (WiFi SSID, MQTT broker, extra
  sensors, etc.), add them below.
*/

#ifndef _USER_CONFIG_OVERRIDE_H_
#define _USER_CONFIG_OVERRIDE_H_

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

// -- Time - America/Denver (Mountain Time, with DST) -------------------
// Equivalent to Console: Backlog Timezone 99; TimeStd 0,1,11,1,2,-420; TimeDst 0,2,3,1,2,-360
#ifdef APP_TIMEZONE
#undef APP_TIMEZONE
#endif
#define APP_TIMEZONE              99         // 99 = use TIME_DST/TIME_STD rules below instead of a fixed offset

// Daylight time (MDT, UTC-6) starts 2nd Sunday of March at 2am
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
#ifdef TIME_DST_OFFSET
#undef TIME_DST_OFFSET
#endif
#define TIME_DST_OFFSET           -360       // UTC-6 (MDT)

// Standard time (MST, UTC-7) starts 1st Sunday of November at 2am
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
#ifdef TIME_STD_OFFSET
#undef TIME_STD_OFFSET
#endif
#define TIME_STD_OFFSET           -420       // UTC-7 (MST)

// -- Location (Denver, CO) - used for Sunrise/Sunset timer entries ----
#ifdef LATITUDE
#undef LATITUDE
#endif
#define LATITUDE                  39.7392

#ifdef LONGITUDE
#undef LONGITUDE
#endif
#define LONGITUDE                 -104.9903

#endif  // _USER_CONFIG_OVERRIDE_H_
