/*
  user_config_override.h - applied automatically by .github/workflows/build-and-release.yml

  This is intentionally minimal: it only adds Prometheus /metrics support
  (xsns_91_prometheus.ino) on top of whatever the upstream Tasmota release
  ships as its default configuration. Everything else stays stock.

  If you want to bake in other settings (WiFi SSID, MQTT broker, extra
  sensors, etc.), add them below the USE_PROMETHEUS block.
*/

#ifndef _USER_CONFIG_OVERRIDE_H_
#define _USER_CONFIG_OVERRIDE_H_

#ifndef USE_PROMETHEUS
#define USE_PROMETHEUS          // Enable /metrics HTTP endpoint for Prometheus scraping
#endif

#endif  // _USER_CONFIG_OVERRIDE_H_
