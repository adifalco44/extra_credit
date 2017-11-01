#include "macros.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

using namespace std;
const size_t MAX_CAKES = 10;

class Bakery {
	public:
		Bakery() {
			int rc;
			Pthread_mutex_init(&lock, NULL);
			Pthread_cond_init (&sell_em, NULL);
			Pthread_cond_init (&bake_em, NULL);
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
				Pthread_cond_wait(&sell_em, &lock);
			}
			ncakes++;
			Pthread_cond_signal(&bake_em);
			Pthread_mutex_unlock(&lock);
		}

		void sell() {
			int rc;
			Pthread_mutex_lock(&lock);
			while (ncakes == 0) {
				Pthread_cond_wait(&bake_em, &lock);
			}
			ncakes--;
			Pthread_cond_signal(&sell_em);
			Pthread_mutex_unlock(&lock);
		}
	private:
		size_t ncakes;
		pthread_mutex_t lock;
		pthread_cond_t sell_em;
		pthread_cond_t bake_em;
};

