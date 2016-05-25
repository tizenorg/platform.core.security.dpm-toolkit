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

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

#include "dpm-toolkit.h"

GList* xtk_policy_group_list;
static xmlDoc* dpmDoc;

int xtk_open_entry_popup(xtk_policy_t* policy, const char* msg, char** entry)
{
	int ret;
	char *title = policy_get_title(policy);
	char *init = policy_get_default_value(policy);

	ret = open_entry_popup(title, msg ? msg : init, entry);
	free(title);
	if (init)
		free(init);
	return ret;
}

int xtk_open_state_change_select_popup(xtk_policy_t* policy, int* index)
{
	int ret;
	char *title = policy_get_title(policy);
	char* text[] = {
		"Allow State Change",
		"Disallow State Change"
	};

	ret = open_radio_popup(title, text, ARRAY_SIZE(text), index);
	*index = *index ? 0 : 1;
	free(title);
	return ret;
}

int xtk_open_restriction_mode_select_popup(xtk_policy_t* policy, int* index)
{
	int ret;
	char *title = policy_get_title(policy);
	char* text[] = {
		"Enable Restriction Mode",
		"Disable Restriction Mode"
	};

	ret = open_radio_popup(title, text, ARRAY_SIZE(text), index);
	*index = *index ? 0 : 1;
	free(title);
	return ret;
}

xmlNodePtr evaluate_xml_node(xmlDoc* dpmDoc, char* policy_group, char* policy_id)
{
	char* xpath = NULL;
	size_t xpath_size;
	xmlXPathContext* context = NULL;
	xmlXPathObject* result = NULL;
	xmlNodePtr xNode = NULL;
	xmlNodeSet* nodeset = NULL;

	xpath_size = strlen(policy_group) + strlen(policy_id) + strlen("//policy-group[@id='%s']/policy[@id='%s']") + 1;
	xpath = (char*)malloc(xpath_size);

	if (xpath == NULL) {
		/* malloc fail */
		return NULL;
	}

	snprintf(xpath, xpath_size, "//policy-group[@id='%s']/policy[@id='%s']", policy_group, policy_id);
	dlog_print(DLOG_DEBUG, LOG_TAG, "xPath: %s \n", xpath);

	context = xmlXPathNewContext(dpmDoc);
	if (context == NULL) {
		/* error */
		dlog_print(DLOG_ERROR, LOG_TAG, "error make context");
		free(xpath);
		return NULL;
	}

	result = xmlXPathEvalExpression((xmlChar*) xpath, context);
	xmlXPathFreeContext(context);
	if (result == NULL) {
		/* error */
		dlog_print(DLOG_ERROR, LOG_TAG, "error make result");
		free(xpath);
		return NULL;
	}

	if (xmlXPathNodeSetIsEmpty(result->nodesetval)) {
		xmlXPathFreeObject(result);
		/* No result */
		dlog_print(DLOG_ERROR, LOG_TAG, "error nodesetval");
		free(xpath);
		return NULL;
	}

	nodeset = result->nodesetval;
	xNode = xmlXPathNodeSetItem(nodeset, 0);
	free(xpath);
	xmlXPathFreeObject(result);

	return xNode;
}

int xtk_init_policy(xtk_policy_group_t* group, xtk_policy_t* policy, int nr)
{
	int i;

	if (policy == NULL) {
		return -1;
	}

	for (i = 0; i < nr; i++) {
		group->policies = g_list_append(group->policies, &policy[i]);
	}
	xtk_policy_group_list = g_list_append(xtk_policy_group_list, group);

	return 0;
}

char* get_now_zone(void)
{
    struct passwd pwd, *result;
    int bufsize;

    bufsize = sysconf(_SC_GETPW_R_SIZE_MAX);
    if (bufsize == -1) {
        bufsize = 16384;
	}

    char *buf = malloc(bufsize * sizeof(char));
	if (buf == NULL) {
		return NULL;
	}

    getpwuid_r(getuid(), &pwd, buf, bufsize, &result);
    if (result == NULL) {
        free(buf);
        return NULL;
    }

    free(buf);

    return strdup(result->pw_name);
}

void xtk_free_policy_list(void)
{
	xmlFreeDoc(dpmDoc);

	GList* policy_group_list = NULL;
	foreach_policy_group(policy_group_list) {
		xtk_policy_group_t* policy_group = glist_to_policy_group(policy_group_list);
		if (policy_group->policies) {
			g_list_free(policy_group->policies);
		}
	}

	g_list_free(xtk_policy_group_list);

	dlog_print(DLOG_DEBUG, LOG_TAG, "All policy group removed");
}

int xtk_rebuild_policy_group(const char *xmlFilePath)
{
	GList* policy_group_list = NULL;

	dpmDoc = xmlParseFile(xmlFilePath);
	if (dpmDoc == NULL) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to load policy specification");
		return -1;
	}

	foreach_policy_group(policy_group_list) {
		xtk_policy_group_t* group = glist_to_policy_group(policy_group_list);

		GList* policy_list = NULL;
		foreach_policy(policy_list, group) {
			xtk_policy_t* policy = glist_to_policy(policy_list);

			xmlNodePtr model = evaluate_xml_node(dpmDoc, group->id, policy->id);
			if (!model) {
				policy_list = g_list_remove(group->policies, policy);
				continue;
			}

			policy->model = model;
		}
	}

	dlog_print(DLOG_DEBUG, LOG_TAG, "Policy group is successfully reconstructed");

	return 0;
}

int main(int argc, char* argv[])
{
	/*
	if (argc > 1) {
		return xtk_cli_main(argc, argv);
	}
	*/

	return xtk_gui_main(argc, argv);
}
