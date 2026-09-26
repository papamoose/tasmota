/*
  user_config_override_central.h - America/Chicago (Central Time) variant.

  Copied by the workflow as tasmota/tasmota/user_config_override.h, next to
  user_config_override_base.h. See the base file for the shared settings
  (Prometheus, NTP servers, US DST dates); this file sets the Central UTC
  offsets and a reference location (Chicago, IL) for Sunrise/Sunset timer
  entries.

  Equivalent to Console: Backlog Timezone 99; TimeStd 0,1,11,1,2,-360; TimeDst 0,2,3,1,2,-300
*/

#ifndef _USER_CONFIG_OVERRIDE_H_
#define _USER_CONFIG_OVERRIDE_H_

#include "user_config_override_base.h"

// Daylight time: CDT, UTC-5
#ifdef TIME_DST_OFFSET
#undef TIME_DST_OFFSET
#endif
#define TIME_DST_OFFSET           -300       // UTC-5 (CDT)

// Standard time: CST, UTC-6
#ifdef TIME_STD_OFFSET
#undef TIME_STD_OFFSET
#endif
#define TIME_STD_OFFSET           -360       // UTC-6 (CST)

// -- Location (Chicago, IL) - used for Sunrise/Sunset timer entries -----
#ifdef LATITUDE
#undef LATITUDE
#endif
#define LATITUDE                  41.8781

#ifdef LONGITUDE
#undef LONGITUDE
#endif
#define LONGITUDE                 -87.6298

#endif  // _USER_CONFIG_OVERRIDE_H_
