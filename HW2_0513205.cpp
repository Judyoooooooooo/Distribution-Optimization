#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
const int maxnum = 50;
const int maxint = 999999;

int dis[maxnum];     // 目前點到原點的最短路徑
int pre[maxnum];     // 前一個點 
int c[maxnum][maxnum];   // 兩點路徑長 
int n, line;             // 節點數&路徑數 

void Dijkstra(int n, int v, int *dis, int *pre, int c[maxnum][maxnum])
{
	bool s[maxnum];    // 判斷是否已存入該點到s
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
 
	// 1為原點 
	for(int i=2; i<=n; i++)
	{
		int tmp = maxint;
		int u = v;
		// 找出目前未使用的點j的dis[j]最小值
		for(int j=1; j<=n; j++)
			if((!s[j]) && dis[j]<tmp)
			{
				u = j;  // 保存當前連接點距離最小的點
				tmp = dis[j];
			}
		s[u] = 1;    // u點存入集合s
		// 更新距離 
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
 
// 找路徑
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
 	cout<<"我將節點的代號改由數字表示"<<endl;
	cout<<"1代表a, 依此類推"<<endl;
	cout << "最小成本: " << dis[n] << endl; 
	cout << "路徑為: ";
	searchPath(pre, 1, n);
	return 0;	
}

