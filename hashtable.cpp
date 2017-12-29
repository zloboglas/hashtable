#include "hashtablebio.h"
#include "md5bio.h"

hashtable::hashtable() {
	pair<const char*, const char*>* arr = new pair<const char*, const char*>[bucket_size];
	arr_ptr = arr;
}

hashtable::~hashtable() {
	delete arr_ptr;
}

void hashtable::set(pair<const char*, const char*> input) {
	int intenger = go_hash(input.first) % bucket_size;
	arr_ptr[intenger] = input;
}

const char * hashtable::get(char * key) {
	int intenger = go_hash(key) % bucket_size;
	return arr_ptr[intenger].second;
}

void hashtable::change_capacity(int new_bucket_size) {
	pair<const char*, const char*>* new_arr = new pair<const char*, const char*>[new_bucket_size];
	for (int i = 0; i < bucket_size; i++) {
		int intenger = go_hash(arr_ptr[i].first) % new_bucket_size;
		new_arr[intenger] = arr_ptr[i];
	}
	delete arr_ptr;
	arr_ptr = new_arr;
	bucket_size = new_bucket_size;

}
