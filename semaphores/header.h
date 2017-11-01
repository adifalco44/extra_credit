#include <iostream>
#include "thread.h"
#include "macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>

using namespace std;
size_t N = 4;

class Friends1 {
	public:
		Friends1() {
		sem_init(&lock, 0, 1);
		sem_init(&cond, 0, 0);
		count = 0;
}

void *person_goes() {
	sem_wait(&lock);
	count++;
	int temp = count;
	cout << "Friends that have arrived: " << count << endl;
	sem_post(&lock);
	if (temp < N) {
		sem_wait(&cond);
	}
	sem_post(&cond);
}

private:
	sem_t lock;
	sem_t cond;
	size_t count;
};

