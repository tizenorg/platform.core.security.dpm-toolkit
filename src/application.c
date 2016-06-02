/*
 *  Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License
 */

#include <dpm/application.h>

#include "dpm-toolkit.h"

int set_installation_mode_handler(struct xtk_policy* self)
{
	int state, index;
	dpm_context_h context;
	const char *text[] = {
		"Disable Package Installation Mode",
		"Enable Package Installation Mode"
	};

	if (xtk_open_radio_popup(self, text, ARRAY_SIZE(text), &index) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Selection canceled");
		return POLICY_RESULT_NONE;
	}

	context = dpm_context_create();
	if (context == NULL) {
		xtk_open_message_popup(self, "Failed to create device policy manager");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_application_set_installation_mode(context, index) != DPM_ERROR_NONE) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to enforce policy");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_application_get_installation_mode(context, &state) != DPM_ERROR_NONE) {
		char buf[128];
		snprintf(buf, 128, "Err: %d", state);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, buf);
		return POLICY_RESULT_FAIL;
	}

	if (index != state) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Policy was not setted properly");
		return POLICY_RESULT_FAIL;
	}

	dpm_context_destroy(context);
	xtk_open_message_popup(self, state ? "Installation Mode Enabled"
									   : "Installation Mode Disabled");

	return POLICY_RESULT_SUCCESS;
}

int get_installation_mode_handler(struct xtk_policy* self)
{
	int state;
	dpm_context_h context;

	context = dpm_context_create();
	if (context == NULL) {
		xtk_open_message_popup(self, "Failed to create device policy manager");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_application_get_installation_mode(context, &state) != DPM_ERROR_NONE) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to query installation mode");
		return POLICY_RESULT_FAIL;
	}

	dpm_context_destroy(context);
	xtk_open_message_popup(self, state ? "Installation Mode Enabled"
									   : "Installation Mode Disabled");

	return POLICY_RESULT_SUCCESS;
}

int set_uninstallation_mode_handler(struct xtk_policy* self)
{
	int index, state;
	dpm_context_h context;
	const char *text[] = {
		"Disable Package Uninstallation Mode",
		"Enable Package Uninstallation Mode"
	};

	if (xtk_open_radio_popup(self, text, ARRAY_SIZE(text), &index) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Selection canceled");
		return POLICY_RESULT_NONE;
	}

	context = dpm_context_create();
	if (context == NULL) {
		xtk_open_message_popup(self, "Failed to create device policy manager");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_application_set_uninstallation_mode(context, index) != DPM_ERROR_NONE) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to enforce policy");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_application_get_uninstallation_mode(context, &state) != DPM_ERROR_NONE) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to query uninstallation mode");
		return POLICY_RESULT_FAIL;
	}

	if (index != state) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Policy was not setted properly");
		return POLICY_RESULT_FAIL;
	}

	xtk_open_message_popup(self, state ? "Uninstallation Mode Enabled"
									   : "Uninstallation Mode Disabled");
	dpm_context_destroy(context);

	return POLICY_RESULT_SUCCESS;
}

int get_uninstallation_mode_handler(struct xtk_policy* self)
{
	int state;
	dpm_context_h context;

	context = dpm_context_create();
	if (context == NULL) {
		xtk_open_message_popup(self, "Failed to create device policy manager");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_application_get_uninstallation_mode(context, &state) != DPM_ERROR_NONE) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to query uninstallation mode");
		return POLICY_RESULT_FAIL;
	}

	xtk_open_message_popup(self, state ? "Uninstallation Mode Enabled"
									   : "Uninstallation Mode Disabled");
	dpm_context_destroy(context);

	return POLICY_RESULT_SUCCESS;
}

int set_package_state_handler(struct xtk_policy* self)
{
	char *pkgid;
	int index, state;
	dpm_context_h context;
	const char* text[] = {
		"Allow package installation"
		"Disallow package installation"
	};

	if (xtk_open_entry_popup(self, "", "Enter package id", &pkgid) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
		return POLICY_RESULT_NONE;
	};


	if (xtk_open_radio_popup(self, text, ARRAY_SIZE(text), &index) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Selection canceled");
		free(pkgid);
		return POLICY_RESULT_NONE;
	}

	context = dpm_context_create();
	if (context == NULL) {
		free(pkgid);
		xtk_open_message_popup(self, "Failed to create device policy manager");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_application_set_package_state(context, pkgid, index) != DPM_ERROR_NONE) {
		free(pkgid);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to enforce policy");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_application_get_package_state(context, pkgid, &state) != DPM_ERROR_NONE) {
		free(pkgid);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to query uninstallation mode");
		return POLICY_RESULT_FAIL;
	}

	free(pkgid);

	if (index != state) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Policy was not setted properly");
		return POLICY_RESULT_FAIL;
	}

	xtk_open_message_popup(self, state ? "Package was enabled"
									   : "Package was disabled");

	dpm_context_destroy(context);

	return POLICY_RESULT_SUCCESS;
}

int get_package_state_handler(struct xtk_policy* self)
{
	int state;
	char *pkgid;
	dpm_context_h context;

	if (xtk_open_entry_popup(self, "", "Enter package id", &pkgid) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
		return POLICY_RESULT_NONE;
	};

	context = dpm_context_create();
	if (context == NULL) {
		xtk_open_message_popup(self, "Failed to create device policy manager");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_application_get_package_state(context, pkgid, &state) != DPM_ERROR_NONE) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to query uninstallation mode");
		return POLICY_RESULT_FAIL;
	}

	xtk_open_message_popup(self, state ? "Package was enabled"
									   : "Package was disabled");
	dpm_context_destroy(context);

	return POLICY_RESULT_SUCCESS;
}

int add_package_to_blacklist_handler(struct xtk_policy* self)
{
	int state;
	char *pkgid;
	dpm_context_h context;

	if (xtk_open_entry_popup(self, "", "Enter package id", &pkgid) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
		return POLICY_RESULT_NONE;
	};

	context = dpm_context_create();
	if (context == NULL) {
		xtk_open_message_popup(self, "Failed to create device policy manager");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_application_add_package_to_blacklist(context, pkgid) != DPM_ERROR_NONE) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to enforce policy");
		return POLICY_RESULT_FAIL;
	}

    if (dpm_application_check_package_is_blacklisted(context, pkgid, &state) != DPM_ERROR_NONE) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to query package blacklist");
		return POLICY_RESULT_FAIL;
	}

	if (!state) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Adding package to blacklist was failed");
		return POLICY_RESULT_FAIL;
	}

	xtk_open_message_popup(self, "Package is added to blacklist");
	dpm_context_destroy(context);

	return POLICY_RESULT_SUCCESS;
}

int remove_package_from_blacklist_handler(struct xtk_policy* self)
{
	int state;
	char *pkgid;
	dpm_context_h context;

	if (xtk_open_entry_popup(self, "", "Enter package id", &pkgid) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
		return POLICY_RESULT_NONE;
	};

	context = dpm_context_create();
	if (context == NULL) {
		free(pkgid);
		xtk_open_message_popup(self, "Failed to create device policy manager");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_application_remove_package_from_blacklist(context, pkgid) != DPM_ERROR_NONE) {
		free(pkgid);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to enforce policy");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_application_check_package_is_blacklisted(context, pkgid, &state) != DPM_ERROR_NONE) {
		free(pkgid);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to query package blacklist");
		return POLICY_RESULT_FAIL;
	}

	free(pkgid);

	if (state) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Removing package to blacklist was failed");
		return POLICY_RESULT_FAIL;
	}

	xtk_open_message_popup(self, "Package is removed from blacklist");
	dpm_context_destroy(context);

	return POLICY_RESULT_SUCCESS;
}

int check_package_is_blacklisted_handler(struct xtk_policy* self)
{
	int state;
	char *pkgid;
	dpm_context_h context;

	if (xtk_open_entry_popup(self, "", "Enter package id", &pkgid) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
		return POLICY_RESULT_NONE;
	};

	context = dpm_context_create();
	if (context == NULL) {
		free(pkgid);
		xtk_open_message_popup(self, "Failed to create device policy manager");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_application_check_package_is_blacklisted(context, pkgid, &state) != DPM_ERROR_NONE) {
		free(pkgid);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to query package blacklist");
		return POLICY_RESULT_FAIL;
	}

	free(pkgid);

	xtk_open_message_popup(self, state ? "Package was blacklisted"
									   : "Package was not blacklisted");
	dpm_context_destroy(context);

	return POLICY_RESULT_SUCCESS;
}

int add_privilege_to_blacklist_handler(struct xtk_policy* self)
{
	int state, index;
	char *privilege;
	dpm_context_h context;
	const char* text[] = {
		"Wrt Packakage Privilege",
		"Core Package Privilege"
	};

	if (xtk_open_radio_popup(self, text, ARRAY_SIZE(text), &index) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Selection canceled");
		return POLICY_RESULT_NONE;
	}

	if (xtk_open_entry_popup(self, "http://tizen.org/privilege/internet",
								   "Enter package privilege name",
								   &privilege) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
		return POLICY_RESULT_NONE;
	};

	context = dpm_context_create();
	if (context == NULL) {
		free(privilege);
		xtk_open_message_popup(self, "Failed to create device policy manager");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_application_add_privilege_to_blacklist(context, index, privilege) != DPM_ERROR_NONE) {
		free(privilege);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to enforce policy");
		return POLICY_RESULT_FAIL;
	}

    if (dpm_application_check_privilege_is_blacklisted(context, index, privilege, &state) != DPM_ERROR_NONE) {
		free(privilege);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to query privilege blacklist");
		return POLICY_RESULT_FAIL;
	}

	if (!state) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Adding privilege to blacklist was failed");
		free(privilege);
		return POLICY_RESULT_FAIL;
	}

	dpm_context_destroy(context);

	xtk_open_message_popup(self, "The privilege is disabled");
	return POLICY_RESULT_SUCCESS;
}

int remove_privilege_from_blacklist_handler(struct xtk_policy* self)
{
	int state, index;
	char *privilege;
	dpm_context_h context;
	const char* text[] = {
		"Wrt Packakage Privilege",
		"Core Package Privilege"
	};

	if (xtk_open_radio_popup(self, text, ARRAY_SIZE(text), &index) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Selection canceled");
		return POLICY_RESULT_NONE;
	}

	if (xtk_open_entry_popup(self, "http://tizen.org/privilege/internet",
								   "Enter package privilege name",
								   &privilege) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
		return POLICY_RESULT_NONE;
	};

	context = dpm_context_create();
	if (context == NULL) {
		free(privilege);
		xtk_open_message_popup(self, "Failed to create device policy manager");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_application_remove_privilege_from_blacklist(context, index, privilege) != DPM_ERROR_NONE) {
		free(privilege);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to enforce policy");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_application_check_privilege_is_blacklisted(context, index, privilege, &state) != DPM_ERROR_NONE) {
		free(privilege);
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to query privilege blacklist");
		return POLICY_RESULT_FAIL;
	}

	free(privilege);

	if (state) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Removing privilege from blacklist was failed");
		return POLICY_RESULT_FAIL;
	}

	xtk_open_message_popup(self, "Privilege is enabled");
	dpm_context_destroy(context);

	return POLICY_RESULT_SUCCESS;
}

int check_privilege_is_blacklisted_handler(struct xtk_policy* self)
{
	int state, index;
	char *privilege;
	dpm_context_h context;
	const char* text[] = {
		"Wrt Packakage Privilege",
		"Core Package Privilege"
	};

	if (xtk_open_radio_popup(self, text, ARRAY_SIZE(text), &index) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Selection canceled");
		return POLICY_RESULT_NONE;
	}

	if (xtk_open_entry_popup(self, "http://tizen.org/privilege/internet",
								   "Enter package privilege name",
								   &privilege) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
		return POLICY_RESULT_NONE;
	};

	context = dpm_context_create();
	if (context == NULL) {
		xtk_open_message_popup(self, "Failed to create device policy manager");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_application_check_privilege_is_blacklisted(context, index, privilege, &state) != DPM_ERROR_NONE) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to query privilege blacklist");
		return POLICY_RESULT_FAIL;
	}

	xtk_open_message_popup(self, state ? "Privilege is disabled"
									   : "Privilege is enabled");

	dpm_context_destroy(context);

	return POLICY_RESULT_SUCCESS;
}

xtk_policy_t xtk_application_policy[] = {
	{
		.id = "SET_INSTALL_MODE",
		.handler = set_installation_mode_handler
	},
	{
		.id = "GET_INSTALL_MODE",
		.handler = get_installation_mode_handler
	},
	{
		.id = "SET_UNINSTALL_MODE",
		.handler = set_uninstallation_mode_handler
	},
	{
		.id = "GET_UNINSTALL_MODE",
		.handler = get_uninstallation_mode_handler
	},
	{
		.id = "SET_PACKAGE_STATE",
		.handler = set_package_state_handler
	},
	{
		.id = "GET_PACKAGE_STATE",
		.handler = get_package_state_handler
	},
	{
		.id = "ADD_PACKAGE_TO_BLACKLIST",
		.handler = add_package_to_blacklist_handler
	},
	{
		.id = "REMOVE_PACKAGE_FROM_BLACKLIST",
		.handler = remove_package_from_blacklist_handler
	},
	{
		.id = "CHECK_PACKAGE_IS_BLACKLISTED",
		.handler = check_package_is_blacklisted_handler
	},
	{
		.id = "ADD_PRIVILEGE_TO_BLACKLIST",
		.handler = add_privilege_to_blacklist_handler
	},
	{
		.id = "REMOVE_PRIVILEGE_FROM_BLACKLIST",
		.handler = remove_privilege_from_blacklist_handler
	},
	{
		.id = "CHECK_PRIVILEGE_IS_BLACKLISTED",
		.handler = check_privilege_is_blacklisted_handler
	}
};

xtk_policy_group_t xtk_application_policy_group = {
	.id = "APPLICATION"
};

void __CONSTRUCTOR__ xtk_application_policy_constructor()
{
	int ret = 0;

	dlog_print(DLOG_DEBUG, LOG_TAG, "application policy constructor");

	int nr = ARRAY_SIZE(xtk_application_policy);
	ret = xtk_init_policy(&xtk_application_policy_group, xtk_application_policy, nr);
	if (ret < 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "application policy initialization failed");
	}
}
