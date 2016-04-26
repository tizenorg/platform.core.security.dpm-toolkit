#include <stdbool.h>

#include "dpm-toolkit.h"
#include <dpm/bluetooth.h>

int add_device_to_blacklist_handler(struct dpm_toolkit_entity *self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "add_device_from_blacklist_handler");

	char *mac_address = NULL;
	handler_display_input_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), self);
	mac_address = self->entry_input;
	if (mac_address == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "can not get mac_address");
	return POLICY_RESULT_FAIL;
	}

	dpm_context_h context;
	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	dpm_bluetooth_policy_h policy = dpm_context_acquire_bluetooth_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get bluetooth policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_bluetooth_add_device_to_blacklist(policy, mac_address) < 0) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to add MAC Address to blacklist");
		dpm_context_release_bluetooth_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	dpm_context_release_bluetooth_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_SUCCESS;
}

int remove_device_from_blacklist_handler(struct dpm_toolkit_entity *self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "remove_device_from_blacklist_handler");

	char *mac_address = NULL;
	handler_display_input_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), self);
	mac_address = self->entry_input;
	if (mac_address == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "can not get mac_address");
		return POLICY_RESULT_FAIL;
	}

	dpm_context_h context;
	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	dpm_bluetooth_policy_h policy = dpm_context_acquire_bluetooth_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get bluetooth policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_bluetooth_remove_device_from_blacklist(policy, mac_address) < 0) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to remove MAC address to blacklist");
		dpm_context_release_bluetooth_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	dpm_context_release_bluetooth_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_SUCCESS;
}

int set_device_restriction_handler(struct dpm_toolkit_entity *self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "set_device_restriction_handler");

	dpm_context_h context;
	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	dpm_bluetooth_policy_h policy = dpm_context_acquire_bluetooth_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get bluetooth policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	char radio_text_quality[][MAX_RADIO_TEXT_LEN] = {"ALLOW", "DISALLOW"};
	int radio_num = sizeof(radio_text_quality) / sizeof(radio_text_quality[0]);
	handler_display_radio_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), self, radio_text_quality, radio_num);

	int ret = -1;
	if (self->radio_index == 0) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "set device restriction (true)");
		ret = dpm_bluetooth_set_device_restriction(policy, true);
	} else if (self->radio_index == 1) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "set device restriction (false)");
		ret = dpm_bluetooth_set_device_restriction(policy, false);
	} else {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get radio index");
		return POLICY_RESULT_FAIL;
	}
	if (ret < 0) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to set device restriction");
		dpm_context_release_bluetooth_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	dpm_context_release_bluetooth_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_SUCCESS;
}

int is_device_restricted_handler(struct dpm_toolkit_entity *self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "is_device_restricted_handler");

	dpm_context_h context;
	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	dpm_bluetooth_policy_h policy = dpm_context_acquire_bluetooth_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get bluetooth policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	int allowed = false;
	if (dpm_bluetooth_is_device_restricted(policy, &allowed) != DPM_ERROR_NONE) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to check device restriction");
		dpm_context_release_bluetooth_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}
	dlog_print(DLOG_DEBUG, LOG_TAG, "allow state. (allow: %d)", allowed);

	if (allowed = true)
		display_result_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), "ALLOW");
	else
		display_result_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), "DISALLOW");

	dpm_context_release_bluetooth_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_NONE;
}

int add_uuid_to_blacklist_handler(struct dpm_toolkit_entity *self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "add_uuid_to_blacklist_handler");

	char *uuid = NULL;
	handler_display_input_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), self);
	uuid = self->entry_input;
	if (uuid == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "can not get uuid");
		return POLICY_RESULT_FAIL;
	}

	dpm_context_h context;
	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	dpm_bluetooth_policy_h policy = dpm_context_acquire_bluetooth_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get bluetooth policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_bluetooth_add_uuid_to_blacklist(policy, uuid) < 0) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to add UUID to blacklist");
		dpm_context_release_bluetooth_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	dpm_context_release_bluetooth_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_SUCCESS;
}

int remove_uuid_from_blacklist_handler(struct dpm_toolkit_entity *self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "remove_uuid_from_blacklist_handler");

	char *uuid = NULL;
	handler_display_input_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), self);
	uuid = self->entry_input;
	if (uuid == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "can not get uuid");
		return POLICY_RESULT_FAIL;
	}

	dpm_context_h context;
	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	dpm_bluetooth_policy_h policy = dpm_context_acquire_bluetooth_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get bluetooth policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	if (dpm_bluetooth_remove_uuid_from_blacklist(policy, uuid) < 0) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to remove UUID to blacklist");
		dpm_context_release_bluetooth_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	dpm_context_release_bluetooth_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_SUCCESS;
}

int set_uuid_restriction_handler(struct dpm_toolkit_entity *self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "set_uuid_restriction_handler");

	dpm_context_h context;
	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	dpm_bluetooth_policy_h policy = dpm_context_acquire_bluetooth_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get bluetooth policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	char radio_text_quality[][MAX_RADIO_TEXT_LEN] = {"ALLOW", "DISALLOW"};
	int radio_num = sizeof(radio_text_quality) / sizeof(radio_text_quality[0]);
	handler_display_radio_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), self, radio_text_quality, radio_num);

	int ret = -1;
	if (self->radio_index == 0) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "set uuid restriction (true)");
		ret = dpm_bluetooth_set_uuid_restriction(policy, true);
	} else if (self->radio_index == 1) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "set uuid restriction (false)");
		ret = dpm_bluetooth_set_uuid_restriction(policy, false);
	} else {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get radio index");
		return POLICY_RESULT_FAIL;
	}
	if (ret < 0) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to set uuid restriction");
		dpm_context_release_bluetooth_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	return POLICY_RESULT_SUCCESS;
}

int is_uuid_restricted_handler(struct dpm_toolkit_entity *self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "is_uuid_restricted_handler");

	dpm_context_h context;
	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
		return POLICY_RESULT_FAIL;
	}

	dpm_bluetooth_policy_h policy = dpm_context_acquire_bluetooth_policy(context);
	if (policy == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get bluetooth policy interface");
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}

	int allowed = false;
	if (dpm_bluetooth_is_uuid_restricted(policy, &allowed) != DPM_ERROR_NONE) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to check uuid restriction");
		dpm_context_release_bluetooth_policy(context, policy);
		dpm_context_destroy(context);
		return POLICY_RESULT_FAIL;
	}
	dlog_print(DLOG_DEBUG, LOG_TAG, "allow state. (allow: %d)", allowed);

	if (allowed = true)
		display_result_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), "ALLOW");
	else
		display_result_popup((char *)xmlGetProp(self->model, (xmlChar *) "desc"), "DISALLOW");

	dpm_context_release_bluetooth_policy(context, policy);
	dpm_context_destroy(context);

	return POLICY_RESULT_NONE;
}


dpm_toolkit_entity_t dpm_toolkit_bluetooth_policy[] = {
	{
		.id = "ADD_DEVICE_TO_BLACKLIST",
		.handler = add_device_to_blacklist_handler
	},
	{
		.id = "REMOVE_DEVICE_FROM_BLACKLIST",
		.handler = remove_device_from_blacklist_handler
	},
	{
		.id = "SET_DEVICE_RESTRICTION",
		.handler = set_device_restriction_handler
	},
	{
		.id = "IS_DEVICE_RESTRICTED",
		.handler = is_device_restricted_handler
	},
	{
		.id = "ADD_UUID_TO_BLACKLIST",
		.handler = add_uuid_to_blacklist_handler
	},
	{
		.id = "REMOVE_UUID_FROM_BLACKLIST",
		.handler = remove_uuid_from_blacklist_handler
	},
	{
		.id = "SET_UUID_RESTRICTION",
		.handler = set_uuid_restriction_handler
	},
	{
		.id = "IS_UUID_RESTRICTED",
		.handler = is_uuid_restricted_handler
	}
};

dpm_toolkit_policy_group_t bluetooth_policy_group = {
	.id = "BLUETOOTH"
};

void __CONSTRUCTOR__ dpm_toolkit_bluetooth_policy_constructor()
{
	int ret = 0;
	dlog_print(DLOG_DEBUG, LOG_TAG, "bluetooth policy constructor");

	int policyNum = sizeof(dpm_toolkit_bluetooth_policy) / sizeof(dpm_toolkit_bluetooth_policy[0]);
	ret = dpm_toolkit_init_policy(&(bluetooth_policy_group.policies), dpm_toolkit_bluetooth_policy, policyNum);

	if (ret < 0)
		dlog_print(DLOG_ERROR, LOG_TAG, "bluetooth policy initialization fail");

	ret = dpm_toolkit_add_policy_group(&global_dpm_policy_group_list, &bluetooth_policy_group);

	if (ret < 0)
		dlog_print(DLOG_ERROR, LOG_TAG, "add bluetooth group fail");
}
