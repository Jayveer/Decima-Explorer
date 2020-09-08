#pragma once

#include "targetver.h"

#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>
#include <string.h>
#include <intrin.h>
#include <assert.h>
#include <Windows.h>

#pragma warning (disable: 4244)

typedef unsigned char byte;
typedef unsigned char uint8;
typedef unsigned int uint32;
typedef unsigned __int64 uint64;
typedef signed __int64 int64;
typedef signed int int32;
typedef unsigned short uint16;
typedef signed short int16;
typedef unsigned int uint;

int Kraken_Decompress(const byte *src, size_t src_len, byte *dst, size_t dst_len);
int Kraken_Decompress_DLL(uint8* src, size_t src_len, byte* dst, size_t dst_len);
int Kraken_Compress(uint8* src, size_t src_len, byte* dst);