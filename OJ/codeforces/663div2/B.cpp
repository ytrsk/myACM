#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define mp make_pair
#define sqr(x) (x)*(x)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const int maxn=100007;
const ll inf=0x3f3f3f3f;
int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
char s[107][107];
int main(){
    int t=read();
    while(t--){
        int n=read(),m=read();
        for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
        int ans=0;
        for(int i=1;i<=n-1;i++) ans+=(s[i][m]=='R');
        for(int i=1;i<=m-1;i++) ans+=(s[n][i]=='D');
        printf("%d\n",ans);
    }
    return 0;
}