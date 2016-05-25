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
	dpm_context_h context = NULL;
	dpm_bluetooth_policy_h policy = NULL;

	if (xtk_open_radio_popup(self, RESTRICTION_MODE_OPTIONS, &enable) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	}

	dlog_print(DLOG_ERROR, LOG_TAG, "enable %d", enable);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_bluetooth_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device restriction policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_bluetooth_set_device_restriction(policy, enable) != 0) {
		dpm_context_release_bluetooth_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_bluetooth_is_device_restricted(policy, &state) != 0) {
		dpm_context_release_bluetooth_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (state == enable) {
		dpm_context_release_bluetooth_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, RESTRICTION_MODE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_bluetooth_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int is_device_restricted_handler(struct xtk_policy *self)
{
	int state;
	dpm_context_h context = NULL;
	dpm_bluetooth_policy_h policy = NULL;

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_bluetooth_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device restriction policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_bluetooth_is_device_restricted(policy, &state) == 0) {
		dpm_context_release_bluetooth_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, RESTRICTION_MODE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_bluetooth_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int set_uuid_restriction_handler(struct xtk_policy *self)
{
	int state;
	int enable;
	dpm_context_h context = NULL;
	dpm_bluetooth_policy_h policy = NULL;

	if (xtk_open_radio_popup(self, RESTRICTION_MODE_OPTIONS, &enable) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	}

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_bluetooth_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create uuid restriction policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_bluetooth_set_uuid_restriction(policy, enable) != 0) {
		dpm_context_release_bluetooth_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_bluetooth_is_uuid_restricted(policy, &state) != 0) {
		dpm_context_release_bluetooth_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (state == enable) {
		dpm_context_release_bluetooth_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, RESTRICTION_MODE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_bluetooth_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int is_uuid_restricted_handler(struct xtk_policy *self)
{
	int state;
	dpm_context_h context = NULL;
	dpm_bluetooth_policy_h policy = NULL;

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_bluetooth_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create uuid restriction policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_bluetooth_is_uuid_restricted(policy, &state) == 0) {
		dpm_context_release_bluetooth_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, RESTRICTION_MODE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_bluetooth_policy(context, policy);
	dpm_context_destroy(context);

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
