#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned int ui;
typedef long double ld;
#define endl "\n"
const ll INF = 1000000001;

ll binpow(ll a,ll b){
    ll res=1;
    while(b>0){
        if(b&1)res=res*a;
        a=a*a;
        b>>=1;
    }
    return res;
}

int gcd(int a,int b){
	if(b==0){return a;}
	return gcd(b,a%b);
}

vector<int> find_lps(string s){
	int n=s.size();
	vector<int> arr(n,0);
	
	for(int i=1;i<n;i++){
		int j=arr[i-1];
		while(j>0 && s[j]!=s[i]){
			j=arr[j-1];
		}
		if(s[j]==s[i]){
			j++;
		}
		arr[i]=j;
	}
	return arr;
}

pair<vector<int>,vector<int>> manachers(string s){
	int n=s.size();
	vector<int> d1(n);
	for (int i = 0, l = 0, r = -1; i < n; i++) {
		int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
		while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
				k++;
		}
		d1[i] = k--;
		if (i + k > r) {
				l = i - k;
				r = i + k;
		}
	}
	
	vector<int> d2(n);
	for (int i = 0, l = 0, r = -1; i < n; i++) {
		int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
		while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
				k++;
		}
		d2[i] = k--;
		if (i + k > r) {
				l = i - k - 1;
				r = i + k ;
		}
	}	
	return {d1,d2}; //d1 is for odd;d2 is for even
}

vector<int> count_div(int n){
    vector<bool> is_prime(n+1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i)
            is_prime[j] = false;
        }
    }
    vector<int> count(n+1,1);
    for(int j=2;j<=n;j++){
        int i=j;
    for (int p = 2; p <= i; p++) {
        if (is_prime[p]) {
            int c = 0;
                while(i%p == 0) {
                    i = i / p;
                    c++;
                }
            count[j] = count[j]*(c+1);
        }
    }
    }
    return count;
}
 
ld find(vector<vector<ld>>& pos){
	int n=pos.size();
	int M=1<<n;
	vector<ld> dp(M);
	dp[0]=0;
	for(int i=1;i<M;i++){
		ld ans=1e9;
		if(__builtin_popcount(i)%2!=0)continue;
		for(int p1=0;p1<n;p1++){
			if(i&(1<<p1)){
				for(int p2=p1+1;p2<n;p2++){
					if(i&(1<<p2)){
						int j=i&(~(1<<p1))&(~(1<<p2));
						
						ld dist=sqrtl( pow((pos[p1][0]-pos[p2][0]),2) + 
														pow((pos[p1][1]-pos[p2][1]),2) );
						
						ans=min(ans,dist+dp[j]);
					}
				}
			}
		}
		dp[i]=ans;
	}
	return dp[M-1];
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  //freopen("in.txt", "r", stdin); //uncomment to read & write from & to files.
  //freopen("out.txt", "w", stdout); //useful in TESTING some UVA qs(let it commented when submit)
	int n;cin>>n;
	int c=1;
	while(n){
		n*=2;
		vector<vector<ld>> pos(n,vector<ld>(2));
		for(int i=0;i<n;i++){
			string s;cin>>s;
			cin>>pos[i][0]>>pos[i][1];
		}
		cout<<setprecision(2)<<fixed<<"Case "<<c++<<": "<<find(pos)<<endl;
		cin>>n;
	}
	return 0;
}

//std::set<int, decltype(cmp)*> s(cmp);   //for custom compartor for set

