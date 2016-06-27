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
#include <dpm/zone.h>

int create_zone_handler(struct xtk_policy* self)
{
	device_policy_manager_h handle;

	char* wizappid = NULL;
	char *input_entry = NULL;

	wizappid = (char *)xmlGetProp(self->model, (xmlChar*) "wizappid");
	if (wizappid == NULL) {
		xtk_open_message_popup(self, "wizappid parameter not found");
		return POLICY_RESULT_FAIL;
	}

	if (xtk_open_entry_popup(self, NULL, "Zone name", &input_entry) == XTK_EVENT_CANCEL) {
		free(wizappid);
		return POLICY_RESULT_FAIL;
	};

	handle = dpm_manager_create();
	if (handle == NULL) {
		xtk_open_message_popup(self, "Failed to create device handle handle handle");
		free(wizappid);
		return POLICY_RESULT_FAIL;
	}

	int ret = dpm_zone_create(handle, input_entry, wizappid);
	dpm_manager_destroy(handle);
	free(wizappid);

	if (ret == DPM_ERROR_NONE) {
		return POLICY_RESULT_SUCCESS;
	}

	xtk_open_message_popup(self, "Failed to create the zone");
	return POLICY_RESULT_FAIL;
}

int destroy_zone_handler(struct xtk_policy* self)
{
	device_policy_manager_h handle;

	char *input_entry = NULL;
	if (xtk_open_entry_popup(self, NULL, "Zone name", &input_entry) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	};

	handle = dpm_manager_create();
	if (handle == NULL) {
		xtk_open_message_popup(self, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	int ret = dpm_zone_destroy(handle, input_entry);
	dpm_manager_destroy(handle);

	if (ret == DPM_ERROR_NONE) {
		return POLICY_RESULT_SUCCESS;
	}

	xtk_open_message_popup(self, "Failed to destroy the zone");
	return POLICY_RESULT_FAIL;
}

int get_zone_state_handler(struct xtk_policy* self)
{
	dpm_zone_state_e state;
	const char *zone_state;
	device_policy_manager_h handle = NULL;

	handle = dpm_manager_create();
	if (handle == NULL) {
		xtk_open_message_popup(self, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	char *input_entry = NULL;
	if (xtk_open_entry_popup(self, NULL, "Zone name", &input_entry) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	};

	int ret = dpm_zone_get_state(handle, input_entry, &state);
	dpm_manager_destroy(handle);

	switch (ret) {
	case DPM_ERROR_NONE:
                if (state & DPM_ZONE_STATE_RUNNING) {
                    zone_state = "Running";
                } else if (state & DPM_ZONE_STATE_LOCKED) {
                    zone_state = "Locked";
                }

		xtk_open_message_popup(self, zone_state);
		return POLICY_RESULT_NONE;
	case DPM_ERROR_NO_DATA:
		xtk_open_message_popup(self, "Not exists");
		return POLICY_RESULT_NONE;
	}

        xtk_open_message_popup(self, "Failed to get zone state");
	return POLICY_RESULT_NONE;
}

xtk_policy_t xtk_zone_policy[] = {
	{
		.id = "CREATE_ZONE",
		.handler = create_zone_handler
	},
	{
		.id = "DESTROY_ZONE",
		.handler = destroy_zone_handler
	},
	{
		.id = "GET_ZONE_STATE",
		.handler = get_zone_state_handler
	}
};

xtk_policy_group_t zone_policy_group = {
	.id = "ZONE"
};

void __CONSTRUCTOR__ xtk_zone_policy_constructor()
{
	int ret = 0;

	dlog_print(DLOG_ERROR, LOG_TAG, "zone policy constructor");

	int nr = ARRAY_SIZE(xtk_zone_policy);
	ret = xtk_init_policy(&zone_policy_group, xtk_zone_policy, nr);
	if (ret < 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "zone policy initialization fail");
	}
}
