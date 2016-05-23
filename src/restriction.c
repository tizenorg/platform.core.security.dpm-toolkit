#include "dpm-toolkit.h"
#include <dpm/restriction.h>

int set_camera_state_handler(struct dpm_toolkit_entity *self)
{
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;
	dpm_toolkit_entity_t *selected_policy = self;
	char radio_text[][MAX_RADIO_TEXT_LEN] = {"ALLOW", "DISALLOW"};
	int radio_num = sizeof(radio_text) / sizeof(radio_text[0]);
	int enable = 1;

	handler_display_radio_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), selected_policy, radio_text, radio_num);

	switch (selected_policy->radio_index) {
	case 0:
		enable = 1;
		break;
	case 1:
		enable = 0;
		break;
	default:
		break;
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

	if (dpm_restriction_set_camera_state(policy, enable) == 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_SUCCESS;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);
	return POLICY_RESULT_FAIL;
}

int get_camera_state_handler(struct dpm_toolkit_entity *self)
{
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;
	dpm_toolkit_entity_t *selected_policy = self;
	int state = 1;
	char state_text[2][MAX_RADIO_TEXT_LEN] = {"DISALLOWED", "ALLOWED"};

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
		display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), state_text[state]);
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);
	return POLICY_RESULT_FAIL;
}

int set_microphone_state_handler(struct dpm_toolkit_entity *self)
{
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;
	dpm_toolkit_entity_t *selected_policy = self;
	char radio_text[][MAX_RADIO_TEXT_LEN] = {"ALLOW", "DISALLOW"};
	int radio_num = sizeof(radio_text) / sizeof(radio_text[0]);
	int enable = 1;

	handler_display_radio_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), selected_policy, radio_text, radio_num);

	switch (selected_policy->radio_index) {
	case 0:
		enable = 1;
		break;
	case 1:
		enable = 0;
		break;
	default:
		break;
	}

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

	if (dpm_restriction_set_microphone_state(policy, enable) == 0) {
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_SUCCESS;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);
	return POLICY_RESULT_FAIL;
}

int get_microphone_state_handler(struct dpm_toolkit_entity *self)
{
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;
	dpm_toolkit_entity_t *selected_policy = self;
	int state = 1;
	char state_text[2][MAX_RADIO_TEXT_LEN] = {"DISALLOWED", "ALLOWED"};

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
		display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), state_text[state]);
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);
	return POLICY_RESULT_FAIL;
}

int set_location_state_handler(struct dpm_toolkit_entity *self)
{
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;
	dpm_toolkit_entity_t *selected_policy = self;
	int enable = 1;
	char radio_text_quality[][MAX_RADIO_TEXT_LEN] = {"ALLOW", "DISALLOW"};
	int radio_num = sizeof(radio_text_quality) / sizeof(radio_text_quality[0]);

	handler_display_radio_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *)"desc"),
								selected_policy, radio_text_quality, radio_num);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create dpm context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	switch (selected_policy->radio_index) {
	case 0:
		enable = 1;
		break;
	case 1:
		enable = 0;
		break;
	default:
		break;
	}

	if (dpm_restriction_set_location_state(policy, enable) != 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set location state");
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);
	return POLICY_RESULT_SUCCESS;
}

int get_location_state_handler(struct dpm_toolkit_entity *self)
{
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;
	dpm_toolkit_entity_t *selected_policy = self;
	int state = 0;
	char state_text[2][MAX_RADIO_TEXT_LEN] = {"DISALLOWED", "ALLOWED"};

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create dpm context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	dpm_restriction_get_location_state(policy, &state);
	if (state < 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to get location state");
		dpm_context_release_restriction_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *)"desc"), state_text[state]);
	return POLICY_RESULT_NONE;
}

/* clipboard toolkit handler */
int set_clipboard_state_handler(struct dpm_toolkit_entity *self)
{
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;
	int ret = POLICY_RESULT_SUCCESS;
	int get_value = 0;
	int set_value = 0;
	char radio_text_quality[][MAX_RADIO_TEXT_LEN] = {"ALLOW", "DISALLOW"};
	int radio_num = sizeof(radio_text_quality) / sizeof(radio_text_quality[0]);
	char state_text[2][MAX_RADIO_TEXT_LEN] = {"DISALLOWED", "ALLOWED"};

	handler_display_radio_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), self, radio_text_quality, radio_num);
	switch (self->radio_index) {
	case 0:
		set_value = 1;
		break;
	case 1:
		set_value = 0;
		break;
	}

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed in dpm_context_create()");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed in dpm_context_acquire_restriction_policy()");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_set_clipboard_state(policy, set_value) != 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed in dpm_restriction_set_clipboard_state()");
		ret = POLICY_RESULT_FAIL;
		goto out;
	}

	if (dpm_restriction_get_clipboard_state(policy, &get_value) < 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed in dpm_restriction_get_clipboard_state()");
		ret = POLICY_RESULT_FAIL;
		goto out;
	}

	if (set_value != get_value) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set value of restriction");
		ret = POLICY_RESULT_FAIL;
		goto out;
	} else {
		display_result_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), state_text[set_value]);
	}
out:
	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	if (ret == POLICY_RESULT_FAIL)
		return ret;
	else
		return POLICY_RESULT_NONE;
}

int get_clipboard_state_handler(struct dpm_toolkit_entity *self)
{
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;
	int ret = POLICY_RESULT_SUCCESS;
	int enable = 0;
	char state_text[2][MAX_RADIO_TEXT_LEN] = {"DISALLOWED", "ALLOWED"};

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed in dpm_context_create()");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed in dpm_context_acquire_restriction_policy()");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_clipboard_state(policy, &enable) < 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed in dpm_restriction_get_clipboard_state()");
		ret = POLICY_RESULT_FAIL;
		goto out;
	}

	if (enable == 1 || enable == 0)
		display_result_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), state_text[enable]);
	else
		ret = POLICY_RESULT_FAIL;

out:
	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	if (ret == POLICY_RESULT_FAIL)
		return ret;
	else
		return POLICY_RESULT_NONE;
}

/* settings changes toolkit handler */
int set_settings_changes_restriction_handler(struct dpm_toolkit_entity *self)
{
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;
	int ret = POLICY_RESULT_SUCCESS;
	int get_value = 0;
	int set_value = 0;
	char radio_text_quality[][MAX_RADIO_TEXT_LEN] = {"ALLOW", "DISALLOW"};
	int radio_num = sizeof(radio_text_quality) / sizeof(radio_text_quality[0]);
	char state_text[2][MAX_RADIO_TEXT_LEN] = {"DISALLOWED", "ALLOWED"};

	handler_display_radio_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), self, radio_text_quality, radio_num);
	switch (self->radio_index) {
	case 0:
		set_value = 1;
		break;
	case 1:
		set_value = 0;
		break;
	}

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed in dpm_context_create()");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed in dpm_context_acquire_restriction_policy()");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_set_settings_changes_state(policy, set_value) != 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed in dpm_restriction_set_settings_changes_state()");
		ret = POLICY_RESULT_FAIL;
		goto out;
	}

	if (dpm_restriction_get_settings_changes_state(policy, &get_value) < 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed in dpm_restriction_get_settings_changes_state()");
		ret = POLICY_RESULT_FAIL;
		goto out;
	}

	if (set_value != get_value) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set value of restriction");
		ret = POLICY_RESULT_FAIL;
		goto out;
	} else {
		display_result_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), state_text[set_value]);
	}

out:
	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	if (ret == POLICY_RESULT_FAIL)
		return ret;
	else
		return POLICY_RESULT_NONE;
}

int get_settings_changes_restriction_handler(struct dpm_toolkit_entity *self)
{
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;
	int ret = POLICY_RESULT_SUCCESS;
	int enable = 0;
	char state_text[2][MAX_RADIO_TEXT_LEN] = {"DISALLOWED", "ALLOWED"};

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed in dpm_context_create()");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed in dpm_context_acquire_restriction_policy()");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_settings_changes_state(policy, &enable) < 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed in dpm_restriction_get_settings_changes_state()");
		ret = POLICY_RESULT_FAIL;
		goto out;
	}

	if (enable == 1 || enable == 0)
		display_result_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), state_text[enable]);
	else
		ret = POLICY_RESULT_FAIL;

out:
	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	if (ret == POLICY_RESULT_FAIL)
		return ret;
	else
		return POLICY_RESULT_NONE;
}

/* usb debugging toolkit handler */
int set_usb_debugging_state_handler(struct dpm_toolkit_entity *self)
{
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;
	int ret = POLICY_RESULT_SUCCESS;
	int get_value = 0;
	int set_value = 0;
	char radio_text_quality[][MAX_RADIO_TEXT_LEN] = {"ALLOW", "DISALLOW"};
	int radio_num = sizeof(radio_text_quality) / sizeof(radio_text_quality[0]);
	char state_text[2][MAX_RADIO_TEXT_LEN] = {"DISALLOWED", "ALLOWED"};

	handler_display_radio_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), self, radio_text_quality, radio_num);
	switch (self->radio_index) {
	case 0:
		set_value = 1;
		break;
	case 1:
		set_value = 0;
		break;
	}

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed in dpm_context_create()");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed in dpm_context_acquire_restriction_policy()");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_set_usb_debugging_state(policy, set_value) != 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed in dpm_restriction_set_usb_debugging_state()");
		ret = POLICY_RESULT_FAIL;
		goto out;
	}

	if (dpm_restriction_get_usb_debugging_state(policy, &get_value) < 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed in dpm_restriction_get_usb_debugging_state()");
		ret = POLICY_RESULT_FAIL;
		goto out;
	}

	if (set_value != get_value) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set value of restriction");
		ret = POLICY_RESULT_FAIL;
		goto out;
	} else {
		display_result_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), state_text[set_value]);
	}

out:
	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	if (ret == POLICY_RESULT_FAIL)
		return ret;
	else
		return POLICY_RESULT_NONE;
}

int get_usb_debugging_state_handler(struct dpm_toolkit_entity *self)
{
	dpm_context_h context = NULL;
	dpm_restriction_policy_h policy = NULL;
	int ret = POLICY_RESULT_SUCCESS;
	int enable = 0;
	char state_text[2][MAX_RADIO_TEXT_LEN] = {"DISALLOWED", "ALLOWED"};

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed in dpm_context_create()");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed in dpm_context_acquire_restriction_policy()");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_usb_debugging_state(policy, &enable) < 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed in dpm_restriction_get_usb_debugging_state()");
		ret = POLICY_RESULT_FAIL;
		goto out;
	}

	if (enable == 1 || enable == 0)
		display_result_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), state_text[enable]);
	else
		ret = POLICY_RESULT_FAIL;

out:
	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	if (ret == POLICY_RESULT_FAIL)
		return ret;
	else
		return POLICY_RESULT_NONE;
}

int set_wifi_state_handler(struct dpm_toolkit_entity *self)
{
	char radio_text[][MAX_RADIO_TEXT_LEN] = {"ALLOW", "DISALLOW"};
	dpm_restriction_policy_h policy;
	dpm_context_h context;
	int ret;

	dlog_print(DLOG_DEBUG, LOG_TAG, __func__);

	handler_display_radio_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"),
		self, radio_text, sizeof(radio_text) / sizeof(char) / MAX_RADIO_TEXT_LEN);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);

	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get restiction policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (self->radio_index == 0)
		ret = dpm_restriction_set_wifi_state(policy, true);
	else
		ret = dpm_restriction_set_wifi_state(policy, false);

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return (ret == DPM_ERROR_NONE) ? POLICY_RESULT_SUCCESS : POLICY_RESULT_FAIL;
}

int get_wifi_state_handler(struct dpm_toolkit_entity *self)
{
	dpm_restriction_policy_h policy;
	dpm_context_h context;
	int state, ret;

	dlog_print(DLOG_DEBUG, LOG_TAG, __func__);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);

	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get wifi policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	ret = dpm_restriction_get_wifi_state(policy, &state);

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	if (ret == DPM_ERROR_NONE) {
		display_result_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"),
			state == true ? "ALLOWED" : "DISALLOWED");

		return POLICY_RESULT_NONE;
	}

	return POLICY_RESULT_FAIL;
}

int set_wifi_hotspot_state_handler(struct dpm_toolkit_entity *self)
{
	char radio_text[][MAX_RADIO_TEXT_LEN] = {"ALLOW", "DISALLOW"};
	dpm_restriction_policy_h policy;
	dpm_context_h context;
	int ret;

	dlog_print(DLOG_DEBUG, LOG_TAG, __func__);

	handler_display_radio_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"),
		self, radio_text, sizeof(radio_text) / sizeof(char) / MAX_RADIO_TEXT_LEN);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);

	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get restriction policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (self->radio_index == 0)
		ret = dpm_restriction_set_wifi_hotspot_state(policy, true);
	else
		ret = dpm_restriction_set_wifi_hotspot_state(policy, false);

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return (ret == DPM_ERROR_NONE) ? POLICY_RESULT_SUCCESS : POLICY_RESULT_FAIL;
}

int get_wifi_hotspot_state_handler(struct dpm_toolkit_entity *self)
{
	dpm_restriction_policy_h policy;
	dpm_context_h context;
	int state, ret;

	dlog_print(DLOG_DEBUG, LOG_TAG, __func__);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);

	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get wifi policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	ret = dpm_restriction_get_wifi_hotspot_state(policy, &state);

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	if (ret == DPM_ERROR_NONE) {
		display_result_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"),
			state == true ? "ALLOWED" : "DISALLOWED");

		return POLICY_RESULT_NONE;
	}

	return POLICY_RESULT_FAIL;
}

int set_bluetooth_tethering_state_handler(struct dpm_toolkit_entity *self)
{
	char radio_text[][MAX_RADIO_TEXT_LEN] = {"ALLOW", "DISALLOW"};
	dpm_restriction_policy_h policy;
	dpm_context_h context;
	int ret;

	dlog_print(DLOG_DEBUG, LOG_TAG, __func__);

	handler_display_radio_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"),
		self, radio_text, sizeof(radio_text) / sizeof(char) / MAX_RADIO_TEXT_LEN);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);

	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get restriction policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (self->radio_index == 0)
		ret = dpm_restriction_set_bluetooth_tethering_state(policy, true);
	else
		ret = dpm_restriction_set_bluetooth_tethering_state(policy, false);

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return (ret == DPM_ERROR_NONE) ? POLICY_RESULT_SUCCESS : POLICY_RESULT_FAIL;
}

int get_bluetooth_tethering_state_handler(struct dpm_toolkit_entity *self)
{
	dpm_restriction_policy_h policy;
	dpm_context_h context;
	int state, ret;

	dlog_print(DLOG_DEBUG, LOG_TAG, __func__);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);

	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get restriction policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	ret = dpm_restriction_get_bluetooth_tethering_state(policy, &state);

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	if (ret == DPM_ERROR_NONE) {
		display_result_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"),
			state == true ? "ALLOWED" : "DISALLOWED");

		return POLICY_RESULT_NONE;
	}

	return POLICY_RESULT_FAIL;
}

int set_usb_tethering_state_handler(struct dpm_toolkit_entity *self)
{
	char radio_text[][MAX_RADIO_TEXT_LEN] = {"ALLOW", "DISALLOW"};
	dpm_restriction_policy_h policy;
	dpm_context_h context;
	int ret;

	dlog_print(DLOG_DEBUG, LOG_TAG, __func__);

	handler_display_radio_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"),
		self, radio_text, sizeof(radio_text) / sizeof(char) / MAX_RADIO_TEXT_LEN);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);

	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get restriction policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (self->radio_index == 0)
		ret = dpm_restriction_set_usb_tethering_state(policy, true);
	else
		ret = dpm_restriction_set_usb_tethering_state(policy, false);

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return (ret == DPM_ERROR_NONE) ? POLICY_RESULT_SUCCESS : POLICY_RESULT_FAIL;
}

int get_usb_tethering_state_handler(struct dpm_toolkit_entity *self)
{
	dpm_restriction_policy_h policy;
	dpm_context_h context;
	int state, ret;

	dlog_print(DLOG_DEBUG, LOG_TAG, __func__);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);

	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get restriction policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	ret = dpm_restriction_get_usb_tethering_state(policy, &state);

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	if (ret == DPM_ERROR_NONE) {
		display_result_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"),
			state == true ? "ALLOWED" : "DISALLOWED");

		return POLICY_RESULT_NONE;
	}

	return POLICY_RESULT_FAIL;
}

int set_bluetooth_mode_change_state_handler(struct dpm_toolkit_entity *self)
{
	char radio_text[][MAX_RADIO_TEXT_LEN] = {"ALLOW", "DISALLOW"};
	dpm_restriction_policy_h policy;
	dpm_context_h context;
	int ret;

	dlog_print(DLOG_DEBUG, LOG_TAG, __func__);

	handler_display_radio_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"),
		self, radio_text, sizeof(radio_text) / sizeof(char) / MAX_RADIO_TEXT_LEN);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);

	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get restriction policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (self->radio_index == 0)
		ret = dpm_restriction_set_bluetooth_mode_change_state(policy, true);
	else
		ret = dpm_restriction_set_bluetooth_mode_change_state(policy, false);

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return (ret == DPM_ERROR_NONE) ? POLICY_RESULT_SUCCESS : POLICY_RESULT_FAIL;
}

int get_bluetooth_mode_change_state_handler(struct dpm_toolkit_entity *self)
{
	dpm_restriction_policy_h policy;
	dpm_context_h context;
	int state, ret;

	dlog_print(DLOG_DEBUG, LOG_TAG, __func__);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);

	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get restriction policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	ret = dpm_restriction_get_bluetooth_mode_change_state(policy, &state);

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	if (ret == DPM_ERROR_NONE) {
		display_result_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"),
			state == true ? "ALLOWED" : "DISALLOWED");

		return POLICY_RESULT_NONE;
	}

	return POLICY_RESULT_FAIL;
}

int set_bluetooth_desktop_connectivity_state_handler(struct dpm_toolkit_entity *self)
{
	char radio_text[][MAX_RADIO_TEXT_LEN] = {"ALLOW", "DISALLOW"};
	dpm_restriction_policy_h policy;
	dpm_context_h context;
	int ret;

	dlog_print(DLOG_DEBUG, LOG_TAG, __func__);

	handler_display_radio_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"),
		self, radio_text, sizeof(radio_text) / sizeof(char) / MAX_RADIO_TEXT_LEN);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);

	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get restriction policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (self->radio_index == 0)
		ret = dpm_restriction_set_bluetooth_desktop_connectivity_state(policy, true);
	else
		ret = dpm_restriction_set_bluetooth_desktop_connectivity_state(policy, false);

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	return (ret == DPM_ERROR_NONE) ? POLICY_RESULT_SUCCESS : POLICY_RESULT_FAIL;
}

int get_bluetooth_desktop_connectivity_state_handler(struct dpm_toolkit_entity *self)
{
	dpm_restriction_policy_h policy;
	dpm_context_h context;
	int state, ret;

	dlog_print(DLOG_DEBUG, LOG_TAG, __func__);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_restriction_policy(context);

	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get restriction policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	ret = dpm_restriction_get_bluetooth_desktop_connectivity_state(policy, &state);

	dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	if (ret == DPM_ERROR_NONE) {
		display_result_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"),
			state == true ? "ALLOWED" : "DISALLOWED");

		return POLICY_RESULT_NONE;
	}

	return POLICY_RESULT_FAIL;
}

dpm_toolkit_entity_t dpm_toolkit_restriction_policy[] = {
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
	 .id = "SET_SETTINGS_CHANGES_RESTRICTION",
	 .handler = set_settings_changes_restriction_handler
	},
	{
	 .id = "GET_SETTINGS_CHANGES_RESTRICTION",
	 .handler = get_settings_changes_restriction_handler
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
	}
};

dpm_toolkit_policy_group_t restriction_policy_group = {
	.id = "RESTRICTION"
};

void __CONSTRUCTOR__ dpm_toolkit_restriction_policy_constructor()
{
	int ret = 0;
	dlog_print(DLOG_DEBUG, LOG_TAG, "restriction policy constructor");

	int policyNum = sizeof(dpm_toolkit_restriction_policy) / sizeof(dpm_toolkit_restriction_policy[0]);
	ret = dpm_toolkit_init_policy(&(restriction_policy_group.policies), dpm_toolkit_restriction_policy, policyNum);
	if (ret < 0)
		dlog_print(DLOG_ERROR, LOG_TAG, "restriction policy initialization fail");
	ret = dpm_toolkit_add_policy_group(&global_dpm_policy_group_list, &restriction_policy_group);
	if (ret < 0)
		dlog_print(DLOG_ERROR, LOG_TAG, "add restriction group fail");
}
