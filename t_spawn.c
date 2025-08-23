#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf(1, "Usage: %s <program> [arguments...]\n", argv[0]);
        exit();
    }

    int n = atoi(argv[1]);
    int pids[n];
    memset(pids, 0, sizeof(pids));

    printf(1, "Value of n read in user space %d and address is %d \n", n, &n);
    printf(1, "Address of pids read in user space %d \n", pids);

    printf(1, "Spawn starting\n");
    int num_child = spawn(n, pids);

    if (num_child < 0)
    {
        printf(1, "Spawn failed\n");
        exit();
    }
    else if (num_child == 0)
    {
        // Child process
        printf(1, "Hi from spawned child with pid %d\n", getpid());
        exit();
    }
    else
    {
        for (int i = 0; i < num_child; i++)
        {
            int cpid = wait();
            printf(1, "Parent reaped children with id %d successfully\n", cpid);
        }
        printf(1, "Child PID list at address %d:\n", pids);
        for (int i = 0; i < num_child; i++)
        {
            printf(1, "%d\n", pids[i]);
        }
        printf(1, "\n");
        printf(1, "Number child spawned: %d\n", num_child);
    }

    exit();
}