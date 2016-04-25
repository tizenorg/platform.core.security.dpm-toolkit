#include "dpm-toolkit.h"
#include <dpm/restriction.h>

/* dpm integration test */
// ON_SET_CHANGES_RESTRICTION
int on_clipboard_restriction_handler(struct dpm_toolkit_entity* self)
{
	dpm_toolkit_entity_t* selected_policy = self;

	dpm_client_h handle;
	bool enable = false;

	handle = dpm_create_client();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_set_clipboard_restriction(handle, true) != 0) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_FAIL;
	}

	enable = dpm_is_clipboard_restricted(handle);
	if (enable == true) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_SUCCESS;
	}

	dpm_destroy_client(handle);
	return POLICY_RESULT_FAIL;
}
int off_clipboard_restriction_handler(struct dpm_toolkit_entity* self)
{
	dpm_toolkit_entity_t* selected_policy = self;

	dpm_client_h handle;
	bool enable = false;

	handle = dpm_create_client();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_set_clipboard_restriction(handle, false) != 0) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_FAIL;
	}

	enable = dpm_is_clipboard_restricted(handle);
	if (enable == false) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_SUCCESS;
	}

	dpm_destroy_client(handle);
	return POLICY_RESULT_FAIL;

}
int on_clipboard_share_restriction_handler(struct dpm_toolkit_entity* self)
{
	dpm_toolkit_entity_t* selected_policy = self;

	dpm_client_h handle;
	bool enable = false;

	handle = dpm_create_client();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_set_clipboard_restriction(handle, true) != 0) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_FAIL;
	}

	enable = dpm_is_clipboard_restricted(handle);
	if (enable == true) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_SUCCESS;
	}

	dpm_destroy_client(handle);
	return POLICY_RESULT_FAIL;
}
int off_clipboard_share_restriction_handler(struct dpm_toolkit_entity* self)
{
	dpm_toolkit_entity_t* selected_policy = self;

	dpm_client_h handle;
	bool enable = false;

	handle = dpm_create_client();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_set_clipboard_share_restriction(handle, false) != 0) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_FAIL;
	}

	enable = dpm_is_clipboard_share_restricted(handle);
	if (enable == false) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_SUCCESS;
	}

	dpm_destroy_client(handle);
	return POLICY_RESULT_FAIL;
}


int on_settings_changes_restriction_handler(struct dpm_toolkit_entity* self)
{
	dpm_toolkit_entity_t* selected_policy = self;

	dpm_client_h handle;
	bool enable = false;

	handle = dpm_create_client();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_set_clipboard_restriction(handle, true) != 0) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_FAIL;
	}

	enable = dpm_is_clipboard_restricted(handle);
	if (enable == true) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_SUCCESS;
	}

	dpm_destroy_client(handle);
	return POLICY_RESULT_FAIL;
}

int off_settings_changes_restriction_handler(struct dpm_toolkit_entity* self)
{
	dpm_toolkit_entity_t* selected_policy = self;

	dpm_client_h handle;
	bool enable = false;

	handle = dpm_create_client();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_set_clipboard_restriction(handle, false) != 0) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_FAIL;
	}

	enable = dpm_is_clipboard_restricted(handle);
	if (enable == false) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_SUCCESS;
	}

	dpm_destroy_client(handle);
	return POLICY_RESULT_FAIL;
}

int on_usb_debugging_restriction_handler(struct dpm_toolkit_entity* self)
{
	dpm_toolkit_entity_t* selected_policy = self;

	dpm_client_h handle;
	bool enable = false;

	handle = dpm_create_client();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_set_usb_debugging_restriction(handle, true) != 0) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_FAIL;
	}

	enable = dpm_is_usb_debugging_restricted(handle);
	if (enable == true) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_SUCCESS;
	}

	dpm_destroy_client(handle);
	return POLICY_RESULT_FAIL;
}
int off_usb_debugging_restriction_handler(struct dpm_toolkit_entity* self)
{
	dpm_toolkit_entity_t* selected_policy = self;

	dpm_client_h handle;
	bool enable = false;

	handle = dpm_create_client();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_set_usb_debugging_restriction(handle, false) != 0) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_FAIL;
	}

	enable = dpm_is_usb_debugging_restricted(handle);
	if (enable == false) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_SUCCESS;
	}

	dpm_destroy_client(handle);
	return POLICY_RESULT_FAIL;
}

int on_usb_mass_storage_restriction_handler(struct dpm_toolkit_entity* self)
{
	dpm_toolkit_entity_t* selected_policy = self;

	dpm_client_h handle;
	bool enable = false;

	handle = dpm_create_client();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_set_usb_mass_storage_restriction(handle, true) != 0) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_FAIL;
	}

	enable = dpm_is_usb_mass_storage_restricted(handle);
	if (enable == true) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_SUCCESS;
	}

	dpm_destroy_client(handle);
	return POLICY_RESULT_FAIL;
}
int off_usb_mass_storage_restriction_handler(struct dpm_toolkit_entity* self)
{
	dpm_toolkit_entity_t* selected_policy = self;

	dpm_client_h handle;
	bool enable = false;

	handle = dpm_create_client();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_set_usb_mass_storage_restriction(handle, false) != 0) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_FAIL;
	}

	enable = dpm_is_usb_mass_storage_restricted(handle);
	if (enable == false) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_SUCCESS;
	}

	dpm_destroy_client(handle);
	return POLICY_RESULT_FAIL;
}

int on_factory_reset_restriction_handler(struct dpm_toolkit_entity* self)
{
	dpm_toolkit_entity_t* selected_policy = self;

	dpm_client_h handle;
	bool enable = false;

	handle = dpm_create_client();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_set_factory_reset_restriction(handle, true) != 0) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_FAIL;
	}

	enable = dpm_is_factory_reset_restricted(handle);
	if (enable == true) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_SUCCESS;
	}

	dpm_destroy_client(handle);
	return POLICY_RESULT_FAIL;
}
int off_factory_reset_restriction_handler(struct dpm_toolkit_entity* self)
{
	dpm_toolkit_entity_t* selected_policy = self;

	dpm_client_h handle;
	bool enable = false;

	handle = dpm_create_client();
	if (handle == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Failed to create client handle");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_set_factory_reset_restriction(handle, false) != 0) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_FAIL;
	}

	enable = dpm_is_factory_reset_restricted(handle);
	if (enable == false) {
		dpm_destroy_client(handle);
		return POLICY_RESULT_SUCCESS;
	}

	dpm_destroy_client(handle);
	return POLICY_RESULT_FAIL;
}


dpm_toolkit_entity_t dpm_toolkit_restriction_policy[] = {
	{
	 .id = "ON_CLIPBOARD_RESTRICTION",
	 .handler = on_clipboard_restriction_handler
	},
	{
	 .id = "OFF_CLIPBOARD_RESTRICTION",
	 .handler = off_clipboard_restriction_handler
	},
	{
	 .id = "ON_CLIPBOARD_SHARE_RESTRICTION",
	 .handler = on_clipboard_share_restriction_handler
	},
	{
	 .id = "OFF_CLIPBOARD_SHARE_RESTRICTION",
	 .handler = off_clipboard_share_restriction_handler
	},
	{
	 .id = "ON_SETTINGS_CHANGES_RESTRICTION",
	 .handler = on_settings_changes_restriction_handler
	},
	{
	 .id = "OFF_SETTINGS_CHANGES_RESTRICTION",
	 .handler = off_settings_changes_restriction_handler
	},
	{
	 .id = "ON_USB_DEBUGGING_RESTRICTION",
	 .handler = on_usb_debugging_restriction_handler
	},
	{
	 .id = "OFF_USB_DEBUGGING_RESTRICTION",
	 .handler = off_usb_debugging_restriction_handler
	},
	{
	 .id = "ON_USB_MASS_STORAGE_RESTRICTION",
	 .handler = on_usb_mass_storage_restriction_handler
	},
	{
	 .id = "OFF_USB_MASS_STORAGE_RESTRICTION",
	 .handler = off_usb_mass_storage_restriction_handler
	},
	{
	 .id = "ON_FACTORY_RESET_RESTRICTION",
	 .handler = on_factory_reset_restriction_handler
	},
	{
	 .id = "OFF_FACTORY_RESET_RESTRICTION",
	 .handler = off_factory_reset_restriction_handler
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

