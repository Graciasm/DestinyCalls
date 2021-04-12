#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

#pragma warning(disable:4996)

#define MAXNAME 100



typedef struct _block
{
	char name[MAXNAME];
	struct tm* startt;
	struct tm* endt;
	int during;
	struct _block* next;
} block;

void drawblock(block* b)
{
	printf("%d:%02d\t┌────────────────────────────────────────────────────────────────────────────────────────────────────┐\n",b->startt->tm_hour, b->startt->tm_min);
	printf("[%4d  ]│%-100s│\n",b->during, b->name);
	//printf("%d:%d\t└────────────────────────────────────────────────────────────────────────────────────────────────────┘\n",b->endt->tm_hour,b->endt->tm_min);
	printf("\t└────────────────────────────────────────────────────────────────────────────────────────────────────┘\n");

}
void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
} //https://m.blog.naver.com/sharonichoya/220873844942


int main()
{
	int nblocks;
	int keyinput;
	int i, j;
	block** Blocks = NULL;
	block* cur,* newB;
	FILE* fp;
	fp = fopen("input.txt", "r+");
	if (fp == NULL)
	{
		fp = fopen("input.txt", "w");
	}
	i = fscanf(fp, "%d", &nblocks);
	if (i == EOF) {
		printf("0\t┌────────────────────────────────────────────────────────────┐\n");
		printf("\t│%-100s│\n","");
		printf("24\t└────────────────────────────────────────────────────────────┘\n");
	}
	/*
	else
	{
		Blocks = (block**)malloc(sizeof(block*) * nblocks);
		for (i = 0; i < nblocks; i++)
		{
			fgets(Blocks[i]->name, MAXNAME, fp);
			fscanf(fp, "%d %d %d %d %d", &(Blocks[i]->startt->tm_hour), &(Blocks[i]->startt->tm_min), &(Blocks[i]->endt->tm_hour), &(Blocks[i]->endt->tm_min), &(Blocks[i]->during));
			printf("%d : %d to %d : %d(for %d min)\n",Blocks[i]->startt->tm_hour, Blocks[i]->startt->tm_min, Blocks[i]->endt->tm_hour, Blocks[i]->endt->tm_min, Blocks[i]->during);
		}
	}
	*/
	else
	{
		fgetc(fp);
		Blocks = (block**)malloc(sizeof(block*) * nblocks);
		for(i = 0;i<nblocks;i++)
			Blocks[i] = (block*)malloc(sizeof(block) * nblocks);
		for (i = 0; i < nblocks; i++)
		{
			fgets(Blocks[i]->name, MAXNAME, fp);
			Blocks[i]->name[strlen(Blocks[i]->name) - 1] = '\0';
			printf("%s", Blocks[i]->name);
			Blocks[i]->startt = (struct tm*)malloc(sizeof(struct tm));
			Blocks[i]->endt = (struct tm*)malloc(sizeof(struct tm));
			fscanf(fp, "%d %d %d %d %d", &(Blocks[i]->startt->tm_hour), &(Blocks[i]->startt->tm_min), &(Blocks[i]->endt->tm_hour), &(Blocks[i]->endt->tm_min), &(Blocks[i]->during));
			Blocks[i]->next = Blocks[i + 1];
			printf("%d : %d to %d : %d(for %d min)\n", Blocks[i]->startt->tm_hour, Blocks[i]->startt->tm_min, Blocks[i]->endt->tm_hour, Blocks[i]->endt->tm_min, Blocks[i]->during);

			fgetc(fp);
		}
		Blocks[nblocks - 1]->next = NULL;
	}
	for (cur = Blocks[0]; cur != NULL; cur = cur->next)
		drawblock(cur);
/*
	keyinput = getch();
	if (keyinput == 224)
	{
		keyinput = getch();
		switch (keyinput)
		{
			case 72:
			break;	
			case 75:
			break;
			case 77:
			break;
			case 80:
			break;
			default:
			break;
		}
	}
	else
	{
		gotoxy(20, 2);
		scanf("%d", &j);
	}
*/
	i = 0;
	while (1)
	{
		newB = (block*)malloc(sizeof(block));
		newB->startt = (struct tm*)malloc(sizeof(struct tm));
		newB->endt = (struct tm*)malloc(sizeof(struct tm));
		fflush(stdin);
		newB->name[i] = (char)getche();

		if (newB->name[i] == 8) {
			fputs(" ", stdout);
			printf("\b");
			i--;
			continue;
		}
		if (newB->name[i] == 27)
		{
			break;
		}
		i++;
	}
	printf("%s", newB->name);
	return 0;
}

