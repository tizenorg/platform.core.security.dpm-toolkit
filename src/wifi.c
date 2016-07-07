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

#include <dpm/wifi.h>

#include "dpm-toolkit.h"

int wifi_set_profile_change_state_handler(struct xtk_policy* self)
{
	int state, allow;
	device_policy_manager_h handle = NULL;

	if (xtk_open_radio_popup(self, STATE_CHANGE_OPTIONS, &allow) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	}

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_wifi_set_profile_change_restriction(handle, allow) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_wifi_is_profile_change_restricted(handle, &state) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (state == allow) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

int wifi_get_profile_change_state_handler(struct xtk_policy* self)
{
	int state;
	device_policy_manager_h handle = NULL;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_wifi_is_profile_change_restricted(handle, &state) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

int wifi_set_network_access_restriction_handler(struct xtk_policy* self)
{
	int state, enable;
	device_policy_manager_h handle = NULL;

	if (xtk_open_radio_popup(self, RESTRICTION_MODE_OPTIONS, &enable) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	}

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_wifi_set_network_access_restriction(handle, enable) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_wifi_is_network_access_restricted(handle, &state) != 0) {
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

int wifi_is_network_access_restricted_handler(struct xtk_policy* self)
{
	int state;
	device_policy_manager_h handle = NULL;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_wifi_is_network_access_restricted(handle, &state) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, RESTRICTION_MODE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

int wifi_add_ssid_to_blocklist_handler(struct xtk_policy* self)
{
	char* entry = NULL;
	device_policy_manager_h handle = NULL;

	if (xtk_open_entry_popup(self, NULL, "SSID", &entry) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
		return POLICY_RESULT_FAIL;
	};

	if (entry == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get null string");
		return POLICY_RESULT_FAIL;
	}

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_wifi_add_ssid_to_blocklist(handle, entry) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, entry);
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

int wifi_remove_ssid_from_blocklist_handler(struct xtk_policy* self)
{
	char* entry = NULL;
	device_policy_manager_h handle = NULL;

	if (xtk_open_entry_popup(self, NULL, "SSID", &entry) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
	};

	if (entry == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get null string");
		return POLICY_RESULT_FAIL;
	}

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_wifi_remove_ssid_from_blocklist(handle, entry) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, entry);
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

xtk_policy_t xtk_wifi_policy[] = {
	{
		.id = "WIFI_SET_PROFILE_CHANGE_STATE",
		.handler = wifi_set_profile_change_state_handler
	},
	{
		.id = "WIFI_GET_PROFILE_CHANGE_STATE",
		.handler = wifi_get_profile_change_state_handler
	},
	{
		.id = "WIFI_SET_NETWORK_ACCESS_RESTRICTION",
		.handler = wifi_set_network_access_restriction_handler
	},
	{
		.id = "WIFI_IS_NETWORK_ACCESS_RESTRICTED",
		.handler = wifi_is_network_access_restricted_handler
	},
	{
		.id = "WIFI_ADD_SSID_TO_BLOCKLIST",
		.handler = wifi_add_ssid_to_blocklist_handler
	},
	{
		.id = "WIFI_REMOVE_SSID_FROM_BLOCKLIST",
		.handler = wifi_remove_ssid_from_blocklist_handler
	},
};

xtk_policy_group_t wifi_policy_group = {
	.id = "WIFI"
};

void __CONSTRUCTOR__ xtk_wifi_policy_constructor()
{
	int ret = 0;

	dlog_print(DLOG_ERROR, LOG_TAG, "wifi policy constructor");

	int nr = ARRAY_SIZE(xtk_wifi_policy);
	ret = xtk_init_policy(&wifi_policy_group, xtk_wifi_policy, nr);
	if (ret < 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "wifi policy initialization fail");
	}
}
