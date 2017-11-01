#include <iostream>
#include "thread.h"
#include "macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>

using namespace std;
size_t N = 4;

class Friends {
	public:
		Friends() {
			sem_init(&lock, 0, 1);
			sem_init(&go_in, 0, 0);
			count = 0;
	}

void *go_inside() {
	sem_wait(&lock);
	count++;
	int temp = count;
	cout << "Number of friends: " << count << endl;
	sem_post(&lock);
	if (temp < N) {
		sem_wait(&go_in);
	}
	sem_post(&go_in);
}

private:
	sem_t lock;
	sem_t go_in;
	size_t count;
};

