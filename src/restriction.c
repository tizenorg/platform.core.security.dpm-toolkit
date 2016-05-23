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

#include "dpm-toolkit.h"
#include <dpm/restriction.h>

int set_camera_state_handler(struct xtk_policy *self)
{
	int state;
	int allow;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	if (xtk_open_radio_popup(self, STATE_CHANGE_OPTIONS, &allow) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	}

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create camera policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_set_camera_state(policy, allow) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_camera_state(policy, &state) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (state == allow) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int get_camera_state_handler(struct xtk_policy *self)
{
	int state;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create camera policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_camera_state(policy, &state) == 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int set_microphone_state_handler(struct xtk_policy *self)
{
	int state;
	int allow;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	if (xtk_open_radio_popup(self, STATE_CHANGE_OPTIONS, &allow) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	}

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create Microphone policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_set_microphone_state(policy, allow) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_microphone_state(policy, &state) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (state == allow) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int get_microphone_state_handler(struct xtk_policy *self)
{
	int state;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create microphone policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_microphone_state(policy, &state) == 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int set_location_state_handler(struct xtk_policy *self)
{
	int state;
	int allow;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	if (xtk_open_radio_popup(self, STATE_CHANGE_OPTIONS, &allow) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	}

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create location policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_set_location_state(policy, allow) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_location_state(policy, &state) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (state == allow) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int get_location_state_handler(struct xtk_policy *self)
{
	int state, ret;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create location policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	ret = dpm_restriction_get_location_state(policy, &state);
	if (ret == 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int set_clipboard_state_handler(struct xtk_policy *self)
{
	int state;
	int allow;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	if (xtk_open_radio_popup(self, STATE_CHANGE_OPTIONS, &allow) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	}

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create clipboard policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_set_clipboard_state(policy, allow) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_clipboard_state(policy, &state) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (state == allow) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int get_clipboard_state_handler(struct xtk_policy *self)
{
	int state;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create clipboard policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_clipboard_state(policy, &state) == 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int set_settings_changes_state_handler(struct xtk_policy *self)
{
	int state;
	int allow;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	if (xtk_open_radio_popup(self, STATE_CHANGE_OPTIONS, &allow) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	}

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create setting changes policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_set_settings_changes_state(policy, allow) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_settings_changes_state(policy, &state) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (state == allow) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int get_settings_changes_state_handler(struct xtk_policy *self)
{
	int state;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create setting changes policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_settings_changes_state(policy, &state) == 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int set_usb_debugging_state_handler(struct xtk_policy *self)
{
	int state;
	int allow;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	if (xtk_open_radio_popup(self, STATE_CHANGE_OPTIONS, &allow) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	}

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create usb debugging policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_set_usb_debugging_state(policy, allow) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_usb_debugging_state(policy, &state) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (state == allow) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int get_usb_debugging_state_handler(struct xtk_policy *self)
{
	int state;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create usb debugging policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_usb_debugging_state(policy, &state) == 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int set_wifi_state_handler(struct xtk_policy *self)
{
	int state;
	int allow;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	if (xtk_open_radio_popup(self, STATE_CHANGE_OPTIONS, &allow) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	}

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create wifi policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_set_wifi_state(policy, allow) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_wifi_state(policy, &state) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (state == allow) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int get_wifi_state_handler(struct xtk_policy *self)
{
	int state;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create wifi policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_wifi_state(policy, &state) == 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int set_wifi_hotspot_state_handler(struct xtk_policy *self)
{
	int state;
	int allow;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	if (xtk_open_radio_popup(self, STATE_CHANGE_OPTIONS, &allow) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	}

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create wifi hotspot policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_set_wifi_hotspot_state(policy, allow) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_wifi_hotspot_state(policy, &state) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (state == allow) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int get_wifi_hotspot_state_handler(struct xtk_policy *self)
{
	int state;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create wifi hotspot policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_wifi_hotspot_state(policy, &state) == 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int set_bluetooth_tethering_state_handler(struct xtk_policy *self)
{
	int state;
	int allow;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	if (xtk_open_radio_popup(self, STATE_CHANGE_OPTIONS, &allow) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	}

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create bluetooth tethering policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_set_bluetooth_tethering_state(policy, allow) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_bluetooth_tethering_state(policy, &state) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (state == allow) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int get_bluetooth_tethering_state_handler(struct xtk_policy *self)
{
	int state;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create bluetooth tethering policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_bluetooth_tethering_state(policy, &state) == 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int set_usb_tethering_state_handler(struct xtk_policy *self)
{
	int state;
	int allow;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	if (xtk_open_radio_popup(self, STATE_CHANGE_OPTIONS, &allow) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	}

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create usb tethering policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_set_usb_tethering_state(policy, allow) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_usb_tethering_state(policy, &state) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (state == allow) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int get_usb_tethering_state_handler(struct xtk_policy *self)
{
	int state;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create usb tethering policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_usb_tethering_state(policy, &state) == 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int set_bluetooth_mode_change_state_handler(struct xtk_policy *self)
{
	int state;
	int allow;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	if (xtk_open_radio_popup(self, STATE_CHANGE_OPTIONS, &allow) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	}

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create usb tethering policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_set_bluetooth_mode_change_state(policy, allow) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_bluetooth_mode_change_state(policy, &state) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (state == allow) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int get_bluetooth_mode_change_state_handler(struct xtk_policy *self)
{
	int state;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create usb tethering policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_bluetooth_mode_change_state(policy, &state) == 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int set_bluetooth_desktop_connectivity_state_handler(struct xtk_policy *self)
{
	int state;
	int allow;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	if (xtk_open_radio_popup(self, STATE_CHANGE_OPTIONS, &allow) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	}

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create usb tethering policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_set_bluetooth_desktop_connectivity_state(policy, allow) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_bluetooth_desktop_connectivity_state(policy, &state) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (state == allow) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int get_bluetooth_desktop_connectivity_state_handler(struct xtk_policy *self)
{
	int state;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create usb tethering policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_bluetooth_desktop_connectivity_state(policy, &state) == 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int set_bluetooth_pairing_state_handler(struct xtk_policy *self)
{
	int state;
	int allow;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	if (xtk_open_radio_popup(self, STATE_CHANGE_OPTIONS, &allow) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	}

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create usb tethering policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_set_bluetooth_pairing_state(policy, allow) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_bluetooth_pairing_state(policy, &state) != 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (state == allow) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

int get_bluetooth_pairing_state_handler(struct xtk_policy *self)
{
	int state;
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create usb tethering policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_bluetooth_pairing_state(policy, &state) == 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_FAIL;
}

xtk_policy_t xtk_restriction_policy[] = {
	{
		.id = "SET_CAMERA_STATE",
		.handler = set_camera_state_handler
	},
	{
		.id = "GET_CAMERA_STATE",
		.handler = get_camera_state_handler
	},
	{
		.id = "SET_MICROPHONE_STATE",
		.handler = set_microphone_state_handler
	},
	{
		.id = "GET_MICROPHONE_STATE",
		.handler = get_microphone_state_handler
	},
	{
		.id = "SET_LOCATION_STATE",
		.handler = set_location_state_handler
	},
	{
		.id = "GET_LOCATION_STATE",
		.handler = get_location_state_handler
	},
	{
		.id = "SET_CLIPBOARD_STATE",
		.handler = set_clipboard_state_handler
	},
	{
		.id = "GET_CLIPBOARD_STATE",
		.handler = get_clipboard_state_handler
	},
	{
		.id = "SET_SETTINGS_CHANGES_STATE",
		.handler = set_settings_changes_state_handler
	},
	{
		.id = "GET_SETTINGS_CHANGES_STATE",
		.handler = get_settings_changes_state_handler
	},
	{
		.id = "SET_USB_DEBUGGING_STATE",
		.handler = set_usb_debugging_state_handler
	},
	{
		.id = "GET_USB_DEBUGGING_STATE",
		.handler = get_usb_debugging_state_handler
	},
	{
		.id = "SET_WIFI_STATE",
		.handler = set_wifi_state_handler
	},
	{
		.id = "GET_WIFI_STATE",
		.handler = get_wifi_state_handler
	},
	{
		.id = "SET_WIFI_HOTSPOT_STATE",
		.handler = set_wifi_hotspot_state_handler
	},
	{
		.id = "GET_WIFI_HOTSPOT_STATE",
		.handler = get_wifi_hotspot_state_handler
	},
	{
		.id = "SET_BLUETOOTH_TETHERING_STATE",
		.handler = set_bluetooth_tethering_state_handler
	},
	{
		.id = "GET_BLUETOOTH_TETHERING_STATE",
		.handler = get_bluetooth_tethering_state_handler
	},
	{
		.id = "SET_USB_TETHERING_STATE",
		.handler = set_usb_tethering_state_handler
	},
	{
		.id = "GET_USB_TETHERING_STATE",
		.handler = get_usb_tethering_state_handler
	},
	{
		.id = "SET_BLUETOOTH_MODE_CHANGE_STATE",
		.handler = set_bluetooth_mode_change_state_handler
	},
	{
		.id = "GET_BLUETOOTH_MODE_CHANGE_STATE",
		.handler = get_bluetooth_mode_change_state_handler
	},
	{
		.id = "SET_BLUETOOTH_DESKTOP_CONNECTIVITY_STATE",
		.handler = set_bluetooth_desktop_connectivity_state_handler
	},
	{
		.id = "GET_BLUETOOTH_DESKTOP_CONNECTIVITY_STATE",
		.handler = get_bluetooth_desktop_connectivity_state_handler
	},
	{
		.id = "SET_BLUETOOTH_PAIRING_STATE",
		.handler = set_bluetooth_pairing_state_handler
	},
	{
		.id = "GET_BLUETOOTH_PAIRING_STATE",
		.handler = get_bluetooth_pairing_state_handler
	}
};

xtk_policy_group_t restriction_policy_group = {
	.id = "RESTRICTION"
};

void __CONSTRUCTOR__ xtk_restriction_policy_constructor()
{
	int ret = 0;

	dlog_print(DLOG_DEBUG, LOG_TAG, "restriction policy constructor");

	int nr = ARRAY_SIZE(xtk_restriction_policy);
	ret = xtk_init_policy(&restriction_policy_group, xtk_restriction_policy, nr);
	if (ret < 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "restriction policy initialization fail");
	}
}
