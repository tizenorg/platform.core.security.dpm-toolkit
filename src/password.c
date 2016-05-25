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
#include <dpm/password.h>

int set_password_quality_handler(struct xtk_policy* self)
{
	dpm_context_h context;
	dpm_password_policy_h policy;
	dpm_password_quality_e quality;

	char* radio_text[] = {"UNSPECIFIED", "SIMPLE_PASSWORD", "SOMETHING", "NUMERIC", "ALPHABETIC", "ALPHANUMERIC"};
	int radio_num = ARRAY_SIZE(radio_text);

	int radio_index;
	xtk_open_radio_popup(self, radio_text, radio_num, &radio_index);

	switch(radio_index) {
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

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_password_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_quality(policy, quality) == 0) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_SUCCESS;
	}

	dpm_context_release_password_policy(context, policy);
	dpm_context_destroy(context);
	return POLICY_RESULT_FAIL;
}

int set_password_min_length_handler(struct xtk_policy* self)
{
	dpm_context_h context;
	dpm_password_policy_h policy;

	char *input_entry;
	if (xtk_open_entry_popup(self, "", &input_entry) == BUTTON_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
	};

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_password_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_minimum_length(policy, atoi(input_entry)) == 0) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, input_entry);
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_password_policy(context, policy);
	dpm_context_destroy(context);
	return POLICY_RESULT_FAIL;
}

int set_password_min_complex_chars_handler(struct xtk_policy* self)
{
	dpm_context_h context;
	dpm_password_policy_h policy;

	char *input_entry;
	if (xtk_open_entry_popup(self, "", &input_entry) == BUTTON_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
	};

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_password_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_min_complex_chars(policy, atoi(input_entry)) == 0) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, input_entry);
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_password_policy(context, policy);
	dpm_context_destroy(context);
	return POLICY_RESULT_FAIL;
}

int set_password_max_failed_attempts_for_wipe_handler(struct xtk_policy* self)
{
	dpm_context_h context;
	dpm_password_policy_h policy;

	char *input_entry;
	if (xtk_open_entry_popup(self, "", &input_entry) == BUTTON_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
	};

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_password_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_maximum_failed_attempts_for_wipe(policy, atoi(input_entry)) == 0) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, input_entry);
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_password_policy(context, policy);
	dpm_context_destroy(context);
	return POLICY_RESULT_FAIL;
}

int set_password_expires_handler(struct xtk_policy* self)
{
	dpm_context_h context;
	dpm_password_policy_h policy;

	char *input_entry;
	if (xtk_open_entry_popup(self, "", &input_entry) == BUTTON_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
	};

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_password_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_expires(policy, atoi(input_entry)) == 0) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, input_entry);
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_password_policy(context, policy);
	dpm_context_destroy(context);
	return POLICY_RESULT_FAIL;
}

int set_password_history_handler(struct xtk_policy* self)
{
	dpm_context_h context;
	dpm_password_policy_h policy;

	char *input_entry;
	if (xtk_open_entry_popup(self, "", &input_entry) == BUTTON_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
	};

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_password_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_history(policy, atoi(input_entry)) == 0) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, input_entry);
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_password_policy(context, policy);
	dpm_context_destroy(context);
	return POLICY_RESULT_FAIL;
}

int reset_password_handler(struct xtk_policy* self)
{
	dpm_context_h context;
	dpm_password_policy_h policy;

	char *input_entry;
	if (xtk_open_entry_popup(self, "", &input_entry) == BUTTON_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
	};

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_password_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_reset(policy, input_entry) == 0) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, input_entry);
		return POLICY_RESULT_SUCCESS;
	}

	dpm_context_release_password_policy(context, policy);
	dpm_context_destroy(context);
	return POLICY_RESULT_FAIL;
}

int enforce_password_change_handler(struct xtk_policy* self)
{
	dpm_context_h context;
	dpm_password_policy_h policy;

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_password_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_enforce_change(policy) == 0) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_SUCCESS;
	}

	dpm_context_release_password_policy(context, policy);
	dpm_context_destroy(context);
	return POLICY_RESULT_FAIL;
}

int set_max_inactivity_time_device_lock_handler(struct xtk_policy* self)
{
	dpm_context_h context;
	dpm_password_policy_h policy;
	int max_inactivity_time, test_max_inactivity_time;

	char *input_entry;
	if (xtk_open_entry_popup(self, "", &input_entry) == BUTTON_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
	};

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_password_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	max_inactivity_time = atoi(input_entry);
	test_max_inactivity_time = 0;

	if (dpm_password_set_max_inactivity_time_device_lock(policy, max_inactivity_time) != 0) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_max_inactivity_time_device_lock(policy, &test_max_inactivity_time) != 0) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (max_inactivity_time == test_max_inactivity_time) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, input_entry);
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_password_policy(context, policy);
	dpm_context_destroy(context);
	return POLICY_RESULT_FAIL;
}

int get_max_inactivity_time_device_lock_handler(struct xtk_policy* self)
{
	dpm_context_h context;
	dpm_password_policy_h policy;
	int max_inactivity_time;

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_password_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_max_inactivity_time_device_lock(policy, &max_inactivity_time) == 0) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		char num_text[10] = {0, };
		snprintf(num_text, sizeof(num_text), "%d", max_inactivity_time);
		xtk_open_message_popup(self, num_text);
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_password_policy(context, policy);
	dpm_context_destroy(context);
	return POLICY_RESULT_FAIL;
}

int set_password_status_handler(struct xtk_policy* self)
{
	dpm_context_h context;
	dpm_password_policy_h policy;

	char *input_entry;
	if (xtk_open_entry_popup(self, "", &input_entry) == BUTTON_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
	};

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_password_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_status(policy, atoi(input_entry)) == 0) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, input_entry);
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_password_policy(context, policy);
	dpm_context_destroy(context);
	return POLICY_RESULT_FAIL;
}

int set_password_pattern_handler(struct xtk_policy* self)
{
	dpm_context_h context;
	dpm_password_policy_h policy;
	char *test_pw_pattern;

	char *input_entry;
	if (xtk_open_entry_popup(self, "", &input_entry) == BUTTON_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
	};

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_password_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_pattern(policy, input_entry) != 0) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_pattern(policy, &test_pw_pattern) != 0) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (strcmp(input_entry, test_pw_pattern) == 0) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, input_entry);
		free(test_pw_pattern);
		return POLICY_RESULT_NONE;
	}

	free(test_pw_pattern);
	dpm_context_release_password_policy(context, policy);
	dpm_context_destroy(context);
	return POLICY_RESULT_FAIL;
}

int get_password_pattern_handler(struct xtk_policy* self)
{
	dpm_context_h context;
	dpm_password_policy_h policy;

	char *pw_pattern;

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_password_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_pattern(policy, &pw_pattern) == 0) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, pw_pattern);
		free(pw_pattern);
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_password_policy(context, policy);
	dpm_context_destroy(context);
	return POLICY_RESULT_FAIL;
}

int delete_password_pattern_handler(struct xtk_policy* self)
{
	dpm_context_h context;
	dpm_password_policy_h policy;

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_password_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_delete_pattern(policy) == 0) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_password_policy(context, policy);
	dpm_context_destroy(context);
	return POLICY_RESULT_FAIL;
}

int set_max_char_occurrences_handler(struct xtk_policy* self)
{
	dpm_context_h context;
	dpm_password_policy_h policy;
	int max_char_occur, test_max_char_occur;

	char *input_entry;
	if (xtk_open_entry_popup(self, "", &input_entry) == BUTTON_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
	};

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_password_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	max_char_occur = atoi(input_entry);
	test_max_char_occur = 0;

	if (dpm_password_set_maximum_character_occurrences(policy, max_char_occur) != 0) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_maximum_character_occurrences(policy, &test_max_char_occur) != 0) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (max_char_occur == test_max_char_occur) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, input_entry);
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_password_policy(context, policy);
	dpm_context_destroy(context);
	return POLICY_RESULT_FAIL;
}

int get_max_char_occurrences_handler(struct xtk_policy* self)
{
	dpm_context_h context;
	dpm_password_policy_h policy;
	int max_char_occur;

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_password_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_maximum_character_occurrences(policy, &max_char_occur) == 0) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		char num_text[10] = {0, };
		snprintf(num_text, sizeof(num_text), "%d", max_char_occur);
		xtk_open_message_popup(self, num_text);
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_password_policy(context, policy);
	dpm_context_destroy(context);
	return POLICY_RESULT_FAIL;
}

int set_max_numeric_sequence_length_handler(struct xtk_policy* self)
{
	dpm_context_h context;
	dpm_password_policy_h policy;
	int max_num_seq_length, test_max_num_seq_length;

	char *input_entry;
	if (xtk_open_entry_popup(self, "", &input_entry) == BUTTON_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
	};

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_password_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	max_num_seq_length = atoi(input_entry);
	test_max_num_seq_length = 0;

	if (dpm_password_set_maximum_numeric_sequence_length(policy, max_num_seq_length) != 0) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_maximum_numeric_sequence_length(policy, &test_max_num_seq_length) != 0) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (max_num_seq_length == test_max_num_seq_length) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, input_entry);
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_password_policy(context, policy);
	dpm_context_destroy(context);
	return POLICY_RESULT_FAIL;
}

int get_max_numeric_sequence_length_handler(struct xtk_policy* self)
{
	dpm_context_h context;
	dpm_password_policy_h policy;
	int max_num_seq_length;

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_password_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_maximum_numeric_sequence_length(policy, &max_num_seq_length) == 0) {
		dpm_context_release_password_policy(context, policy);
		dpm_context_destroy(context);
		char num_text[10] = {0, };
		snprintf(num_text, sizeof(num_text), "%d", max_num_seq_length);
		xtk_open_message_popup(self, num_text);
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_password_policy(context, policy);
	dpm_context_destroy(context);
	return POLICY_RESULT_FAIL;
}

xtk_policy_t xtk_password_policy[] = {
	{
		.id = "SET_PASSWORD_QUALITY",
		.handler = set_password_quality_handler
	},
	{
		.id = "SET_PASSWORD_MIN_LENGTH",
		.handler = set_password_min_length_handler
	},
	{
		.id = "SET_PASSWORD_MIN_COMPLEX_CHARS",
		.handler = set_password_min_complex_chars_handler
	},
	{
		.id = "SET_PASSWORD_MAX_FAILED_ATTEMPTS_FOR_WIPE",
		.handler = set_password_max_failed_attempts_for_wipe_handler
	},
	{
		.id = "SET_PASSWORD_EXPIRES",
		.handler = set_password_expires_handler
	},
	{
		.id = "SET_PASSWORD_HISTORY",
		.handler = set_password_history_handler
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

xtk_policy_group_t password_policy_group = {
	.id = "PASSWORD"
};

void __CONSTRUCTOR__ xtk_password_policy_constructor()
{
	int ret = 0;

	dlog_print(DLOG_DEBUG, LOG_TAG, "password policy constructor");

	int nr = ARRAY_SIZE(xtk_password_policy);
	ret = xtk_init_policy(&password_policy_group, xtk_password_policy, nr);
	if (ret < 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "password policy initialization fail");
	}
}
