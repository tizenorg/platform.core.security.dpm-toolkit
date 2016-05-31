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

enum color {
	DEFAULT	= 0,
	BLACK	= 30,
	RED		= 31,
	GREEN	= 32,
	YELLOW	= 33,
	BLUE	= 34,
	MAGENTA	= 35,
	CYAN	= 36,
	WHITE	= 37
};

enum attribute {
	NONE = 0,
	BOLD = 1
};

#define fancy_text(color, attr, fmt, ...) \
	printf("%c[%u;%um" fmt, 0x1B, attr, color, ##__VA_ARGS__)

inline void set_color(int color, int attr)
{
	printf("%c[%u;%um", 0x1B, attr, color);
}

inline void section_separator(void)
{
	fancy_text(DEFAULT, NONE, "==================================================\n");
}

inline void group_separator(void)
{
    fancy_text(DEFAULT, NONE, "--------------------------------------------------\n");
}

inline void text_header(const char* title, const char* msg)
{
	fancy_text(DEFAULT, NONE, "\n[ ");
	fancy_text(BLUE, BOLD, "%s", title);
	fancy_text(DEFAULT, NONE, " : %s ]\n", msg);
}

inline void error_message(const char *msg, int code)
{
	fancy_text(RED, BOLD, "\n%s(%d)\n", msg, code);
}

static int open_entry_popup(const char* title, const char* msg, const char* guide, char** value)
{
	text_header(title, msg);
	section_separator();
	fancy_text(DEFAULT, NONE, "Enter text(type '.' to cancel) : ");
        *value = malloc(64);
	scanf("%64s", *value);
	if (*value[0] == '.') {
		return XTK_EVENT_CANCEL;
	}

	if (*value[0] == '~') {
		return XTK_EVENT_OK;
	}

	return XTK_EVENT_OK;
}

static int open_radio_popup(const char* title, const char* text[], int nr, int* index)
{
	int i, option;

	while (1) {
		text_header(title, "Select Option");
		section_separator();
		for (i = 0; i < nr; i++) {
			fancy_text(DEFAULT, NONE, "%3d - %s\n", i, text[i]);
		}
		group_separator();
		fancy_text(DEFAULT, NONE, " -1 - Cancel\n");
		section_separator();
		fancy_text(DEFAULT, NONE, "Select item : ");
		scanf("%d", &option);
		if (option == -1) {
			return XTK_EVENT_CANCEL;
		}

		if (option < 0 || option >= i) {
			error_message("WRONG OPTION", option);
			continue;
		}

		*index = option;
		return XTK_EVENT_OK;
	}
}

static int open_message_popup(const char* title, const char* message)
{
	text_header(title, message);

	return XTK_EVENT_OK;
}

static int open_confirm_popup(const char* title, const char* message)
{
	int cont;
	text_header(title, message);
	section_separator();
	while (1) {
		fancy_text(YELLOW, NONE, "Enter 1 to continue, or -1 to cancel: ");
		scanf("%d", &cont);
		printf("\n");

		if (cont == 1) {
			return XTK_EVENT_OK;
		} if (cont == -1) {
			return XTK_EVENT_CANCEL;
		}
	}

	return 0;
}

static int xtk_cli_select_policy(xtk_policy_group_t* group)
{
	int i = 0, code, maxid;
	GList* policy_list;
	xtk_policy_t* policy_map[64];

	xtk_foreach_policy(policy_list, group) {
		xtk_policy_t* policy = glist_to_policy(policy_list);
		policy_map[i] = policy;
		i++;
	}

	maxid = i - 1;
	while (1) {
		int done = 0;
		fancy_text(DEFAULT, NONE, "\n=");
		fancy_text(BLUE, BOLD, " Policy List ");
		fancy_text(DEFAULT, NONE, "=============================\n");
		for (i = 0; i <= maxid; i++) {
			fancy_text(DEFAULT, BOLD, "%3d - %s\n", i, policy_map[i]->description);
		}
		group_separator();
		fancy_text(DEFAULT, NONE, " 99 - Back to policy group list menu\n");
		fancy_text(DEFAULT, NONE, " -1 - Exit\n");
		section_separator();

		while (!done) {
			fancy_text(YELLOW, NONE, "> Select policy to test: ");
			scanf("%d", &code);
			if ((code > maxid) && (code != 99) && (code != -1)) {
				fancy_text(RED, BOLD, "\n***INVALID POLICY ID (%d)\n", code);
				continue;
			}

			if (code == 99 || code == -1) {
				return code;
			}

			printf("Start handler\n");
			policy_map[code]->handler(policy_map[code]);
			done = 1;
		}
	}

	return 0;
}

static int xtk_cli_start_toolkit(void)
{
	int i = 0, code, maxid;
	xtk_policy_group_t* policy_group_map[16];
	GList* group_list;

	xtk_foreach_policy_group(group_list) {
		xtk_policy_group_t* group = glist_to_policy_group(group_list);
		policy_group_map[i] = group;
		i++;
	}

	maxid = i - 1;

	while (1) {
		fancy_text(DEFAULT, NONE, "\n=");
		fancy_text(BLUE, BOLD, " Device Policy Group List ");
		fancy_text(DEFAULT, NONE, "=======================\n");
		for (i = 0; i <= maxid; i++) {
			fancy_text(DEFAULT, NONE, "%3d - %s\n", i, policy_group_map[i]->id);
		}
		group_separator();
		fancy_text(DEFAULT, NONE, " -1 - Exit\n");
		section_separator();
		fancy_text(YELLOW, NONE, " > Enter policy group ID: ");
		scanf("%d", &code);
		if (code > maxid) {
			error_message("INVALID POLICY GROUP ID", code);
			continue;
		}

		if (code < 0) {
			set_color(DEFAULT, NONE);
			return 0;
		}

		if (xtk_cli_select_policy(policy_group_map[code]) == -1) {
			set_color(DEFAULT, NONE);
			return 0;
		}
	}

	return 0;
}

static xtk_context_t xtk_cli_context = {
	.entry_popup = open_entry_popup,
	.radio_popup = open_radio_popup,
	.message_popup = open_message_popup,
	.confirm_popup = open_confirm_popup
};

int xtk_cli_main(int argc, char* argv[])
{
	xtk_context_set_current(&xtk_cli_context);

	if (xtk_rebuild_policy_group(POLICY_XML_FILE_PATH) != 0) {
		dlog_print(DLOG_DEBUG, LOG_TAG, "Failed to rebuild policy group");
		xtk_free_policy_list();
		return EXIT_FAILURE;
	}

	xtk_cli_start_toolkit();

	xtk_free_policy_list();

	return EXIT_SUCCESS;
}
