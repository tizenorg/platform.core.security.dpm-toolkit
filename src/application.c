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

int install_package_handler(struct xtk_policy* self)
{
	char* pkgpath;
	dpm_context_h context;

	if (xtk_open_entry_popup(self, "/opt/data/dpm/sampleapp.tpk",
								   "Enter package path",
								   &pkgpath) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
		return POLICY_RESULT_NONE;
	};

	context = dpm_context_create();
	if (context == NULL) {
		xtk_open_message_popup(self, "Failed to create device policy manager");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_application_install_package(context, pkgpath) != DPM_ERROR_NONE) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to enforce policy");
		return POLICY_RESULT_FAIL;
	}

	xtk_open_message_popup(self, "Package installed");
	dpm_context_destroy(context);

	return POLICY_RESULT_SUCCESS;
}

int uninstall_package_handler(struct xtk_policy* self)
{
	char* pkgid;
	dpm_context_h context;

	context = dpm_context_create();
	if (context == NULL) {
		xtk_open_message_popup(self, "Failed to create device policy manager");
		return POLICY_RESULT_FAIL;
	}

	if (xtk_open_entry_popup(self, "org.tizen.sampleapp",
								   "Enter package id",
								   &pkgid) == XTK_EVENT_CANCEL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Entry get canceled");
		return POLICY_RESULT_NONE;
	};

	if (dpm_application_uninstall_package(context, pkgid) != DPM_ERROR_NONE) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to enforce policy");
		return POLICY_RESULT_FAIL;
	}

	xtk_open_message_popup(self, "Package uninstalled");
	dpm_context_destroy(context);

	return POLICY_RESULT_SUCCESS;
}

int set_mode_restriction_handler(struct xtk_policy* self)
{
	char* msg;
	int state, index;
	dpm_context_h context;
	const char *text[] = {
		"Disable package installation",
		"Disable package uninstallation"
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

	switch (index) {
	case 0 : index = DPM_PACKAGE_RESTRICTION_MODE_INSTALL; break;
	case 1 : index = DPM_PACKAGE_RESTRICTION_MODE_UNINSTALL; break;
	}

	if (dpm_application_set_mode_restriction(context, index) != DPM_ERROR_NONE) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to enforce policy");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_application_get_mode_restriction(context, &state) != DPM_ERROR_NONE) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to query policy");
		return POLICY_RESULT_FAIL;
	}

	if (index != (state & index)) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Policy was not setted properly");
		return POLICY_RESULT_FAIL;
	}

	dpm_context_destroy(context);
	switch (index) {
	case DPM_PACKAGE_RESTRICTION_MODE_INSTALL:
		msg = "All package installation will not be allowed";
		break;
	case DPM_PACKAGE_RESTRICTION_MODE_UNINSTALL:
		msg = "All package uninstallation will not be allowed";
		break;
	}

	xtk_open_message_popup(self, msg);

	return POLICY_RESULT_SUCCESS;
}

int unset_mode_restriction_handler(struct xtk_policy* self)
{
	char* msg;
	int state, index;
	dpm_context_h context;
	const char *text[] = {
		"Enable package installation",
		"Enable package uninstallation"
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

	switch (index) {
	case 0 : index = DPM_PACKAGE_RESTRICTION_MODE_INSTALL; break;
	case 1 : index = DPM_PACKAGE_RESTRICTION_MODE_UNINSTALL; break;
	}

	if (dpm_application_unset_mode_restriction(context, index) != DPM_ERROR_NONE) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to enforce policy");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_application_get_mode_restriction(context, &state) != DPM_ERROR_NONE) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to query policy");
		return POLICY_RESULT_FAIL;
	}

	if ((state & index) == index) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Policy was not setted properly");
		return POLICY_RESULT_FAIL;
	}

	switch (index) {
	case DPM_PACKAGE_RESTRICTION_MODE_INSTALL:
		msg = "All package installation is disabled";
		break;
	case DPM_PACKAGE_RESTRICTION_MODE_UNINSTALL:
		msg = "All package uninstallation is disabled";
		break;
	}

	xtk_open_message_popup(self, msg);
	dpm_context_destroy(context);

	return POLICY_RESULT_SUCCESS;
}

int get_mode_restriction_handler(struct xtk_policy* self)
{
	int state;
	char msg[128];
	dpm_context_h context;

	context = dpm_context_create();
	if (context == NULL) {
		xtk_open_message_popup(self, "Failed to create device policy manager");
		return POLICY_RESULT_FAIL;
	}

	if (dpm_application_get_mode_restriction(context, &state) != DPM_ERROR_NONE) {
		dpm_context_destroy(context);
		xtk_open_message_popup(self, "Failed to enforce policy");
		return POLICY_RESULT_FAIL;
	}

	dpm_context_destroy(context);
	snprintf(msg, 128, "Package installation is %s, Package uninstallation is %s",
			(state & DPM_PACKAGE_RESTRICTION_MODE_INSTALL) ? "DISABLED" : "ENABLED",
		 	(state & DPM_PACKAGE_RESTRICTION_MODE_UNINSTALL) ? "DISABLED" : "ENABLED");

	xtk_open_message_popup(self, msg);

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
		.id = "INSTALL_PACKAGE",
		.handler = install_package_handler
	},
	{
		.id = "UNINSTALL_PACKAGE",
		.handler = uninstall_package_handler
	},
	{
		.id = "SET_MODE_RESTRICTION",
		.handler = set_mode_restriction_handler
	},
	{
		.id = "UNSET_MODE_RESTRICTION",
		.handler = unset_mode_restriction_handler
	},
	{
		.id = "GET_MODE_RESTRICTION",
		.handler = get_mode_restriction_handler
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
