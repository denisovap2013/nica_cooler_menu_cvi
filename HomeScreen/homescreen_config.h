#ifndef __homescreen_config_H__
#define __homescreen_config_H__

//==============================================================================
// Include files

#include "cvidef.h"
#include "inifile.h"   

#define MAX_CFG_BLOCKS_NUM 20

#define MAX_PATH_LENGTH 512
#define MAX_SECTION_NAME_LENGTH 256  
#define MAX_TAG_LENGTH 256 

#define CONFIG_NAME "homescreen_config.ini"

#define TAG_SERVER_APP "serverAppPath"
#define TAG_SERVER_CFG_1 "serverConfig_1" 
#define TAG_SERVER_CFG_2 "serverConfig_2"
#define TAG_CLIENT_APP "clientAppPath"
#define TAG_CLIENT_CFG_1 "clientConfig_1"
#define TAG_CLIENT_CFG_2 "clientConfig_2"

typedef char TPath[MAX_PATH_LENGTH];
typedef char ConfigSectionName[MAX_SECTION_NAME_LENGTH];
typedef char ConfigTagName[MAX_TAG_LENGTH];

int readString(IniText iniText, char *section, char *key, char *default_value, char *output, int output_size);
int writeString(IniText iniText, char *section, char *key, char *string);


typedef struct appPaths {
	TPath server_app;
	TPath client_app;
	TPath server_config_1;	
	TPath server_config_2;
	TPath client_config_1;	
	TPath client_config_2;		
} appPaths_t;


typedef struct appBlockConfig {
	ConfigSectionName section_name;
	appPaths_t paths;
} appBlockConfig_t, *p_appBlockConfig_t;

extern int cfg_blocks_num;
extern p_appBlockConfig_t cfg_blocks[MAX_CFG_BLOCKS_NUM];


// Main config structure

void ReadConfiguration(char *configFilePath);
void WriteConfiguration(char *configFilePath);
void AddConfBlock(p_appBlockConfig_t confBlock);


#endif  /* ndef __homescreen_config_H__ */
