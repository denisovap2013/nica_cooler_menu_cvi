//==============================================================================
//
// Title:       HomeScreen
// Purpose:     A short description of the application.
//
// Created on:  13.06.2023 at 10:08:59 by Vasya.
// Copyright:   Laboratory of anomalous materials. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <ansi_c.h>
#include <cvirte.h>     
#include <userint.h>
#include "HomeScreen.h"
#include "toolbox.h"
#include "homescreen_config.h"
#include "menu_blocks.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

static int panelHandle;
appBlockConfig_t psmcuCfgBlock;

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions
void RegisterBlocks(void);


/// HIFN The main entry-point function.
int main (int argc, char *argv[])
{
    int error = 0;
	
    /* initialize and load resources */
    nullChk (InitCVIRTE (0, argv, 0));
    errChk (panelHandle = LoadPanel (0, "HomeScreen.uir", MAIN));
	
	RegisterBlocks();
	ReadConfiguration(CONFIG_NAME);
    
	checkAllBlocksFiles();
	
    /* display the panel and run the user interface */
    errChk (DisplayPanel (panelHandle));
    errChk (RunUserInterface ());

Error:
    /* clean up */
    DiscardPanel (panelHandle);
    return 0;
}

//==============================================================================
// UI callback function prototypes

/// HIFN Exit when the user dismisses the panel.
int CVICALLBACK panelCB (int panel, int event, void *callbackData,
        int eventData1, int eventData2)
{
    if (event == EVENT_CLOSE)
        QuitUserInterface (0);
    return 0;
}


void RegisterBlocks(void) {
	// 1. Add configuration blocks
	//    1.1 Create configuration file entries
	//    1.2 Create GUI elements
	//    1.3 Assign callbacks
	// 2. Init configuration
	// 3. Place GUI elements
	
	p_menuBlock_t p_block;
	
	InitBlocks();
	p_block = addMenuBlock(panelHandle, "POWER SUPPLIES", "PSMCU");
	positionControls(&p_block->gui, 0, 0);
}
