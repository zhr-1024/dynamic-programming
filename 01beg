#include<iostream>
using namespace std;
int main()
{
	int n, C, i, j;
	cout << "请输入背包容量：";
	cin >> C;
	cout << "请输入物品数：";
	cin >> n;
	int *w = new int[n+1];
	int *v = new int[n+1];
	int *x = new int[n+1];
	int **V = new int*[n+1];//设立动态数组，节省空间
	for (i = 0; i < n + 1; i++)
	{
		V[i] = new int[C + 1];
	}
	cout << "请输入这些物品的重量：";
	w[0] = 0;
	for (i = 1; i < n + 1; i++)
		cin >> w[i];
	cout << "请输入这些物品的价值：";
	v[0] = 0;
	for (i = 1; i < n + 1; i++)
		cin >> v[i];
	for (i = 0; i < n + 1; i++)//初始化第0列
		V[i][0] = 0;
	for (j = 0; j < C + 1; j++)//初始化第0行
		V[0][j] = 0;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= C; j++)
		{
			if (j < w[i])
				V[i][j] = V[i - 1][j];
			else
				V[i][j] = V[i - 1][j] > (V[i - 1][j - w[i]] + v[i]) ? V[i - 1][j] : (V[i - 1][j - w[i]] + v[i]);
		}

/*V(i,r)=V(i-1,r)                         当r<w[i]时，物品i放不下
V(i,r)=max{V(i-1,r)，V(i-1,r-w[i])+v[i]}     否则在不放入和放入物品i之间选最优解*/
	for (j = C, i = n; i > 0; i--)
	{
		if (V[i][j] > V[i - 1][j])
		{
			x[i] = 1;
			j = j - w[i];
		}
		else
			x[i] = 0;
	}//回溯求最优解
	cout << "此题最优解为：X={";
	for (i = 1; i < n; i++)
		cout << x[i] << ",";
	cout << x[i] << "}" << endl;
  delete[] w; 
delete[] v; 
delete[] x; 
delete[] V;
return 0;
}
