#include "dpm-toolkit.h"

#define handler_display_input_popup(title, selected_policy) \
if (global_popup.popup_flag == 0) {						\
	display_input_popup(title, selected_policy);			\
	return POLICY_RESULT_NONE;						\
}													\
else													\
	global_popup.popup_flag = 0;

#define handler_display_radio_popup(title, selected_policy, radio_text, row) \
if (global_popup.popup_flag == 0) {										\
	display_radio_popup(title, selected_policy, radio_text, row);			\
	return POLICY_RESULT_NONE;									\
}																\
else	{															\
	global_popup.popup_flag = 0;									\
	global_popup.radio_index = -1;								\
}
