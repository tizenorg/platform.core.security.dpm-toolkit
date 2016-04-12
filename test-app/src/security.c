#include "dpm-toolkit.h"

int rock_now_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "rock_now_handler");
	return POLICY_RESULT_SUCCESS;
}

int wipe_data_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "wipe_data_handler");
	return POLICY_RESULT_SUCCESS;
}

int reboot_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "reboot_handler");
	return POLICY_RESULT_SUCCESS;
}

int power_off_device_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "power_off_device_handler");
	return POLICY_RESULT_SUCCESS;
}

dpm_toolkit_entity_t dpm_toolkit_security_policy[] = {
	{
	 .id = "LOCK_NOW",
	 .handler = rock_now_handler
	},
	{
	 .id = "WIPE_DATA",
	 .handler = wipe_data_handler
	},
	{
	 .id = "REBOOT",
	 .handler = reboot_handler
	},
	{
	 .id = "POWER_OFF_DEVICE",
	 .handler = power_off_device_handler
	}
};

dpm_toolkit_policy_group_t security_policy_group = {
	.id = "SECURITY"
};

void __CONSTRUCTOR__ dpm_toolkit_security_policy_constructor()
{
	int ret = 0;
	dlog_print(DLOG_DEBUG, LOG_TAG, "security policy constructor");

	int policyNum = sizeof(dpm_toolkit_security_policy) / sizeof(dpm_toolkit_security_policy[0]);
	ret = dpm_toolkit_init_policy(&(security_policy_group.policies), dpm_toolkit_security_policy, policyNum);
	if (ret < 0)
		dlog_print(DLOG_ERROR, LOG_TAG, "security policy initialization fail");
	ret = dpm_toolkit_add_policy_group(&global_dpm_policy_group_list, &security_policy_group);
	if (ret < 0)
		dlog_print(DLOG_ERROR, LOG_TAG, "add security group fail");

}

