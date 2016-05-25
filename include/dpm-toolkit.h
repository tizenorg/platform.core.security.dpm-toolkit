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
#define POLICY_RESULT_FAIL		-1
#define POLICY_RESULT_NONE		100

#define POLICY_XML_FILE_PATH "/usr/apps/org.tizen.dpm-toolkit/test.xml"

typedef struct xtk_policy {
	const char* id;
	const char* description;
	const char* param;
	int (*handler)(struct xtk_policy* self);
	xmlNodePtr model;
} xtk_policy_t;

typedef struct xtk_policy_group {
	const char* id;
	const char* title;
	const char* description;
	GList* policies;
} xtk_policy_group_t;

typedef struct xtk_context {
	int (*message_popup)(const char* title, const char* message);
	int (*confirm_popup)(const char* title, const char* message);
	int (*entry_popup)(const char* title, const char* message, char** value);
	int (*radio_popup)(const char* title, const char* text[], int nr, int* index);
} xtk_context_t;

#define xtk_foreach_policy_group(_g_)					\
	for (_g_ = g_list_first(xtk_policy_group_list);		\
		(_g_ && _g_->data);								\
		(_g_ = g_list_next(_g_)))

#define xtk_foreach_policy(_e_, _g_)					\
	for (_e_ = g_list_first(_g_->policies);				\
		(_e_ && _e_->data);								\
		(_e_ = g_list_next(_e_)))

static inline xtk_policy_group_t* glist_to_policy_group(GList *list)
{
	return (xtk_policy_group_t *)(list->data);
}

static inline xtk_policy_t* glist_to_policy(GList *list)
{
	return (xtk_policy_t *)(list->data);
}

static inline const char* policy_get_title(xtk_policy_t* entity)
{
	return entity->description;
}

static inline const char* policy_get_default_value(xtk_policy_t* entity)
{
 	return entity->param;
}

xtk_context_t* xtk_context_get_current(void);
void xtk_context_set_current(xtk_context_t* context);

int xtk_init_policy(xtk_policy_group_t* group, xtk_policy_t* policy, int nr);
void xtk_free_policy_list(void);
int xtk_rebuild_policy_group(const char *xmlFilePath);

#define XTK_EVENT_CANCEL	1
#define XTK_EVENT_OK		2

#define STATE_CHANGE_OPTIONS \
	state_change_options, ARRAY_SIZE(state_change_options)

#define RESTRICTION_MODE_OPTIONS \
	restriction_mode_options, ARRAY_SIZE(restriction_mode_options)

#define STATE_CHANGE_MESSAGE(status)					\
({														\
	char buffer[64] = "State Change ";					\
	strncat(buffer, state_change_results[!status], 16);		\
})

#define RESTRICTION_MODE_MESSAGE(status)			 	\
({														\
	char buffer[64] = "Restriction Mode ";				\
	strncat(buffer, restriction_mode_results[!status], 16);	\
})

int xtk_open_message_popup(xtk_policy_t* policy, const char* message);
int xtk_open_confirm_popup(xtk_policy_t* policy, const char *message);
int xtk_open_entry_popup(xtk_policy_t* policy, const char* message, char** entry);
int xtk_open_radio_popup(xtk_policy_t* policy, const char* text[], int nr, int* index);

char* get_now_zone(void);

int xtk_gui_main(int argc, char* argv[]);
int xtk_cli_main(int argc, char* argv[]);

extern const char* state_change_options[2];
extern const char* restriction_mode_options[2];

extern const char state_change_results[2][16];
extern const char restriction_mode_results[2][16];

extern GList* xtk_policy_group_list;

#endif /* __DPM_TOOLKIT_H__ */
