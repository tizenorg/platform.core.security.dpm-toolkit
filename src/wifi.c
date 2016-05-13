#include <dpm/wifi.h>

#include "dpm-toolkit.h"

static char radio_text[][MAX_RADIO_TEXT_LEN] = {"Allow", "Disallow"};

int wifi_set_profile_change_restriction_handler(struct dpm_toolkit_entity* self)
{
	dpm_wifi_policy_h policy;
	dpm_context_h context;
	int ret;

	dlog_print(DLOG_DEBUG, LOG_TAG, __func__);

	handler_display_radio_popup("Restriction", self, radio_text, sizeof(radio_text) / sizeof(char) / MAX_RADIO_TEXT_LEN);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_wifi_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get wifi policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	ret = dpm_wifi_set_profile_change_restriction(policy, self->radio_index);

	dpm_context_release_wifi_policy(context, policy);
	dpm_context_destroy(context);

	return (ret == DPM_ERROR_NONE) ? POLICY_RESULT_SUCCESS : POLICY_RESULT_FAIL;
}

int wifi_is_profile_change_restricted_handler(struct dpm_toolkit_entity* self)
{	dpm_wifi_policy_h policy;
	dpm_context_h context;
	int state, ret;

	dlog_print(DLOG_DEBUG, LOG_TAG, __func__);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_wifi_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get wifi policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	ret = dpm_wifi_is_profile_change_restricted(policy, &state);

	dpm_context_release_wifi_policy(context, policy);
	dpm_context_destroy(context);

	if (ret == DPM_ERROR_NONE) {
        	display_result_popup("Restriction state", state? "Disallowed":"Allowed");

		return POLICY_RESULT_NONE;
	}

	return POLICY_RESULT_FAIL;
}

int wifi_set_network_access_restriction_handler(struct dpm_toolkit_entity* self)
{
	dpm_wifi_policy_h policy;
	dpm_context_h context;
	int ret;

	dlog_print(DLOG_DEBUG, LOG_TAG, __func__);

	handler_display_radio_popup("Restriction", self, radio_text, sizeof(radio_text) / sizeof(char) / MAX_RADIO_TEXT_LEN);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_wifi_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get wifi policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	ret = dpm_wifi_set_network_access_restriction(policy, self->radio_index);

	dpm_context_release_wifi_policy(context, policy);
	dpm_context_destroy(context);

	return (ret == DPM_ERROR_NONE) ? POLICY_RESULT_SUCCESS : POLICY_RESULT_FAIL;
}

int wifi_is_network_access_restricted_handler(struct dpm_toolkit_entity* self)
{
	dpm_wifi_policy_h policy;
	dpm_context_h context;
	int state, ret;

	dlog_print(DLOG_DEBUG, LOG_TAG, __func__);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_wifi_policy(context);

	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get wifi policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	ret = dpm_wifi_is_network_access_restricted(policy, &state);

	dpm_context_release_wifi_policy(context, policy);
	dpm_context_destroy(context);

	if (ret == DPM_ERROR_NONE) {
        	display_result_popup("Restriction state", state? "Disallowed":"Allowed");

		return POLICY_RESULT_NONE;
	}

	return POLICY_RESULT_FAIL;
}

int wifi_add_ssid_to_blocklist_handler(struct dpm_toolkit_entity* self)
{
	dpm_wifi_policy_h policy;
	dpm_context_h context;
	int ret;

	dlog_print(DLOG_DEBUG, LOG_TAG, __func__);

	handler_display_input_popup("SSID", self);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_wifi_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get wifi policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	ret = dpm_wifi_add_ssid_to_blocklist(policy, self->entry_input);

	dpm_context_release_wifi_policy(context, policy);
	dpm_context_destroy(context);

	return (ret == DPM_ERROR_NONE) ? POLICY_RESULT_SUCCESS : POLICY_RESULT_FAIL;
}

int wifi_remove_ssid_from_blocklist_handler(struct dpm_toolkit_entity* self)
{
	dpm_wifi_policy_h policy;
	dpm_context_h context;
	int ret;

	dlog_print(DLOG_DEBUG, LOG_TAG, __func__);

	handler_display_input_popup("SSID", self);

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	policy = dpm_context_acquire_wifi_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get wifi policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	ret = dpm_wifi_remove_ssid_from_blocklist(policy, self->entry_input);

	dpm_context_release_wifi_policy(context, policy);
	dpm_context_destroy(context);

	return (ret == DPM_ERROR_NONE) ? POLICY_RESULT_SUCCESS : POLICY_RESULT_FAIL;
}

dpm_toolkit_entity_t dpm_toolkit_wifi_policy[] = {
	{
	 .id = "WIFI_SET_PROFILE_CHANGE_RESTRICTION",
	 .handler = wifi_set_profile_change_restriction_handler
	},
	{
	 .id = "WIFI_IS_PROFILE_CHANGE_RESTRICTED",
	 .handler = wifi_is_profile_change_restricted_handler
	},
	{
	 .id = "WIFI_SET_NETWORK_ACCESS_RESTRICTION",
	 .handler = wifi_set_network_access_restriction_handler
	},
	{
	 .id = "WIFI_IS_NETWORK_ACCESS_RESTRICTED",
	 .handler = wifi_is_network_access_restricted_handler
	},
	{
	 .id = "WIFI_ADD_SSID_TO_BLOCKLIST",
	 .handler = wifi_add_ssid_to_blocklist_handler
	},
	{
	 .id = "WIFI_REMOVE_SSID_FROM_BLOCKLIST",
	 .handler = wifi_remove_ssid_from_blocklist_handler
	},
};

dpm_toolkit_policy_group_t wifi_policy_group = {
	.id = "WIFI"
};

void __CONSTRUCTOR__ dpm_toolkit_wifi_policy_constructor()
{
	int ret = 0;
	dlog_print(DLOG_ERROR, LOG_TAG, "wifi policy constructor");

	int policyNum = sizeof(dpm_toolkit_wifi_policy) / sizeof(dpm_toolkit_wifi_policy[0]);
	ret = dpm_toolkit_init_policy(&(wifi_policy_group.policies), dpm_toolkit_wifi_policy, policyNum);
	if (ret < 0)
		dlog_print(DLOG_ERROR, LOG_TAG, "wifi policy initialization fail");
	ret = dpm_toolkit_add_policy_group(&global_dpm_policy_group_list, &wifi_policy_group);
	if (ret < 0)
		dlog_print(DLOG_ERROR, LOG_TAG, "add wifi group fail");

}

