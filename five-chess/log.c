#include <stdio.h>

int main(void)
{
	int x, y;
	int step;
	int oldx = -1;
	int oldy = -1;
	char buf[64];

	FILE * fd;

	fd = fopen("log.txt", "a+");

	while (1)
	{
		scanf("%s %d : %d %d", buf, &step, &x, &y);
		if (strcmp(buf, "step") != 0)
			continue;
		
		fprintf(stderr, "[pipe: <%d> %d %d]\n", getpid(), x, y);
		fflush(stderr);

		if (x == oldx && y == oldy)
			break;

		printf("%d %d\n", x, y);
		fflush(stdout);

		fprintf(fd, "step %d : %d %d\n", step, x, y);
		fflush(fd);

		oldx = x;
		oldy = y;

		usleep(1000*200);
	}	
	
	fclose(fd);

	return 0;
}
