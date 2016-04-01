#include "dpm-toolkit.h"

int set_allow_wifi_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "set_allow_wifi_handler");
	return 0;
}

int get_allow_wifi_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "get_allow_wifi_handler");
	return 0;
}

int get_ssid_handler(struct dpm_toolkit_entity* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "get_ssid_handler");
	return 0;
}

dpm_toolkit_entity_t dpm_toolkit_wifi_policy[] = {
	{
	 .id = "SET_ALLOW_WIFI",
	 .handler = set_allow_wifi_handler
	},
	{
	 .id = "GET_ALLOW_WIFI",
	 .handler = get_allow_wifi_handler
	},
	{
	 .id = "GET_SSID",
	 .handler = get_ssid_handler
	}
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

