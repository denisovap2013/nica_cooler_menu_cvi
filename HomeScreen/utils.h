#ifndef __utils_H__
#define __utils_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "cvidef.h"

typedef void (*updateFunction_t)(void);    
		

int getFileParentDir(char *file_path, char *res_dir);
int runExecutableWithConfig(char *path, char *configFile);

int selectConfig(char *prompt, char *output);
int selectExecutable(char *prompt, char *output);
int isFileAvailable(char *file_path);
void setButtonColor(int panel, int control, int valid);

void openExecutableLocation(char *path);
void openConfigFile(char *path);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __utils_H__ */
