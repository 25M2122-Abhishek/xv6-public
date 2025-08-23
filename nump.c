#include "types.h"
#include "stat.h"
#include "user.h"

#define SHORT_LOOP 10
#define LONG_LOOP  100
#define LONGEST_LOOP 1000

void busy_loop(int n)
{
    int i;
    for (i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
         {
    	    int*a =malloc(sizeof(int));
            *a=i*j;
            free(a);
         } // Simulate some busy work
    }
}

int main(void) {
    int pid1 = fork();
    if (pid1 == 0)
    {
        // Child process 1

        busy_loop(SHORT_LOOP); 
        exit();
    }
    else if(fork()==0)
    {
        // Child process 2
        busy_loop(LONG_LOOP); 
        exit();
    }
    else if(fork()==0)
    {
        // Child process 3
        busy_loop(LONGEST_LOOP);
        exit();
    }

    // Parent process
    int n1 = numberofreadyprocesses();

    wait(); // Wait for child 1
    int n2 = numberofreadyprocesses();

    wait(); // Wait for child 2
    int n3= numberofreadyprocesses();

    wait(); // Wait for child 3
    int n4= numberofreadyprocesses();

    printf(1, "ready processes: %d\n", n1);
    printf(1, "ready processes: %d\n", n2);
    printf(1, "ready processes: %d\n", n3);
    printf(1, "ready processes: %d\n", n4);

    exit();
}
