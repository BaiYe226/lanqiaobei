#include <bits/stdc++.h>
using namespace std;
//输入样例前戳和
/*
  0  0  0  0  0
  0  1  2  3  4
  0  6  8  10 12
  0  15 18 21 24
*/
/*
  i j确定上下边界:当i = 1，j = 1 时为第一行
                 当i = 2, j = 3 时为第二行和第三行 此时sum = a[j][r] - a[i - 1][r] = 15 - 1 = 14 (14为第一列后两行的和)
  l为左指针 r为右指针 
  每次循环右指针右移 sum += a[j][r] - [i - 1][r];
  如果sum < k，则num += r - l + 1;(矩阵数目) 
  如果sum > k, 则左指针向右移动，右指针位置不变 sum -= a[j][l] -[i - 1][l];
                                              l += 1;
*/

typedef long long ll;

int main()
{
    int n,m,k;
    int a[505][505] = {0};
    cin >> n;
    cin >> m;
    cin >> k;
    for(int i  = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= m ; j++){
            cin >> a[i][j];
            //求前戳和
            a[i][j] = a[i][j] + a[i - 1][j];
        }
    }

    ll num  = 0 ,sum = 0;
    //i为上边界j为下边界
    for(int i = 1 ; i <= n ; i++){
        for(int j = i ; j <= n ; j++){
            sum = 0;
            //l左指针r右指针
            for(int l = 1, r = 1 ; r <= m ; r++){
                sum += a[j][r] - a[i - 1][r];
                while(sum > k){
                    //左指针右移sum减小
                    sum -= a[j][l] - a[i - 1][l];
                    l += 1;
                }
                num += r - l + 1;
            }
        }
    }
    cout << num;
    return 0;
}
