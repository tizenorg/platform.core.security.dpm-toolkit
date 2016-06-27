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

#include <stdbool.h>

#include "dpm-toolkit.h"
#include <dpm/bluetooth.h>

int set_device_restriction_handler(struct xtk_policy *self)
{
	int state;
	int enable;
	device_policy_manager_h handle = NULL;

	if (xtk_open_radio_popup(self, RESTRICTION_MODE_OPTIONS, &enable) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	}

	dlog_print(DLOG_ERROR, LOG_TAG, "enable %d", enable);

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_bluetooth_set_device_restriction(handle, enable) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_bluetooth_is_device_restricted(handle, &state) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (state == enable) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, RESTRICTION_MODE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

int is_device_restricted_handler(struct xtk_policy *self)
{
	int state;
	device_policy_manager_h handle = NULL;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_bluetooth_is_device_restricted(handle, &state) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, RESTRICTION_MODE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

int set_uuid_restriction_handler(struct xtk_policy *self)
{
	int state;
	int enable;
	device_policy_manager_h handle = NULL;

	if (xtk_open_radio_popup(self, RESTRICTION_MODE_OPTIONS, &enable) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	}

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_bluetooth_set_uuid_restriction(handle, enable) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_bluetooth_is_uuid_restricted(handle, &state) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (state == enable) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, RESTRICTION_MODE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

int is_uuid_restricted_handler(struct xtk_policy *self)
{
	int state;
	device_policy_manager_h handle = NULL;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_bluetooth_is_uuid_restricted(handle, &state) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, RESTRICTION_MODE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

xtk_policy_t xtk_bluetooth_policy[] = {
	{
		.id = "SET_DEVICE_RESTRICTION",
		.handler = set_device_restriction_handler
	},
	{
		.id = "IS_DEVICE_RESTRICTED",
		.handler = is_device_restricted_handler
	},
	{
		.id = "SET_UUID_RESTRICTION",
		.handler = set_uuid_restriction_handler
	},
	{
		.id = "IS_UUID_RESTRICTED",
		.handler = is_uuid_restricted_handler
	}
};

xtk_policy_group_t bluetooth_policy_group = {
	.id = "BLUETOOTH"
};

void __CONSTRUCTOR__ xtk_bluetooth_policy_constructor()
{
	int ret = 0;
	dlog_print(DLOG_DEBUG, LOG_TAG, "bluetooth policy constructor");

	int nr = ARRAY_SIZE(xtk_bluetooth_policy);
	ret = xtk_init_policy(&bluetooth_policy_group, xtk_bluetooth_policy, nr);

	if (ret < 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "bluetooth policy initialization fail");
	}
}
