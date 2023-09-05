#include "utils.h"  
#include "menu_blocks.h"

int menuBlocksNum;
menuBlock_t menu_blocks[MAX_CFG_BLOCKS_NUM]; 


void InitBlocks(void) {
	menuBlocksNum = 0;
	memset(menu_blocks, 0, sizeof(menu_blocks));
}


p_menuBlock_t addMenuBlock(
	int panel,
	BlockName name,
	ConfigSectionName section
) {
	p_menuBlock_t p_block;
	appGuiElements_t *gui;

	if (menuBlocksNum >= MAX_CFG_BLOCKS_NUM) return 0;

	p_block = &menu_blocks[menuBlocksNum++];
	
	// Fill config entries info
	strcpy(p_block->config.section_name, section);
	AddConfBlock(&p_block->config);
	
	// Create GUI elements
	gui = &p_block->gui;
	gui->panel = panel;
	gui->frame = NewCtrl(panel, CTRL_RECESSED_NARROW_FRAME, "", 0, 0);
	gui->frame_caption = NewCtrl(panel, CTRL_TEXT_MSG, name, 0, 0);

	// App run buttons
	M_MAKE_BTN(panel, "Server 1", gui->server1_run_btn);
	M_MAKE_BTN(panel, "Server 2", gui->server2_run_btn);
	M_MAKE_BTN(panel, "Client 1", gui->client1_run_btn);
	M_MAKE_BTN(panel, "Client 2", gui->client2_run_btn);

	M_SET_SIZE(panel, gui->server1_run_btn, M_RUN_BTN_H, M_RUN_BTN_W);
	M_SET_SIZE(panel, gui->server2_run_btn, M_RUN_BTN_H, M_RUN_BTN_W);
	M_SET_SIZE(panel, gui->client1_run_btn, M_RUN_BTN_H, M_RUN_BTN_W);
	M_SET_SIZE(panel, gui->client2_run_btn, M_RUN_BTN_H, M_RUN_BTN_W);
	
	M_SET_BTN_COLOR(panel, gui->server1_run_btn, M_COLOR_INVALID);
	M_SET_BTN_COLOR(panel, gui->server2_run_btn, M_COLOR_INVALID);
	M_SET_BTN_COLOR(panel, gui->client1_run_btn, M_COLOR_INVALID);
	M_SET_BTN_COLOR(panel, gui->client2_run_btn, M_COLOR_INVALID);
	
	// Config selection buttons
	M_MAKE_BTN(panel, "Config", gui->server1_cfg_btn);
	M_MAKE_BTN(panel, "Config", gui->server2_cfg_btn);
	M_MAKE_BTN(panel, "Config", gui->client1_cfg_btn);
	M_MAKE_BTN(panel, "Config", gui->client2_cfg_btn);
	
	M_SET_SIZE(panel, gui->server1_cfg_btn, M_CFG_BTN_H, M_CFG_BTN_W);
	M_SET_SIZE(panel, gui->server2_cfg_btn, M_CFG_BTN_H, M_CFG_BTN_W);
	M_SET_SIZE(panel, gui->client1_cfg_btn, M_CFG_BTN_H, M_CFG_BTN_W);
	M_SET_SIZE(panel, gui->client2_cfg_btn, M_CFG_BTN_H, M_CFG_BTN_W);
	
	M_SET_BTN_COLOR(panel, gui->server1_cfg_btn, M_COLOR_INVALID);
	M_SET_BTN_COLOR(panel, gui->server2_cfg_btn, M_COLOR_INVALID);
	M_SET_BTN_COLOR(panel, gui->client1_cfg_btn, M_COLOR_INVALID);
	M_SET_BTN_COLOR(panel, gui->client2_cfg_btn, M_COLOR_INVALID);
	
	// App path selection buttons
	M_MAKE_BTN(panel, "Server path", gui->server_path_btn);
	M_MAKE_BTN(panel, "Client path", gui->client_path_btn);
	
	M_SET_SIZE(panel, gui->server_path_btn, M_APP_BTN_H, M_APP_BTN_W);
	M_SET_SIZE(panel, gui->client_path_btn, M_APP_BTN_H, M_APP_BTN_W);

	M_SET_BTN_COLOR(panel, gui->server_path_btn, M_COLOR_INVALID);
	M_SET_BTN_COLOR(panel, gui->client_path_btn, M_COLOR_INVALID);
	
	// Set callbacks
	InstallCtrlCallback(panel, gui->server1_run_btn, menuCallbackRunApp, p_block);
	InstallCtrlCallback(panel, gui->server2_run_btn, menuCallbackRunApp, p_block);
	InstallCtrlCallback(panel, gui->client1_run_btn, menuCallbackRunApp, p_block);
	InstallCtrlCallback(panel, gui->client2_run_btn, menuCallbackRunApp, p_block);
	
	InstallCtrlCallback(panel, gui->server1_cfg_btn, menuCallbackSetConfig, p_block);
	InstallCtrlCallback(panel, gui->server2_cfg_btn, menuCallbackSetConfig, p_block);
	InstallCtrlCallback(panel, gui->client1_cfg_btn, menuCallbackSetConfig, p_block);
	InstallCtrlCallback(panel, gui->client2_cfg_btn, menuCallbackSetConfig, p_block);
	
	InstallCtrlCallback(panel, gui->server_path_btn, menuCallbackSetAppPath, p_block);
	InstallCtrlCallback(panel, gui->client_path_btn, menuCallbackSetAppPath, p_block);

	return p_block;
}


void positionControls(appGuiElements_t *gui, int top, int left) {
	int x, y, panel;
	
	panel = gui->panel;
	
	M_SET_POSE(panel, gui->frame, top + M_BLOCK_PAD_H, left + M_BLOCK_PAD_W);
	M_SET_POSE(panel, gui->frame_caption, top + M_BLOCK_PAD_H - 6, left + M_BLOCK_PAD_W + 14);
	M_SET_SIZE(panel, gui->frame, M_BLOCK_SIZE_H - 2*M_BLOCK_PAD_H, M_BLOCK_SIZE_W - 2*M_BLOCK_PAD_W);
	
	x = left + M_BLOCK_PAD_W + M_BLOCK_MARGIN_W;
	y = top + M_BLOCK_PAD_H + M_BLOCK_MARGIN_H;
	
	M_SET_POSE(panel, gui->server1_run_btn, y, x + (M_RUN_BTN_W + M_BTN_SPACE_W) * 0);
	M_SET_POSE(panel, gui->server2_run_btn, y, x + (M_RUN_BTN_W + M_BTN_SPACE_W) * 1);
	M_SET_POSE(panel, gui->client1_run_btn, y, x + (M_RUN_BTN_W + M_BTN_SPACE_W) * 2);
	M_SET_POSE(panel, gui->client2_run_btn, y, x + (M_RUN_BTN_W + M_BTN_SPACE_W) * 3);
	
	y += M_RUN_BTN_H + M_BTN_SPACE_H;
	M_SET_POSE(panel, gui->server1_cfg_btn, y, x + (M_CFG_BTN_W + M_BTN_SPACE_W) * 0);
	M_SET_POSE(panel, gui->server2_cfg_btn, y, x + (M_CFG_BTN_W + M_BTN_SPACE_W) * 1);
	M_SET_POSE(panel, gui->client1_cfg_btn, y, x + (M_CFG_BTN_W + M_BTN_SPACE_W) * 2);
	M_SET_POSE(panel, gui->client2_cfg_btn, y, x + (M_CFG_BTN_W + M_BTN_SPACE_W) * 3);
	
	y += M_CFG_BTN_H + M_BTN_SPACE_H;
	M_SET_POSE(panel, gui->server_path_btn, y, x + (M_APP_BTN_W + M_BTN_SPACE_W) * 0);
	M_SET_POSE(panel, gui->client_path_btn, y, x + (M_APP_BTN_W + M_BTN_SPACE_W) * 1);
}


void checkBlockFiles(p_menuBlock_t block) {
	int server_app_available, client_app_available;
	int sconf1_available, sconf2_available;
	int cconf1_available, cconf2_available;
	
	appPaths_t *paths;
	appGuiElements_t *gui;
	
	paths = &block->config.paths;
	gui = &block->gui;

	cconf1_available = isFileAvailable(paths->client_config_1);
	cconf2_available = isFileAvailable(paths->client_config_2);
	sconf1_available = isFileAvailable(paths->server_config_1);
	sconf2_available = isFileAvailable(paths->server_config_2);
	
	server_app_available = isFileAvailable(paths->server_app);
	client_app_available = isFileAvailable(paths->client_app);
	
	setButtonColor(gui->panel, gui->server1_run_btn, server_app_available && sconf1_available);
	setButtonColor(gui->panel, gui->server2_run_btn, server_app_available && sconf2_available);
	setButtonColor(gui->panel, gui->client1_run_btn, client_app_available && cconf1_available);
	setButtonColor(gui->panel, gui->client2_run_btn, client_app_available && cconf2_available);

	setButtonColor(gui->panel, gui->server1_cfg_btn, sconf1_available); 
	setButtonColor(gui->panel, gui->server2_cfg_btn, sconf2_available);
	setButtonColor(gui->panel, gui->client1_cfg_btn, cconf1_available); 
	setButtonColor(gui->panel, gui->client2_cfg_btn, cconf2_available);
	
	setButtonColor(gui->panel, gui->server_path_btn, server_app_available); 
	setButtonColor(gui->panel, gui->client_path_btn, client_app_available);
}


void checkAllBlocksFiles(void) {
	int i;
	
	for (i=0; i < menuBlocksNum; i++) {
		checkBlockFiles(&menu_blocks[i]);		
	}
}


// =====================
// ====  Callbacks  ====
// =====================

int CVICALLBACK menuCallbackRunApp (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	p_menuBlock_t block;
	appGuiElements_t *gui;
	appPaths_t *paths;
	
	switch (event)
	{
		case EVENT_COMMIT:
			block = callbackData;
			gui = &block->gui;
			paths = &block->config.paths;
			
			if      (control == gui->server1_run_btn) runExecutableWithConfig(paths->server_app, paths->server_config_1);
			else if (control == gui->server2_run_btn) runExecutableWithConfig(paths->server_app, paths->server_config_2); 	
			else if (control == gui->client1_run_btn) runExecutableWithConfig(paths->client_app, paths->client_config_1); 	
			else if (control == gui->client2_run_btn) runExecutableWithConfig(paths->client_app, paths->client_config_2);	
			else break;	

			checkBlockFiles(block);
			break;
	}
	return 0;
}


int CVICALLBACK menuCallbackSetAppPath (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int res;
	p_menuBlock_t block;
	appGuiElements_t *gui;
	appPaths_t *paths;
	
	switch (event)
	{
		case EVENT_COMMIT:
			
			block = callbackData;
			gui = &block->gui;
			paths = &block->config.paths;
			
			if      (control == gui->server_path_btn) res = selectExecutable("Select the PSMCU Server application path", paths->server_app);  	
			else if (control == gui->client_path_btn) res = selectExecutable("Select the PSMCU Client application path", paths->client_app);
			else break;	

			if (res) {
				WriteConfiguration(CONFIG_NAME);	
			}
			checkBlockFiles(block);
			break;

		case EVENT_RIGHT_DOUBLE_CLICK:
			block = callbackData;
			gui = &block->gui;
			paths = &block->config.paths;

			if      (control == gui->server_path_btn) openExecutableLocation(paths->server_app);    	
			else if (control == gui->client_path_btn) openExecutableLocation(paths->client_app);  
			else break;	

			checkBlockFiles(block);
			break; 
	}
	return 0;
}


int CVICALLBACK menuCallbackSetConfig (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int res;
	p_menuBlock_t block;
	appGuiElements_t *gui;
	appPaths_t *paths;

	switch (event)
	{
		case EVENT_COMMIT:
			block = callbackData;
			gui = &block->gui;
			paths = &block->config.paths;
			
			if      (control == gui->server1_cfg_btn) res = selectConfig("Select the PSMCU Server 1 configuration", paths->server_config_1);
			else if (control == gui->server2_cfg_btn) res = selectConfig("Select the PSMCU Server 2 configuration", paths->server_config_2); 	
			else if (control == gui->client1_cfg_btn) res = selectConfig("Select the PSMCU Client 1 configuration", paths->client_config_1);	
			else if (control == gui->client2_cfg_btn) res = selectConfig("Select the PSMCU Client 2 configuration", paths->client_config_2);
			else break;	
	
			if (res) WriteConfiguration(CONFIG_NAME);	
			checkBlockFiles(block);
			break;

		case EVENT_RIGHT_DOUBLE_CLICK:
			block = callbackData;
			gui = &block->gui;
			paths = &block->config.paths;
			
			if      (control == gui->server1_cfg_btn) openConfigFile(paths->server_config_1);
			else if (control == gui->server2_cfg_btn) openConfigFile(paths->server_config_2); 	
			else if (control == gui->client1_cfg_btn) openConfigFile(paths->client_config_1);	
			else if (control == gui->client2_cfg_btn) openConfigFile(paths->client_config_2); 
			else break;	

			checkBlockFiles(block);
			break;
	}
	return 0;
}
