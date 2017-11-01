#include <iostream>
#include "header.h"
#include "thread.h"
#include "macros.h"
#include <pthread.h>
using namespace std;

void *baker(void *arg); 

void *seller(void *arg);

int main() {
	Thread threads[2];
	Bakery b;

	threads[0].start(baker, &b);
	threads[1].start(seller, &b);

	threads[0].join(NULL);
	threads[1].join(NULL);

	return 0;
}

void *seller(void *arg) {
	size_t cakes;
	while (true) {
		Bakery *seller = (Bakery *) arg;
		seller->sell();
		cakes = seller->available();
		cout << "Cakes sold: " << cakes << endl;
		usleep(100000);
	}
}

void *baker(void *arg) {
	while(true) {
		Bakery *baker = (Bakery *) arg;
		baker->bake();
		size_t cakes = baker->available();
		cout << "Cakes baked: " << cakes << endl;
		usleep(100000);
	}
}
