#include <stdio.h>
#include <string.h>

/* define chessboard size */
#define ROW  15
#define COL  15

/* define how many chess win */
#define N  5

#define printf(fmt, args...)    fprintf(stderr, fmt, ##args)

struct dir_struct
{
	int dx;		// row diff
	int dy;		// col diff
	char name[16];	// name of dir
};

struct dir_struct dirs[8] =
{
	{0, 1, "right"},
	{0, -1, "left"},
	{-1, 0, "up"},
	{1, 0, "down"},
	{-1, 1, "right_up"},	
	{1, -1, "left_down"},
	{-1, -1, "left_up"},
	{1, 1, "right_down"},
};

int board[ROW][COL] = {{0} };

void print_board(void)
{
	int i, j;

	printf("\n");
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
			printf("%d ", board[i][j]);

		printf("\n");
	}
	printf("\n");

	return;
}

void get(int* x_addr, int* y_addr)
{
	printf("man please input x y : ");
	scanf("%d %d", x_addr, y_addr);
}

int is_onboard(int x, int y)
{
	if (x < 0 || x >=ROW || y < 0 || y >= COL)
		return 0;

	return 1;
}

int is_empty(int x, int y)
{
	if (board[x][y] != 0)
		return 0;

	return 1;
}

void put(int x, int y, int who)
{
	board[x][y] = who;

	return;
}

int count(int x, int y, struct dir_struct onedir)
{
	int counter = 0;

	// get current x and y to nextx & nexty
	int nx = x, ny = y;

	int i;
	for (counter = 0, i = 0; i < 4; i++) 
	{
		// get next x & y in onedir
		nx += onedir.dx;
		ny += onedir.dy;

		if (!is_onboard(x, y))
			break;

		if (board[nx][ny] != board[x][y])
			break;

		counter++;
	}

	return counter;
}

int check(int x, int y)
{
	int i = 0;

	/* judge if there is 5-chess in a line */
	for (i = 0; i < 4; i++)
	{
		int counter1;
		int counter2;

		counter1 = count(x, y, dirs[i*2]);
		counter2 = count(x, y, dirs[i*2+1]);

		if (counter1 + counter2 + 1 >= N)
		{
			printf("%s: %d, %s: %d\n", dirs[i*2].name, counter1, dirs[i*2+1].name,  counter2);
			return 1;
		}
	}

	return 0;
}

int think(int *x, int *y)
{
	printf("machine is thinking x y ...\n");
	/* random position */
	do {
		*x = rand() % ROW;
		*y = rand() % ROW;
	} while (!is_empty(*x, *y));

	return 0;
}

int main(int argc, char * argv[])
{
	int x = 4;
	int y = 5;
	int who = 0;
	int step = 0;

	char logfile[64];
	char buf[64];

	int oldx = -1;
	int oldy = -1;

	FILE * fd;

        if (argc < 2)
        {
		strcpy(logfile, "m.log");
        }
	else
		strcpy(logfile, argv[1]);

	printf("Hello, chess board!\n");
	printf("logfile is %s\n", logfile);

	fd = fopen(logfile, "r");

	print_board();

	while (1)
	{
		who = step % 2 + 1;
		printf("player %d -> ", who);

		fscanf(fd, "%s %d : %d %d", buf, &step, &x, &y);
		fprintf(stdout, "step %d : %d %d\n", step, x, y);

		if (!is_onboard(x, y))
		{
			printf("this place is out of board, please reinput\n");
			continue;
		}

		if (!is_empty(x, y))
		{
			printf("this place is taken, please reinput\n");
			continue;
		}

		/* put the chess down */
		put(x, y, who);
		

		printf("step %d : %d %d [Player %d]\n", step, x, y, who); 

		print_board();

		/* check if this chess (x, y) leads to win */
		if (check(x, y))
		{
			printf("player %d wins! (%d %d) \n", who, x, y);
			break;
		}
		sleep(1);


	}

	printf("game over!\n");

	return 0;
}
