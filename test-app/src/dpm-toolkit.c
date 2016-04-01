#include "dpm-toolkit.h"

/*#define POLICY_XML_FILE_PATH "/home/owner/test.xml"*/
#define POLICY_XML_FILE_PATH "/usr/apps/org.tizen.dpm-toolkit-app/test.xml"
static Elm_Genlist_Item_Class *itc_policy_group, *itc_policy;
static xmlDoc *dpmDoc = NULL;

xmlNodePtr evaluate_xmlNode(xmlDoc * dpmDoc, char *policy_group, char *policy_id)
{
	char *xpath = NULL;
	size_t xpath_size;
	xmlXPathContext *context = NULL;
	xmlXPathObject *result = NULL;
	xmlNodePtr xNode = NULL;
	xmlNodeSet *nodeset = NULL;

	xpath_size = strlen(policy_group) + strlen(policy_id) + strlen("//policy-group[@id='%s']/policy[@id='%s']") + 1;
	xpath = (char *)malloc(xpath_size);

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
	result = xmlXPathEvalExpression((xmlChar *) xpath, context);
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

int dpm_toolkit_add_policy_group(GList ** Grouplist, dpm_toolkit_policy_group_t * group)
{
	int ret = 0;

	if (group == NULL) {
		ret = -1;
		return ret;
	}

	*Grouplist = g_list_append(*Grouplist, group);

	return ret;
}

int dpm_toolkit_init_policy(GList ** policies, dpm_toolkit_entity_t * policy, int policyNum)
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

int dpm_toolkit_add_policy(GList ** policies, dpm_toolkit_entity_t * policy)
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

	xmlFreeDoc(dpmDoc);

	GList *pg_list = NULL;
	dpm_toolkit_policy_group_t *policy_group = NULL;

	for (pg_list = g_list_first(effective_dpm_policy_group_list); (pg_list && pg_list->data); pg_list = g_list_next(pg_list)) {

		policy_group = (dpm_toolkit_policy_group_t *) pg_list->data;
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
		policy_group = (dpm_toolkit_policy_group_t *) pg_list->data;
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

static void win_delete_request_cb(void *data, Evas_Object * obj, void *event_info)
{
	/* To make your application go to background,
	   Call the elm_win_lower() instead
	   Evas_Object *win = (Evas_Object *) data;
	   elm_win_lower(win); */
	ui_app_exit();
}

static char *_gl_policy_group_label_get(void *data, Evas_Object * obj, const char *part)
{
	dpm_toolkit_policy_group_t *selected_group = (dpm_toolkit_policy_group_t *) data;

	if (strcmp(part, "elm.text") == 0)
		return strdup(selected_group->id);
	else
		return NULL;
}

static char *_gl_policy_label_get(void *data, Evas_Object * obj, const char *part)
{
	dpm_toolkit_entity_t *policy_cmd = (dpm_toolkit_entity_t *) data;
	if (strcmp(part, "elm.text") == 0)
		return strdup((char *)xmlGetProp((xmlNodePtr) policy_cmd->model, (xmlChar *) "desc"));
	else
		return NULL;
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

}

static Eina_Bool naviframe_pop_cb(void *data, Elm_Object_Item * it)
{
	appdata_s *ad = data;

	/* Let window go to hide state. */
	elm_win_lower(ad->win);

	return EINA_FALSE;
}

static void _gl_policy_select(void *data, Evas_Object * obj, void *event_info)
{
	dpm_toolkit_entity_t *selected_policy = (dpm_toolkit_entity_t *) data;
	dlog_print(DLOG_DEBUG, LOG_TAG, "## debug-- 1 id : %s  ", selected_policy->id);

	int ret = selected_policy->handler(selected_policy);
	dlog_print(DLOG_DEBUG, LOG_TAG, "## return : %d  ", ret);
}

static void _gl_policy_group_select(void *data, Evas_Object * obj, void *event_info)
{
	Evas_Object *genlist = elm_genlist_add(global_ad->nf);

	dpm_toolkit_policy_group_t *selected_group = (dpm_toolkit_policy_group_t *) data;
	dpm_toolkit_entity_t *policy_entity_info = NULL;

	elm_genlist_item_selected_set((Elm_Object_Item *) event_info, EINA_FALSE);
	elm_genlist_mode_set(genlist, ELM_LIST_COMPRESS);

	/* add list */
	GList *policyList = NULL;
	for (policyList = g_list_first(selected_group->policies); (policyList && policyList->data); policyList = g_list_next(policyList)) {
		policy_entity_info = (dpm_toolkit_entity_t *) policyList->data;

		if (xmlStrcmp(xmlGetProp(policy_entity_info->model, (xmlChar *) "status"), (xmlChar *) "ON") == 0)
			elm_genlist_item_append(genlist, itc_policy, (void *)policy_entity_info, NULL, ELM_GENLIST_ITEM_NONE, _gl_policy_select, (void *)policy_entity_info);
	}
	elm_naviframe_item_push(global_ad->nf, selected_group->id, NULL, NULL, genlist, NULL);

}

void create_genlist(appdata_s * ad)
{
	dpm_toolkit_policy_group_t *policy_group = NULL;
	GList *g_list = NULL;
	ad->list = elm_genlist_add(ad->nf);

	dlog_print(DLOG_ERROR, LOG_TAG, "g_list_length(ad->dpm_policy_group_list) = %d", g_list_length(effective_dpm_policy_group_list));
	for (g_list = g_list_first(effective_dpm_policy_group_list); (g_list && g_list->data); g_list = g_list_next(g_list)) {

		policy_group = (dpm_toolkit_policy_group_t *) g_list->data;
		elm_genlist_item_append(ad->list, itc_policy_group, (void *)policy_group, NULL, ELM_GENLIST_ITEM_NONE, _gl_policy_group_select, (void *)policy_group);
	}
	evas_object_show(ad->list);
}

static void create_base_gui(appdata_s * ad)
{
	Elm_Object_Item *nf_it;
	dlog_print(DLOG_ERROR, LOG_TAG, "create base gui");
	/* Window */
	ad->win = elm_win_util_standard_add(PACKAGE, PACKAGE);
	elm_win_conformant_set(ad->win, EINA_TRUE);
	elm_win_autodel_set(ad->win, EINA_TRUE);

	if (elm_win_wm_rotation_supported_get(ad->win)) {
		int rots[4] = { 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(ad->win, (const int *)(&rots), 4);
	}

	evas_object_smart_callback_add(ad->win, "delete,request", win_delete_request_cb, NULL);

	/* Conformant */
	ad->conform = elm_conformant_add(ad->win);
	evas_object_size_hint_weight_set(ad->conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(ad->win, ad->conform);
	evas_object_show(ad->conform);

	/* Naviframe */
	ad->nf = elm_naviframe_add(ad->conform);
	eext_object_event_callback_add(ad->nf, EEXT_CALLBACK_BACK, eext_naviframe_back_cb, ad);
	evas_object_size_hint_weight_set(ad->nf, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_content_set(ad->conform, ad->nf);
	evas_object_show(ad->nf);

	/*Genlist */
	create_genlist_items_classes();
	create_genlist(ad);
	nf_it = elm_naviframe_item_push(ad->nf, "DPM Toolkit", NULL, NULL, ad->list, NULL);
	elm_naviframe_item_pop_cb_set(nf_it, naviframe_pop_cb, ad);

	/* Show window after base gui is set up */
	evas_object_show(ad->win);

}

static void dpm_toolkit_rebuild_policyGorup(const char *xmlFilePath)
{
	dlog_print(DLOG_DEBUG, LOG_TAG, "start dpm_toolkit_rebuild_policyGorup");
	dpmDoc = xmlParseFile(xmlFilePath);

	if (dpmDoc == NULL) {
		/*error */
		dlog_print(DLOG_DEBUG, LOG_TAG, "docfile parsing fail");
		return;
	}
	dlog_print(DLOG_DEBUG, LOG_TAG, "docfile parsing success");

	dpm_toolkit_policy_group_t *group_node = NULL;
	GList *pg_list = NULL;
	GList *p_list = NULL;

	for (pg_list = g_list_first(global_dpm_policy_group_list); (pg_list && pg_list->data); pg_list = g_list_next(pg_list)) {

		group_node = (dpm_toolkit_policy_group_t *) pg_list->data;
		dlog_print(DLOG_DEBUG, LOG_TAG, "group_node [%s] ", group_node->id);
		int emptyFlag = 1;

		dpm_toolkit_entity_t *policy = NULL;
		for (p_list = g_list_first(group_node->policies); (p_list && p_list->data); p_list = g_list_next(p_list)) {
			policy = (dpm_toolkit_entity_t *) p_list->data;
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

static bool app_create(void *data)
{
	/* Hook to take necessary actions before main event loop starts
	   Initialize UI resources and application's data
	   If this function returns true, the main loop of application starts
	   If this function returns false, the application is terminated */

	dlog_print(DLOG_DEBUG, LOG_TAG, " ###### app_create ###### ");
	appdata_s *ad = data;
	elm_app_base_scale_set(1.8);

	dpm_toolkit_rebuild_policyGorup(POLICY_XML_FILE_PATH);
	create_base_gui(ad);

	return true;
}

static void app_control(app_control_h app_control, void *data)
{
	/* Handle the launch request. */
}

static void app_pause(void *data)
{
	/* Take necessary actions when application becomes invisible. */
	dlog_print(DLOG_DEBUG, LOG_TAG, " ###### app_pause ###### ");
}

static void app_resume(void *data)
{
	/* Take necessary actions when application becomes visible. */
	dlog_print(DLOG_DEBUG, LOG_TAG, " ###### app_resume ###### ");
}

static void app_terminate(void *data)
{
	/* Release all resources. */
	dlog_print(DLOG_DEBUG, LOG_TAG, " ###### app_terminate ###### ");
	dpm_parser_free_policy_list();
}

static void ui_app_lang_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LANGUAGE_CHANGED */
	char *locale = NULL;
	system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &locale);
	elm_language_set(locale);
	free(locale);
	return;
}

static void ui_app_orient_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_DEVICE_ORIENTATION_CHANGED */
	return;
}

static void ui_app_region_changed(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_REGION_FORMAT_CHANGED */
}

static void ui_app_low_battery(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_BATTERY */
}

static void ui_app_low_memory(app_event_info_h event_info, void *user_data)
{
	/*APP_EVENT_LOW_MEMORY */
}

int main(int argc, char *argv[])
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

