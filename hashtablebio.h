#pragma once
#include <iostream>
#include <vector>
#include "md5bio.h"

using namespace std;

class hashtable {
	int bucket_size = 256;
	pair<const char*, const char*>* arr_ptr;
public:
	hashtable();
	~hashtable();
	void set(pair<const char*, const char*> input);
	const char* get(char* key);
	void change_capacity(int new_bucket_size);
};



