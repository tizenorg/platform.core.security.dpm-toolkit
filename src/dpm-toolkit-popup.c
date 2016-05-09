#include "dpm-toolkit.h"

void _popup_hide_cb(void* data, Evas_Object* obj, void* event_info)
{
	global_popup.popup_flag = 0;
	evas_object_del(obj);
}

void _popup_hide_finished_cb(void* data, Evas_Object* obj, void* event_info)
{
	global_popup.popup_flag = 0;
	evas_object_del(obj);
}

void _popup_block_clicked_cb(void* data, Evas_Object* obj, void* event_info)
{
	global_popup.popup_flag = 0;
	evas_object_del(obj);
}

void _response_cb(void* data, Evas_Object* obj, void* event_info)
{
	global_popup.popup_flag = 0;
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

void _radio_set_btn_response_cb(void *data, Evas_Object *obj, void *event_info)
{
	int ret;

	if (global_popup.radio_index < 0)
		global_popup.policy->radio_index = 0;
	else
		global_popup.policy->radio_index = global_popup.radio_index;

	SLOGD("selected radio index : %d", global_popup.policy->radio_index);
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
	char* default_text = NULL;

	popup = elm_popup_add(global_ad->nf);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_part_text_set(popup, "title,text", title);

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	entry = elm_entry_add(popup);
	global_popup.entry = entry;
	elm_entry_single_line_set(entry, EINA_TRUE);
	elm_entry_scrollable_set(entry, EINA_TRUE);
	evas_object_size_hint_weight_set(entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_style_set(entry, "center");
	elm_object_part_content_set(popup, "elm.swallow.content", entry);

	default_text = (char*)xmlGetProp(selected_policy->model, (xmlChar *) "default");
	if (default_text != NULL) {
		elm_entry_entry_set(entry, default_text);
		free(default_text);
	} else
		elm_object_part_text_set(entry, "guide", "Enter value");

	btn = elm_button_add(popup);
	elm_object_text_set(btn, "set");
	elm_object_style_set(btn, "bottom");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_smart_callback_add(btn, "clicked", _set_btn_response_cb, popup);

	btn = elm_button_add(popup);
	elm_object_text_set(btn, "cancel");
	elm_object_style_set(btn, "bottom");
	elm_object_part_content_set(popup, "button2", btn);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_smart_callback_add(btn, "clicked", _response_cb, popup);
	evas_object_show(popup);

}

void radio_changed_cb(void* data, Evas_Object* obj, void* evas_info)
{
	int value = 0;
	SLOGD("Selected Radio : %d ", (int)data);
	value = elm_radio_value_get(obj);
	global_popup.radio_index = value;
	SLOGD("selected value for the group : %d", value);
}

void display_radio_popup(const char* title, dpm_toolkit_entity_t* selected_policy, char radio_text[][MAX_RADIO_TEXT_LEN], int array_row)
{
	Evas_Object* popup = NULL, * radio = NULL, * radio_group = NULL, * btn = NULL;
	Evas_Object* box = NULL;
	int radioNum = array_row;
	int i;

	global_popup.popup_flag = 1;
	global_popup.policy = selected_policy;
	global_popup.radio_index = -1;

	popup = elm_popup_add(global_ad->nf);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_popup_scrollable_set(popup, EINA_TRUE);
	elm_object_part_text_set(popup, "title,text", title);

	eext_object_event_callback_add(popup, EEXT_CALLBACK_BACK, _popup_hide_cb, NULL);
	evas_object_smart_callback_add(popup, "dismissed", _popup_hide_finished_cb, NULL);
	evas_object_smart_callback_add(popup, "block,clicked", _popup_block_clicked_cb, NULL);

	box = elm_box_add(popup);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(box, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_style_set(box, "center");
	elm_object_part_content_set(popup, "elm.swallow.content", box);

	for (i = 0; i < radioNum; i++) {
		radio = elm_radio_add(box);
		evas_object_size_hint_align_set(radio, EVAS_HINT_FILL, EVAS_HINT_FILL);
		elm_object_text_set(radio, radio_text[i]);
		evas_object_show(radio);
		elm_box_pack_end(box, radio);

		elm_radio_state_value_set(radio, i);

		if (i == 0) {
			evas_object_smart_callback_add(radio, "changed", radio_changed_cb, (void*)i);
			radio_group = radio;
			continue;
		}

		elm_radio_group_add(radio, radio_group);
		evas_object_smart_callback_add(radio, "changed", radio_changed_cb, (void*)i);

	}

	evas_object_size_hint_align_set(radio_group, EVAS_HINT_FILL, EVAS_HINT_FILL);

	btn = elm_button_add(popup);
	elm_object_text_set(btn, "set");
	elm_object_style_set(btn, "bottom");
	elm_object_part_content_set(popup, "button1", btn);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_smart_callback_add(btn, "clicked", _radio_set_btn_response_cb, popup);

	btn = elm_button_add(popup);
	elm_object_text_set(btn, "cancel");
	elm_object_style_set(btn, "bottom");
	elm_object_part_content_set(popup, "button2", btn);
	evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_smart_callback_add(btn, "clicked", _response_cb, popup);
	evas_object_show(popup);

}
