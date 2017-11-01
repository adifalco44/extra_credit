#include <pthread.h>
#include "macros.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;
const size_t MAX_CAKES = 10;
class Bakery {
	public:
		Bakery() {
			int rc;
			Pthread_mutex_init(&lock, NULL);
			Pthread_cond_init (&cond_1, NULL);
			Pthread_cond_init (&cond_2, NULL);
			ncakes = 0;
		}

		size_t available() const {
			int rc;
			Pthread_mutex_lock(&lock);
			size_t temp = ncakes;
			Pthread_mutex_unlock(&lock);
			return temp;
		}

		void bake() {
			int rc;
			Pthread_mutex_lock(&lock);
			while (ncakes == MAX_CAKES) {
				Pthread_cond_wait(&cond_1, &lock);
			}
			ncakes++;
			Pthread_cond_signal(&cond_2);
			Pthread_mutex_unlock(&lock);
		}

		void sell() {
			int rc;
			Pthread_mutex_lock(&lock);
			while (ncakes != MAX_CAKES) {
				Pthread_cond_wait(&cond_2, &lock);
			}
			ncakes --;
			Pthread_cond_signal(&cond_1);
			Pthread_mutex_unlock(&lock);
		}
	private:
		size_t ncakes;
		pthread_mutex_t lock;
		pthread_cond_t cond_1;
		pthread_cond_t cond_2;
	};

