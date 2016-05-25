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
