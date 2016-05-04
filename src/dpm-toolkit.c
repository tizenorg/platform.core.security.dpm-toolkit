#include "dpm-toolkit.h"

/*#define POLICY_XML_FILE_PATH "/home/owner/test.xml"*/
#define POLICY_XML_FILE_PATH "/usr/apps/org.tizen.dpm-toolkit/test.xml"
static Elm_Genlist_Item_Class* itc_policy_group, * itc_policy, * itc_policy_entry;
static xmlDoc* dpmDoc = NULL;

xmlNodePtr evaluate_xmlNode(xmlDoc* dpmDoc, char* policy_group, char* policy_id)
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
	dlog_print(DLOG_DEBUG, LOG_TAG, "xPath Length : %d \n", xmlXPathNodeSetGetLength(nodeset));

	xNode = xmlXPathNodeSetItem(nodeset, 0);
	free(xpath);
	xmlXPathFreeObject(result);

	return xNode;

}

int dpm_toolkit_add_policy_group(GList** Grouplist, dpm_toolkit_policy_group_t* group)
{
	int ret = 0;

	if (group == NULL) {
		ret = -1;
		return ret;
	}

	*Grouplist = g_list_append(*Grouplist, group);

	return ret;
}

int dpm_toolkit_init_policy(GList** policies, dpm_toolkit_entity_t* policy, int policyNum)
{
	int ret = 0;
	int i;
	if (policy == NULL) {
		ret = -1;
		return ret;
	}

	for (i = 0; i < policyNum; i++)
		*policies = g_list_append(*policies, &policy[i]);

	return ret;
}

int dpm_toolkit_add_policy(GList** policies, dpm_toolkit_entity_t* policy)
{
	int ret = 0;

	if (policy == NULL) {
		ret = -1;
		return ret;
	}

	*policies = g_list_append(*policies, policy);

	return ret;
}

void dpm_parser_free_policy_list(void)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "## policy list free ## ");

	GList* pg_list = NULL;
	dpm_toolkit_policy_group_t* policy_group = NULL;

	xmlFreeDoc(dpmDoc);

	for (pg_list = g_list_first(effective_dpm_policy_group_list); (pg_list && pg_list->data); pg_list = g_list_next(pg_list)) {

		policy_group = (dpm_toolkit_policy_group_t*) pg_list->data;
		if (policy_group) {
			if (policy_group->policies) {
				dlog_print(DLOG_DEBUG, LOG_TAG, "## effective policy free ## ");
				g_list_foreach(policy_group->policies, (GFunc) g_free, NULL);
				g_list_free(policy_group->policies);
			}
		}
	}
	g_list_free_full(effective_dpm_policy_group_list, g_free);

	for (pg_list = g_list_first(global_dpm_policy_group_list); (pg_list && pg_list->data); pg_list = g_list_next(pg_list)) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "## global policy free! ## ");
		policy_group = (dpm_toolkit_policy_group_t*) pg_list->data;
		if (policy_group) {
			if (policy_group->policies) {
				dlog_print(DLOG_DEBUG, LOG_TAG, "## global policy free ## ");
				g_list_foreach(policy_group->policies, (GFunc) g_free, NULL);
				g_list_free(policy_group->policies);
			}
		}
	}
	g_list_free_full(global_dpm_policy_group_list, g_free);

}

char* get_now_zone(void) {
    struct passwd pwd, *result;
    int bufsize;

    bufsize = sysconf(_SC_GETPW_R_SIZE_MAX);
    if (bufsize == -1)
        bufsize = 16384;

    char *buf = malloc(bufsize * sizeof(char));

    getpwuid_r(getuid(), &pwd, buf, bufsize, &result);
    if (result == NULL) {
        free(buf);
        return NULL;
    }
    free(buf);
    return strdup(result->pw_name);

}

static void win_delete_request_cb(void* data, Evas_Object* obj, void* event_info)
{
	/* To make your application go to background,
	   Call the elm_win_lower() instead
	   Evas_Object *win = (Evas_Object *) data;
	   elm_win_lower(win); */
	ui_app_exit();
}

static char* _gl_policy_group_label_get(void* data, Evas_Object* obj, const char* part)
{
	dpm_toolkit_policy_group_t *selected_group = (dpm_toolkit_policy_group_t*) data;

	if (strcmp(part, "elm.text") == 0)
		return strdup(selected_group->id);
	else
		return NULL;
}

static char* _gl_policy_label_get(void* data, Evas_Object* obj, const char* part)
{
	dpm_toolkit_entity_t* policy_cmd = (dpm_toolkit_entity_t*) data;
	if (strcmp(part, "elm.text") == 0)
		return strdup((char*)xmlGetProp((xmlNodePtr) policy_cmd->model, (xmlChar*) "desc"));
	else
		return NULL;
}

static void _entry_cb(void* data, Evas_Object* obj, void* event_info, const char* smart_event)
{
	dpm_toolkit_entity_t* selected_entity = (dpm_toolkit_entity_t*)data;
	Evas_Object* entry = obj;
	const char* entry_str = NULL;
	entry_str = elm_entry_entry_get(entry);

	/* Free previous entry */
	g_free(selected_entity->entry_input);
	selected_entity->entry_input = strdup(entry_str);
}

static void _entry_changed_cb(void* data, Evas_Object* obj, void* event_info)
{
	_entry_cb(data, obj, event_info, "changed");
}

static void _entry_preedit_cb(void *data, Evas_Object *obj, void *event_info)
{
	_entry_cb(data, obj, event_info, "preedit,changed");
}

static Evas_Object* _gl_entry_content_get(void* data, Evas_Object* obj, const char* part)
{
	Evas_Object* layout, * entry, * label;
	dpm_toolkit_entity_t* selected_entity = NULL;

	selected_entity = (dpm_toolkit_entity_t*)data;

	layout = elm_layout_add(obj);
	elm_layout_file_set(layout, global_ad->edj_path, "gl_custom_item");
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);

	label = elm_label_add(obj);
	evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(label, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_text_set(label, (const char*)xmlGetProp(selected_entity->model, (xmlChar*) "desc"));
	elm_object_part_content_set(layout, "elm.text", label);

	entry = elm_entry_add(obj);
	elm_entry_single_line_set(entry, EINA_TRUE);
	elm_entry_scrollable_set(entry, EINA_TRUE);
	evas_object_size_hint_weight_set(entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(entry, EVAS_HINT_FILL, EVAS_HINT_FILL);

	elm_entry_entry_set(entry, (const char*)xmlGetProp(selected_entity->model, (xmlChar*) "default"));
	selected_entity->entry_input = strdup((char*)xmlGetProp((xmlNodePtr)selected_entity->model, (xmlChar*) "default"));

	elm_object_part_content_set(layout, "elm.swallow.content" , entry);
	evas_object_smart_callback_add(entry, "changed", _entry_changed_cb, selected_entity);
	evas_object_smart_callback_add(entry, "preedit,changed", _entry_preedit_cb, selected_entity);

	return layout;
}

static void create_genlist_items_classes()
{
	itc_policy_group = elm_genlist_item_class_new();
	itc_policy_group->item_style = "1line";
	itc_policy_group->func.text_get = _gl_policy_group_label_get;
	itc_policy_group->func.state_get = NULL;
	itc_policy_group->func.del = NULL;

	itc_policy = elm_genlist_item_class_new();
	itc_policy->item_style = "1line";
	itc_policy->func.text_get = _gl_policy_label_get;
	itc_policy->func.state_get = NULL;
	itc_policy->func.del = NULL;

	itc_policy_entry = elm_genlist_item_class_new();
	itc_policy_entry->item_style = "full";
	itc_policy_entry->func.text_get = NULL;
	itc_policy_entry->func.content_get = _gl_entry_content_get;
	itc_policy_entry->func.state_get = NULL;
	itc_policy_entry->func.del = NULL;

}

static Eina_Bool naviframe_pop_cb(void* data, Elm_Object_Item* it)
{
	ui_app_exit();
	return EINA_FALSE;
}

static void _gl_policy_select(void* data, Evas_Object* obj, void* event_info)
{
	dpm_toolkit_entity_t* selected_policy = (dpm_toolkit_entity_t*) data;
	int ret = selected_policy->handler(selected_policy);
	elm_genlist_item_selected_set((Elm_Object_Item*) event_info, EINA_FALSE);

	if (ret == POLICY_RESULT_SUCCESS)
		display_result_popup((char*)xmlGetProp((xmlNodePtr) selected_policy->model, (xmlChar*) "desc"), POLICY_SUCCESS_TXT);
	else if (ret == POLICY_RESULT_FAIL)
		display_result_popup((char*)xmlGetProp((xmlNodePtr) selected_policy->model, (xmlChar*) "desc"), POLICY_FAIL_TXT);

}

static void _gl_policy_group_select(void* data, Evas_Object* obj, void* event_info)
{
	Evas_Object* genlist = elm_genlist_add(global_ad->nf);

	dpm_toolkit_policy_group_t* selected_group = (dpm_toolkit_policy_group_t*) data;
	dpm_toolkit_entity_t* policy_entity_info = NULL;
	GList* policyList = NULL;

	elm_genlist_item_selected_set((Elm_Object_Item*) event_info, EINA_FALSE);
	elm_genlist_mode_set(genlist, ELM_LIST_COMPRESS);

	/* add list */
	for (policyList = g_list_first(selected_group->policies); (policyList && policyList->data); policyList = g_list_next(policyList)) {
		policy_entity_info = (dpm_toolkit_entity_t*) policyList->data;

		if (xmlStrcmp(xmlGetProp(policy_entity_info->model, (xmlChar*) "status"), (xmlChar*) "ON") != 0)
			continue;

		elm_genlist_item_append(genlist, itc_policy, (void*)policy_entity_info, NULL, ELM_GENLIST_ITEM_NONE, _gl_policy_select, (void*)policy_entity_info);
	}
	elm_naviframe_item_push(global_ad->nf, selected_group->id, NULL, NULL, genlist, NULL);

}

void create_genlist(appdata_s* ad)
{
	dpm_toolkit_policy_group_t* policy_group = NULL;
	GList* g_list = NULL;
	ad->list = elm_genlist_add(ad->nf);

	dlog_print(DLOG_DEBUG, LOG_TAG, "g_list_length(ad->dpm_policy_group_list) = %d", g_list_length(effective_dpm_policy_group_list));
	for (g_list = g_list_first(effective_dpm_policy_group_list); (g_list && g_list->data); g_list = g_list_next(g_list)) {
		policy_group = (dpm_toolkit_policy_group_t *) g_list->data;
		elm_genlist_item_append(ad->list, itc_policy_group, (void*)policy_group, NULL, ELM_GENLIST_ITEM_NONE, _gl_policy_group_select, (void*)policy_group);
	}

}

void _end_btn_cb(void* data, Evas_Object* obj, void* event_info)
{
	ui_app_exit();
}

static void create_base_gui(appdata_s* ad)
{
	Elm_Object_Item* nf_it;
	Evas_Object* btn;
	char* res_path = NULL;
	char* edj_path = NULL;
	size_t path_size;
	dlog_print(DLOG_DEBUG, LOG_TAG, "create base gui");

	/* Get EDJ path */
	res_path = app_get_resource_path();
	if (res_path == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "failed get resource path");
		ui_app_exit();
		return;
	}
	path_size = strlen(res_path) + strlen("org.tizen.dpm-toolkit.edj") + 1;
	edj_path = (char*)malloc(path_size);
	if (edj_path == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "malloc fail");
		ui_app_exit();
		return;
	}
	snprintf(edj_path, path_size, "%s%s", res_path, "org.tizen.dpm-toolkit.edj");
	global_ad->edj_path = strdup(edj_path);
	free(res_path);
	free(edj_path);

	/* Window */
	ad->win = elm_win_util_standard_add(PACKAGE, PACKAGE);
	elm_win_conformant_set(ad->win, EINA_TRUE);
	elm_win_autodel_set(ad->win, EINA_TRUE);

	if (elm_win_wm_rotation_supported_get(ad->win)) {
		int rots[4] = { 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(ad->win, (const int*)(&rots), 4);
	}

	evas_object_smart_callback_add(ad->win, "delete,request", win_delete_request_cb, NULL);

	/* Conformant */
	ad->conform = elm_conformant_add(ad->win);
	evas_object_size_hint_weight_set(ad->conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(ad->win, ad->conform);
	evas_object_show(ad->conform);

	/* Indicator */
	elm_win_indicator_mode_set(ad->win, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(ad->win, ELM_WIN_INDICATOR_TRANSPARENT);

	/* Naviframe */
	ad->nf = elm_naviframe_add(ad->conform);
	elm_naviframe_prev_btn_auto_pushed_set(ad->nf, EINA_TRUE);
	eext_object_event_callback_add(ad->nf, EEXT_CALLBACK_BACK, eext_naviframe_back_cb, ad);
	evas_object_size_hint_weight_set(ad->nf, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_content_set(ad->conform, ad->nf);
	evas_object_show(ad->nf);

	/*Genlist */
	create_genlist_items_classes();
	create_genlist(ad);

	btn = elm_button_add(ad->nf);
	elm_object_style_set(btn, "naviframe/end_btn/default");
	evas_object_smart_callback_add(btn, "clicked", _end_btn_cb, NULL);

	nf_it = elm_naviframe_item_push(ad->nf, "DPM Toolkit", btn, NULL, ad->list, NULL);
	elm_naviframe_item_pop_cb_set(nf_it, naviframe_pop_cb, ad);

	/* Show window after base gui is set up */
	evas_object_show(ad->win);

}

static void dpm_toolkit_rebuild_policyGroup(const char *xmlFilePath)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "start dpm_toolkit_rebuild_policyGroup");

	dpmDoc = xmlParseFile(xmlFilePath);

	GList* pg_list = NULL;
	GList* p_list = NULL;
	dpm_toolkit_policy_group_t* group_node = NULL;
	dpm_toolkit_entity_t* policy = NULL;
	int emptyFlag;

	if (dpmDoc == NULL) {
		/*error */
		dlog_print(DLOG_DEBUG, LOG_TAG, "docfile parsing fail");
		return;
	}
	dlog_print(DLOG_DEBUG, LOG_TAG, "docfile parsing success");

	for (pg_list = g_list_first(global_dpm_policy_group_list); (pg_list && pg_list->data); pg_list = g_list_next(pg_list)) {

		group_node = (dpm_toolkit_policy_group_t*) pg_list->data;
		dlog_print(DLOG_DEBUG, LOG_TAG, "group_node [%s] ", group_node->id);
		emptyFlag = 1;

		for (p_list = g_list_first(group_node->policies); (p_list && p_list->data); p_list = g_list_next(p_list)) {
			policy = (dpm_toolkit_entity_t*) p_list->data;
			xmlNodePtr policyNode = evaluate_xmlNode(dpmDoc, group_node->id, policy->id);

			if (!policyNode)
				continue;

			policy->model = policyNode;

			if (emptyFlag == 1)
				emptyFlag = 0;
		}
		if (emptyFlag == 0) {
			dpm_toolkit_add_policy_group(&effective_dpm_policy_group_list, group_node);
			dlog_print(DLOG_DEBUG, LOG_TAG, "add policy group %s", group_node->id);
		}

	}
}

static bool app_create(void* data)
{
	/* Hook to take necessary actions before main event loop starts
	   Initialize UI resources and application's data
	   If this function returns true, the main loop of application starts
	   If this function returns false, the application is terminated */

	dlog_print(DLOG_DEBUG, LOG_TAG, " ###### app_create ###### ");
	appdata_s* ad = data;
	elm_app_base_scale_set(1.8);

	dpm_toolkit_rebuild_policyGroup(POLICY_XML_FILE_PATH);
	create_base_gui(ad);

	return true;
}

static void app_control(app_control_h app_control, void* data)
{
	/* Handle the launch request. */
}

static void app_pause(void* data)
{
	/* Take necessary actions when application becomes invisible. */
	dlog_print(DLOG_DEBUG, LOG_TAG, " ###### app_pause ###### ");
}

static void app_resume(void* data)
{
	/* Take necessary actions when application becomes visible. */
	dlog_print(DLOG_DEBUG, LOG_TAG, " ###### app_resume ###### ");
}

static void app_terminate(void* data)
{
	/* Release all resources. */
	dlog_print(DLOG_DEBUG, LOG_TAG, " ###### app_terminate ###### ");
	dpm_parser_free_policy_list();
}

static void ui_app_lang_changed(app_event_info_h event_info, void* user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED */
	char* locale = NULL;
	system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
	elm_language_set(locale);
	free(locale);
	return;
}

static void ui_app_orient_changed(app_event_info_h event_info, void* user_data)
{
	/*APP_EVENT_DEVICE_ORIENTATION_CHANGED */
	return;
}

static void ui_app_region_changed(app_event_info_h event_info, void* user_data)
{
	/*APP_EVENT_REGION_FORMAT_CHANGED */
}

static void ui_app_low_battery(app_event_info_h event_info, void* user_data)
{
	/*APP_EVENT_LOW_BATTERY */
}

static void ui_app_low_memory(app_event_info_h event_info, void* user_data)
{
	/*APP_EVENT_LOW_MEMORY */
}

int main(int argc, char* argv[])
{
	appdata_s ad = { 0, };
	int ret = 0;

	ui_app_lifecycle_callback_s event_callback = { 0, };
	app_event_handler_h handlers[5] = { NULL, };

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, ui_app_low_battery, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, ui_app_low_memory, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, ui_app_orient_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ui_app_lang_changed, &ad);
	ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, ui_app_region_changed, &ad);
	ui_app_remove_event_handler(handlers[APP_EVENT_LOW_MEMORY]);

	global_ad = &ad;
	ret = ui_app_main(argc, argv, &event_callback, &ad);

	if (ret != APP_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "app_main() is failed. err = %d", ret);

	return ret;
}

