#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
const int maxnum = 50;
const int maxint = 999999;

int dis[maxnum];     // �ثe�I����I���̵u���|
int pre[maxnum];     // �e�@���I 
int c[maxnum][maxnum];   // ���I���|�� 
int n, line;             // �`�I��&���|�� 

void Dijkstra(int n, int v, int *dis, int *pre, int c[maxnum][maxnum])
{
	bool s[maxnum];    // �P�_�O�_�w�s�J���I��s
	for(int i=1; i<=n; i++)
	{
		dis[i] = c[v][i];
		s[i] = 0;    
		if(dis[i] == maxint)
			pre[i] = 0;
		else
			pre[i] = v;
	}
	dis[v] = 0;
	s[v] = 1;
 
	// 1�����I 
	for(int i=2; i<=n; i++)
	{
		int tmp = maxint;
		int u = v;
		// ��X�ثe���ϥΪ��Ij��dis[j]�̤p��
		for(int j=1; j<=n; j++)
			if((!s[j]) && dis[j]<tmp)
			{
				u = j;  // �O�s��e�s���I�Z���̤p���I
				tmp = dis[j];
			}
		s[u] = 1;    // u�I�s�J���Xs
		// ��s�Z�� 
		for(int j=1; j<=n; j++)
			if((!s[j]) && c[u][j]<maxint)
			{
				int newd = dis[u] + c[u][j];
				if(newd < dis[j])
				{
					dis[j] = newd;
					pre[j] = u;
				}
			}
			cout<<i-1<<"->"<<pre[i]-1<<endl;
	}	
}
 
// ����|
void searchPath(int *pre,int v, int u)
{
	int que[maxnum];
	int tot = 1;
	que[tot] = u;
	tot++;
	int tmp = pre[u];
	while(tmp != v)
	{
		que[tot] = tmp;
		tot++;
		tmp = pre[tmp];
	}
	que[tot] = v;
	for(int i=tot; i>=1; i--)
		if(i != 1)
			cout << que[i] << " -> ";
		else
			cout << que[i] << endl;
}
 
int main()
{
	freopen("data.txt", "r", stdin); //data	
	cin >> n;
	cin >> line;
	int p, q, len; 
	for(int i=1; i<=n; i++)
		for(int j=1; j<=n; j++)
			c[i][j] = maxint;
 
	for(int i=1; i<=line; i++)  
	{
		cin >> p >> q >> len;
		if(len < c[p][q])     
		{
			c[p][q] = len;      // p->q
			c[q][p] = len;      // q->p
		}
	} 
	for(int i=1; i<=n; i++)
		dis[i] = maxint;
	for(int i=1; i<=n; i++)
	{
		for(int j=1; j<=n; j++)
		printf("%8d", c[i][j]);
		printf("\n");
	}
	
 	Dijkstra(n, 1, dis, pre, c);
 	cout<<"�ڱN�`�I���N����ѼƦr���"<<endl;
	cout<<"1�N��a, �̦�����"<<endl;
	cout << "�̤p����: " << dis[n] << endl; 
	cout << "���|��: ";
	searchPath(pre, 1, n);
	return 0;	
}

