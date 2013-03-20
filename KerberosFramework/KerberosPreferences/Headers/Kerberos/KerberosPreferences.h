/* $Copyright:
 *
 * Copyright � 2000 by the Massachusetts Institute of Technology.
 * 
 * All rights reserved.
 * 
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appear in all copies and that
 * both that copyright notice and this permission notice appear in
 * supporting documentation, and that the name of M.I.T. not be used in
 * advertising or publicity pertaining to distribution of the software
 * without specific, written prior permission.  Furthermore if you modify
 * this software you must label your software as modified software and not
 * distribute it in such a fashion that it might be confused with the
 * original MIT software. M.I.T. makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 * 
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * Individual source code files are copyright MIT, Cygnus Support,
 * OpenVision, Oracle, Sun Soft, FundsXpress, and others.
 * 
 * Project Athena, Athena, Athena MUSE, Discuss, Hesiod, Kerberos, Moira,
 * and Zephyr are trademarks of the Massachusetts Institute of Technology
 * (MIT).  No commercial use of these trademarks may be made without prior
 * written permission of MIT.
 * 
 * "Commercial use" means use of a name in a product or other for-profit
 * manner.  It does NOT prevent a commercial firm from referring to the MIT
 * trademarks in order to convey information (although in doing so,
 * recognition of their trademark status should be given).
 * $
 */

/* $Header: /cvs/kfm/KerberosFramework/KerberosPreferences/Headers/Kerberos/KerberosPreferences.h,v 1.12 2003/03/19 21:19:23 lxs Exp $ */

/* 
 *
 * PreferenceLib.h -- Functions to handle Kerberos Preference file access.
 *
 */


#ifndef __KERBEROSPREFERENCES__
#define __KERBEROSPREFERENCES__

#if defined(macintosh) || (defined(__MACH__) && defined(__APPLE__))
	#include <TargetConditionals.h>
    #if TARGET_RT_MAC_CFM
        #error "Use KfM 4.0 SDK headers for CFM compilation."
    #endif
#endif

#include <CoreServices/CoreServices.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__MWERKS__)
    #pragma import on
#endif

/* ************************************************ */
/* Locations for where to look for preference files */
/* ************************************************ */
enum
{
	kpUserPreferences				= 0x00000001,
	kpSystemPreferences				= 0x00000002
};

/* ********************** */
/* Name, Creator and Type */
/* ********************** */

#define kerberosPreferences_FileType	FOUR_CHAR_CODE ('pref')
#define kerberosPreferences_Creator		FOUR_CHAR_CODE ('Krb ')
#define kerberosPreferences_FileName	"\pKerberos Preferences"

/* ******************* */
/* Function prototypes */
/* ******************* */

/* ********************************************************* */
/* Creates a valid preference file at the location specified */
/* ********************************************************* */
OSErr KPInitializeWithDefaultKerberosLibraryPreferences (
	const FSSpec* prefLocation);

/* ****************************************************************************** */
/* File the array with list of preferences that match the options provided        */
/* ****************************************************************************** */
OSErr KPGetListOfPreferencesFiles (
	UInt32 userSystemFlags,
	FSSpecPtr* thePrefFiles,
	UInt32* outNumberOfFiles);

/* ********************************************************* */
/* Free the array containing the list of preference files    */
/* ********************************************************* */
void KPFreeListOfPreferencesFiles (
	FSSpecPtr thePrefFiles);

/* ********************************************************* */
/* Check if file exists and is readable                      */
/* ********************************************************* */
OSErr KPPreferencesFileIsReadable (
	const FSSpec*	inPrefsFile);

/* ********************************************************* */
/* Check if file is writable                                 */
/* ********************************************************* */
OSErr KPPreferencesFileIsWritable (
	const FSSpec*	inPrefsFile);

/* ********************************************************* */
/* Create an empty file                                      */
/* ********************************************************* */
OSErr KPCreatePreferencesFile (
	const FSSpec*	inPrefsFile);


#if defined(__MWERKS__)
    #pragma import reset
#endif

#ifdef __cplusplus
}
#endif

#endif /* __KERBEROSPREFERENCES__ */
