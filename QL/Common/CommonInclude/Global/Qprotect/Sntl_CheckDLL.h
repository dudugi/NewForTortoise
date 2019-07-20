#ifndef _EMULATOR_H
#define _EMULATOR_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef __cplusplus
extern "C" {
#endif

enum EmulatorDetectResultType{
    EMULATOR_NOT_FOUND = 0,      //emulator not found
    EMULATOR_FOUND,              //emulator has been found
    INTERNAL_ERROR               //internal error
};

/*Return Value: EMULATOR_NOT_FOUND - emulator not found
EMULATOR_FOUND - emulator has been found
INTERNAL_ERROR - internal error
*/
int SntlCheckDLL(char* dll_list);

#ifdef __cplusplus
}
#endif   //__cplusplus

#endif   //_EMULATOR_H