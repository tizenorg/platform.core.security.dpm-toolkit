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

int lock_now_handler(struct xtk_policy* self)
{
	char *entry;
	if (xtk_open_entry_popup(self, "Enter name", &entry) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
		return POLICY_RESULT_FAIL;
	};

	xtk_open_message_popup(self, entry);

	return POLICY_RESULT_SUCCESS;
}

int wipe_data_handler(struct xtk_policy* self)
{
	return POLICY_RESULT_SUCCESS;
}

int reboot_handler(struct xtk_policy* self)
{
	return POLICY_RESULT_SUCCESS;
}

int power_off_device_handler(struct xtk_policy* self)
{
	int index;
	if (xtk_open_radio_popup(self, STATE_CHANGE_OPTIONS, &index) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Selection canceled");
		return POLICY_RESULT_FAIL;
	}

	dlog_print(DLOG_DEBUG, LOG_TAG, "Selected: %d", index);
	return POLICY_RESULT_SUCCESS;
}

xtk_policy_t xtk_security_policy[] = {
	{
		.id = "LOCK_NOW",
		.handler = lock_now_handler
	},
	{
		.id = "WIPE_DATA",
		.handler = wipe_data_handler
	},
	{
		.id = "REBOOT",
		.handler = reboot_handler
	},
	{
		.id = "POWER_OFF_DEVICE",
		.handler = power_off_device_handler
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
