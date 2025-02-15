#include <bits/stdc++.h>
#define mp make_pair
#define sqr(x) (x)*(x)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const int maxn=1000007;
const ll inf=0x3f3f3f3f;
int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
int e1,head[maxn],to[maxn<<1],nex[maxn<<1],dfn[maxn],cl,d[maxn],st[maxn][21];
void addedge(int u,int v,int x){
    ++e1;nex[e1]=head[u];head[u]=e1;to[e1]=v;
}
int lca(int u,int v){
	if(d[u]<d[v]) swap(u,v);
	for(int i=20;i>=0;i--) if(d[st[u][i]]>=d[v]) u=st[u][i];
	if(u==v) return u;
	for(int i=20;i>=0;i--) if(st[u][i]^st[v][i]) u=st[u][i],v=st[v][i];
	return st[u][0];
}
void dfs(int u,int fa){
	st[u][0]=fa;d[u]=d[fa]+1;dfn[u]=++cl;
	for(int i=1;i<=20;i++) st[u][i]=st[st[u][i-1]][i-1];
	for(int i=head[u];i;i=nex[i]){
		int v=to[i];
		if(v!=fa) dfs(v,u);
	}
}
int s[maxn],top;
vector<int> g[maxn];
int sz[maxn],mx[maxn],mn[maxn];
ll num[maxn];
void Addedge(int u,int v){
    g[u].push_back(v);
}
void init(int x){
    g[x].clear();
}
void ins(int u){
    init(u);
    if(top==1) {if(u>1) s[++top]=u;}
    else{
        int x=lca(u,s[top]);
        if(x!=s[top]){
            while(top>1&&dfn[s[top-1]]>=dfn[x]) Addedge(s[top-1],s[top]),top--;
            if(x!=s[top]) init(x),Addedge(x,s[top]),s[top]=x;
        }
        s[++top]=u;
    }
}
ll MX,MN,ANS;
int you[maxn];
void dp(int u){
    sz[u]=you[u];mx[u]=you[u]?d[u]:-inf;
    mn[u]=you[u]?d[u]:inf;
    num[u]=you[u]?d[u]:0;
    for(int i=0;i<g[u].size();i++){
        int v=g[u][i];dp(v);
        MX=max(MX,0LL+mx[u]+mx[v]-2*d[u]);
        MN=min(MN,0LL+mn[u]+mn[v]-2*d[u]);
        ANS+=sz[v]*(num[u]-1LL*sz[u]*d[u])+sz[u]*(num[v]-1LL*sz[v]*d[u]);
        mx[u]=max(mx[u],mx[v]);
        mn[u]=min(mn[u],mn[v]);
        sz[u]+=sz[v];
        num[u]+=num[v];
    }
}
bool cmp(int x,int y){
    return dfn[x]<dfn[y];
}
int a[maxn];
int main(){
    int n=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        addedge(u,v,0);addedge(v,u,0);
    }
    dfs(1,0);
    int q=read();
    while(q--){
        int tot=read();s[top=1]=1;init(1);
        for(int i=1;i<=tot;i++){
            a[i]=read();you[a[i]]=1;
        }
        MX=-inf;MN=inf;ANS=0;
        sort(a+1,a+tot+1,cmp);
        for(int i=1;i<=tot;i++) ins(a[i]);
        while(top>1) Addedge(s[top-1],s[top]),top--;
        dp(1);
        printf("%lld %lld %lld\n",ANS,MN,MX);
        for(int i=1;i<=tot;i++) you[a[i]]=0;
    }
    return 0;
}