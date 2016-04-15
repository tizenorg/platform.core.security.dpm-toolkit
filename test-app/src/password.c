#include "dpm-toolkit.h"
#include <dpm/password.h>

/* dpm integration test */

int password_set_password_quality_handler(struct dpm_toolkit_entity* self)
{
	dpm_client_h handle;
	dpm_toolkit_entity_t* selected_policy = self;
	char* param_username = NULL;
	char* param_quality = NULL;

	handle = dpm_create_client();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}

	param_username = (char*)xmlGetProp(selected_policy->model, (xmlChar*)"username");
	param_quality = (char*)xmlGetProp(selected_policy->model, (xmlChar*)"quality");
	if (param_username == NULL || param_quality == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "not founded parameter");
		return POLICY_RESULT_FAIL;
	}
	dlog_print(DLOG_DEBUG, LOG_TAG, "username: %s quality: %s", param_username, param_quality);
	if (dpm_set_password_quality(handle, param_username, (int)param_quality) == 0) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_SUCCESS;
	}

	dpm_destroy_client(handle);
	return POLICY_RESULT_FAIL;
}

int set_enforce_password_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "set_enforce_password_handler");

	dpm_toolkit_entity_t* selected_policy = self;
	char* param = NULL;

	param = (char*)xmlGetProp(selected_policy->model, (xmlChar*) "status");
	if (param == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "not founded :(");
		return -1;
	}
	dlog_print(DLOG_DEBUG, LOG_TAG, "status : %s ", param);
	dlog_print(DLOG_DEBUG, LOG_TAG, "entry : %s ", selected_policy->entry_input);
	xmlFree(param);
	return POLICY_RESULT_SUCCESS;
}

int get_password_policy_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "get_password_policy_handler");
	return POLICY_RESULT_SUCCESS;
}

int set_password_recovery(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "set_password_recovery");
	dlog_print(DLOG_DEBUG, LOG_TAG, "entry: %s ", self->entry_input);
	return POLICY_RESULT_SUCCESS;
}

dpm_toolkit_entity_t dpm_toolkit_password_policy[] = {
	{
	 .id = "SET_ENFORCE_PASSWORD",
	 .handler = set_enforce_password_handler
	},
	{
	 .id = "GET_PASSWORD_POLICY",
	 .handler = get_password_policy_handler
	},
	{
	 .id = "SET_PASSWORD_RECOVERY",
	 .handler = set_password_recovery
	},
	{
	 .id = "SET_PASSWORD_QUALITY",
	 .handler = password_set_password_quality_handler
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
