#include <bits/stdc++.h>
using namespace std;

/*
    主函数中"//"注释的地方是对value1的调用，
    value1函数是根据传统的01背包问题所写的，dp1代表不使用魔法时最优解情况 ，dp2代表使用魔法时最优解情况。
    在不使用魔法时就是传统的01背包问题：定义j为背包重量,vm[n][2]存放物品的体积和价值 
    当j < vm[n][0]时(背包空间小于物品重量)：dp1[i][j] = dp1[i - 1][j];上一次的最优解；
    当j >= vm[n][0]时(背包空间大于物品重量)：dp1[i][j] = max(dp1[i - 1][j] , vm[n][1] + dp1[i - 1][j - vm[n][0]]);选取‘上次最优解’和‘当前物体价值 + 剩余空间所产生的的最大价值’中大的一个
    然后需要考虑使用魔法的情况，需要注意的是魔法只能使用一次。
    当j < vm[n][0] + k时(背包空间小于对物品使用魔法后的重量)；dp2[i][j] = dp2[i - 1][j];
    当j >= vm[n][0] + k时(背包空间大于对物品使用魔法后的重量)：
        此时有三种情况：
            因为只能对物品使用一次魔法，所以当对物品使用魔法时，背包剩余重量不能从dp2中选。当不对物品使用魔法时，背包剩余的重量可以通过dp2计算价值
            1.不选择此物品：此时价值为dp2[i - 1][j];
            2.选择此物品但不使用魔法 ：此时价值为vm[n][1] + dp2[i - 1][j - vm[n][0]];
            3.选择此物品并使用魔法：此时价值为vm[n][1] * 2 + dp1[i - 1][j - vm[n][0] - k];
        所以 dp2[i][j] = max({dp2[i - 1][j] , vm[n][1] + dp2[i - 1][j - vm[n][0]]} , vm[n][1] * 2 + dp1[i - 1][j - vm[n][0] - k])
    最终的结果只要比较dp1[n][m]和dp2[n][m]选出最大的即可
    此种方法虽然在时间复杂度上没有增加，但是在空间复杂度上增加了。
    当dp1和dp2采用long类型进行存储时只能够通过70%案例，剩下的超出内存限制；
    将dp1和dp2改为int类型后可以通过所有测试案例，但是当数据庞大时就不能够使用int类型了；
*/
/*
    value函数是根据传统01背包问题改写的，dp1代表不使用魔法时最优解情况 ，dp2代表使用魔法时最优解情况。
    不存储所有的情况，只存储最新的情况。
    内层循环需要从m开始，判定条件为j >= vm[i][0]
    在选择当次最优解的时候，需要与上次的最优解做判断。从m开始是从后往前的求解，索引j和j前方的位置记录的是上一次的情况。
    因为记录的是上一次的情况所以不需要考虑j < vm[i][0]的情况
    当vm[i][0] <= j < vm[i][0] + K时:此时不能使用魔法 dp1[j] = max({dp1[j] , vm[i][1] + dp1[j - vm[i][0]]});
    当j >= vm[i][0] + k时：此时可以使用魔法 dp2[j] = max({dp2[j] , vm[i][1] + dp2[j - vm[i][0]] , vm[i][1] * 2 + dp1[j - vm[i][0] - k]});
    最终的结果只要比较dp1[n][m]和dp2[n][m]选出最大的即可
*/

//vm记录物品重量和价值 ，dp1不使用魔法数组 ，dp2使用魔法的数组
//n有多少个物品 ，m背包的最大重量 ，k魔法
long value(vector<vector<int>> &vm , vector<int> &dp1 ,  vector<int> &dp2 , int n , int m , int k){
    for(int  i = 1; i <= n; i++){
        for (int j = m; j >= vm[i][0]; j--)
        {
            //不使用魔法
            dp1[j] = max({dp1[j] , vm[i][1] + dp1[j - vm[i][0]]});
            //使用魔法
            if(j >= vm[i][0] + k){
                dp2[j] = max({dp2[j] , vm[i][1] + dp2[j - vm[i][0]] , vm[i][1] * 2 + dp1[j - vm[i][0] - k]});
            }
        }
    }
    return max(dp1[m] , dp2[m]);
}

int main() 
{
    // n件物品 ，m为最大载重 ， k使用魔法后增加的重量
    int n , m ,k;
    cin>>n;
    cin>>m;
    cin>>k;
    vector<vector<int>> vm( n + 1 , vector<int> (2 , 0));
    vector<int> dp1( m + 1 , 0);
    vector<int> dp2( m + 1 , 0);
    //vector<vector<int>> dp1( n + 1 , vector<int> (m + 1, 0));
    //vector<vector<int>> dp2( n + 1 , vector<int> (m + 1, 0));
    for(int i = 1 ; i < n + 1; i ++){
        cin>>vm[i][0];
        cin>>vm[i][1];
    }
    long MaxValue;
    //MaxValue = value1(vm , dp1 , dp2 ,n , m , k );
    MaxValue = value(vm , dp1 , dp2 , n , m , k);
    cout<<MaxValue;
    return 0;
}

//vm记录物品重量和价值 ，dp1不使用魔法数组 ，dp2使用魔法的数组
//n有多少个物品 ，m背包的最大重量 ，k魔法
long value1(vector<vector<int>> &vm , vector<vector<int>> &dp1 ,  vector<vector<int>> &dp2 , int n , int m , int k){
    for( int i = 1 ; i <= n ; i++){
        for ( int j = 1 ; j <= m; j++)
        {
            //不使用魔法
            if(j < vm[i][0]){
                dp1[i][j] = dp1[i - 1][j];
            }else{
                dp1[i][j] = max({dp1[i - 1][j] , vm[i][1] + dp1[i - 1][j - vm[i][0]]});
            }
            //使用魔法
            if(j < vm[i][0] + k){
                dp2[i][j] = dp2[i - 1][j];
            }else{
                dp2[i][j] = max({dp2[i - 1][j] , vm[i][1] + dp2[i - 1][j - vm[i][0]] , vm[i][1] * 2 + dp1[i - 1][j - vm[i][0] - k]});
            }
        }
    }
    return max(dp1[n][m] , dp2[n][m]);
}
