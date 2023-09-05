//==============================================================================
// Include files

#include "cvidef.h"  
#include "toolbox.h"
#include "inifile.h"
#include "homescreen_config.h"


// Global variables
int cfg_blocks_num = 0;
p_appBlockConfig_t cfg_blocks[MAX_CFG_BLOCKS_NUM];
// ---------------------------------------------

// Private functions
int WriteSingleBlockConfig(IniText iniText, p_appBlockConfig_t cfg_block);
int ReadSingleBlockConfig(IniText iniText, p_appBlockConfig_t cfg_block);
// --------------------------------------------------------------------------


int readString(IniText iniText, char *section, char *key, char *default_value, char *output, int output_size) {
	char msg[512];
	if (Ini_ItemExists(iniText, section, key)) {
		if(Ini_GetStringIntoBuffer(iniText, section, key, output, output_size) <= 0) {
			sprintf(msg, "Cannot read '%s' from the '%s' section. (Line: %d)", key, section, Ini_LineOfLastAccess(iniText));
			MessagePopup("Configuration Error", (msg));
			return 0;
		}		
	} else {
		if (default_value) strcpy(output, default_value);
	}
	return 1;  // OK
}


int writeString(IniText iniText, char *section, char *key, char *string) {
	char msg[512];

	if (Ini_PutString(iniText, section, key, string) != 0) {
		sprintf(msg, "Cannot write string using the '%s' key into the '%s' section. String length: %d", key, section, strlen(string));
		MessagePopup("Configuration Error", (msg));
		return 0;
	}
	return 1;
}


void ReadConfiguration(char *configFilePath) {
	IniText iniText;
	char msg[512];
	int i;
	
	if (!FileExists(configFilePath, NULL)) return;
	
	iniText = Ini_New(0);
	if( Ini_ReadFromFile(iniText, configFilePath) < 0 ) {
		sprintf(msg, "Unable to read the configuration from the specified file: '%s'", configFilePath); 
		MessagePopup("Configuration file read error", msg);
		Ini_Dispose(iniText);
		return;
	}
	
	// Run specific readers
	for (i=0; i<cfg_blocks_num; i++) {
		ReadSingleBlockConfig(iniText, cfg_blocks[i]);	
	}

	// Close the ini file.
	Ini_Dispose(iniText);
	return;
}


void WriteConfiguration(char *configFilePath) {
	IniText iniText;
	char msg[512];
	int i;
	
	iniText = Ini_New(0);
	
	// Run specific writers
	for (i=0; i<cfg_blocks_num; i++) {
		WriteSingleBlockConfig(iniText, cfg_blocks[i]);	
	}
	
	// Write into a file
	if (Ini_WriteToFile(iniText, configFilePath) != 0) {
		sprintf(msg, "Unable to write the configuration to the specified file: '%s'", configFilePath);
		MessagePopup("Configuration file write error", msg);  	
	}
	
	// Close the ini file.
	Ini_Dispose(iniText);
	return;
}


void AddConfBlock(p_appBlockConfig_t confBlock) {
	if (cfg_blocks_num >= MAX_CFG_BLOCKS_NUM) return;
	
	memset(&confBlock->paths, 0, sizeof(appPaths_t));
	
	cfg_blocks[cfg_blocks_num] = confBlock;
	cfg_blocks_num++;
}


int WriteSingleBlockConfig(IniText iniText, p_appBlockConfig_t cfg_block) {
	appPaths_t *paths = &cfg_block->paths;

	writeString(iniText, cfg_block->section_name, TAG_SERVER_APP, paths->server_app);
	writeString(iniText, cfg_block->section_name, TAG_SERVER_CFG_1, paths->server_config_1); 
	writeString(iniText, cfg_block->section_name, TAG_SERVER_CFG_2, paths->server_config_2); 
	writeString(iniText, cfg_block->section_name, TAG_CLIENT_APP, paths->client_app);  
	writeString(iniText, cfg_block->section_name, TAG_CLIENT_CFG_1, paths->client_config_1); 
	writeString(iniText, cfg_block->section_name, TAG_CLIENT_CFG_2, paths->client_config_2);
	return 1;	
}


int ReadSingleBlockConfig(IniText iniText, p_appBlockConfig_t cfg_block) {
	appPaths_t *paths = &cfg_block->paths;

	readString(iniText, cfg_block->section_name, TAG_SERVER_APP, NULL, paths->server_app, sizeof(TPath));
	readString(iniText, cfg_block->section_name, TAG_SERVER_CFG_1, NULL, paths->server_config_1, sizeof(TPath)); 
	readString(iniText, cfg_block->section_name, TAG_SERVER_CFG_2, NULL, paths->server_config_2, sizeof(TPath)); 
	readString(iniText, cfg_block->section_name, TAG_CLIENT_APP, NULL, paths->client_app, sizeof(TPath));  
	readString(iniText, cfg_block->section_name, TAG_CLIENT_CFG_1, NULL, paths->client_config_1, sizeof(TPath)); 
	readString(iniText, cfg_block->section_name, TAG_CLIENT_CFG_2, NULL, paths->client_config_2, sizeof(TPath));
	return 1;	
}
