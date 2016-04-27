#include "dpm-toolkit.h"
#include <dpm/restriction.h>

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

	dpm_restriction_get_location_state(handle, location_status);
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

dpm_toolkit_entity_t dpm_toolkit_location_policy[] = {
	{
		.id = "SET_LOCATION_STATE",
		.handler = set_location_state_handler
	},
	{
		.id = "GET_LOCATION_STATE",
		.handler = get_location_state_handler
	}
};

dpm_toolkit_policy_group_t location_policy_group = {
	.id = "LOCATION"
};

void __CONSTRUCTOR__ dpm_toolkit_location_policy_constructor()
{
	int ret = 0;
	dlog_print(DLOG_ERROR, LOG_TAG, "location policy constructor");

	int policyNum = sizeof(dpm_toolkit_location_policy) / sizeof(dpm_toolkit_location_policy[0]);

	ret = dpm_toolkit_init_policy(&(location_policy_group.policies), dpm_toolkit_location_policy, policyNum);
	if (ret < 0)
		dlog_print(DLOG_ERROR, LOG_TAG, "location policy initialization fail");

	ret = dpm_toolkit_add_policy_group(&global_dpm_policy_group_list, &location_policy_group);
	if (ret < 0)
		dlog_print(DLOG_ERROR, LOG_TAG, "add location group fail");
}
