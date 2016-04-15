#ifndef __dpm-toolkit_H__
#define __dpm-toolkit_H__

#include <stdio.h>
#include <glib.h>
#include <libxml/xpath.h>
#include <string.h>
#include <app.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <dlog.h>

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "dpm-toolkit"

#if !defined(PACKAGE)
#define PACKAGE "org.example.dpm-toolkit"
#endif

#define __CONSTRUCTOR__ __attribute__ ((constructor))

#define POLICY_SUCCESS_TXT "SUCCESS"
#define POLICY_FAIL_TXT "FAIL"

#define POLICY_RESULT_SUCCESS 0
#define POLICY_RESULT_FAIL 1

typedef struct appdata {
	Evas_Object* win;
	Evas_Object* conform;
	Evas_Object* nf;
	Evas_Object* list;
	char* edj_path;
} appdata_s;

appdata_s* global_ad;

typedef struct dpm_toolkit_entity{
	char* id;
	int (*handler)(struct dpm_toolkit_entity* self);
	xmlNodePtr model;
	char* entry_input;
}dpm_toolkit_entity_t;

typedef struct dpm_toolkit_policy_group {
	char* id;
	GList* policies;
}dpm_toolkit_policy_group_t;

GList* global_dpm_policy_group_list;
GList* effective_dpm_policy_group_list;

int dpm_toolkit_add_policy_group(GList** Grouplist , dpm_toolkit_policy_group_t* group);
int dpm_toolkit_init_policy(GList** policies, dpm_toolkit_entity_t* policy, int policyNum);

#endif /* __dpm-toolkit_H__ */
