/*****************************************************************
|
|    AP4 - Utilities
|
|    Copyright 2002-2006 Gilles Boccon-Gibod & Julien Boeuf
|
|
|    This file is part of Bento4/AP4 (MP4 Atom Processing Library).
|
|    Unless you have obtained Bento4 under a difference license,
|    this version of Bento4 is Bento4|GPL.
|    Bento4|GPL is free software; you can redistribute it and/or modify
|    it under the terms of the GNU General Public License as published by
|    the Free Software Foundation; either version 2, or (at your option)
|    any later version.
|
|    Bento4|GPL is distributed in the hope that it will be useful,
|    but WITHOUT ANY WARRANTY; without even the implied warranty of
|    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|    GNU General Public License for more details.
|
|    You should have received a copy of the GNU General Public License
|    along with Bento4|GPL; see the file COPYING.  If not, write to the
|    Free Software Foundation, 59 Temple Place - Suite 330, Boston, MA
|    02111-1307, USA.
|
 ****************************************************************/

#ifndef _AP4_UTILS_H_
#define _AP4_UTILS_H_

/*----------------------------------------------------------------------
|   includes
+---------------------------------------------------------------------*/
#include "Ap4Config.h"
#include "Ap4Types.h"
#include "Ap4Results.h"
#include "Ap4Config.h"
#include "Ap4Atom.h"

/*----------------------------------------------------------------------
|   byte I/O
+---------------------------------------------------------------------*/
double   AP4_BytesToDoubleBE(const unsigned char* bytes);
AP4_UI64 AP4_BytesToUInt64BE(const unsigned char* bytes);
AP4_UI32 AP4_BytesToUInt32BE(const unsigned char* bytes);
AP4_UI32 AP4_BytesToUInt24BE(const unsigned char* bytes);
AP4_UI16 AP4_BytesToUInt16BE(const unsigned char* bytes);
AP4_SI32 AP4_BytesToInt32BE(const unsigned char* bytes);
AP4_SI16 AP4_BytesToInt16BE(const unsigned char* bytes);

void AP4_BytesFromDoubleBE(unsigned char* bytes, double value);
void AP4_BytesFromUInt64BE(unsigned char* bytes, AP4_UI64 value);
void AP4_BytesFromUInt32BE(unsigned char* bytes, AP4_UI32 value);
void AP4_BytesFromUInt24BE(unsigned char* bytes, AP4_UI32 value);
void AP4_BytesFromUInt16BE(unsigned char* bytes, AP4_UI16 value);
unsigned long AP4_DurationMsFromUnits(unsigned long units,
                                      unsigned long units_per_second);
unsigned long AP4_ConvertTime(unsigned long time_value,
                              unsigned long from_time_scale,
                              unsigned long to_time_scale);

/*----------------------------------------------------------------------
|   string utils
+---------------------------------------------------------------------*/
#if defined (AP4_CONFIG_HAVE_STDIO_H)
#include <stdio.h>
#endif

#if defined (AP4_CONFIG_HAVE_SNPRINTF)
#define AP4_FormatString AP4_snprintf
#else
int AP4_FormatString(char* str, AP4_Size size, const char* format, ...);
#endif
#if defined(AP4_CONFIG_HAVE_VSNPRINTF)
#define AP4_FormatStringVN(s,c,f,a) AP4_vsnprintf(s,c,f,a)
#else
extern int AP4_FormatStringVN(char *buffer, size_t count, const char *format, va_list argptr);
#endif

#if defined (AP4_CONFIG_HAVE_STRING_H)
#include <string.h>
#define AP4_StringLength(x) strlen(x)
#define AP4_CopyMemory(x,y,z) memcpy(x,y,z)
#define AP4_SetMemory(x,y,z) memset(x,y,z)
#define AP4_CompareStrings(x,y) strcmp(x,y)
#endif

void AP4_FormatFourChars(char* str, AP4_UI32 value);
void AP4_FormatFourCharsPrintable(char* str, AP4_UI32 value);
AP4_Result
AP4_ParseHex(const char* hex, unsigned char* bytes, unsigned int count);
AP4_Result
AP4_SplitArgs(char* arg, char*& arg0, char*& arg1, char*& arg2);
AP4_Result
AP4_SplitArgs(char* arg, char*& arg0, char*& arg1);

/*----------------------------------------------------------------------
|   AP4_PrintInspector
+---------------------------------------------------------------------*/
class AP4_PrintInspector : public AP4_AtomInspector {
public:
    AP4_PrintInspector(AP4_ByteStream& stream);
    ~AP4_PrintInspector();

    // methods
    void StartElement(const char* name, const char* info);
    void EndElement();
    void AddField(const char* name, AP4_UI32 value, FormatHint hint);
    void AddFieldF(const char* name, float value, FormatHint hint);
    void AddField(const char* name, const char* value, FormatHint hint);
    void AddField(const char* name, const unsigned char* bytes, AP4_Size size, FormatHint hint);

private:
    // members
    AP4_ByteStream* m_Stream;
    AP4_Cardinal    m_Indent;
};


#endif // _AP4_UTILS_H_
