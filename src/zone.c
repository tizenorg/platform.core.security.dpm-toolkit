#include "dpm-toolkit.h"
#include <dpm/zone.h>

int create_zone_handler(struct dpm_toolkit_entity* self)
{
	dpm_client_h handle;
	char* wizappid;
	int ret;

	handle = dpm_create_client();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}

	handler_display_input_popup("Zone name", self);
	wizappid = (char*)xmlGetProp(self->model, (xmlChar*) "wizappid");

	if (wizappid == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "wizappid parameter not found");
		return POLICY_RESULT_FAIL;
	}

	ret = dpm_create_zone(handle, self->entry_input, wizappid);

	dpm_destroy_client(handle);

	return (ret == DPM_ERROR_NONE) ? POLICY_RESULT_SUCCESS : POLICY_RESULT_FAIL;
}

int destroy_zone_handler(struct dpm_toolkit_entity* self)
{
	dpm_client_h handle;
	int ret;

	handle = dpm_create_client();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}

	handler_display_input_popup("Zone name", self);

	ret = dpm_remove_zone(handle, self->entry_input);

	dpm_destroy_client(handle);

	return (ret == DPM_ERROR_NONE) ? POLICY_RESULT_SUCCESS : POLICY_RESULT_FAIL;
}

int get_zone_list_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "get_zone_list_handler");
	return POLICY_RESULT_SUCCESS;
}

int get_zone_state_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "get_zone_state_handler");
	return POLICY_RESULT_SUCCESS;
}

dpm_toolkit_entity_t dpm_toolkit_zone_policy[] = {
	{
	 .id = "CREATE_ZONE",
	 .handler = create_zone_handler
	},
	{
	 .id = "DESTROY_ZONE",
	 .handler = destroy_zone_handler
	},
	{
	 .id = "GET_ZONE_LIST",
	 .handler = get_zone_list_handler
	},
	{
	 .id = "GET_ZONE_STATE",
	 .handler = get_zone_state_handler
	}
};

dpm_toolkit_policy_group_t zone_policy_group = {
	.id = "ZONE"
};

void __CONSTRUCTOR__ dpm_toolkit_zone_policy_constructor()
{
	int ret = 0;
	dlog_print(DLOG_ERROR, LOG_TAG, "zone policy constructor");

	int policyNum = sizeof(dpm_toolkit_zone_policy) / sizeof(dpm_toolkit_zone_policy[0]);
	ret = dpm_toolkit_init_policy(&(zone_policy_group.policies), dpm_toolkit_zone_policy, policyNum);
	if (ret < 0)
		dlog_print(DLOG_ERROR, LOG_TAG, "zone policy initialization fail");
	ret = dpm_toolkit_add_policy_group(&global_dpm_policy_group_list, &zone_policy_group);
	if (ret < 0)
		dlog_print(DLOG_ERROR, LOG_TAG, "add zone group fail");

}
