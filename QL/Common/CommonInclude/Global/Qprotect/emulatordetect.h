/*
**  $FileName: emulatordetect.h $
**  Copyright (C) 2017, SafeNet, Inc. All rights reserved.
*/

#ifndef EMULATORDETECT_H
#define EMULATORDETECT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#if defined(__cplusplus)
extern "C"
{
#endif /* #if defined(__cplusplus) */

// Detect whether exists emulator in current process or not.
// If the function succeeds, the output detect_status indicates whether there exists emulator
// or not.
//
// INPUT
//   vendor_code: vendor code for accessing Sentinel HL/SL key
//   scope: scope used to search for Sentinel HL/SL key
//
// OUTPUT
//   detect_status: 0 indicates that an emulator was not found;
//                  Any other value indicates that an emulator was detected.
//
// RETURN
//   0 means the function succeeded. Check value of out parameter detect_status for further details;
//   Any other values means the function failed. The function fails if no Sentinel HL or SL key is attached.
//
int detect_emulator(const void *vendor_code, const char *scope, int *detect_status);

#if defined(__cplusplus)
}
#endif /* #if defined(__cplusplus) */

#endif /* #ifndef EMULATORDETECT_H */

