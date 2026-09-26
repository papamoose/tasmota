/*
  user_config_override_pacific.h - America/Los_Angeles (Pacific Time) variant.

  Copied by the workflow as tasmota/tasmota/user_config_override.h, next to
  user_config_override_base.h. See the base file for the shared settings
  (Prometheus, NTP servers, US DST dates); this file sets the Pacific UTC
  offsets and a reference location (Los Angeles, CA) for Sunrise/Sunset
  timer entries.

  Equivalent to Console: Backlog Timezone 99; TimeStd 0,1,11,1,2,-480; TimeDst 0,2,3,1,2,-420
*/

#ifndef _USER_CONFIG_OVERRIDE_H_
#define _USER_CONFIG_OVERRIDE_H_

#include "user_config_override_base.h"

// Daylight time: PDT, UTC-7
#ifdef TIME_DST_OFFSET
#undef TIME_DST_OFFSET
#endif
#define TIME_DST_OFFSET           -420       // UTC-7 (PDT)

// Standard time: PST, UTC-8
#ifdef TIME_STD_OFFSET
#undef TIME_STD_OFFSET
#endif
#define TIME_STD_OFFSET           -480       // UTC-8 (PST)

// -- Location (Los Angeles, CA) - used for Sunrise/Sunset timer entries -
#ifdef LATITUDE
#undef LATITUDE
#endif
#define LATITUDE                  34.0522

#ifdef LONGITUDE
#undef LONGITUDE
#endif
#define LONGITUDE                 -118.2437

#endif  // _USER_CONFIG_OVERRIDE_H_
