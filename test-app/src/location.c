#include "dpm-toolkit.h"
#include <dpm/misc.h>

int allow_location_state_change_handler(struct dpm_toolkit_entity *self)
{
	dpm_context_h ctx = NULL;
	dpm_location_h handle = NULL;

	ctx = dpm_context_create();

	handle = dpm_context_acquire_location_policy(ctx);
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		dpm_context_destroy(ctx);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_location_allow_state_change(handle, true) != 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to allow location state change");
		dpm_context_release_location_policy(handle);
		dpm_context_destroy(ctx);
		return POLICY_RESULT_FAIL;
	}

	dpm_context_release_location_policy(handle);
	dpm_context_destroy(ctx);
	return POLICY_RESULT_SUCCESS;
}

int disallow_location_state_change_handler(struct dpm_toolkit_entity *self)
{
	dpm_context_h ctx = NULL;
	dpm_location_h handle = NULL;

	ctx = dpm_context_create();

	handle = dpm_context_acquire_location_policy(ctx);
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		dpm_context_destroy(ctx);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_location_allow_state_change(handle, false) != 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to disallow location state change");
		dpm_context_release_location_policy(handle);
		dpm_context_destroy(ctx);
		return POLICY_RESULT_FAIL;
	}

	dpm_context_release_location_policy(handle);
	dpm_context_destroy(ctx);
	return POLICY_RESULT_SUCCESS;
}

dpm_toolkit_entity_t dpm_toolkit_location_policy[] = {
	{
		.id = "ALLOW_LOCATION_STATE_CHANGE",
		.handler = allow_location_state_change_handler
	},
	{
		.id = "ALLOW_LOCATION_STATE_CHANGE",
		.handler = disallow_location_state_change_handler
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
