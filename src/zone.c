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
 
#include "dpm-toolkit.h"
#include <dpm/zone.h>

int create_zone_handler(struct xtk_policy* self)
{
        dpm_zone_policy_h policy;
	dpm_context_h context;
	char* wizappid;
	int ret;

	handler_display_input_popup("Zone name", self);
	wizappid = (char*)xmlGetProp(self->model, (xmlChar*) "wizappid");

	if (wizappid == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "wizappid parameter not found");
		return POLICY_RESULT_FAIL;
	}

        context = dpm_context_create();
        if (context == NULL) {
                dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
                return POLICY_RESULT_FAIL;
        }

        policy = dpm_context_acquire_zone_policy(context);
        if (policy == NULL) {
                dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get zone policy interface");
                dpm_context_destroy(context);
                return POLICY_RESULT_FAIL;
        }

	ret = dpm_zone_create(policy, self->entry_input, wizappid);

        dpm_context_release_zone_policy(context, policy);
        dpm_context_destroy(context);

	return (ret == DPM_ERROR_NONE) ? POLICY_RESULT_SUCCESS : POLICY_RESULT_FAIL;
}

int destroy_zone_handler(struct xtk_policy* self)
{
        dpm_zone_policy_h policy;
	dpm_context_h context;
	int ret;

	handler_display_input_popup("Zone name", self);

        context = dpm_context_create();
        if (context == NULL) {
                dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to create client context");
                return POLICY_RESULT_FAIL;
        }

        policy = dpm_context_acquire_zone_policy(context);
        if (policy == NULL) {
                dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to get zone policy interface");
                dpm_context_destroy(context);
                return POLICY_RESULT_FAIL;
        }

	ret = dpm_zone_destroy(policy, self->entry_input);

        dpm_context_release_zone_policy(context, policy);
        dpm_context_destroy(context);

	return (ret == DPM_ERROR_NONE) ? POLICY_RESULT_SUCCESS : POLICY_RESULT_FAIL;
}

int get_zone_list_handler(struct xtk_policy* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "get_zone_list_handler");
	return POLICY_RESULT_SUCCESS;
}

int get_zone_state_handler(struct xtk_policy* self)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "get_zone_state_handler");
	return POLICY_RESULT_SUCCESS;
}

xtk_policy_t xtk_zone_policy[] = {
	{
		.id = "CREATE_ZONE",
		.handler = create_zone_handler
	},
	{
		.id = "DESTROY_ZONE",
		.handler = destroy_zone_handler
	},
	{
		.id = "GET_ZONE_LIST",
		.handler = get_zone_list_handler
	},
	{
		.id = "GET_ZONE_STATE",
		.handler = get_zone_state_handler
	}
};

xtk_policy_group_t zone_policy_group = {
	.id = "ZONE"
};

void __CONSTRUCTOR__ xtk_zone_policy_constructor()
{
	int ret = 0;

	dlog_print(DLOG_ERROR, LOG_TAG, "zone policy constructor");

	int nr = ARRAY_SIZE(xtk_zone_policy);
	ret = xtk_init_policy(&zone_policy_group, xtk_zone_policy, nr);
	if (ret < 0) {
		dlog_print(DLOG_ERROR, LOG_TAG, "zone policy initialization fail");
	}
}
