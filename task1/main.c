#include <stdlib.h>
#include <stdio.h>
//using namespace std;


int main(int args, char *argv)
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "o", stdout);

	int n;
	scanf("%d", &n);
	int **a;
	a = malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++)
		a[i] = malloc(sizeof(int)* n);
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++)
		a[i][j] = (i + 1)*(j + 1);
	int x1, x2, y1, y2;
	while (scanf("%d", &x1);){
		if (x1 == 0){
			return 0;
			free(a);
		}
		scanf("%d%d%d",&y1,&x2,&y2);
		for (int i = y1 - 1; i <= y2 - 1; i++)
		{
			for (int j = x1 - 1; j <= x2 - 1; j++)
				printf("%d ", a[i][j]);
			printf("\n");
		}
	}
}
