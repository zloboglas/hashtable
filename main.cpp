#include "hashtablebio.h"
#include "md5bio.h"

using namespace std;

int main() {
	hashtable H;

	H.change_capacity(4);
	
	pair<const char*, const char*> arr[3] = {
		{ "first key" , "first value" },
		{ "second key", "second value"},
		{"third key", "third value"}
	};

	for (int i = 0; i < 3; i++) {
		H.set(arr[i]);
	}

	H.change_capacity(2);

	return 0;
}
