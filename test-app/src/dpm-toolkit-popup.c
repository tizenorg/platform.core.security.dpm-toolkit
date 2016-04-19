#include "dpm-toolkit.h"

void _popup_hide_cb(void* data, Evas_Object* obj, void* event_info)
{
	evas_object_del(obj);
}

void _popup_hide_finished_cb(void* data, Evas_Object* obj, void* event_info)
{
	evas_object_del(obj);
}

void _popup_block_clicked_cb(void* data, Evas_Object* obj, void* event_info)
{
	evas_object_del(obj);
}

void _response_cb(void* data, Evas_Object* obj, void* event_info)
{
	evas_object_del(data);
}

void _set_btn_response_cb(void *data, Evas_Object *obj, void *event_info)
{
	char* input = NULL;
	int ret;
	input = (char*)elm_entry_entry_get(global_popup.entry);
	dlog_print(DLOG_DEBUG, LOG_TAG, "popup btn click cb entry input: %s \n", input);
	global_popup.policy->entry_input = strdup(input);

	ret = global_popup.policy->handler(global_popup.policy);

	if (ret == POLICY_RESULT_SUCCESS) {
		evas_object_del(data);
		display_result_popup((char*)xmlGetProp((xmlNodePtr) global_popup.policy->model, (xmlChar*) "desc"), "SUCCESS");
	} else if (ret == POLICY_RESULT_FAIL) {
		evas_object_del(data);
		display_result_popup((char*)xmlGetProp((xmlNodePtr) global_popup.policy->model, (xmlChar*) "desc"), "FAIL");
	} else
		evas_object_del(data);

}

void display_result_popup(const char* title, const char* popup_message)
{
	Evas_Object* popup = NULL;
	Evas_Object* btn = NULL;

	if (title == NULL || popup_message == NULL)
		dlog_print(DLOG_ERROR, LOG_TAG, "Invalid parameters");

	popup = elm_popup_add(global_ad->nf);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_text_set(popup, "title,text", title);
	elm_object_text_set(popup, popup_message);

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	btn = elm_button_add(popup);
	elm_object_text_set(btn, "OK");
	elm_object_style_set(btn, "bottom");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_smart_callback_add(btn, "clicked", _response_cb, popup);
	evas_object_show(popup);

}

void display_input_popup(const char* title, dpm_toolkit_entity_t* selected_policy)
{
	Evas_Object* popup = NULL, * entry = NULL, * btn = NULL;

	global_popup.popup_flag = 1;
	global_popup.policy = selected_policy;

	popup = elm_popup_add(global_ad->nf);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_text_set(popup, "title,text", title);

	entry = elm_entry_add(popup);
	global_popup.entry = entry;
	elm_entry_single_line_set(entry, EINA_TRUE);
	elm_entry_scrollable_set(entry, EINA_TRUE);
	evas_object_size_hint_weight_set(entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_style_set(entry, "center");
	elm_object_part_content_set(popup, "elm.swallow.content", entry);

	btn = elm_button_add(popup);
	elm_object_text_set(btn, "set");
	elm_object_style_set(btn, "bottom");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_smart_callback_add(btn, "clicked", _set_btn_response_cb, popup);
	evas_object_show(popup);

	btn = elm_button_add(popup);
	elm_object_text_set(btn, "cancel");
	elm_object_style_set(btn, "bottom");
	elm_object_part_content_set(popup, "button2", btn);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_smart_callback_add(btn, "clicked", _response_cb, popup);
	evas_object_show(popup);

}
