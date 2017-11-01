#include "header.h"
#include <unistd.h>

using namespace std;

void *student(void *arg) {
	Friends1 *student_goes = (Friends1 *) arg;
	student_goes->person_goes();
}

int main() {
	Thread threads[4];
	Friends1 f;

	threads[0].start(student, &f);
	threads[1].start(student, &f);
	threads[2].start(student, &f);
	threads[3].start(student, &f);

	threads[0].join(NULL);
	threads[1].join(NULL);
	threads[2].join(NULL);
	threads[3].join(NULL);
	return 0;
}

