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

#ifndef __DPM_TOOLKIT_H__
#define __DPM_TOOLKIT_H__

#include <stdio.h>
#include <stdbool.h>
#include <glib.h>
#include <string.h>

#include <app.h>
#include <dlog.h>
#include <libxml/xpath.h>
#include <system_settings.h>
#include <efl_extension.h>

#include "dpm-toolkit-popup.h"

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "dpm-toolkit"

#if !defined(PACKAGE)
#define PACKAGE "org.tizen.dpm-toolkit"
#endif

#define __CONSTRUCTOR__			__attribute__ ((constructor))

#define ARRAY_SIZE(p)			(sizeof(p) / sizeof(p[0]))

#define POLICY_RESULT_SUCCESS	0
#define POLICY_RESULT_FAIL		1
#define POLICY_RESULT_NONE		100

#define MAX_RADIO_TEXT_LEN		35

#define POLICY_XML_FILE_PATH "/usr/apps/org.tizen.dpm-toolkit/test.xml"

#define foreach_policy_group(_g_)						\
	for (_g_ = g_list_first(xtk_policy_group_list);		\
		(_g_ && _g_->data);								\
		(_g_ = g_list_next(_g_)))

#define foreach_policy(_e_, _g_)						\
	for (_e_ = g_list_first(_g_->policies);				\
		(_e_ && _e_->data);								\
		(_e_ = g_list_next(_e_)))

typedef struct xtk_policy {
	char* id;
	int (*handler)(struct xtk_policy* self);
	xmlNodePtr model;
	char* entry_input;
	int radio_index;
} xtk_policy_t;

typedef struct xtk_policy_group {
	char* id;
	GList* policies;
} xtk_policy_group_t;

typedef struct appdata {
	Evas_Object* nf;
} appdata_s;

appdata_s* global_ad;

typedef struct popup_data {
	Evas_Object* popup;
	Evas_Object* entry;
	xtk_policy_t* policy;
	int popup_flag;
	int radio_index;
} popup_data_t;

popup_data_t global_popup;

static inline xtk_policy_group_t* glist_to_policy_group(GList *list)
{
	return (xtk_policy_group_t *)(list->data);
}

static inline xtk_policy_t* glist_to_policy(GList *list)
{
	return (xtk_policy_t *)(list->data);
}

static inline char* policy_get_title(xtk_policy_t* entity)
{
	return (char *)xmlGetProp((xmlNodePtr)entity->model, (xmlChar *)"desc");
}

static inline char* policy_get_default_value(xtk_policy_t* entity)
{
 	return (char *)xmlGetProp(entity->model, (xmlChar *) "default");
}

static inline int is_invalid_policy(xtk_policy_t* entity)
{
	return (xmlStrcmp(xmlGetProp(entity->model, (xmlChar*) "status"), (xmlChar*) "ON") != 0);
}

int xtk_init_policy(xtk_policy_group_t* group, xtk_policy_t* policy, int nr);
void xtk_free_policy_list(void);
int xtk_rebuild_policy_group(const char *xmlFilePath);

#define BUTTON_CANCEL	1
#define BUTTON_OK		2
#define BUTTON_SET		4

extern char* state_change_radio_options[2];
extern char* restriction_mode_radio_options[2];

#define GET_STATE_CHANGE_OPTIONS \
	state_change_radio_options, ARRAY_SIZE(state_change_radio_options)

#define GET_RESTRICTION_MODE_OPTIONS \
	restriction_mode_radio_options, ARRAY_SIZE(restriction_mode_radio_options)

int xtk_open_radio_popup(xtk_policy_t* policy, char* radio_text[], int nr, int* index);

extern char* state_change_radio_results[2];
extern char* restriction_mode_radio_results[2];

#define GET_STATE_CHANGE_MESSAGE(status) \
	status ? state_change_radio_results[0] : state_change_radio_results[1]

#define GET_RESTRICTION_MODE_MESSAGE(status) \
	status ? restriction_mode_radio_results[0] : restriction_mode_radio_results[1]

void xtk_open_message_popup(xtk_policy_t* policy, const char* popup_message);
int xtk_open_entry_popup(xtk_policy_t* policy, const char* msg, char** entry);

void open_message_popup(const char* title, const char* popup_message);
int open_entry_popup(const char* title, const char* msg, char** value);
int open_radio_popup(const char* title, char* radio_text[], int nr, int* index);

char* get_now_zone(void);

int xtk_gui_main(int argc, char* argv[]);
int xtk_cli_main(int argc, char* argv[]);

extern GList* xtk_policy_group_list;

#endif /* __DPM_TOOLKIT_H__ */
