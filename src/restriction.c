#include "dpm-toolkit.h"
#include <dpm/restriction.h>

/* dpm integration test */
// ON_SET_CHANGES_RESTRICTION
int set_clipboard_state_handler(struct dpm_toolkit_entity* self)
{

	dpm_context_h context;
    dpm_restriction_policy_h policy;
	int ret;
	int enable = false;
	int set_value = false;

	dpm_toolkit_entity_t* selected_policy = self;
	char radio_text_quality[][MAX_RADIO_TEXT_LEN] = {"ON", "OFF"};
	int radio_num = sizeof(radio_text_quality) / sizeof(radio_text_quality[0]);

	handler_display_radio_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), selected_policy, radio_text_quality, radio_num);
	switch (selected_policy->radio_index) {
	case 0:
		set_value = true;
		break;
	case 1:
		set_value = false;
		break;
	}

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed in dpm_context_create()");
		return POLICY_RESULT_FAIL;
	}

    policy = dpm_context_acquire_restriction_policy(context);
    if (policy == NULL) {
    	dlog_print(DLOG_DEBUG, LOG_TAG, "Failed in dpm_context_acquire_restriction_policy()");
        dpm_context_destroy(context);
        return POLICY_RESULT_FAIL;
    }

	ret = POLICY_RESULT_SUCCESS;
	if (dpm_restriction_set_clipboard_state(policy, set_value) != 0) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed in dpm_restriction_set_clipboard_state()");
		ret = POLICY_RESULT_FAIL;
		goto out;
	}

	if (dpm_restriction_get_clipboard_state(policy, &enable) < 0) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed in dpm_restriction_get_clipboard_state()");
		ret = POLICY_RESULT_FAIL;
		goto out;
	}

	if (set_value == true && enable != true) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Set : true, Get : not true");
		ret = POLICY_RESULT_FAIL;
		goto out;
	} else if (set_value == false && enable != false) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Set : false, Get : not false");
		ret = POLICY_RESULT_FAIL;
		goto out;
	} else {
		if(set_value == true) display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), "ON");
		else display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), "OFF");
	}

out:
    dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	if(ret == POLICY_RESULT_FAIL) return ret;
	else if (ret == POLICY_RESULT_SUCCESS) return POLICY_RESULT_NONE;
}

int get_clipboard_state_handler(struct dpm_toolkit_entity* self)
{

	dpm_context_h context;
    dpm_restriction_policy_h policy;
	int ret;
	bool enable = false;
	bool set_value = false;

	dpm_toolkit_entity_t* selected_policy = self;
	context = dpm_context_create();
	if (context == NULL) {
		printf("Failed to create client context\n");
		return POLICY_RESULT_FAIL;
	}

    policy = dpm_context_acquire_restriction_policy(context);
    if (policy == NULL) {
        printf("Failed to get datashare policy interface\n");
        dpm_context_destroy(context);
        return POLICY_RESULT_FAIL;
    }

    ret = POLICY_RESULT_SUCCESS;
	if (dpm_restriction_get_clipboard_state(policy, &enable) < 0) {
		ret = POLICY_RESULT_FAIL;
		goto out;
	}

	if(enable == true) display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), "ON");
	else if(enable == false) display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), "OFF");
	else ret = POLICY_RESULT_FAIL;

out:
    dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	if(ret == POLICY_RESULT_FAIL) return ret;
	else if (ret == POLICY_RESULT_SUCCESS) return POLICY_RESULT_NONE;
}

int set_settings_changes_restriction_handler(struct dpm_toolkit_entity* self)
{

	dpm_context_h context;
    dpm_restriction_policy_h policy;
	int ret;
	int enable = false;
	int set_value = false;

	dpm_toolkit_entity_t* selected_policy = self;
	char radio_text_quality[][MAX_RADIO_TEXT_LEN] = {"ON", "OFF"};
	int radio_num = sizeof(radio_text_quality) / sizeof(radio_text_quality[0]);

	handler_display_radio_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), selected_policy, radio_text_quality, radio_num);
	switch (selected_policy->radio_index) {
	case 0:
		set_value = true;
		break;
	case 1:
		set_value = false;
		break;
	}

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed in dpm_context_create()");
		return POLICY_RESULT_FAIL;
	}

    policy = dpm_context_acquire_restriction_policy(context);
    if (policy == NULL) {
    	dlog_print(DLOG_DEBUG, LOG_TAG, "Failed in dpm_context_acquire_restriction_policy()");
        dpm_context_destroy(context);
        return POLICY_RESULT_FAIL;
    }

	ret = POLICY_RESULT_SUCCESS;
	if (dpm_restriction_set_settings_changes_state(policy, set_value) != 0) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed in dpm_restriction_set_settings_changes_state()");
		ret = POLICY_RESULT_FAIL;
		goto out;
	}

	if (dpm_restriction_get_settings_changes_state(policy, &enable) < 0) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed in dpm_restriction_get_settings_changes_state()");
		ret = POLICY_RESULT_FAIL;
		goto out;
	}

	if (set_value == true && enable != true) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Set : true, Get : not true");
		ret = POLICY_RESULT_FAIL;
		goto out;
	} else if (set_value == false && enable != false) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Set : false, Get : not false");
		ret = POLICY_RESULT_FAIL;
		goto out;
	} else {
		if(set_value == true) display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), "ON");
		else display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), "OFF");
	}

out:
    dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	if(ret == POLICY_RESULT_FAIL) return ret;
	else if (ret == POLICY_RESULT_SUCCESS) return POLICY_RESULT_NONE;
}

int get_settings_changes_restriction_handler(struct dpm_toolkit_entity* self)
{

	dpm_context_h context;
    dpm_restriction_policy_h policy;
	int ret;
	int enable = false;
	int set_value = false;

	dpm_toolkit_entity_t* selected_policy = self;
	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed in dpm_context_create()");
		return POLICY_RESULT_FAIL;
	}

    policy = dpm_context_acquire_restriction_policy(context);
    if (policy == NULL) {
        dlog_print(DLOG_DEBUG, LOG_TAG, "Failed in dpm_context_acquire_restriction_policy()");
        dpm_context_destroy(context);
        return POLICY_RESULT_FAIL;
    }

    ret = POLICY_RESULT_SUCCESS;
	if (dpm_restriction_get_settings_changes_state(policy, &enable) < 0) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed in dpm_restriction_get_settings_changes_state()");
		ret = POLICY_RESULT_FAIL;
		goto out;
	}

	if(enable == true) display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), "ON");
	else if(enable == false) display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), "OFF");
	else ret = POLICY_RESULT_FAIL;

out:
    dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	if(ret == POLICY_RESULT_FAIL) return ret;
	else if (ret == POLICY_RESULT_SUCCESS) return POLICY_RESULT_NONE;
}

int set_usb_debugging_state_handler(struct dpm_toolkit_entity* self)
{

	dpm_context_h context;
    dpm_restriction_policy_h policy;
	int ret;
	int enable = false;
	int set_value = false;

	dpm_toolkit_entity_t* selected_policy = self;
	char radio_text_quality[][MAX_RADIO_TEXT_LEN] = {"ON", "OFF"};
	int radio_num = sizeof(radio_text_quality) / sizeof(radio_text_quality[0]);

	handler_display_radio_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), selected_policy, radio_text_quality, radio_num);
	switch (selected_policy->radio_index) {
	case 0:
		set_value = true;
		break;
	case 1:
		set_value = false;
		break;
	}

	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed in dpm_context_create()");
		return POLICY_RESULT_FAIL;
	}

    policy = dpm_context_acquire_restriction_policy(context);
    if (policy == NULL) {
    	dlog_print(DLOG_DEBUG, LOG_TAG, "Failed in dpm_context_acquire_restriction_policy()");
        dpm_context_destroy(context);
        return POLICY_RESULT_FAIL;
    }

	ret = POLICY_RESULT_SUCCESS;
	if (dpm_restriction_set_usb_debugging_state(policy, set_value) != 0) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed in dpm_restriction_set_usb_debugging_state()");
		ret = POLICY_RESULT_FAIL;
		goto out;
	}

	if (dpm_restriction_get_usb_debugging_state(policy, &enable) < 0) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed in dpm_restriction_get_usb_debugging_state()");
		ret = POLICY_RESULT_FAIL;
		goto out;
	}

	if (set_value == true && enable != true) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Set : true, Get : not true");
		ret = POLICY_RESULT_FAIL;
		goto out;
	} else if (set_value == false && enable != false) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Set : false, Get : not false");
		ret = POLICY_RESULT_FAIL;
		goto out;
	} else {
		if(set_value == true) display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), "ON");
		else display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), "OFF");
	}

out:
    dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	if(ret == POLICY_RESULT_FAIL) return ret;
	else if (ret == POLICY_RESULT_SUCCESS) return POLICY_RESULT_NONE;
}

int get_usb_debugging_state_handler(struct dpm_toolkit_entity* self)
{

	dpm_context_h context;
    dpm_restriction_policy_h policy;
	int ret;
	int enable = false;
	int set_value = false;

	dpm_toolkit_entity_t* selected_policy = self;
	context = dpm_context_create();
	if (context == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed in dpm_context_create()");
		return POLICY_RESULT_FAIL;
	}

    policy = dpm_context_acquire_restriction_policy(context);
    if (policy == NULL) {
        dlog_print(DLOG_DEBUG, LOG_TAG, "Failed in dpm_context_acquire_restriction_policy()");
        dpm_context_destroy(context);
        return POLICY_RESULT_FAIL;
    }

    ret = POLICY_RESULT_SUCCESS;
	if (dpm_restriction_get_usb_debugging_state(policy, &enable) < 0) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed in dpm_restriction_get_usb_debugging_state()");
		ret = POLICY_RESULT_FAIL;
		goto out;
	}

	if(enable == true) display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), "ON");
	else if(enable == false) display_result_popup((char *)xmlGetProp(selected_policy->model, (xmlChar *) "desc"), "OFF");
	else ret = POLICY_RESULT_FAIL;

out:
    dpm_context_release_restriction_policy(context, policy);
	dpm_context_destroy(context);

	if(ret == POLICY_RESULT_FAIL) return ret;
	else if (ret == POLICY_RESULT_SUCCESS) return POLICY_RESULT_NONE;
}






dpm_toolkit_entity_t dpm_toolkit_restriction_policy[] = {
	{
	 .id = "SET_CLIPBOARD_RESTRICTION",
	 .handler = set_clipboard_state_handler
	},
	{
	 .id = "GET_CLIPBOARD_RESTRICTION",
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
	 .id = "SET_USB_DEBUGGING_RESTRICTION",
	 .handler = set_usb_debugging_state_handler
	},
	{
	 .id = "GET_USB_DEBUGGING_RESTRICTION",
	 .handler = get_usb_debugging_state_handler
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

