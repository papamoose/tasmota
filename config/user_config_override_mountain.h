/*
  user_config_override_mountain.h - America/Denver (Mountain Time) variant.

  Copied by the workflow as tasmota/tasmota/user_config_override.h, next to
  user_config_override_base.h. See the base file for the shared settings
  (Prometheus, NTP servers, US DST dates); this file sets the Mountain UTC
  offsets and a reference location (Denver, CO) for Sunrise/Sunset timer
  entries.

  Equivalent to Console: Backlog Timezone 99; TimeStd 0,1,11,1,2,-420; TimeDst 0,2,3,1,2,-360
*/

#ifndef _USER_CONFIG_OVERRIDE_H_
#define _USER_CONFIG_OVERRIDE_H_

#include "user_config_override_base.h"

// Daylight time: MDT, UTC-6
#ifdef TIME_DST_OFFSET
#undef TIME_DST_OFFSET
#endif
#define TIME_DST_OFFSET           -360       // UTC-6 (MDT)

// Standard time: MST, UTC-7
#ifdef TIME_STD_OFFSET
#undef TIME_STD_OFFSET
#endif
#define TIME_STD_OFFSET           -420       // UTC-7 (MST)

// -- Location (Denver, CO) - used for Sunrise/Sunset timer entries ------
#ifdef LATITUDE
#undef LATITUDE
#endif
#define LATITUDE                  39.7392

#ifdef LONGITUDE
#undef LONGITUDE
#endif
#define LONGITUDE                 -104.9903

#endif  // _USER_CONFIG_OVERRIDE_H_
