#include "thread.h"
#include "macros.h"
#include "header.h"
#include <iostream>
#include <pthread.h>
using namespace std;

void *baker(void *arg); 

void *seller(void *arg);

int main() {
	Thread threads[2];
	Bakery a;

	threads[0].start(baker, &a);
	threads[1].start(seller, &a);

	threads[0].join(NULL);
	threads[1].join(NULL);

	return 0;
}

void *seller(void *arg) {
	size_t cakes;
	while (true) {
		Bakery *seller = (Bakery *)arg;
		seller->sell();
		cakes = seller->available();
		cout << "Number sold: " << cakes << endl;
		usleep(99999);
	}
}

void *baker(void *arg) {
	while(true) {
		Bakery *baker = (Bakery *) arg;
		baker->bake();
		size_t cakes = baker->available();
		cout << "Number baked: " << cakes << endl;
		usleep(99999);
	}
}
