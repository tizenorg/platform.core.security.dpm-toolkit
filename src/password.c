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

#include <dpm/password.h>

#include "dpm-toolkit.h"

int set_password_quality_handler(struct xtk_policy *self)
{
	int index;
	device_policy_manager_h handle;
	dpm_password_quality_e quality;

	const char *text[] = {
		"UNSPECIFIED",
		"SIMPLE_PASSWORD",
		"SOMETHING",
		"NUMERIC",
		"ALPHABETIC",
		"ALPHANUMERIC"
	};

	if (xtk_open_radio_popup(self, text, ARRAY_SIZE(text), &index) == XTK_EVENT_CANCEL) {
		return POLICY_RESULT_FAIL;
	}

	switch (index) {
	case 0:
		quality = DPM_PASSWORD_QUALITY_UNSPECIFIED;
		break;
	case 1:
		quality = DPM_PASSWORD_QUALITY_SIMPLE_PASSWORD;
		break;
	case 2:
		quality = DPM_PASSWORD_QUALITY_SOMETHING;
		break;
	case 3:
		quality = DPM_PASSWORD_QUALITY_NUMERIC;
		break;
	case 4:
		quality = DPM_PASSWORD_QUALITY_ALPHABETIC;
		break;
	case 5:
		quality = DPM_PASSWORD_QUALITY_ALPHANUMERIC;
		break;
	default:
		quality = DPM_PASSWORD_QUALITY_UNSPECIFIED;
		break;
	}

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_quality(handle, quality) == 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_SUCCESS;
	}

	dpm_manager_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int get_password_quality_handler(struct xtk_policy *self)
{
	int index;
	device_policy_manager_h handle;
	dpm_password_quality_e quality;

	const char *text[] = {
		"UNSPECIFIED",
		"SIMPLE_PASSWORD",
		"SOMETHING",
		"NUMERIC",
		"ALPHABETIC",
		"ALPHANUMERIC"
	};

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_quality(handle, &quality) == 0) {
		dpm_manager_destroy(handle);
		switch (quality) {
		case DPM_PASSWORD_QUALITY_UNSPECIFIED:
			index = 0;
			break;
		case DPM_PASSWORD_QUALITY_SIMPLE_PASSWORD:
			index = 1;
			break;
		case DPM_PASSWORD_QUALITY_SOMETHING:
			index = 2;
			break;
		case DPM_PASSWORD_QUALITY_NUMERIC:
			index = 3;
			break;
		case DPM_PASSWORD_QUALITY_ALPHABETIC:
			index = 4;
			break;
		case DPM_PASSWORD_QUALITY_ALPHANUMERIC:
			index = 5;
			break;
		default:
			index = 0;
			break;
		}
		xtk_open_message_popup(self, text[index]);
		return POLICY_RESULT_SUCCESS;
	}

	dpm_manager_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int set_password_min_length_handler(struct xtk_policy *self)
{
	device_policy_manager_h handle;

	char *input_entry;
	if (xtk_open_entry_popup(self, "", "", &input_entry) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
		return POLICY_RESULT_FAIL;
	};

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_minimum_length(handle, atoi(input_entry)) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, input_entry);
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int get_password_min_length_handler(struct xtk_policy *self)
{
	device_policy_manager_h handle;
	int min_length;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_minimum_length(handle, &min_length) == 0) {
		dpm_manager_destroy(handle);
		char num_text[10] = {0, };
		snprintf(num_text, sizeof(num_text), "%d", min_length);
		xtk_open_message_popup(self, num_text);
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int set_password_min_complex_chars_handler(struct xtk_policy *self)
{
	device_policy_manager_h handle;

	char *input_entry;
	if (xtk_open_entry_popup(self, "", "", &input_entry) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
		return POLICY_RESULT_FAIL;
	};

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_min_complex_chars(handle, atoi(input_entry)) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, input_entry);
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int get_password_min_complex_chars_handler(struct xtk_policy *self)
{
	device_policy_manager_h handle;
	int min_complex_chars;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_min_complex_chars(handle, &min_complex_chars) == 0) {
		dpm_manager_destroy(handle);
		char num_text[10] = {0, };
		snprintf(num_text, sizeof(num_text), "%d", min_complex_chars);
		xtk_open_message_popup(self, num_text);
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int set_password_max_failed_attempts_for_wipe_handler(struct xtk_policy *self)
{
	device_policy_manager_h handle;

	char *input_entry;
	if (xtk_open_entry_popup(self, "", "", &input_entry) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
		return POLICY_RESULT_FAIL;
	};

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_maximum_failed_attempts_for_wipe(handle, atoi(input_entry)) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, input_entry);
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int get_password_max_failed_attempts_for_wipe_handler(struct xtk_policy *self)
{
	device_policy_manager_h handle;
	int max_failed_attempts;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_maximum_failed_attempts_for_wipe(handle, &max_failed_attempts) == 0) {
		dpm_manager_destroy(handle);
		char num_text[10] = {0, };
		snprintf(num_text, sizeof(num_text), "%d", max_failed_attempts);
		xtk_open_message_popup(self, num_text);
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int set_password_expires_handler(struct xtk_policy *self)
{
	device_policy_manager_h handle;

	char *input_entry;
	if (xtk_open_entry_popup(self, "", "", &input_entry) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
		return POLICY_RESULT_FAIL;
	};

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_expires(handle, atoi(input_entry)) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, input_entry);
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int get_password_expires_handler(struct xtk_policy *self)
{
	device_policy_manager_h handle;
	int expires;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_expires(handle, &expires) == 0) {
		dpm_manager_destroy(handle);
		char num_text[10] = {0, };
		snprintf(num_text, sizeof(num_text), "%d", expires);
		xtk_open_message_popup(self, num_text);
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int set_password_history_handler(struct xtk_policy *self)
{
	device_policy_manager_h handle;

	char *input_entry;
	if (xtk_open_entry_popup(self, "", "", &input_entry) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
		return POLICY_RESULT_FAIL;
	};

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_history(handle, atoi(input_entry)) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, input_entry);
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int get_password_history_handler(struct xtk_policy *self)
{
	device_policy_manager_h handle;
	int history;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_history(handle, &history) == 0) {
		dpm_manager_destroy(handle);
		char num_text[10] = {0, };
		snprintf(num_text, sizeof(num_text), "%d", history);
		xtk_open_message_popup(self, num_text);
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int reset_password_handler(struct xtk_policy *self)
{
	device_policy_manager_h handle;

	char *input_entry;
	if (xtk_open_entry_popup(self, "", "", &input_entry) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
		return POLICY_RESULT_FAIL;
	};

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_reset(handle, input_entry) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, input_entry);
		return POLICY_RESULT_SUCCESS;
	}

	dpm_manager_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int enforce_password_change_handler(struct xtk_policy *self)
{
	device_policy_manager_h handle;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_enforce_change(handle) == 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_SUCCESS;
	}

	dpm_manager_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int set_max_inactivity_time_device_lock_handler(struct xtk_policy *self)
{
	device_policy_manager_h handle;
	int max_inactivity_time, test_max_inactivity_time;

	char *input_entry;
	if (xtk_open_entry_popup(self, "", "", &input_entry) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
		return POLICY_RESULT_FAIL;
	};

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	max_inactivity_time = atoi(input_entry);
	test_max_inactivity_time = 0;

	if (dpm_password_set_max_inactivity_time_device_lock(handle, max_inactivity_time) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_max_inactivity_time_device_lock(handle, &test_max_inactivity_time) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (max_inactivity_time == test_max_inactivity_time) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, input_entry);
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int get_max_inactivity_time_device_lock_handler(struct xtk_policy *self)
{
	device_policy_manager_h handle;
	int max_inactivity_time;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_max_inactivity_time_device_lock(handle, &max_inactivity_time) == 0) {
		dpm_manager_destroy(handle);
		char num_text[10] = {0, };
		snprintf(num_text, sizeof(num_text), "%d", max_inactivity_time);
		xtk_open_message_popup(self, num_text);
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int set_password_status_handler(struct xtk_policy *self)
{
	device_policy_manager_h handle;

	char *input_entry;
	if (xtk_open_entry_popup(self, "", "", &input_entry) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
		return POLICY_RESULT_FAIL;
	};

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_status(handle, atoi(input_entry)) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, input_entry);
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int set_password_pattern_handler(struct xtk_policy *self)
{
	device_policy_manager_h handle;
	char *test_pw_pattern;

	char *input_entry;
	if (xtk_open_entry_popup(self, "", "", &input_entry) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
		return POLICY_RESULT_FAIL;
	};

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_pattern(handle, input_entry) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_pattern(handle, &test_pw_pattern) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (strcmp(input_entry, test_pw_pattern) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, input_entry);
		free(test_pw_pattern);
		return POLICY_RESULT_NONE;
	}

	free(test_pw_pattern);
	dpm_manager_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int get_password_pattern_handler(struct xtk_policy *self)
{
	device_policy_manager_h handle;

	char *pw_pattern;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_pattern(handle, &pw_pattern) == 0) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, pw_pattern);
		free(pw_pattern);
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int delete_password_pattern_handler(struct xtk_policy *self)
{
	device_policy_manager_h handle;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_delete_pattern(handle) == 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int set_max_char_occurrences_handler(struct xtk_policy *self)
{
	device_policy_manager_h handle;
	int max_char_occur, test_max_char_occur;

	char *input_entry;
	if (xtk_open_entry_popup(self, "", "", &input_entry) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
		return POLICY_RESULT_FAIL;
	};

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	max_char_occur = atoi(input_entry);
	test_max_char_occur = 0;

	if (dpm_password_set_maximum_character_occurrences(handle, max_char_occur) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_maximum_character_occurrences(handle, &test_max_char_occur) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (max_char_occur == test_max_char_occur) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, input_entry);
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int get_max_char_occurrences_handler(struct xtk_policy *self)
{
	device_policy_manager_h handle;
	int max_char_occur;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_maximum_character_occurrences(handle, &max_char_occur) == 0) {
		dpm_manager_destroy(handle);
		char num_text[10] = {0, };
		snprintf(num_text, sizeof(num_text), "%d", max_char_occur);
		xtk_open_message_popup(self, num_text);
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int set_max_numeric_sequence_length_handler(struct xtk_policy *self)
{
	device_policy_manager_h handle;
	int max_num_seq_length, test_max_num_seq_length;

	char *input_entry;
	if (xtk_open_entry_popup(self, "", "", &input_entry) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
		return POLICY_RESULT_FAIL;
	};

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	max_num_seq_length = atoi(input_entry);
	test_max_num_seq_length = 0;

	if (dpm_password_set_maximum_numeric_sequence_length(handle, max_num_seq_length) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_maximum_numeric_sequence_length(handle, &test_max_num_seq_length) != 0) {
		dpm_manager_destroy(handle);
		return POLICY_RESULT_FAIL;
	}

	if (max_num_seq_length == test_max_num_seq_length) {
		dpm_manager_destroy(handle);
		xtk_open_message_popup(self, input_entry);
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int get_max_numeric_sequence_length_handler(struct xtk_policy *self)
{
	device_policy_manager_h handle;
	int max_num_seq_length;

	handle = dpm_manager_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device handle handle handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_maximum_numeric_sequence_length(handle, &max_num_seq_length) == 0) {
		dpm_manager_destroy(handle);
		char num_text[10] = {0, };
		snprintf(num_text, sizeof(num_text), "%d", max_num_seq_length);
		xtk_open_message_popup(self, num_text);
		return POLICY_RESULT_NONE;
	}

	dpm_manager_destroy(handle);
	return POLICY_RESULT_FAIL;
}

xtk_policy_t xtk_password_handle[] = {
	{
		.id = "SET_PASSWORD_QUALITY",
		.handler = set_password_quality_handler
	},
	{
		.id = "GET_PASSWORD_QUALITY",
		.handler = get_password_quality_handler
	},
	{
		.id = "SET_PASSWORD_MIN_LENGTH",
		.handler = set_password_min_length_handler
	},
	{
		.id = "GET_PASSWORD_MIN_LENGTH",
		.handler = get_password_min_length_handler
	},
	{
		.id = "SET_PASSWORD_MIN_COMPLEX_CHARS",
		.handler = set_password_min_complex_chars_handler
	},
	{
		.id = "GET_PASSWORD_MIN_COMPLEX_CHARS",
		.handler = get_password_min_complex_chars_handler
	},
	{
		.id = "SET_PASSWORD_MAX_FAILED_ATTEMPTS_FOR_WIPE",
		.handler = set_password_max_failed_attempts_for_wipe_handler
	},
	{
		.id = "GET_PASSWORD_MAX_FAILED_ATTEMPTS_FOR_WIPE",
		.handler = get_password_max_failed_attempts_for_wipe_handler
	},
	{
		.id = "SET_PASSWORD_EXPIRES",
		.handler = set_password_expires_handler
	},
	{
		.id = "GET_PASSWORD_EXPIRES",
		.handler = get_password_expires_handler
	},
	{
		.id = "SET_PASSWORD_HISTORY",
		.handler = set_password_history_handler
	},
	{
		.id = "GET_PASSWORD_HISTORY",
		.handler = get_password_history_handler
	},
	{
		.id = "RESET_PASSWORD",
		.handler = reset_password_handler
	},
	{
		.id = "ENFORCE_PASSWORD_CHANGE",
		.handler = enforce_password_change_handler
	},
	{
		.id = "SET_MAX_INACTIVITY_TIME_DEVICE_LOCK",
		.handler = set_max_inactivity_time_device_lock_handler
	},
	{
		.id = "GET_MAX_INACTIVITY_TIME_DEVICE_LOCK",
		.handler = get_max_inactivity_time_device_lock_handler
	},
	{
		.id = "SET_PASSWORD_STATUS",
		.handler = set_password_status_handler
	},
	{
		.id = "SET_PASSWORD_PATTERN",
		.handler = set_password_pattern_handler
	},
	{
		.id = "GET_PASSWORD_PATTERN",
		.handler = get_password_pattern_handler
	},
	{
		.id = "DELETE_PASSWORD_PATTERN",
		.handler = delete_password_pattern_handler
	},
	{
		.id = "SET_MAX_CHAR_OCCURRENCES",
		.handler = set_max_char_occurrences_handler
	},
	{
		.id = "GET_MAX_CHAR_OCCURRENCES",
		.handler = get_max_char_occurrences_handler
	},
	{
		.id = "SET_MAX_NUMERIC_SEQUENCE_LENGTH",
		.handler = set_max_numeric_sequence_length_handler
	},
	{
		.id = "GET_MAX_NUMERIC_SEQUENCE_LENGTH",
		.handler = get_max_numeric_sequence_length_handler
	}
};

xtk_policy_group_t password_handle_group = {
	.id = "PASSWORD"
};

void __CONSTRUCTOR__ xtk_password_handle_constructor()
{
	int ret = 0;

	dlog_print(DLOG_DEBUG, LOG_TAG, "password handle constructor");

	int nr = ARRAY_SIZE(xtk_password_handle);
	ret = xtk_init_policy(&password_handle_group, xtk_password_handle, nr);
	if (ret < 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "password handle initialization fail");
	}
}
