//written in C99
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

#define BUFFER_SIZE 40

int map[50][50] = {0};
void valid (int turn, int current_x, int current_y, int *next_x, int *next_y);
int run (int *turn, int last_x, int last_y, int *x, int *y);

const int child_win = 2;
const int parent_win = 3;

int main (int argc, char* argv[]) 
{
    char *buf;
    int fd;
    pid_t cpid;

    int turn = 0;
    char file[20];

    int x, y;
    int last_x, last_y;

    srand(time(NULL));
    x = rand() % 50;
    y = rand() % 50;

    map[x][y] = 2; //parent first


	int shm_id = shmget(IPC_PRIVATE, BUFFER_SIZE, 0666);
	if (shm_id < 0)
	{
		perror("shmget");
		exit(1);
	}

    cpid = fork();
    if ( cpid < 0 ) {
        perror("Fork failed.");
        return -1;
    } else if ( cpid == 0 ) {         
        sprintf(file, "%u_SHM.txt", getpid());
        freopen(file, "w", stdout);
        puts("1");
    }
    else { //parent first
        buf = (char *)shmat(shm_id, 0, 0);
        if (buf < (char*)0)
        {
            perror("shmat");
            exit(1);
        }

        sprintf(buf, "%d %d %d", turn, x, y);
        shmdt(buf);

        sprintf(file, "%u_SHM.txt", getpid());
        freopen(file, "w", stdout);
        puts("0");
    }

    // game start!
    while (turn < 2) 
    {
        buf = (char *)shmat(shm_id, 0, 0);
        if (buf < (char*)0)
        {
            perror("shmat");
            exit(1);
        }

        sscanf(buf, "%d%d%d", &turn, &last_x, &last_y);
        shmdt(buf);

        x = last_x;
        y = last_y;

        if (cpid == 0) 
        {
            if (turn == 0)  // child's turn
            {      
                run(&turn, last_x, last_y, &x, &y);

                buf = (char *)shmat(shm_id, 0, 0);
                if (buf < (char*)0)
                {
                    perror("shmat");
                    exit(1);
                }

                sprintf(buf, "%d %d %d", turn, x, y);
                shmdt(buf);

                if (turn >= 2) break;
            }
        }
        else 
        {
            if (turn == 1)  // parent's turn 
            {      
                run(&turn, last_x, last_y, &x, &y);

                buf = (char *)shmat(shm_id, 0, 0);
                if (buf < (char*)0)
                {
                    perror("shmat");
                    exit(1);
                }
                sprintf(buf, "%d %d %d", turn, x, y);
                shmdt(buf);

                if (turn >= 2) break;
            }
        }
    }

    if (cpid == 0) printf("%c\n", turn == child_win ? '1' : '0'); 
    else printf("%c\n", turn == parent_win ? '1' : '0');

    if (turn >= 2 && cpid != 0)
    {
        if (shmctl(shm_id, IPC_RMID, 0) !=0)
        {
            perror("shmctl IPC_RMID");
        }
    }

    return 0;
}


int run (int *turn, int last_x, int last_y, int *x, int *y) 
{
    valid(*turn, last_x, last_y, x, y);

    if (*x == -1 && *y == -1) 
        *turn = *turn ? child_win : parent_win;
    else 
    {
        *turn = 1 - *turn; //exchange turn
        printf("%d %d\n", *x, *y);
    }
}


void valid (int turn, int current_x, int current_y, int *next_x, int *next_y) 
{
    int dir[4][2] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

    int x, y;
    *next_x = -1;
    *next_y = -1;

    //find path
    for (int d = 0; d < 4; d++) 
    {
        x = current_x + dir[d][0];
        y = current_y + dir[d][1];

        if (0 <= x && x < 50 &&
            0 <= y && y < 50 &&
            map[x][y] == 0) 
        {
            *next_x = x;
            *next_y = y;
            map[x][y] = turn + 1;
            break;
        }
    }
}

