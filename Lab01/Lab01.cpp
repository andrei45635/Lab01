#include <iostream>
#include <fstream>
using namespace std;
ifstream f("in.txt");

void DFS(int x)
{
	int i, A[101][101], viz[21], n;
	viz[i] = 1;
	for (i = 1; i <= n; i++)
	{
		if (A[i][x] == 1 && viz[i] == 0)
			DFS(i);
	}
}

int Conex()
{
	int i, n, viz[101];
	DFS(1);
	for (i = 1; i <= n; i++)
	{
		if (viz[i] == 0)
			return 0;
	}
	return 1;
}

int main()
{
	int m,n=0, A[22][22], i, j, k, L[101][101], K[101][101];
	//A este matricea de adiacenta
	//L este lista de adiacenta
	//K este matricea de incidenta
	//n este numarul de muchii
	f >> m; //nr varfuri
	for (i = 1; i <= m; i++)
		for (j = 1; j <= m; j++)
		{
			A[i][j] = 0;
		}
	while (f >> i >> j)
	{
		A[i][j] = 1;
		A[j][i] = 1;
		n++; //n este numarul de muchii
	}
	for (i = 1; i <= m; i++)
		for (j = 1; j <= n; j++)
			K[i][j] = 0;
	int x = 1;
	for (i = 1; i <= m; i++)
		for (j = 1; j <= n; j++)
		{
			if (A[i][j] == 1 && A[i][j] == A[i + 1][j - 1])
			{
				K[i][x] = 1;
				K[j][x] = 1;
				x++;
			}
			else if (A[i][j] == 0 && A[i][j] == A[i + 1][j - 1])
				K[i][j] = 0;
		}
	cout << n << " " <<m;
	cout << endl;

	int s1 = 0;
	bool ok = false; //pp ca graful nu e regular
	for (i = 1; i <= m; i++)
	{
		for (j = 1; j <= m; j++)
		{
			s1 += A[i][j];
			A[i][0] = s1;
		}
		cout << "suma liniei " << i << " este " << s1 << endl;
		if (s1 == 0)
			cout << "varful " << i << " este izolat deci graful nu poate fi regular" << endl;
		else if (A[i-1][0] == s1)
			ok = true; //graful e regular
		s1 = 0;
	}
	if (ok)
		cout << "Graf regular" << endl;
	cout << endl;

	//roy-floyd
	for (k = 1; k <= n; k++)
	{
		for (i = 1; i <= n; i++)
		{
			for (j = 1; j <= n; j++)
			{
				if (A[i][k] != NULL && A[k][j] != NULL)
				{
					if (A[i][j] > A[i][k] + A[k][j])
					{
						A[i][j] = A[i][k] + A[k][j];
					}
				}
			}
		}
	}

	//conexitate
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (Conex())
			{
				cout << "Graful este conex" << endl;
			}
			else
			{
				cout << "Graful nu este conex" << endl;
			}
		}
	}

	cout << "Matricea de adiacenta este: " << endl;
	for (i = 1; i <= m; i++)
	{
		for (j = 1; j <= m; j++)
		{
			cout << A[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "Matricea de incidenta este: " << endl;
	for (i = 1; i <= m; i++)
	{
		for (j = 1; j <= n; j++)
		{
			cout << K[i][j] << " ";
		}
		cout << endl;
	}
	f.close();
	return 0;
}