#pragma once

typedef unsigned long DWORD;
typedef unsigned char BYTE;

static const DWORD dwA = 0x67452301;
static const DWORD dwB = 0xefcdab89;
static const DWORD dwC = 0x98badcfe;
static const DWORD dwD = 0x10325476;

bool CodeMD5(const char *buffer, DWORD size, DWORD digest[4]);

DWORD go_hash(const char* buffer);
