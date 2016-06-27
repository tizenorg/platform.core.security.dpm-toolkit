/*
 *  Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License
 */

#include <dpm/security.h>

#include "dpm-toolkit.h"

int lock_now_handler(struct xtk_policy* self)
{
	device_policy_manager_h handle;

	if (xtk_open_confirm_popup(self,"This operation will lockout the screen") == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	};

	handle = dpm_manager_create();
	if (handle == NULL) {
		xtk_open_message_popup(self, "Failed to create device policy manager");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_security_lockout_screen(handle) != DPM_ERROR_NONE) {
		xtk_open_message_popup(self, "Failed to lockout screen");
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	dpm_manager_destroy(handle);

	return POLICY_RESULT_SUCCESS;
}

int encrypt_device_handler(struct xtk_policy* self)
{
    int index;
    device_policy_manager_h handle;
    const char *text[] = {
        "Encrypt Internal Storage",
        "Encrypt External Storage"
    };

    if (xtk_open_radio_popup(self, text, ARRAY_SIZE(text), &index) == XTK_EVENT_CANCEL) {
        dlog_print(DLOG_DEBUG, LOG_TAG, "Selection canceled");
        return POLICY_RESULT_NONE;
    }

    handle = dpm_manager_create();
    if (handle == NULL) {
        xtk_open_message_popup(self, "Failed to create device policy manager");
        return POLICY_RESULT_FAIL;
    }

    if (index == 0) {
        if (dpm_security_set_internal_storage_encryption(handle, TRUE) != DPM_ERROR_NONE) {
            dpm_manager_destroy(handle);
            xtk_open_message_popup(self, "Failed to enforce policy");
            return POLICY_RESULT_FAIL;
        }
    } else if (index == 1) {
        if (dpm_security_set_external_storage_encryption(handle, TRUE) != DPM_ERROR_NONE) {
            dpm_manager_destroy(handle);
            xtk_open_message_popup(self, "Failed to enforce policy");
            return POLICY_RESULT_FAIL;
        }
    }

    dpm_manager_destroy(handle);

    xtk_open_message_popup(self, "Operation successfully triggerred, "
                                 "but product must provide encryption backend");

    return POLICY_RESULT_SUCCESS;
}

int decrypt_device_handler(struct xtk_policy* self)
{
    int index;
    device_policy_manager_h handle;
    const char *text[] = {
        "Decrypt Internal Storage",
        "Decrypt External Storage"
    };

    if (xtk_open_radio_popup(self, text, ARRAY_SIZE(text), &index) == XTK_EVENT_CANCEL) {
        dlog_print(DLOG_DEBUG, LOG_TAG, "Selection canceled");
        return POLICY_RESULT_NONE;
    }

    handle = dpm_manager_create();
    if (handle == NULL) {
        xtk_open_message_popup(self, "Failed to create device policy manager");
        return POLICY_RESULT_FAIL;
    }

    if (index == 0) {
        if (dpm_security_set_internal_storage_encryption(handle, FALSE) != DPM_ERROR_NONE) {
            dpm_manager_destroy(handle);
            xtk_open_message_popup(self, "Failed to enforce policy");
            return POLICY_RESULT_FAIL;
        }
    } else if (index == 1) {
        if (dpm_security_set_external_storage_encryption(handle, FALSE) != DPM_ERROR_NONE) {
            dpm_manager_destroy(handle);
            xtk_open_message_popup(self, "Failed to enforce policy");
            return POLICY_RESULT_FAIL;
        }
    }

    dpm_manager_destroy(handle);

    xtk_open_message_popup(self, "Operation successfully triggerred, "
                                 "but product must provide decryption backend");

    return POLICY_RESULT_SUCCESS;

}

int wipe_data_handler(struct xtk_policy* self)
{
    int index;
    device_policy_manager_h handle;
    const char *text[] = {
        "Wipe Internal Storage",
        "Wipe External Storage"
    };

    if (xtk_open_radio_popup(self, text, ARRAY_SIZE(text), &index) == XTK_EVENT_CANCEL) {
        dlog_print(DLOG_DEBUG, LOG_TAG, "Selection canceled");
        return POLICY_RESULT_NONE;
    }

    handle = dpm_manager_create();
    if (handle == NULL) {
        xtk_open_message_popup(self, "Failed to create device policy manager");
        return POLICY_RESULT_FAIL;
    }

    if (index == 0) {
        if (dpm_security_wipe_data(handle, DPM_SECURITY_WIPE_INTERNAL_STORAGE) != DPM_ERROR_NONE) {
            dpm_manager_destroy(handle);
            xtk_open_message_popup(self, "Failed to enforce policy");
            return POLICY_RESULT_FAIL;
        }
    } else if (index == 1) {
        if (dpm_security_wipe_data(handle, DPM_SECURITY_WIPE_EXTERNAL_STORAGE) != DPM_ERROR_NONE) {
            dpm_manager_destroy(handle);
            xtk_open_message_popup(self, "Failed to enforce policy");
            return POLICY_RESULT_FAIL;
        }
    }

    dpm_manager_destroy(handle);

    xtk_open_message_popup(self, "Operation successfully triggerred "
                                 "but it may take a long time to complete");

    return POLICY_RESULT_SUCCESS;
}

xtk_policy_t xtk_security_policy[] = {
	{
		.id = "LOCK_NOW",
		.handler = lock_now_handler
	},
	{
		.id = "ENCRYPT_DEVICE",
		.handler = encrypt_device_handler
	},
	{
		.id = "DECRYPT_DEVICE",
		.handler = decrypt_device_handler
	},
	{
		.id = "WIPE_DATA",
		.handler = wipe_data_handler
	}
};

xtk_policy_group_t security_policy_group = {
	.id = "SECURITY"
};

void __CONSTRUCTOR__ xtk_security_policy_constructor()
{
	int ret = 0;

	dlog_print(DLOG_DEBUG, LOG_TAG, "security policy constructor");

	int nr = ARRAY_SIZE(xtk_security_policy);
	ret = xtk_init_policy(&security_policy_group, xtk_security_policy, nr);
	if (ret < 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "security policy initialization fail");
	}
}
