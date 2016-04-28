#include "dpm-toolkit.h"
#include <dpm/restriction.h>

/* dpm integration test */
// ON_SET_CHANGES_RESTRICTION
int set_camera_state_handler(struct dpm_toolkit_entity *self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "set_camera_state_handler");
	dpm_context_h handle;
	dpm_restriction_policy_h camera_policy_handle;
	dpm_toolkit_entity_t *selected_policy = self;
	char radio_text[][MAX_RADIO_TEXT_LEN] = {"ENABLE", "DISABLE"};
	int radio_num = sizeof(radio_text) / sizeof(radio_text[0]);
	int enable = 1;

	handler_display_radio_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), selected_policy, radio_text, radio_num);

	dlog_print(DLOG_DEBUG, LOG_TAG, "radio index: %d", selected_policy->radio_index);

	switch (selected_policy->radio_index) {
	case 0:
		enable = 1;
		break;
	case 1:
		enable = 0;
		break;
	default:
		enable = 1;
		break;
	}

	dlog_print(DLOG_DEBUG, LOG_TAG, "Camera State: %d", enable);

	handle = dpm_context_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	camera_policy_handle = dpm_context_acquire_restriction_policy(handle);
	if (camera_policy_handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create camera policy handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_set_camera_state(camera_policy_handle, enable) == 0) {
		dpm_context_release_restriction_policy(handle, camera_policy_handle);
		dpm_context_destroy(handle);
		return POLICY_RESULT_SUCCESS;
	}

	dpm_context_release_restriction_policy(handle, camera_policy_handle);
	dpm_context_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int get_camera_state_handler(struct dpm_toolkit_entity *self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "get_camera_state_handler");
	dpm_context_h handle;
	dpm_restriction_policy_h camera_policy_handle;
	dpm_toolkit_entity_t *selected_policy = self;
	int state = 1;
	char state_text[2][MAX_RADIO_TEXT_LEN] = {"DISABLE", "ENABLE"};

	handle = dpm_context_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	camera_policy_handle = dpm_context_acquire_restriction_policy(handle);
	if (camera_policy_handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create camera policy handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_camera_state(camera_policy_handle, &state) == 0) {
		dpm_context_release_restriction_policy(handle, camera_policy_handle);
		dpm_context_destroy(handle);
		display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), state_text[state]);
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(handle, camera_policy_handle);
	dpm_context_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int set_microphone_state_handler(struct dpm_toolkit_entity *self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "set_microphone_state_handler");
	dpm_context_h handle;
	dpm_restriction_policy_h mic_policy_handle;
	dpm_toolkit_entity_t *selected_policy = self;
	char radio_text[][MAX_RADIO_TEXT_LEN] = {"ENABLE", "DISABLE"};
	int radio_num = sizeof(radio_text) / sizeof(radio_text[0]);
	int enable = 1;

	handler_display_radio_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), selected_policy, radio_text, radio_num);

	dlog_print(DLOG_DEBUG, LOG_TAG, "radio index: %d", selected_policy->radio_index);

	switch (selected_policy->radio_index) {
	case 0:
		enable = 1;
		break;
	case 1:
		enable = 0;
		break;
	default:
		enable = 1;
		break;
	}

	dlog_print(DLOG_DEBUG, LOG_TAG, "Microphone State: %d", enable);

	handle = dpm_context_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	mic_policy_handle = dpm_context_acquire_restriction_policy(handle);
	if (mic_policy_handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create microphone policy handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_set_microphone_state(mic_policy_handle, enable) == 0) {
		dpm_context_release_restriction_policy(handle, mic_policy_handle);
		dpm_context_destroy(handle);
		return POLICY_RESULT_SUCCESS;
	}

	dpm_context_release_restriction_policy(handle, mic_policy_handle);
	dpm_context_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int get_microphone_state_handler(struct dpm_toolkit_entity *self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "get_microphone_state_handler");
	dpm_context_h handle;
	dpm_restriction_policy_h mic_policy_handle;
	dpm_toolkit_entity_t *selected_policy = self;
	int state = 1;
	char state_text[2][MAX_RADIO_TEXT_LEN] = {"DISABLE", "ENABLE"};

	handle = dpm_context_create();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create device policy context handle");
		return POLICY_RESULT_FAIL;
	}

	mic_policy_handle = dpm_context_acquire_restriction_policy(handle);
	if (mic_policy_handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create microphone policy handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_restriction_get_microphone_state(mic_policy_handle, &state) == 0) {
		dpm_context_release_restriction_policy(handle, mic_policy_handle);
		dpm_context_destroy(handle);
		display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), state_text[state]);
		return POLICY_RESULT_NONE;
	}

	dpm_context_release_restriction_policy(handle, mic_policy_handle);
	dpm_context_destroy(handle);
	return POLICY_RESULT_FAIL;
}

int set_location_state_handler(struct dpm_toolkit_entity *self)
{
	dpm_context_h ctx = NULL;
	dpm_restriction_policy_h handle = NULL;
	dpm_toolkit_entity_t *selected_policy = self;
	int enable = -1;
	char radio_text_quality[][MAX_RADIO_TEXT_LEN] = {"ALLOW", "DISALLOW"};
	int radio_num = sizeof(radio_text_quality) / sizeof(radio_text_quality[0]);

	handler_display_radio_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *)"desc"),
								selected_policy, radio_text_quality, radio_num);

	ctx = dpm_context_create();
	if (ctx == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create dpm context");
		return POLICY_RESULT_FAIL;
	}

	handle = dpm_context_acquire_restriction_policy(ctx);
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		dpm_context_destroy(ctx);
		return POLICY_RESULT_FAIL;
	}

	switch (selected_policy->radio_index) {
	case 0:
		enable = 0;
		break;
	case 1:
		enable = 1;
		break;
	default:
		break;
	}

	if (dpm_restriction_set_location_state(handle, enable) != 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to set location state");
		dpm_context_release_restriction_policy(ctx, handle);
		dpm_context_destroy(ctx);
		return POLICY_RESULT_FAIL;
	}

	dpm_context_release_restriction_policy(ctx, handle);
	dpm_context_destroy(ctx);
	return POLICY_RESULT_SUCCESS;
}

int get_location_state_handler(struct dpm_toolkit_entity *self)
{
	dpm_context_h ctx = NULL;
	dpm_restriction_policy_h handle = NULL;
	dpm_toolkit_entity_t *selected_policy = self;
	int location_status = -1;
	char input[PATH_MAX] = "\0";

	ctx = dpm_context_create();
	if (ctx == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create dpm context");
		return POLICY_RESULT_FAIL;
	}

	handle = dpm_context_acquire_restriction_policy(ctx);
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		dpm_context_destroy(ctx);
		return POLICY_RESULT_FAIL;
	}

	dpm_restriction_get_location_state(handle, &location_status);
	if (location_status < 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to get location status");
		dpm_context_release_restriction_policy(ctx, handle);
		dpm_context_destroy(ctx);
		return POLICY_RESULT_FAIL;
	}

	dpm_context_release_restriction_policy(ctx, handle);
	dpm_context_destroy(ctx);

	snprintf(input, PATH_MAX, "Location Allow status : %d", location_status);
	display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *)"desc"), input);
	return POLICY_RESULT_SUCCESS;
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
