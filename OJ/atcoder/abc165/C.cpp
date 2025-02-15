#include <bits/stdc++.h>
#define mp make_pair
#define sqr(x) (x)*(x)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const int maxn=100007;
const ll inf=0x3f3f3f3f;
const int mod=998244353;
#define rep(i,x,y) for(auto i=(x);i<=(y);++i)
#define dep(i,x,y) for(auto i=(x);i>=(y);--i)
int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
int ans,A[maxn],cnt,q,n,m,a[maxn],b[maxn],c[maxn],d[maxn];
void dfs(int o,int x){
    if(o==n+1){
        int now=0;
        for(int i=1;i<=q;i++){
            if(A[b[i]]-A[a[i]]==c[i]) now+=d[i];
        }
        ans=max(ans,now);
        return;
    }
    for(int i=x;i<=m;i++){
        A[o]=i;dfs(o+1,i);
    }
}
int main(){
    n=read(),m=read(),q=read();
    for(int i=1;i<=q;i++){
        a[i]=read();b[i]=read();c[i]=read();d[i]=read();
    }
    dfs(1,1);cout<<ans;
    return 0;
}