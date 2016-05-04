#ifndef __DPM_TOOLKIT_H__
#define __DPM_TOOLKIT_H__

#include <stdio.h>
#include <glib.h>
#include <libxml/xpath.h>
#include <string.h>
#include <app.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>
#include "dpm-toolkit-popup.h"

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "dpm-toolkit"

#if !defined(PACKAGE)
#define PACKAGE "org.tizen.dpm-toolkit"
#endif

#define __CONSTRUCTOR__ __attribute__ ((constructor))

#define POLICY_SUCCESS_TXT "SUCCESS"
#define POLICY_FAIL_TXT "FAIL"

#define POLICY_RESULT_SUCCESS 0
#define POLICY_RESULT_FAIL 1
#define POLICY_RESULT_NONE 100

#define MAX_RADIO_TEXT_LEN 35

typedef struct appdata {
	Evas_Object* win;
	Evas_Object* conform;
	Evas_Object* nf;
	Evas_Object* list;
	char* edj_path;
} appdata_s;

appdata_s* global_ad;

typedef struct dpm_toolkit_entity {
	char* id;
	int (*handler)(struct dpm_toolkit_entity* self);
	xmlNodePtr model;
	char* entry_input;
	int radio_index;
} dpm_toolkit_entity_t;

typedef struct dpm_toolkit_policy_group {
	char* id;
	GList* policies;
} dpm_toolkit_policy_group_t;

typedef struct popup_data {
	Evas_Object* popup;
	Evas_Object* entry;
	dpm_toolkit_entity_t* policy;
	int popup_flag;
	int radio_index;
} popup_data_t;

popup_data_t global_popup;

GList* global_dpm_policy_group_list;
GList* effective_dpm_policy_group_list;

int dpm_toolkit_add_policy_group(GList** Grouplist , dpm_toolkit_policy_group_t* group);
int dpm_toolkit_init_policy(GList** policies, dpm_toolkit_entity_t* policy, int policyNum);

void display_result_popup(const char* title, const char* popup_message);
void display_input_popup(const char* title, dpm_toolkit_entity_t* selected_policy);
void display_radio_popup(const char* title, dpm_toolkit_entity_t* selected_policy, char radio_text[][MAX_RADIO_TEXT_LEN], int array_row);

char* get_now_zone(void);

#endif /* __DPM_TOOLKIT_H__ */
