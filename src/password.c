#include "dpm-toolkit.h"
#include <stdlib.h>
#include <dpm/password.h>

/* dpm integration test & radio popup test */
int set_password_quality_handler(struct dpm_toolkit_entity* self)
{
    dlog_print(DLOG_DEBUG, LOG_TAG, "set_password_quality_handler");
	dpm_context_h handle;
	dpm_password_policy_h password_policy_handle;
	dpm_toolkit_entity_t* selected_policy = self;
	char radio_text[][MAX_RADIO_TEXT_LEN] = {"UNSPECIFIED", "SIMPLE_PASSWORD", "SOMETHING", "NUMERIC", "ALPHABETIC", "ALPHANUMERIC"};
	int radio_num = sizeof(radio_text) / sizeof(radio_text[0]);
	dpm_password_quality_e quality;
	const char param_zone[] = "owner";

	handler_display_radio_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), selected_policy, radio_text, radio_num);
	
	dlog_print(DLOG_DEBUG, LOG_TAG, "radio index: %d", selected_policy->radio_index);

	switch(selected_policy->radio_index) {
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

	dlog_print(DLOG_DEBUG, LOG_TAG, "Password Quality: %s", radio_text[selected_policy->radio_index]);

	handle = dpm_context_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	password_policy_handle = dpm_context_acquire_password_policy(handle, param_zone);
	if (password_policy_handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_quality(password_policy_handle, quality) == 0) {
        dpm_context_release_password_policy(handle, password_policy_handle);
		dpm_context_destroy(handle);
		return POLICY_RESULT_SUCCESS;
	}

    dpm_context_release_password_policy(handle, password_policy_handle);
	dpm_context_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int set_password_min_length_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "set_password_min_length_handler");
	dpm_context_h handle;
	dpm_password_policy_h password_policy_handle;
	dpm_toolkit_entity_t* selected_policy = self;
    char* input;
	int min_length;
	const char param_zone[] = "owner";

	handler_display_input_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"),selected_policy);

	input = selected_policy->entry_input;

	dlog_print(DLOG_DEBUG, LOG_TAG, "Min Length: %s", input);

	min_length = atoi(input);

	handle = dpm_context_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}
	
	password_policy_handle = dpm_context_acquire_password_policy(handle, param_zone);
	if (password_policy_handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_minimum_length(password_policy_handle, min_length) == 0) {
        dpm_context_release_password_policy(handle, password_policy_handle);
		dpm_context_destroy(handle);
		display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"),input);
		return POLICY_RESULT_NONE;
	}

    dpm_context_release_password_policy(handle, password_policy_handle);
	dpm_context_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int set_password_min_complex_chars_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "set_password_min_complex_chars_handler");
	dpm_context_h handle;
	dpm_password_policy_h password_policy_handle;
	dpm_toolkit_entity_t* selected_policy = self;
    char* input;
	int min_complex_chars;
	const char param_zone[] = "owner";

	handler_display_input_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"),selected_policy);

	input = selected_policy->entry_input;

	dlog_print(DLOG_DEBUG, LOG_TAG, "Min Complex Chars: %s", input);

	min_complex_chars = atoi(input);

	handle = dpm_context_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}
	
	password_policy_handle = dpm_context_acquire_password_policy(handle, param_zone);
	if (password_policy_handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_min_complex_chars(password_policy_handle, min_complex_chars) == 0) {
        dpm_context_release_password_policy(handle, password_policy_handle);
		dpm_context_destroy(handle);
		display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"),input);
		return POLICY_RESULT_NONE;
	}

    dpm_context_release_password_policy(handle, password_policy_handle);
	dpm_context_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int set_password_max_failed_attempts_for_wipe_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "set_password_max_failed_attempts_for_wipe_handler");
	dpm_context_h handle;
	dpm_password_policy_h password_policy_handle;
	dpm_toolkit_entity_t* selected_policy = self;
    char* input;
	int max_failed_attempts;
	const char param_zone[] = "owner";

	handler_display_input_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"),selected_policy);

	input = selected_policy->entry_input;

	dlog_print(DLOG_DEBUG, LOG_TAG, "Max Failed Attempts: %s", input);

	max_failed_attempts = atoi(input);

	handle = dpm_context_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}
	
	password_policy_handle = dpm_context_acquire_password_policy(handle, param_zone);
	if (password_policy_handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_maximum_failed_attempts_for_wipe(password_policy_handle, max_failed_attempts) == 0) {
        dpm_context_release_password_policy(handle, password_policy_handle);
		dpm_context_destroy(handle);
		display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"),input);
		return POLICY_RESULT_NONE;
	}

    dpm_context_release_password_policy(handle, password_policy_handle);
	dpm_context_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int set_password_expires_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "set_password_expires_handler");
	dpm_context_h handle;
	dpm_password_policy_h password_policy_handle;
	dpm_toolkit_entity_t* selected_policy = self;
    char* input;
	int expired_day;
	const char param_zone[] = "owner";

	handler_display_input_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"),selected_policy);

	input = selected_policy->entry_input;

	dlog_print(DLOG_DEBUG, LOG_TAG, "Expired Day: %s", input);

	expired_day = atoi(input);

	handle = dpm_context_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}
	
	password_policy_handle = dpm_context_acquire_password_policy(handle, param_zone);
	if (password_policy_handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_expires(password_policy_handle, expired_day) == 0) {
        dpm_context_release_password_policy(handle, password_policy_handle);
		dpm_context_destroy(handle);
		display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"),input);
		return POLICY_RESULT_NONE;
	}

    dpm_context_release_password_policy(handle, password_policy_handle);
	dpm_context_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int set_password_history_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "set_password_history_handler");
	dpm_context_h handle;
	dpm_password_policy_h password_policy_handle;
	dpm_toolkit_entity_t* selected_policy = self;
    char* input;
	int history;
	const char param_zone[] = "owner";

	handler_display_input_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"),selected_policy);

	input = selected_policy->entry_input;

	dlog_print(DLOG_DEBUG, LOG_TAG, "History: %s", input);

	history = atoi(input);

	handle = dpm_context_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}
	
	password_policy_handle = dpm_context_acquire_password_policy(handle, param_zone);
	if (password_policy_handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_history(password_policy_handle, history) == 0) {
        dpm_context_release_password_policy(handle, password_policy_handle);
		dpm_context_destroy(handle);
		display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"),input);
		return POLICY_RESULT_NONE;
	}

    dpm_context_release_password_policy(handle, password_policy_handle);
	dpm_context_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int set_password_pattern_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "set_password_pattern_handler");
	dpm_context_h handle;
	dpm_password_policy_h password_policy_handle;
	dpm_toolkit_entity_t* selected_policy = self;
    char* input;
	const char param_zone[] = "owner";

	handler_display_input_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"),selected_policy);

	input = selected_policy->entry_input;

	dlog_print(DLOG_DEBUG, LOG_TAG, "Password Pattern: %s", input);

	handle = dpm_context_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}
	
	password_policy_handle = dpm_context_acquire_password_policy(handle, param_zone);
	if (password_policy_handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_pattern(password_policy_handle, input) == 0) {
        dpm_context_release_password_policy(handle, password_policy_handle);
		dpm_context_destroy(handle);
		display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"),input);
		return POLICY_RESULT_NONE;
	}

    dpm_context_release_password_policy(handle, password_policy_handle);
	dpm_context_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int reset_password_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "reset_password_handler");
	dpm_context_h handle;
	dpm_password_policy_h password_policy_handle;
	dpm_toolkit_entity_t* selected_policy = self;
    char* input;
	const char param_zone[] = "owner";

	handler_display_input_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"),selected_policy);

	input = selected_policy->entry_input;

	dlog_print(DLOG_DEBUG, LOG_TAG, "New Password: %s", input);

	handle = dpm_context_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}
	
	password_policy_handle = dpm_context_acquire_password_policy(handle, param_zone);
	if (password_policy_handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_reset(password_policy_handle, input) == 0) {
        dpm_context_release_password_policy(handle, password_policy_handle);
		dpm_context_destroy(handle);
		display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"),input);
		return POLICY_RESULT_NONE;
	}

    dpm_context_release_password_policy(handle, password_policy_handle);
	dpm_context_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int enforce_password_change_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "enforce_password_change_handler");
	dpm_context_h handle;
	dpm_password_policy_h password_policy_handle;
	const char param_zone[] = "owner";

	handle = dpm_context_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}
	
	password_policy_handle = dpm_context_acquire_password_policy(handle, param_zone);
	if (password_policy_handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_enforce_change(password_policy_handle) == 0) {
        dpm_context_release_password_policy(handle, password_policy_handle);
		dpm_context_destroy(handle);
		return POLICY_RESULT_SUCCESS;
	}

    dpm_context_release_password_policy(handle, password_policy_handle);
	dpm_context_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int set_max_inactivity_time_device_lock_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "set_max_inactivity_time_device_lock_handler");
	dpm_context_h handle;
	dpm_password_policy_h password_policy_handle;
	dpm_toolkit_entity_t* selected_policy = self;
    char* input;
	int max_inactivity_time;
	const char param_zone[] = "owner";

	handler_display_input_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"),selected_policy);

	input = selected_policy->entry_input;

	dlog_print(DLOG_DEBUG, LOG_TAG, "Max Inactivity Time: %s", input);

	max_inactivity_time = atoi(input);

	handle = dpm_context_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}
	
	password_policy_handle = dpm_context_acquire_password_policy(handle, param_zone);
	if (password_policy_handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_max_inactivity_time_device_lock(password_policy_handle, max_inactivity_time) == 0) {
        dpm_context_release_password_policy(handle, password_policy_handle);
		dpm_context_destroy(handle);
		display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"),input);
		return POLICY_RESULT_NONE;
	}

    dpm_context_release_password_policy(handle, password_policy_handle);
	dpm_context_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int get_max_inactivity_time_device_lock_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "get_max_inactivity_time_device_lock_handler");
	dpm_context_h handle;
	dpm_password_policy_h password_policy_handle;
	dpm_toolkit_entity_t* selected_policy = self;
	char num_text[10];
	int max_inactivity_time;
	const char param_zone[] = "owner";

	handle = dpm_context_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}
	
	password_policy_handle = dpm_context_acquire_password_policy(handle, param_zone);
	if (password_policy_handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_max_inactivity_time_device_lock(password_policy_handle, &max_inactivity_time) == 0) {
        dpm_context_release_password_policy(handle, password_policy_handle);
		dpm_context_destroy(handle);
		snprintf(num_text,sizeof(num_text),"%d",max_inactivity_time);
		display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), num_text);
		return POLICY_RESULT_NONE;
	}

    dpm_context_release_password_policy(handle, password_policy_handle);
	dpm_context_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int set_password_status_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "set_password_status_handler");
	dpm_context_h handle;
	dpm_password_policy_h password_policy_handle;
	dpm_toolkit_entity_t* selected_policy = self;
    char* input;
	int status;
	const char param_zone[] = "owner";

	handler_display_input_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"),selected_policy);

	input = selected_policy->entry_input;

	dlog_print(DLOG_DEBUG, LOG_TAG, "Status: %s", input);

	status = atoi(input);

	handle = dpm_context_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}
	
	password_policy_handle = dpm_context_acquire_password_policy(handle, param_zone);
	if (password_policy_handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_status(password_policy_handle, status) == 0) {
        dpm_context_release_password_policy(handle, password_policy_handle);
		dpm_context_destroy(handle);
		display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"),input);
		return POLICY_RESULT_NONE;
	}

    dpm_context_release_password_policy(handle, password_policy_handle);
	dpm_context_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int delete_password_pattern_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "delete_password_pattern_handler");
	dpm_context_h handle;
	dpm_password_policy_h password_policy_handle;
	const char param_zone[] = "owner";

	handle = dpm_context_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}
	
	password_policy_handle = dpm_context_acquire_password_policy(handle, param_zone);
	if (password_policy_handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_delete_pattern(password_policy_handle) == 0) {
        dpm_context_release_password_policy(handle, password_policy_handle);
		dpm_context_destroy(handle);
		return POLICY_RESULT_SUCCESS;
	}

    dpm_context_release_password_policy(handle, password_policy_handle);
	dpm_context_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int get_password_pattern_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "get_password_pattern_handler");
	dpm_context_h handle;
	dpm_password_policy_h password_policy_handle;
	dpm_toolkit_entity_t* selected_policy = self;
    char* password_pattern;
	const char param_zone[] = "owner";

	handle = dpm_context_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}
	
	password_policy_handle = dpm_context_acquire_password_policy(handle, param_zone);
	if (password_policy_handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		return POLICY_RESULT_FAIL;
	}

    dlog_print(DLOG_DEBUG, LOG_TAG, "dpm_password_get_pattern_in");
	if (dpm_password_get_pattern(password_policy_handle, &password_pattern) == 0) {
        dlog_print(DLOG_DEBUG, LOG_TAG, "dpm_password_get_pattern_out");
		display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), password_pattern);
		free(password_pattern);
		dpm_context_release_password_policy(handle, password_policy_handle);
		dpm_context_destroy(handle);
		return POLICY_RESULT_NONE;
	}

    dpm_context_release_password_policy(handle, password_policy_handle);
	dpm_context_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int set_max_char_occurrences_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "set_max_char_occurrences_handler");
	dpm_context_h handle;
	dpm_password_policy_h password_policy_handle;
	dpm_toolkit_entity_t* selected_policy = self;
    char* input;
	int max_char_occur;
	const char param_zone[] = "owner";

	handler_display_input_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"),selected_policy);

	input = selected_policy->entry_input;

	dlog_print(DLOG_DEBUG, LOG_TAG, "Max Char Occurrences: %s", input);

	max_char_occur = atoi(input);

	handle = dpm_context_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}
	
	password_policy_handle = dpm_context_acquire_password_policy(handle, param_zone);
	if (password_policy_handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_maximum_character_occurrences(password_policy_handle, max_char_occur) == 0) {
        dpm_context_release_password_policy(handle, password_policy_handle);
		dpm_context_destroy(handle);
		display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"),input);
		return POLICY_RESULT_NONE;
	}

    dpm_context_release_password_policy(handle, password_policy_handle);
	dpm_context_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int get_max_char_occurrences_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "get_max_char_occurrences_handler");
	dpm_context_h handle;
	dpm_password_policy_h password_policy_handle;
	dpm_toolkit_entity_t* selected_policy = self;
	char num_text[10];
	int max_char_occur;
	const char param_zone[] = "owner";

	handle = dpm_context_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}
	
	password_policy_handle = dpm_context_acquire_password_policy(handle, param_zone);
	if (password_policy_handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_maximum_character_occurrences(password_policy_handle, &max_char_occur) == 0) {
        dpm_context_release_password_policy(handle, password_policy_handle);
		dpm_context_destroy(handle);
		snprintf(num_text,sizeof(num_text),"%d",max_char_occur);
		display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), num_text);
		return POLICY_RESULT_NONE;
	}

    dpm_context_release_password_policy(handle, password_policy_handle);
	dpm_context_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int set_max_numeric_sequence_length_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "set_max_numeric_sequence_length_handler");
	dpm_context_h handle;
	dpm_password_policy_h password_policy_handle;
	dpm_toolkit_entity_t* selected_policy = self;
    char* input;
	int max_numeric_seq_length;
	const char param_zone[] = "owner";

	handler_display_input_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"),selected_policy);

	input = selected_policy->entry_input;

	dlog_print(DLOG_DEBUG, LOG_TAG, "Max Numeric Sequence Length: %s", input);

	max_numeric_seq_length = atoi(input);

	handle = dpm_context_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}
	
	password_policy_handle = dpm_context_acquire_password_policy(handle, param_zone);
	if (password_policy_handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_set_maximum_numeric_sequence_length(password_policy_handle, max_numeric_seq_length) == 0) {
        dpm_context_release_password_policy(handle, password_policy_handle);
		dpm_context_destroy(handle);
		display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"),input);
		return POLICY_RESULT_NONE;
	}

    dpm_context_release_password_policy(handle, password_policy_handle);
	dpm_context_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int get_max_numeric_sequence_length_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "get_max_numeric_sequence_length_handler");
	dpm_context_h handle;
	dpm_password_policy_h password_policy_handle;
	dpm_toolkit_entity_t* selected_policy = self;
	char num_text[10];
	int max_numeric_seq_length;
	const char param_zone[] = "owner";

	handle = dpm_context_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}
	
	password_policy_handle = dpm_context_acquire_password_policy(handle, param_zone);
	if (password_policy_handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create password policy handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_password_get_maximum_numeric_sequence_length(password_policy_handle, &max_numeric_seq_length) == 0) {
        dpm_context_release_password_policy(handle, password_policy_handle);
		dpm_context_destroy(handle);
		snprintf(num_text,sizeof(num_text),"%d",max_numeric_seq_length);
		display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), num_text);
		return POLICY_RESULT_NONE;
	}

    dpm_context_release_password_policy(handle, password_policy_handle);
	dpm_context_destroy(handle);
	return POLICY_RESULT_FAIL;
}


dpm_toolkit_entity_t dpm_toolkit_password_policy[] = {
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
	 .id = "SET_PASSWORD_PATTERN",
	 .handler = set_password_pattern_handler
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
	 .id = "DELETE_PASSWORD_PATTERN",
	 .handler = delete_password_pattern_handler
	},
	{
	 .id = "GET_PASSWORD_PATTERN",
	 .handler = get_password_pattern_handler
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

dpm_toolkit_policy_group_t password_policy_group = {
	.id = "PASSWORD"
};

void __CONSTRUCTOR__ dpm_toolkit_password_policy_constructor()
{
	int ret = 0;
	dlog_print(DLOG_DEBUG, LOG_TAG, "password policy constructor");

	int policyNum = sizeof(dpm_toolkit_password_policy) / sizeof(dpm_toolkit_password_policy[0]);
	ret = dpm_toolkit_init_policy(&(password_policy_group.policies), dpm_toolkit_password_policy, policyNum);
	if (ret < 0)
		dlog_print(DLOG_ERROR, LOG_TAG, "password policy initialization fail");
	ret = dpm_toolkit_add_policy_group(&global_dpm_policy_group_list, &password_policy_group);
	if (ret < 0)
		dlog_print(DLOG_ERROR, LOG_TAG, "add password group fail");
}
