#include <ansi_c.h>
#include "toolbox.h"
#include <utility.h>
#include <userint.h>
#include "utils.h"


int getFileParentDir(char *file_path, char *res_dir) {
	char drive[256], dir_path[512]; 
	
	if (!isFileAvailable(file_path)) return 0;
	
	SplitPath(file_path, drive, dir_path, NULL);
	sprintf(res_dir, "%s%s", drive, dir_path);
	return 1;
}


int runExecutableWithConfig(char *path, char *configFile) {
	char command[1024];
	if (!path) return 0;
	if (strlen(path) == 0) return 0;
	if (!FileExists(path, NULL)) return 0;
	
	if (configFile) {
		if (strlen(configFile) == 0) return 0;
		if (!FileExists(configFile, NULL)) return 0;
		
		sprintf(command, "%s \"%s\"", path, configFile);    
	} else {
		strcpy(command, path);	
	}
	
	if (LaunchExecutable(command) == 0) return 1;
	return 0;
}


int selectConfig(char *prompt, char *output) {
	char default_dir[1024];
	
	strcpy(default_dir, "");
	
	if (isFileAvailable(output)) {
		getFileParentDir(output, default_dir);		
	}
	
	return FileSelectPopup(default_dir, "*.ini", "", prompt, VAL_SELECT_BUTTON, 0, 1, 1, 0, output);
}


int selectExecutable(char *prompt, char *output) {
	char default_dir[1024];
	
	strcpy(default_dir, "");
	
	if (isFileAvailable(output)) {
		getFileParentDir(output, default_dir);		
	}

	return FileSelectPopup(default_dir, "*.exe", "", prompt, VAL_SELECT_BUTTON, 0, 1, 1, 0, output); 	
}


void openExecutableLocation(char *file_path) {
	char parent_path[512];

	if(!getFileParentDir(file_path, parent_path)) return;

	OpenDocumentInDefaultViewer(parent_path, 0);
}

void openConfigFile(char *path) {
	if (!isFileAvailable(path)) return; 
	OpenDocumentInDefaultViewer(path, 0); 	
}


int isFileAvailable(char *file_path) {
	return (strlen(file_path) != 0) && FileExists(file_path, NULL);
}


void setButtonColor(int panel, int control, int valid) {
	if (valid) {
		SetCtrlAttribute(panel, control, ATTR_CMD_BUTTON_COLOR, MakeColor(204, 255, 153));	
	} else {
		SetCtrlAttribute(panel, control, ATTR_CMD_BUTTON_COLOR, MakeColor(255, 153, 153));	
	}
}
