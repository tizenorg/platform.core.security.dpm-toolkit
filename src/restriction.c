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

#include <dpm/restriction.h>

#include "dpm-toolkit.h"

int set_camera_state_handler(struct xtk_policy *self)
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

	if (dpm_restriction_set_camera_state(handle, allow) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_camera_state(handle, &state) != 0) {
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

int get_camera_state_handler(struct xtk_policy *self)
{
	int state;
	device_policy_manager_h handle = NULL;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_camera_state(handle, &state) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

int set_microphone_state_handler(struct xtk_policy *self)
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

	if (dpm_restriction_set_microphone_state(handle, allow) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_microphone_state(handle, &state) != 0) {
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

int get_microphone_state_handler(struct xtk_policy *self)
{
	int state;
	device_policy_manager_h handle = NULL;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_microphone_state(handle, &state) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

int set_location_state_handler(struct xtk_policy *self)
{
	int state;
	int allow;
	device_policy_manager_h handle = NULL;

	if (xtk_open_radio_popup(self, STATE_CHANGE_OPTIONS, &allow) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	}

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_set_location_state(handle, allow) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_location_state(handle, &state) != 0) {
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

int get_location_state_handler(struct xtk_policy *self)
{
	int state, ret;
	device_policy_manager_h handle = NULL;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	ret = dpm_restriction_get_location_state(handle, &state);
	if (ret == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

int set_clipboard_state_handler(struct xtk_policy *self)
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

	if (dpm_restriction_set_clipboard_state(handle, allow) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_clipboard_state(handle, &state) != 0) {
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

int get_clipboard_state_handler(struct xtk_policy *self)
{
	int state;
	device_policy_manager_h handle = NULL;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_clipboard_state(handle, &state) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

int set_usb_debugging_state_handler(struct xtk_policy *self)
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

	if (dpm_restriction_set_usb_debugging_state(handle, allow) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_usb_debugging_state(handle, &state) != 0) {
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

int get_usb_debugging_state_handler(struct xtk_policy *self)
{
	int state;
	device_policy_manager_h handle = NULL;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_usb_debugging_state(handle, &state) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

int set_wifi_state_handler(struct xtk_policy *self)
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

	if (dpm_restriction_set_wifi_state(handle, allow) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_wifi_state(handle, &state) != 0) {
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

int get_wifi_state_handler(struct xtk_policy *self)
{
	int state;
	device_policy_manager_h handle = NULL;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_wifi_state(handle, &state) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

int set_wifi_hotspot_state_handler(struct xtk_policy *self)
{
	int state;
	int allow;
	device_policy_manager_h handle = NULL;

	if (xtk_open_radio_popup(self, STATE_CHANGE_OPTIONS, &allow) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	}

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_set_wifi_hotspot_state(handle, allow) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_wifi_hotspot_state(handle, &state) != 0) {
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

int get_wifi_hotspot_state_handler(struct xtk_policy *self)
{
	int state;
	device_policy_manager_h handle = NULL;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_wifi_hotspot_state(handle, &state) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

int set_bluetooth_tethering_state_handler(struct xtk_policy *self)
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

	if (dpm_restriction_set_bluetooth_tethering_state(handle, allow) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_bluetooth_tethering_state(handle, &state) != 0) {
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

int get_bluetooth_tethering_state_handler(struct xtk_policy *self)
{
	int state;
	device_policy_manager_h handle = NULL;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_bluetooth_tethering_state(handle, &state) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

int set_usb_tethering_state_handler(struct xtk_policy *self)
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

	if (dpm_restriction_set_usb_tethering_state(handle, allow) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_usb_tethering_state(handle, &state) != 0) {
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

int get_usb_tethering_state_handler(struct xtk_policy *self)
{
	int state;
	device_policy_manager_h handle = NULL;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_usb_tethering_state(handle, &state) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

int set_external_storage_state_handler(struct xtk_policy *self)
{
	int index, state;
	device_policy_manager_h handle = NULL;
	const char* text[] = {
		"Disallow External Storage",
		"Allow External Storage"
	};

	if (xtk_open_radio_popup(self, text, ARRAY_SIZE(text), &index) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	}

	handle = dpm_manager_create();
	if (handle == NULL) {
		xtk_open_message_popup(self, "Failed to create device handle manager");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_set_external_storage_state(handle, index) != DPM_ERROR_NONE) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, "Failed to enforce handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_external_storage_state(handle, &state) != DPM_ERROR_NONE) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, "Failed to query handle");
		return POLICY_RESULT_FAIL;
	}

	if (state != index) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, "Policy was not setted properly");;
		return POLICY_RESULT_NONE;
	}

	xtk_open_message_popup(self, state ? "External Storage Allowed"
									   : "External Storage Disallowed");

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

int get_external_storage_state_handler(struct xtk_policy *self)
{
	int state;
	device_policy_manager_h handle = NULL;

	handle = dpm_manager_create();
	if (handle == NULL) {
		xtk_open_message_popup(self, "Failed to create device handle manager");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_external_storage_state(handle, &state) != DPM_ERROR_NONE) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, "Failed to query handle");
		return POLICY_RESULT_NONE;
	}

	xtk_open_message_popup(self, state ? "External Storage Allowed"
									   : "External Storage Disallowed");

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

int set_bluetooth_mode_change_state_handler(struct xtk_policy *self)
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

	if (dpm_restriction_set_bluetooth_mode_change_state(handle, allow) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_bluetooth_mode_change_state(handle, &state) != 0) {
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

int get_bluetooth_mode_change_state_handler(struct xtk_policy *self)
{
	int state;
	device_policy_manager_h handle = NULL;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_bluetooth_mode_change_state(handle, &state) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

int set_bluetooth_desktop_connectivity_state_handler(struct xtk_policy *self)
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

	if (dpm_restriction_set_bluetooth_desktop_connectivity_state(handle, allow) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_bluetooth_desktop_connectivity_state(handle, &state) != 0) {
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

int get_bluetooth_desktop_connectivity_state_handler(struct xtk_policy *self)
{
	int state;
	device_policy_manager_h handle = NULL;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_bluetooth_desktop_connectivity_state(handle, &state) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

int set_bluetooth_pairing_state_handler(struct xtk_policy *self)
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

	if (dpm_restriction_set_bluetooth_pairing_state(handle, allow) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_bluetooth_pairing_state(handle, &state) != 0) {
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

int get_bluetooth_pairing_state_handler(struct xtk_policy *self)
{
	int state;
	device_policy_manager_h handle = NULL;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_bluetooth_pairing_state(handle, &state) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

int set_popimap_email_state_handler(struct xtk_policy *self)
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

	if (dpm_restriction_set_popimap_email_state(handle, allow) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_popimap_email_state(handle, &state) != 0) {
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

int get_popimap_email_state_handler(struct xtk_policy *self)
{
	int state;
	device_policy_manager_h handle = NULL;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_popimap_email_state(handle, &state) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

int set_messaging_state_handler(struct xtk_policy *self)
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

	if (dpm_restriction_set_messaging_state(handle, allow) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_messaging_state(handle, &state) != 0) {
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

int get_messaging_state_handler(struct xtk_policy *self)
{
	int state;
	device_policy_manager_h handle = NULL;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_messaging_state(handle, &state) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);

	return POLICY_RESULT_FAIL;
}

int set_browser_state_handler(struct xtk_policy *self)
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

	if (dpm_restriction_set_browser_state(handle, allow) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_browser_state(handle, &state) != 0) {
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

int get_browser_state_handler(struct xtk_policy *self)
{
	int state;
	device_policy_manager_h handle = NULL;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_browser_state(handle, &state) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, STATE_CHANGE_MESSAGE(state));
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);

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
		.id = "SET_EXTERNAL_STORAGE_STATE",
		.handler = set_external_storage_state_handler
	},
	{
		.id = "GET_EXTERNAL_STORAGE_STATE",
		.handler = get_external_storage_state_handler
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
	},
	{
		.id = "SET_POPIMAP_EMAIL_STATE",
		.handler = set_popimap_email_state_handler
	},
	{
		.id = "GET_POPIMAP_EMAIL_STATE",
		.handler = get_popimap_email_state_handler
	},
	{
		.id = "SET_MESSAGING_STATE",
		.handler = set_messaging_state_handler
	},
	{
		.id = "GET_MESSAGING_STATE",
		.handler = get_messaging_state_handler
	},
	{
		.id = "SET_BROWSER_STATE",
		.handler = set_browser_state_handler
	},
	{
		.id = "GET_BROWSER_STATE",
		.handler = get_browser_state_handler
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
