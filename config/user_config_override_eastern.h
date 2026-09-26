/*
  user_config_override_eastern.h - America/New_York (Eastern Time) variant.

  Copied by the workflow as tasmota/tasmota/user_config_override.h, next to
  user_config_override_base.h. See the base file for the shared settings
  (Prometheus, NTP servers, US DST dates); this file sets the Eastern UTC
  offsets and a reference location (New York, NY) for Sunrise/Sunset timer
  entries.

  Equivalent to Console: Backlog Timezone 99; TimeStd 0,1,11,1,2,-300; TimeDst 0,2,3,1,2,-240
*/

#ifndef _USER_CONFIG_OVERRIDE_H_
#define _USER_CONFIG_OVERRIDE_H_

#include "user_config_override_base.h"

// Daylight time: EDT, UTC-4
#ifdef TIME_DST_OFFSET
#undef TIME_DST_OFFSET
#endif
#define TIME_DST_OFFSET           -240       // UTC-4 (EDT)

// Standard time: EST, UTC-5
#ifdef TIME_STD_OFFSET
#undef TIME_STD_OFFSET
#endif
#define TIME_STD_OFFSET           -300       // UTC-5 (EST)

// -- Location (New York, NY) - used for Sunrise/Sunset timer entries ----
#ifdef LATITUDE
#undef LATITUDE
#endif
#define LATITUDE                  40.7128

#ifdef LONGITUDE
#undef LONGITUDE
#endif
#define LONGITUDE                 -74.0060

#endif  // _USER_CONFIG_OVERRIDE_H_
