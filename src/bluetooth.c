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
	dlog_print(DLOG_DEBUG, LOG_TAG, "set_device_restriction_handler");

	dpm_context_h context;
	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	dpm_bluetooth_policy_h policy = dpm_context_acquire_bluetooth_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get bluetooth policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	char radio_text_quality[][MAX_RADIO_TEXT_LEN] = {"ALLOW", "DISALLOW"};
	int radio_num = ARRAY_SIZE(radio_text_quality);
	handler_display_radio_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), self, radio_text_quality, radio_num);

	int ret = -1;
	if (self->radio_index == 0) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "set device restriction (true)");
		ret = dpm_bluetooth_set_device_restriction(policy, true);
	} else if (self->radio_index == 1) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "set device restriction (false)");
		ret = dpm_bluetooth_set_device_restriction(policy, false);
	} else {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get radio index");
		return POLICY_RESULT_FAIL;
	}
	if (ret < 0) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to set device restriction");
		dpm_context_release_bluetooth_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	dpm_context_release_bluetooth_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_SUCCESS;
}

int is_device_restricted_handler(struct xtk_policy *self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "is_device_restricted_handler");

	dpm_context_h context;
	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	dpm_bluetooth_policy_h policy = dpm_context_acquire_bluetooth_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get bluetooth policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	int allowed = false;
	if (dpm_bluetooth_is_device_restricted(policy, &allowed) != DPM_ERROR_NONE) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to check device restriction");
		dpm_context_release_bluetooth_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}
	dlog_print(DLOG_DEBUG, LOG_TAG, "allow state. (allow: %d)", allowed);

	if (allowed == true)
		display_result_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), "ALLOW");
	else
		display_result_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), "DISALLOW");

	dpm_context_release_bluetooth_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_NONE;
}

int set_uuid_restriction_handler(struct xtk_policy *self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "set_uuid_restriction_handler");

	dpm_context_h context;
	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	dpm_bluetooth_policy_h policy = dpm_context_acquire_bluetooth_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get bluetooth policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	char radio_text_quality[][MAX_RADIO_TEXT_LEN] = {"ALLOW", "DISALLOW"};
	int radio_num = sizeof(radio_text_quality) / sizeof(radio_text_quality[0]);
	handler_display_radio_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), self, radio_text_quality, radio_num);

	int ret = -1;
	if (self->radio_index == 0) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "set uuid restriction (true)");
		ret = dpm_bluetooth_set_uuid_restriction(policy, true);
	} else if (self->radio_index == 1) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "set uuid restriction (false)");
		ret = dpm_bluetooth_set_uuid_restriction(policy, false);
	} else {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get radio index");
		return POLICY_RESULT_FAIL;
	}
	if (ret < 0) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to set uuid restriction");
		dpm_context_release_bluetooth_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	return POLICY_RESULT_SUCCESS;
}

int is_uuid_restricted_handler(struct xtk_policy *self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "is_uuid_restricted_handler");

	dpm_context_h context;
	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	dpm_bluetooth_policy_h policy = dpm_context_acquire_bluetooth_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get bluetooth policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	int allowed = false;
	if (dpm_bluetooth_is_uuid_restricted(policy, &allowed) != DPM_ERROR_NONE) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to check uuid restriction");
		dpm_context_release_bluetooth_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}
	dlog_print(DLOG_DEBUG, LOG_TAG, "allow state. (allow: %d)", allowed);

	if (allowed == true)
		display_result_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), "ALLOW");
	else
		display_result_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), "DISALLOW");

	dpm_context_release_bluetooth_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_NONE;
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
