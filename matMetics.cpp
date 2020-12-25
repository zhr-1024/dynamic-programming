/*
 用动态规划求解矩阵乘法链
 本算法使用迭代方法来求解最优乘法数：
 按 s = 2，3，…，q-1 的顺序计算c (i, i+s)，每个c 和kay 仅需计算一次。
 该函数的复杂性为 Θ(q^3)。
*/

#include<iostream>
using namespace std;
const int size=1000;
int c[size][size];
int kay[size][size];
void MatrixChain(int r[], int q,int c[size][size],int key[size][size])
{// 为所有的M(i j) 计算耗费和 k a y
 // 初始化c[i][i], c[i][i+1]和 k a y [ i ] [ i + 1 ]
    for (int i = 1; i < q; i++) {
    c[i][i] = 0;
    c[i][i+1] = r[i]*r[i+1]*r[i+2];
    kay[i][i+1] = i;
}
    c[q][q] = 0;
    //计算余下的 c和k a y
    for (int s = 2; s < q; s++)
      for (int i = 1; i <= q - s; i++) {
       // k = i时的最小项
       c[i][i+s] = c[i][i] + c[i+1][i+s] + r[i]*r[i+1]*r[i+s+1];
       kay[i][i+s] = i; 
       // 余下的最小项
       for (int k = i+1; k < i + s; k++) {
       int t = c[i][k] + c[k+1][i+s] + r[i]*r[k+1]*r[i+s+1];
       if (t < c[i][i+s]) {// 更小的最小项
        c[i][i+s] = t;
        kay[i][i+s] = k;}
        }
    }
}

void Traceback (int i, int j )
{ 
//利用k a y值来推导出最优乘法算法的步骤。
if ( i == j) {
	cout<<i-1<<",";
	return;
}
    cout<<"(";
    Traceback(i, kay[i][j]);
    Traceback(kay[i][j]+1, j);
    cout<<")";
}

int main(){
	int q,p[size],r[size];
	cout<<"请输入矩阵的个数q : ";
	cin>>q;
	cout<<"请输入矩阵:"<<endl; 
    for(int i=1;i<=2*q;i++)
		cin>>p[i];
	for(int i=1;i<=q;i++)
		  r[i]=p[2*i-1];
    r[q+1]=p[2*q];
	MatrixChain(r,q,c,kay);
	cout<<"最优计算量的值为："<<c[1][q]<<endl;
	cout<<"乘法顺序如下"<<endl; 
    Traceback ( 1, q);  
}

