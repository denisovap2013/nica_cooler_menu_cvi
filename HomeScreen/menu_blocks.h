#ifndef __menu_blocks_H__
#define __menu_blocks_H__

#include "cvidef.h"
#include "homescreen_config.h"


#define MAX_BLOCK_NAME_LENGTH 128
#define M_RUN_BTN_H 42
#define M_RUN_BTN_W 55
#define M_CFG_BTN_H 18
#define M_CFG_BTN_W 55
#define M_APP_BTN_H 18
#define M_APP_BTN_W 111
#define M_BTN_SPACE_H 1
#define M_BTN_SPACE_W 1
#define M_BLOCK_PAD_W 12
#define M_BLOCK_PAD_H 12
#define M_BLOCK_MARGIN_W 12
#define M_BLOCK_MARGIN_H 14

#define M_BLOCK_SIZE_W M_BLOCK_PAD_W*2 + M_BLOCK_MARGIN_W*2 + M_RUN_BTN_W*4 + M_BTN_SPACE_W*3 
#define M_BLOCK_SIZE_H M_BLOCK_PAD_H*2 + M_BLOCK_MARGIN_H*2 + M_RUN_BTN_H + M_CFG_BTN_H + M_APP_BTN_H + M_BTN_SPACE_H*2  

#define M_COLOR_VALID MakeColor(204, 255, 153)
#define M_COLOR_INVALID MakeColor(255, 153, 153)

typedef char BlockName[MAX_BLOCK_NAME_LENGTH];


typedef struct appGuiElements{
	int panel;

	int server1_run_btn;
	int server2_run_btn;
	int client1_run_btn;
	int client2_run_btn;
	
	int server_path_btn;
	int client_path_btn;
	
	int server1_cfg_btn;
	int server2_cfg_btn;
	int client1_cfg_btn;
	int client2_cfg_btn;
	
	int frame;
	int frame_caption;
} appGuiElements_t;


typedef struct menuBlock {
	appGuiElements_t gui;
	appBlockConfig_t config;
} menuBlock_t, *p_menuBlock_t;


extern int menuBlocksNum;
extern menuBlock_t menu_blocks[MAX_CFG_BLOCKS_NUM]; 


// Functions
void InitBlocks(void);


p_menuBlock_t addMenuBlock(
	int panel,
	BlockName name,
	ConfigSectionName section
);

void positionControls(appGuiElements_t *gui, int top, int left);
void checkBlockFiles(p_menuBlock_t block);
void checkAllBlocksFiles(void);

int  CVICALLBACK menuCallbackRunApp(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK menuCallbackSetAppPath(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK menuCallbackSetConfig(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);

#define M_MAKE_BTN(panel, name, res_id) {(res_id) = NewCtrl((panel), CTRL_SQUARE_COMMAND_BUTTON_LS, (name), 0, 0); SetCtrlAttribute((panel),(res_id), ATTR_AUTO_SIZING, VAL_NEVER_AUTO_SIZE);}
#define M_SET_SIZE(panel, elem_id, elem_h, elem_w) {SetCtrlAttribute((panel), (elem_id), ATTR_HEIGHT, (elem_h)); SetCtrlAttribute((panel), (elem_id), ATTR_WIDTH, (elem_w));}
#define M_SET_POSE(panel, elem_id, top, left) {SetCtrlAttribute((panel), (elem_id), ATTR_TOP, (top)); SetCtrlAttribute((panel), (elem_id), ATTR_LEFT, (left));}
#define M_SET_BTN_COLOR(panel, elem_id, color) SetCtrlAttribute((panel), (elem_id), ATTR_CMD_BUTTON_COLOR, (color))

#endif  /* ndef __menu_blocks_H__ */
