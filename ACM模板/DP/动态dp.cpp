#include <bits/stdc++.h>
#define mp make_pair
#define sqr(x) (x)*(x)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
const int maxn=100007;
const int inf=0x3f3f3f3f;
int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
struct matrix{
    int a[2][2];
    matrix(){
        memset(a,-0x3f,sizeof(a));
    }
    matrix operator * (matrix x){
        matrix New;
        for(int i=0;i<2;i++)
        for(int k=0;k<2;k++)
        for(int z=0;z<2;z++){
            New.a[i][k]=max(New.a[i][k],a[i][z]+x.a[z][k]);
        }
        return New;
    }
}g[maxn<<2];
int cl,n,dfn[maxn],f[maxn],d[maxn],sz[maxn],id[maxn];
int e1,head[maxn],to[maxn<<1],nex[maxn<<1],tp[maxn];
int son[maxn],bt[maxn];
int G[maxn][2],F[maxn][2],val[maxn];
void pushup(int o){
    g[o]=g[o<<1|1]*g[o<<1];
}
void build(int o,int l,int r){
    if(l==r){
        g[o].a[1][0]=g[o].a[0][0]=G[id[l]][0];
        g[o].a[0][1]=G[id[l]][1];
        g[o].a[1][1]=-inf;
        return;
    }
    int m=(l+r)>>1;
    build(o<<1,l,m);
    build(o<<1|1,m+1,r);
    pushup(o);
}
void modify(int o,int l,int r,int x){
    if(l==r){
        g[o].a[1][0]=g[o].a[0][0]=G[id[l]][0];
        g[o].a[0][1]=G[id[l]][1];
        g[o].a[1][1]=-inf;
        return;
    }
    int m=(l+r)>>1;
    if(x<=m) modify(o<<1,l,m,x);
    else modify(o<<1|1,m+1,r,x);
    pushup(o);
}
matrix query(int o,int l,int r,int ql,int qr){
    if(l==ql&&r==qr){
        return g[o];
    }
    int m=(l+r)>>1;
    if(ql<=m&&qr>m) return query(o<<1|1,m+1,r,m+1,qr)*query(o<<1,l,m,ql,m);
    else if(ql<=m) return query(o<<1,l,m,ql,qr);
    else return query(o<<1|1,m+1,r,ql,qr);
}
void addedge(int u,int v){
    ++e1;nex[e1]=head[u];head[u]=e1;to[e1]=v;
}
void dfs1(int u,int fa){
    f[u]=fa;
    sz[u]=1;son[u]=0;
    F[u][1]=val[u];F[u][0]=0;
    for(int i=head[u];i;i=nex[i]){
        int v=to[i];
        if(v==fa) continue;
        d[v]=d[u]+1;
        dfs1(v,u);
        F[u][1]+=F[v][0];
        F[u][0]+=max(F[v][0],F[v][1]);
        sz[u]+=sz[v];
        if(sz[v]>sz[son[u]]){
            son[u]=v;
        }
    }
}
void dfs2(int u,int t){
    tp[u]=t;dfn[u]=++cl;id[cl]=u;
    G[u][0]=F[u][0];G[u][1]=F[u][1];
    if(!son[u]){
        bt[u]=u;return;
    }
    G[u][1]-=F[son[u]][0];
    G[u][0]-=max(F[son[u]][0],F[son[u]][1]);
    dfs2(son[u],t);bt[u]=bt[son[u]];
    for(int i=head[u];i;i=nex[i]){
        int v=to[i];
        if(v!=son[u]&&v!=f[u]) dfs2(v,v);
    }
}
matrix ask(int x){
    return query(1,1,n,dfn[x],dfn[bt[x]]);
}
void Update(int x,int y){
    G[x][1]+=y-val[x];val[x]=y;
    while(x){
        matrix last=ask(tp[x]);
        modify(1,1,n,dfn[x]);
        matrix now=ask(tp[x]);
        x=f[tp[x]];
        G[x][0]+=max(now.a[0][0],now.a[0][1])-max(last.a[0][0],last.a[0][1]);
        G[x][1]+=now.a[0][0]-last.a[0][0];
    }
}
void init(){
    for(int i=1;i<=n;i++) head[i]=0;
    e1=cl=0;
}
int main(){
    n=read();int m=read();init();
    for(int i=1;i<=n;i++) val[i]=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        addedge(u,v);addedge(v,u);
    }
    dfs1(1,0);dfs2(1,1);
    build(1,1,n);
    for(int i=1;i<=m;i++){
        int x=read(),y=read();Update(x,y);
        matrix now=ask(1);
        printf("%d\n",max(now.a[0][0],now.a[0][1]));
    }
    return 0;
}
