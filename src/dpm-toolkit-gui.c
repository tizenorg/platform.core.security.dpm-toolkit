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
#include <getopt.h>
#include <stdio.h>

#include "dpm-toolkit.h"

#define BUTTON_CANCEL	1
#define BUTTON_OK		2
#define BUTTON_SET		4

static Evas_Object* naviframe;
static Evas_Object* mainwindow;

static void on_popup_hide(void* data, Evas_Object* obj, void* event_info)
{
	int* done = (int *)data;
	*done = BUTTON_CANCEL;
}

static void on_dismissed(void* data, Evas_Object* obj, void* event_info)
{
	int* done = (int *)data;
	*done = BUTTON_CANCEL;
}

static void on_block_clicked(void* data, Evas_Object* obj, void* event_info)
{
	int* done = (int *)data;
	*done = BUTTON_CANCEL;
}

static void on_cancel_button_clicked(void* data, Evas_Object* obj, void* event_info)
{
	int* done = (int *)data;
	*done = BUTTON_CANCEL;
}

static void on_set_button_clicked(void* data, Evas_Object* obj, void* event_info)
{
	int* done = (int *)data;
	*done = BUTTON_SET;
}

void wait_for_event(int* done)
{
	ecore_thread_main_loop_begin();
	while (!*done) {
		ecore_main_loop_iterate();
	}

	ecore_thread_main_loop_end();
}

static Evas_Object* create_basic_popup(Evas_Object* parent, const char* title, void* data)
{
	Evas_Object* popup = elm_popup_add(parent);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_text_set(popup, "title,text", title);

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, on_popup_hide, data);
	evas_object_smart_callback_add(popup, "dismissed", on_dismissed, data);
	evas_object_smart_callback_add(popup, "block,clicked", on_block_clicked, data);

	return popup;
}

static Evas_Object* create_entry_box(Evas_Object* parent, const char* msg, const char* guide)
{
	Evas_Object* entry = elm_entry_add(parent);
	elm_entry_single_line_set(entry, EINA_TRUE);
	elm_entry_scrollable_set(entry, EINA_TRUE);
	evas_object_size_hint_weight_set(entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_style_set(entry, "center");
	elm_object_part_content_set(parent, "elm.swallow.content", entry);

	if (msg != NULL) {
		elm_entry_entry_set(entry, msg);
	} else if (guide != NULL) {
		elm_object_part_text_set(entry, "guide", guide);
	} else {
		elm_object_part_text_set(entry, "guide", "Enter value");
	}

	return entry;
}

static Evas_Object* create_radio_group(Evas_Object* parent, const char* text[], int nr)
{
	int i;
	Evas_Object* radio_group;
	Evas_Object* box = elm_box_add(parent);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_style_set(box, "center");
	elm_object_part_content_set(parent, "elm.swallow.content", box);

	for (i = 0; i < nr; i++) {
		Evas_Object* radio = elm_radio_add(box);
		evas_object_size_hint_align_set(radio, EVAS_HINT_FILL, EVAS_HINT_FILL);
		elm_object_text_set(radio, text[i]);
		evas_object_show(radio);
		elm_box_pack_end(box, radio);

		elm_radio_state_value_set(radio, i);

		if (i == 0) {
			radio_group = radio;
		}

		elm_radio_group_add(radio, radio_group);
	}

	evas_object_size_hint_align_set(radio_group, EVAS_HINT_FILL, EVAS_HINT_FILL);

	return radio_group;
}

static void create_button_group(Evas_Object* parent, int mask, void* data)
{
	Evas_Object* button;

	if (mask & BUTTON_SET) {
		button = elm_button_add(parent);
		elm_object_text_set(button, "set");
		elm_object_style_set(button, "bottom");
		elm_object_part_content_set(parent, "button1", button);
		evas_object_size_hint_weight_set(button, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_smart_callback_add(button, "clicked", on_set_button_clicked, data);
	}

	if (mask & BUTTON_OK) {
		button = elm_button_add(parent);
		elm_object_text_set(button, "OK");
		elm_object_style_set(button, "bottom");
		elm_object_part_content_set(parent, "button1", button);
		evas_object_size_hint_weight_set(button, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_smart_callback_add(button, "clicked", on_set_button_clicked, data);
	}

	if (mask & BUTTON_CANCEL) {
		button = elm_button_add(parent);
		elm_object_text_set(button, "cancel");
		elm_object_style_set(button, "bottom");
		elm_object_part_content_set(parent, "button2", button);
		evas_object_size_hint_weight_set(button, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
		evas_object_smart_callback_add(button, "clicked", on_cancel_button_clicked, data);
	}
}

static int open_entry_popup(const char* title, const char* msg, const char* guide, char** value)
{
	int done = 0;
	Evas_Object* popup = NULL;
	Evas_Object* entry = NULL;

	popup = create_basic_popup(naviframe, title, (void *)&done);
	entry = create_entry_box(popup, msg, guide);
	create_button_group(popup, BUTTON_SET | BUTTON_CANCEL, (void *)&done);
	evas_object_show(popup);

	wait_for_event(&done);
	if (done != BUTTON_CANCEL) {
		*value = strdup(elm_entry_entry_get(entry));
	} else {
		*value = NULL;
	}

	evas_object_del(popup);

	return done == BUTTON_CANCEL ? XTK_EVENT_CANCEL : XTK_EVENT_OK;
}

static int open_radio_popup(const char* title, const char* text[], int nr, int* index)
{
	int done = 0;
	Evas_Object* popup = NULL;
	Evas_Object* radio = NULL;

	popup = create_basic_popup(naviframe, title, (void *)&done);
	radio = create_radio_group(popup, text, nr);
	create_button_group(popup, BUTTON_SET | BUTTON_CANCEL, (void *)&done);
	evas_object_show(popup);

	wait_for_event(&done);

	if (done != BUTTON_CANCEL) {
		*index = elm_radio_value_get(radio);
	} else {
		*index = -1;
	}

	evas_object_del(popup);

	return done == BUTTON_CANCEL ? XTK_EVENT_CANCEL : XTK_EVENT_OK;
}

static int open_message_popup(const char* title, const char* message)
{
	int done = 0;
	Evas_Object* popup = NULL;

	if (title == NULL || message == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Invalid parameters");
	}

	popup = create_basic_popup(naviframe, title, (void *)&done);
	elm_object_text_set(popup, message);
	create_button_group(popup, BUTTON_OK, (void *)&done);
	evas_object_show(popup);

	wait_for_event(&done);

	evas_object_del(popup);

	return done == BUTTON_CANCEL ? XTK_EVENT_CANCEL : XTK_EVENT_OK;
}

static int open_confirm_popup(const char* title, const char* message)
{
	int done = 0;
	Evas_Object* popup = NULL;

	if (title == NULL || message == NULL) {
		dlog_print(DLOG_ERROR, LOG_TAG, "Invalid parameters");
	}

	popup = create_basic_popup(naviframe, title, (void *)&done);
	elm_object_text_set(popup, message);
	create_button_group(popup, BUTTON_OK | BUTTON_CANCEL, (void *)&done);
	evas_object_show(popup);

	wait_for_event(&done);

	evas_object_del(popup);

	return done == BUTTON_CANCEL ? XTK_EVENT_CANCEL : XTK_EVENT_OK;
}

static void _gl_policy_select(void* data, Evas_Object* obj, void* event_info)
{
	xtk_policy_t* entity = (xtk_policy_t *)data;

	entity->handler(entity);

	elm_genlist_item_selected_set((Elm_Object_Item *)event_info, EINA_FALSE);
}

static char* _gl_policy_label_get(void* data, Evas_Object* obj, const char* part)
{
	if (strcmp(part, "elm.text") == 0)
		return strdup(policy_get_title((xtk_policy_t *)data));
	else
		return NULL;
}

static void _gl_policy_group_select(void* data, Evas_Object* obj, void* event_info)
{
	GList* policy_list = NULL;
	Elm_Genlist_Item_Class* itc;
	Evas_Object* genlist = elm_genlist_add(naviframe);
	xtk_policy_group_t* selected_group = (xtk_policy_group_t *)data;

	elm_genlist_item_selected_set((Elm_Object_Item *) event_info, EINA_FALSE);
	elm_genlist_mode_set(genlist, ELM_LIST_COMPRESS);

	itc = elm_genlist_item_class_new();
	itc->item_style = "type1";
	itc->func.text_get = _gl_policy_label_get;
	itc->func.state_get = NULL;
	itc->func.del = NULL;

	xtk_foreach_policy(policy_list, selected_group) {
		xtk_policy_t* entity = glist_to_policy(policy_list);

		elm_genlist_item_append(genlist, itc, (void *)entity, NULL, ELM_GENLIST_ITEM_NONE,
							    _gl_policy_select, (void *)entity);
	}
	elm_genlist_item_class_free(itc);

	elm_naviframe_item_push(naviframe, selected_group->id, NULL, NULL, genlist, NULL);
}

static char* _gl_policy_group_label_get(void* data, Evas_Object* obj, const char* part)
{
	if (strcmp(part, "elm.text") == 0)
		return strdup(((xtk_policy_group_t *)data)->id);

	return NULL;
}

static Evas_Object* create_genlist(Evas_Object* naviframe)
{
	Evas_Object* widget;
	Elm_Genlist_Item_Class* itc;
	GList* policy_group_list = NULL;

	itc = elm_genlist_item_class_new();
	itc->item_style = "type1";
	itc->func.text_get = _gl_policy_group_label_get;
	itc->func.state_get = NULL;
	itc->func.del = NULL;

	widget = elm_genlist_add(naviframe);

	xtk_foreach_policy_group(policy_group_list) {
		xtk_policy_group_t* policy_group = glist_to_policy_group(policy_group_list);
		elm_genlist_item_append(widget, itc, (void *)policy_group, NULL, ELM_GENLIST_ITEM_NONE,
								_gl_policy_group_select, (void *)policy_group);
	}
	elm_genlist_item_class_free(itc);

	return widget;
}

static void win_terminate_request_cb(void* data, Evas_Object* obj, void* event_info)
{
	ui_app_exit();
}

static void win_delete_request_cb(void* data, Evas_Object* obj, void* event_info)
{
	/* To make your application go to background,
	   Call the elm_win_lower() instead
	   Evas_Object *win = (Evas_Object *) data;
	   elm_win_lower(win); */
	ui_app_exit();
}

static Eina_Bool naviframe_pop_cb(void* data, Elm_Object_Item* it)
{
	ui_app_exit();
	return EINA_FALSE;
}

static int create_base_gui()
{
	Elm_Object_Item* nfitem;
	Evas_Object* button;
	Evas_Object* genlist;
	Evas_Object* conform;

	/* Window */
	mainwindow = elm_win_util_standard_add(PACKAGE, PACKAGE);
	elm_win_conformant_set(mainwindow, EINA_TRUE);
	elm_win_autodel_set(mainwindow, EINA_TRUE);

	if (elm_win_wm_rotation_supported_get(mainwindow)) {
		int rots[4] = { 0, 90, 180, 270 };
		elm_win_wm_rotation_available_rotations_set(mainwindow, (const int*)(&rots), 4);
	}

	evas_object_smart_callback_add(mainwindow, "delete,request", win_delete_request_cb, NULL);

	/* Conformant */
	conform = elm_conformant_add(mainwindow);
	evas_object_size_hint_weight_set(conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(mainwindow, conform);
	evas_object_show(conform);

	/* Indicator */
	elm_win_indicator_mode_set(mainwindow, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(mainwindow, ELM_WIN_INDICATOR_TRANSPARENT);

	/* Naviframe */
	naviframe = elm_naviframe_add(conform);
	elm_naviframe_prev_btn_auto_pushed_set(naviframe, EINA_TRUE);
	eext_object_event_callback_add(naviframe, EEXT_CALLBACK_BACK, eext_naviframe_back_cb, NULL);
	evas_object_size_hint_weight_set(naviframe, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_content_set(conform, naviframe);
	evas_object_show(naviframe);

	/*Genlist */
	genlist = create_genlist(naviframe);

	button = elm_button_add(naviframe);
	elm_object_style_set(button, "naviframe/end_btn/default");
	evas_object_smart_callback_add(button, "clicked", win_terminate_request_cb, NULL);

	nfitem = elm_naviframe_item_push(naviframe, "DPM Toolkit", button, NULL, genlist, NULL);
	elm_naviframe_item_pop_cb_set(nfitem, naviframe_pop_cb, NULL);

	/* Show window after base gui is set up */
	evas_object_show(mainwindow);

	return 0;
}

static xtk_context_t gui_context = {
	.radio_popup = open_radio_popup,
	.entry_popup = open_entry_popup,
	.message_popup = open_message_popup,
	.confirm_popup = open_confirm_popup
};

static bool app_create(void* data)
{
	/* Hook to take necessary actions before main event loop starts
	   Initialize UI resources and application's data
	   If this function returns true, the main loop of application starts
	   If this function returns false, the application is terminated */

	dlog_print(DLOG_DEBUG, LOG_TAG, " ###### app_create ###### ");

	xtk_context_set_current(&gui_context);

	if (xtk_rebuild_policy_group(POLICY_XML_FILE_PATH) != 0) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to rebuild policy group");
		return false;
	}

	elm_app_base_scale_set(1.8);
	if (create_base_gui() != 0) {
		return false;
	}

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
	xtk_free_policy_list();
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

int xtk_gui_main(int argc, char* argv[])
{
	int ret = 0;

	ui_app_lifecycle_callback_s event_callback = { 0, };
	app_event_handler_h handlers[5] = { NULL, };

	event_callback.create = app_create;
	event_callback.terminate = app_terminate;
	event_callback.pause = app_pause;
	event_callback.resume = app_resume;
	event_callback.app_control = app_control;

	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_BATTERY], APP_EVENT_LOW_BATTERY, ui_app_low_battery, NULL);
	ui_app_add_event_handler(&handlers[APP_EVENT_LOW_MEMORY], APP_EVENT_LOW_MEMORY, ui_app_low_memory, NULL);
	ui_app_add_event_handler(&handlers[APP_EVENT_DEVICE_ORIENTATION_CHANGED], APP_EVENT_DEVICE_ORIENTATION_CHANGED, ui_app_orient_changed, NULL);
	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, ui_app_lang_changed, NULL);
	ui_app_add_event_handler(&handlers[APP_EVENT_REGION_FORMAT_CHANGED], APP_EVENT_REGION_FORMAT_CHANGED, ui_app_region_changed, NULL);
	ui_app_remove_event_handler(handlers[APP_EVENT_LOW_MEMORY]);

	ret = ui_app_main(argc, argv, &event_callback, NULL);
	if (ret != APP_ERROR_NONE)
		dlog_print(DLOG_ERROR, LOG_TAG, "app_main() is failed. err = %d", ret);

	return ret;
}
