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

static char radio_text[][MAX_RADIO_TEXT_LEN] = {"Allow", "Disallow"};

int wifi_set_profile_change_restriction_handler(struct xtk_policy* self)
{
	dpm_wifi_policy_h policy;
	dpm_context_h context;
	int ret;

	dlog_print(DLOG_DEBUG, LOG_TAG, __func__);

	handler_display_radio_popup("Restriction", self, radio_text, sizeof(radio_text) / sizeof(char) / MAX_RADIO_TEXT_LEN);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_wifi_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get wifi policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	ret = dpm_wifi_set_profile_change_restriction(policy, self->radio_index);

	dpm_context_release_wifi_policy(context, policy);
	dpm_context_destroy(context);

	return (ret == DPM_ERROR_NONE) ? POLICY_RESULT_SUCCESS : POLICY_RESULT_FAIL;
}

int wifi_is_profile_change_restricted_handler(struct xtk_policy* self)
{	dpm_wifi_policy_h policy;
	dpm_context_h context;
	int state, ret;

	dlog_print(DLOG_DEBUG, LOG_TAG, __func__);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_wifi_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get wifi policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	ret = dpm_wifi_is_profile_change_restricted(policy, &state);

	dpm_context_release_wifi_policy(context, policy);
	dpm_context_destroy(context);

	if (ret == DPM_ERROR_NONE) {
        	display_result_popup("Restriction state", state? "Disallowed":"Allowed");

		return POLICY_RESULT_NONE;
	}

	return POLICY_RESULT_FAIL;
}

int wifi_set_network_access_restriction_handler(struct xtk_policy* self)
{
	dpm_wifi_policy_h policy;
	dpm_context_h context;
	int ret;

	dlog_print(DLOG_DEBUG, LOG_TAG, __func__);

	handler_display_radio_popup("Restriction", self, radio_text, sizeof(radio_text) / sizeof(char) / MAX_RADIO_TEXT_LEN);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_wifi_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get wifi policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	ret = dpm_wifi_set_network_access_restriction(policy, self->radio_index);

	dpm_context_release_wifi_policy(context, policy);
	dpm_context_destroy(context);

	return (ret == DPM_ERROR_NONE) ? POLICY_RESULT_SUCCESS : POLICY_RESULT_FAIL;
}

int wifi_is_network_access_restricted_handler(struct xtk_policy* self)
{
	dpm_wifi_policy_h policy;
	dpm_context_h context;
	int state, ret;

	dlog_print(DLOG_DEBUG, LOG_TAG, __func__);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_wifi_policy(context);

	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get wifi policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	ret = dpm_wifi_is_network_access_restricted(policy, &state);

	dpm_context_release_wifi_policy(context, policy);
	dpm_context_destroy(context);

	if (ret == DPM_ERROR_NONE) {
        	display_result_popup("Restriction state", state? "Disallowed":"Allowed");

		return POLICY_RESULT_NONE;
	}

	return POLICY_RESULT_FAIL;
}

int wifi_add_ssid_to_blocklist_handler(struct xtk_policy* self)
{
	dpm_wifi_policy_h policy;
	dpm_context_h context;
	int ret;

	dlog_print(DLOG_DEBUG, LOG_TAG, __func__);

	handler_display_input_popup("SSID", self);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_wifi_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get wifi policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	ret = dpm_wifi_add_ssid_to_blocklist(policy, self->entry_input);

	dpm_context_release_wifi_policy(context, policy);
	dpm_context_destroy(context);

	return (ret == DPM_ERROR_NONE) ? POLICY_RESULT_SUCCESS : POLICY_RESULT_FAIL;
}

int wifi_remove_ssid_from_blocklist_handler(struct xtk_policy* self)
{
	dpm_wifi_policy_h policy;
	dpm_context_h context;
	int ret;

	dlog_print(DLOG_DEBUG, LOG_TAG, __func__);

	handler_display_input_popup("SSID", self);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_wifi_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get wifi policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	ret = dpm_wifi_remove_ssid_from_blocklist(policy, self->entry_input);

	dpm_context_release_wifi_policy(context, policy);
	dpm_context_destroy(context);

	return (ret == DPM_ERROR_NONE) ? POLICY_RESULT_SUCCESS : POLICY_RESULT_FAIL;
}

xtk_policy_t xtk_wifi_policy[] = {
	{
		.id = "WIFI_SET_PROFILE_CHANGE_RESTRICTION",
		.handler = wifi_set_profile_change_restriction_handler
	},
	{
		.id = "WIFI_IS_PROFILE_CHANGE_RESTRICTED",
		.handler = wifi_is_profile_change_restricted_handler
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
