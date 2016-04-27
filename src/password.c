#include "dpm-toolkit.h"
#include <dpm/password.h>

/* dpm integration test & radio popup test */
int password_set_password_quality_handler(struct dpm_toolkit_entity* self)
{
	dpm_client_h handle;
	dpm_toolkit_entity_t* selected_policy = self;
	char* param_username = NULL;
	dpm_password_quality_e param_quality = -1;
	char radio_text_quality[][MAX_RADIO_TEXT_LEN] = {"UNSPECIFIED", "SIMPLE PASSWORD", "SOMETHING", "NUMERIC", "ALPAHBETIC", "ALPAHNUMERIC"};
	int radio_num = sizeof(radio_text_quality) / sizeof(radio_text_quality[0]);

	handler_display_radio_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), selected_policy, radio_text_quality, radio_num);

	handle = dpm_create_cilent();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}

	param_username = (char*)xmlGetProp(selected_policy->model, (xmlChar*)"username");

	dlog_print(DLOG_DEBUG, LOG_TAG, "username: %s", param_username);
	dlog_print(DLOG_DEBUG, LOG_TAG, "radio index: %d", selected_policy->radio_index);

	switch (selected_policy->radio_index) {
	case 0:
		param_quality = DPM_PASSWORD_QUALITY_UNSPECIFIED;
		break;
	case 1:
		param_quality = DPM_PASSWORD_QUALITY_SIMPLE_PASSWORD;
		break;
	case 2:
		param_quality = DPM_PASSWORD_QUALITY_SOMETHING;
		break;
	case 3:
		param_quality = DPM_PASSWORD_QUALITY_NUMERIC;
		break;
	case 4:
		param_quality = DPM_PASSWORD_QUALITY_ALPHABETIC;
		break;
	case 5:
		param_quality = DPM_PASSWORD_QUALITY_ALPHANUMERIC;
		break;
	}

	dlog_print(DLOG_DEBUG, LOG_TAG, "password quality: %d", param_quality);
	if (param_username == NULL || param_quality < 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "not founded parameter");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_set_password_quality(handle, param_username, param_quality) == 0) {
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

/* input popup test */
int set_password_recovery(struct dpm_toolkit_entity* self)
{
	SLOGD("set_password_recovery");
	dpm_toolkit_entity_t* selected_policy = self;
	char *input;

	handler_display_input_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), selected_policy);

	input = selected_policy->entry_input;
	SLOGD("input data : %s", input);

	display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), input);
	return POLICY_RESULT_NONE;
}

int radio_popup_test(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "radio_popup_test");

	dpm_toolkit_entity_t* selected_policy = self;
	char radio_text[][MAX_RADIO_TEXT_LEN] = {"radio1", "radio2", "radio3", "radio4 -abcdefghij"};
	int radio_num = sizeof(radio_text) / sizeof(radio_text[0]);

	handler_display_radio_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), selected_policy, radio_text, radio_num);

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
	},
	{
	 .id = "RADIO_POPUP_TEST",
	 .handler = radio_popup_test
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
