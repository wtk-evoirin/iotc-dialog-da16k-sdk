/* Copyright (C) 2020 Avnet - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Authors: Nikola Markovic <nikola.markovic@avnet.com> et al.
 */

#ifndef IOTCONNECT_LIB_H
#define IOTCONNECT_LIB_H

#include <stdbool.h>

// SSL style configuration. You can use a different include
#ifndef ITOTCONNECT_LIB_CONFIG_HEADER

#include "iotconnect_lib_config.h"

#else
#include ITOTCONNECT_LIB_CONFIG_HEADER
#endif

#include "iotconnect_event.h"
#include "iotconnect_telemetry.h"

#ifdef __cplusplus
extern "C" {
#endif


// CPID + '-'(separator) + UUID(device name)  cannot exceed 128 characters (IoTHub name limitation)
#define MAX_DEVICE_COMBINED_NAME 128

typedef struct {
    const char *duid;   // Your Device Unique ID
    const char *cpid;   // Obtained Settings->KeyVault at IoTConnect Web Site
    const char *env;    // Obtained Settings->KeyVault at IoTConnect Web Site
} IotclDeviceConfig;

typedef struct IotclTelemetryConfig {
    // Can be copied at the device page. Can be obtained via REST Sync call.
    // Device template GUID required to send telemetry data.
    const char *dtg;
} IotclTelemetryConfig;

typedef struct {
    IotclDeviceConfig device;
    IotclTelemetryConfig telemetry;
    IotclEventFunctions event_functions; // Event callbacks for the event library. @see iotconnect_event.h
} IotclConfig;

IotclConfig *iotcl_get_config(void);

bool iotcl_preinit_certs(IotclConfig *c); // pre-initialization, e.g. setting up HTTPS/MQTTS certificates -- may not be affected by iotcl_deinit()
bool iotcl_init(IotclConfig *c);
void iotcl_deinit(void);            // undo iotcl_init()

#ifdef __cplusplus
}
#endif

#endif //IOTCONNECT_LIB_H
