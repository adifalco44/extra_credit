#include "header.h"
#include <unistd.h>

using namespace std;

void *student(void *arg) {
	Friends *student_in = (Friends *) arg;
	student_in->go_inside();
}

int main() {
	Thread threads[4];
	Friends a;

	threads[0].start(student, &a);
	threads[1].start(student, &a);
	threads[2].start(student, &a);
	threads[3].start(student, &a);

	threads[0].join(NULL);
	threads[1].join(NULL);
	threads[2].join(NULL);
	threads[3].join(NULL);
	return 0;
}

