#include <memory.h>
#include <iostream>
#include "md5bio.h"




bool CodeMD5(const char *buffer, DWORD size, DWORD digest[4]) {
	if (!buffer || !digest)return 0;
	DWORD exp = ((size + 8) / 64) * 64 + 56;
	BYTE *data = new BYTE[exp + 8];
	memcpy(data, buffer, size);
	data[size] = 0x80;
	memset(data + size + 1, 0, exp - size - 1);
	*((DWORD*)(&data[exp])) = size * sizeof(char) * 8;
	*((DWORD*)(&data[exp]) + 1) = 0;

	DWORD *M = (DWORD*)data;
	DWORD X[16];
	const int blockM = (exp + 8) / 64;

	digest[0] = dwA;
	digest[1] = dwB;
	digest[2] = dwC;
	digest[3] = dwD;

	BYTE *tmp = data;

	for (int n = 0; n < blockM; n++) {
		memcpy(X, tmp, 64);
		tmp += 64;

		DWORD A = digest[0];
		DWORD B = digest[1];
		DWORD C = digest[2];
		DWORD D = digest[3];

		/* Round 1. */

#define F(X, Y, Z) (((X) & (Y)) | ((~X) & (Z)))
#define ROTATE(x, n) (((x) << (n)) | ((x) >> (32-(n))))
#define fun1(a,b,c,d, k, s, t) a = ROTATE(a + F(b,c,d) + X[k] + t, s) + b

		fun1(A, B, C, D, 0, 7, 0xd76aa478);
		fun1(D, A, B, C, 1, 12, 0xe8c7b756);
		fun1(C, D, A, B, 2, 17, 0x242070db);
		fun1(B, C, D, A, 3, 22, 0xc1bdceee);
		fun1(A, B, C, D, 4, 7, 0xf57c0faf);
		fun1(D, A, B, C, 5, 12, 0x4787c62a);
		fun1(C, D, A, B, 6, 17, 0xa8304613);
		fun1(B, C, D, A, 7, 22, 0xfd469501);
		fun1(A, B, C, D, 8, 7, 0x698098d8);
		fun1(D, A, B, C, 9, 12, 0x8b44f7af);
		fun1(C, D, A, B, 10, 17, 0xffff5bb1);
		fun1(B, C, D, A, 11, 22, 0x895cd7be);
		fun1(A, B, C, D, 12, 7, 0x6b901122);
		fun1(D, A, B, C, 13, 12, 0xfd987193);
		fun1(C, D, A, B, 14, 17, 0xa679438e);
		fun1(B, C, D, A, 15, 22, 0x49b40821);

		/* Round 2. */

#define G(X, Y, Z) ((X) & (Z) | (Y) & (~Z))
#define fun2(a,b,c,d, k, s, t) a = b + ROTATE((a + G(b,c,d) + X[k] + t), s)

		fun2(A, B, C, D, 1, 5, 0xf61e2562);
		fun2(D, A, B, C, 6, 9, 0xc040b340);
		fun2(C, D, A, B, 11, 14, 0x265e5a51);
		fun2(B, C, D, A, 0, 20, 0xe9b6c7aa);
		fun2(A, B, C, D, 5, 5, 0xd62f105d);
		fun2(D, A, B, C, 10, 9, 0x2441453);
		fun2(C, D, A, B, 15, 14, 0xd8a1e681);
		fun2(B, C, D, A, 4, 20, 0xe7d3fbc8);
		fun2(A, B, C, D, 9, 5, 0x21e1cde6);
		fun2(D, A, B, C, 14, 9, 0xc33707d6);
		fun2(C, D, A, B, 3, 14, 0xf4d50d87);
		fun2(B, C, D, A, 8, 20, 0x455a14ed);
		fun2(A, B, C, D, 13, 5, 0xa9e3e905);
		fun2(D, A, B, C, 2, 9, 0xfcefa3f8);
		fun2(C, D, A, B, 7, 14, 0x676f02d9);
		fun2(B, C, D, A, 12, 20, 0x8d2a4c8a);

		/* Round 3. */

#define H(X, Y, Z) ((X) ^ (Y) ^ (Z))
#define fun3(a,b,c,d, k, s, t) a = b + ROTATE((a + H(b,c,d) + X[k] + t), s)

		fun3(A, B, C, D, 5, 4, 0xfffa3942);
		fun3(D, A, B, C, 8, 11, 0x8771f681);
		fun3(C, D, A, B, 11, 16, 0x6d9d6122);
		fun3(B, C, D, A, 14, 23, 0xfde5380c);
		fun3(A, B, C, D, 1, 4, 0xa4beea44);
		fun3(D, A, B, C, 4, 11, 0x4bdecfa9);
		fun3(C, D, A, B, 7, 16, 0xf6bb4b60);
		fun3(B, C, D, A, 10, 23, 0xbebfbc70);
		fun3(A, B, C, D, 13, 4, 0x289b7ec6);
		fun3(D, A, B, C, 0, 11, 0xeaa127fa);
		fun3(C, D, A, B, 3, 16, 0xd4ef3085);
		fun3(B, C, D, A, 6, 23, 0x4881d05);
		fun3(A, B, C, D, 9, 4, 0xd9d4d039);
		fun3(D, A, B, C, 12, 11, 0xe6db99e5);
		fun3(C, D, A, B, 15, 16, 0x1fa27cf8);
		fun3(B, C, D, A, 2, 23, 0xc4ac5665);

		/* Round 4. */

#define I(X, Y, Z) ((Y) ^ ((X) | (~Z)))
#define fun4(a,b,c,d, k, s, t) a = b + ROTATE((a + I(b,c,d) + X[k] + t), s)

		fun4(A, B, C, D, 0, 6, 0xf4292244);
		fun4(D, A, B, C, 7, 10, 0x432aff97);
		fun4(C, D, A, B, 14, 15, 0xab9423a7);
		fun4(B, C, D, A, 5, 21, 0xfc93a039);
		fun4(A, B, C, D, 12, 6, 0x655b59c3);
		fun4(D, A, B, C, 3, 10, 0x8f0ccc92);
		fun4(C, D, A, B, 10, 15, 0xffeff47d);
		fun4(B, C, D, A, 1, 21, 0x85845dd1);
		fun4(A, B, C, D, 8, 6, 0x6fa87e4f);
		fun4(D, A, B, C, 15, 10, 0xfe2ce6e0);
		fun4(C, D, A, B, 6, 15, 0xa3014314);
		fun4(B, C, D, A, 13, 21, 0x4e0811a1);
		fun4(A, B, C, D, 4, 6, 0xf7537e82);
		fun4(D, A, B, C, 11, 10, 0xbd3af235);
		fun4(C, D, A, B, 2, 15, 0x2ad7d2bb);
		fun4(B, C, D, A, 9, 21, 0xeb86d391);

		digest[0] += A;
		digest[1] += B;
		digest[2] += C;
		digest[3] += D;
	}
	delete data;
	return 1;
}

DWORD go_hash(const char * buffer) {
	DWORD md5[4];
	CodeMD5(buffer, sizeof(buffer) - 1, md5);
	return md5[0] & md5[1] | md5[2] & md5[3];
}
