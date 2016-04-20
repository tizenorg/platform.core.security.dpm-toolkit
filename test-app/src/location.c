#include "dpm-toolkit.h"
#include <dpm/restriction.h>

int set_location_state_handler(struct dpm_toolkit_entity *self)
{
	dpm_context_h ctx = NULL;
	dpm_restriction_policy_h handle = NULL;
	dpm_toolkit_entity_t *selected_policy = self;
	char *status = NULL;
	int enable = -1;

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

	/* [TBD] : need to add "enable" option to xmlFile */
	status = (char *)xmlGetProp(selected_policy->model, (xmlChar *)"enable");
	if (status == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to get test option");
		dpm_context_destroy(ctx);
		return POLICY_RESULT_FAIL;
	}

	if (!strcmp(status, "ON"))
		enable = 1;
	else
		enable = 0;

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

	location_status = dpm_restriction_get_location_state(handle);
	if (location_status < 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to get location status");
		dpm_context_release_restriction_policy(ctx, handle);
		dpm_context_destroy(ctx);
		return POLICY_RESULT_FAIL;
	}

	dpm_context_release_restriction_policy(ctx, handle);
	dpm_context_destroy(ctx);
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
