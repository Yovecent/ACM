#   [P1373 小a和uim之大逃离](https://www.luogu.com.cn/problem/P1373)


    这道题写的时候把自己都给写蒙了，还是题感不行。
    
    
    题目中一共有以下的要求：
    1. 开始必须是a先吸收，结束必须是aim，同时开始和结束的地点随机。
    2. 两人的瓶子内的液体必须相同
    3. 瓶子容量为k，到k + 1 时变为0，k + 2时变为1。
    
    
    对于3，我们比较好判断出来的是我们只需要将瓶子的容量 + 1，然后拿k去模就好了，这样刚好符合。
    
    对于2，我当时想着开两个维度分别记录两个瓶子的容量，但是内存不够也不会写，
    真是没有想到可以存他们两个的差值就可以了。
    
    对于1，我们可以将每一个点都初始化上，同时对于谁先谁后的问题，我们可以再多设置一个维度，1代表最后一下是a走的，
    0代表最后一下是aim走的，然后1 和 0之间相互转化就可以了。
    
    同时这道题竟然会卡掉i64内存超限， 在dp数组中设置为int,  最后统计答案的时候设为i64即可。
 
 ACcode:
 ```C++
 #include <bits/stdc++.h>

using namespace std;
using i64 = long long;
const int mod = 1e9 + 7;

int dp[810][810][16][2];
int a[810][810];

int main()
{
	ios::sync_with_stdio(false);cin.tie(0);
	
	int n, m, K;  cin >> n >> m >> K;
	K++;
	for(int i = 1 ; i <= n ; i++){
		for(int j = 1; j <= m ; j++){
			cin >> a[i][j];
			dp[i][j][a[i][j] % K][1] = 1;
		}
	}
	i64 ans = 0;
	for(int i = 1; i <= n ; i++){
		for(int j = 1; j <= m ; j++){
			for(int k = 0 ; k < K ; k++){
				dp[i][j][(k + a[i][j]) % K][1] = (dp[i][j][(k + a[i][j]) % K][1] + dp[i - 1][j][k][0])%mod;
				dp[i][j][(k + a[i][j]) % K][1] = (dp[i][j][(k + a[i][j]) % K][1] + dp[i][j - 1][k][0])%mod;
				dp[i][j][((k - a[i][j]) % K + K ) % K][0] = (dp[i][j][((k - a[i][j]) % K + K ) % K][0] + dp[i - 1][j][k][1])%mod;
				dp[i][j][((k - a[i][j]) % K + K ) % K][0] = (dp[i][j][((k - a[i][j]) % K + K ) % K][0] + dp[i][j - 1][k][1])%mod;
			}
		}
	}
	for(int i = 1; i <= n ; i++){
		for(int j = 1; j <= m ; j++){
			ans = (ans + dp[i][j][0][0]) % mod;
		}
	}
	cout << ans << endl;
	return 0;
}

 ```

 ```diff
 !    2022-04-16 🐤
 ```
