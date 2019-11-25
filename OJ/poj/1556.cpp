#include <stdio.h>
#include <iostream>
#include <string.h>
#include <math.h>
#include <queue>
#include <algorithm>
#define sqr(x) (x)*(x)
using namespace std;
typedef long long ll;
const int maxn=20007;
const double eps=1e-7;
#define ppb pair<pair<point,point>,bool>
#define pp pair<point,point>
struct point{
	double x,y;
	point(double _x=0.0,double _y=0.0):x(_x),y(_y){
	}
	double operator ^ (point a){
		return x*a.y-y*a.x;
	}
	double operator * (point a){
		return x*a.x+y*a.y;
	}
	point operator - (point a){
		return point(x-a.x,y-a.y);
	}
	point operator + (point a){
		return point(x+a.x,y+a.y);
	}
    bool operator == (point a){
        return fabs(x-a.x)<eps&&fabs(y-a.y)<eps;
	}
	bool operator < (point a){
        if(fabs(x-a.x)<eps) return y<a.y;
        return x<a.x;
	}
	void print(){
        cout<<x<<" "<<y<<" ";
	}
}p[maxn][5],s;
bool equal0(double x){
    return fabs(x)<1e-7;
}
bool equal_num(double x,double y){
    return fabs(x-y)<eps;
}
typedef point vec;
double length(point a){
    return sqrt(sqr(a.x)+sqr(a.y));
}
double dis(point a,point b){
    return length(a-b);
}
double dot(point a,point b,point c){
    return (a-c)*(b-c);
}
double mul(point a,point b,point c){
    return (a-c)^(b-c);
}
bool cmp(point a,point b){
    if(fabs(mul(a,b,s))<eps) return dis(a,s)<dis(b,s);
    else return mul(a,b,s)>0;
}
int sign(double x){
    if(fabs(x)<eps) return 0;
    else if(x>0) return 1;
    else return -1;
}
int top;point q[maxn];
void sort_by_angle1(point *p,int n){
    int pos=1;
    for(int i=2;i<=n;i++){
        if(p[i].y<p[pos].y||p[i].y==p[pos].y&&p[i].x<p[pos].x) pos=i;
    }
    swap(p[1],p[pos]);s=p[1];
    sort(p+2,p+n+1,cmp);
}
void graham(point *p,int n){
    sort_by_angle1(p,n);
    top=0;
    if(n==1){
        q[++top]=p[1];return;
    }
    else if(n==2){
        q[++top]=p[1];q[++top]=p[2];return;
    }
    q[++top]=p[1];q[++top]=p[2];q[++top]=p[3];
    for(int i=4;i<=n;i++){
        while(top>=2&&mul(p[i],q[top],q[top-1])>=0) top--;
        q[++top]=p[i];
    }
}
double tri_s(point a,point b,point c){
	return fabs((a-b)^(c-b))/2;
}
void sort_by_angle2(point *p,point a,int n){
    s=a;
    sort(p+1,p+n+1,cmp);
}
//intersection of segment and line
bool parallel(point a,point b,point c,point d){
    return equal0((b-a)^(d-c));
}
bool intersect_line_segment(point a,point b,point c,point d){
    double x=mul(b,c,a)*mul(b,d,a);
    return !equal0(x)||x<0;
}
double dis_point_to_line(point a,point b,point c){
    double x=mul(c,b,a);
    return fabs(x)/length(b-c);
}
bool online(point a,point b,point c){
    return equal0(mul(c,b,a));
}
bool onsegment(point a,point b,point c){
    return online(a,b,c)&&sign(dot(b,c,a))<=0;
}
bool intersect_segment(point a,point b,point c,point d){
    double x1=mul(b,c,a),x2=mul(b,d,a);
    double x3=mul(d,a,c),x4=mul(d,b,c);
    if(equal0(x1)&&equal0(x2)) return onsegment(a,c,d)||onsegment(b,c,d);
    else if(sign(x1*x2)>0||sign(x3*x4)>0) return false;
    else return true;
}
point get_intersect_point(point p1,point p2,point p3,point p4){
    double x1=p1.x,y1=p1.y;
    double x2=p2.x,y2=p2.y;
    double x3=p3.x,y3=p3.y;
    double x4=p4.x,y4=p4.y;
    double t=((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1))/((x2-x1)*(y3-y4)-(x3-x4)*(y2-y1));
    return point(x3+t*(x4-x3),y3+t*(y4-y3));
}
//probably some eps problem===================================
inline ppb get_intersect_segment(point a,point b,point c,point d){
    if(onsegment(a,c,d)||onsegment(b,c,d)){
        if(b<a) swap(a,b);
        if(d<c) swap(c,d);
        point x,y;
        if(onsegment(c,a,b)) x=c;else x=a;
        if(onsegment(d,a,b)) y=d;else y=b;
        return make_pair(make_pair(x,y),true);
    }
    else return make_pair(make_pair(0,0),false);
}
inline point project_point(point p,point a,point b){
    point ans;
    double u=((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y));
    u = ((b.x-a.x)*(b.x-p.x)+(b.y-a.y)*(b.y-p.y))/u;
    ans.x=u*a.x+(1-u)*b.x;
    ans.y=u*a.y+(1-u)*b.y;
    return ans;
}
inline ppb project_segment(point a,point b,point c,point d){
    point x=project_point(c,a,b),y=project_point(d,a,b);
    return get_intersect_segment(a,b,x,y);
}
inline pp project_line(point a,point b,point c,point d){
    point x=project_point(c,a,b),y=project_point(d,a,b);
    return make_pair(x,y);
}
//==========================================================
struct segment{
    point a,b;
    segment(point a=point(),point b=point()):a(a),b(b){
    }
}seg[maxn][4];
int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
int e1,head[maxn],to[maxn<<1],nex[maxn<<1],n;
double w[maxn<<1];
void addedge(int u,int v,double x){
    ++e1;nex[e1]=head[u];head[u]=e1;to[e1]=v;w[e1]=x;
}
void init(){
    for(int i=1;i<=4*n+2;i++) head[i]=0;
    e1=0;
}
int inq[maxn];
double d[maxn];
void spfa(){
    queue<int> q;
    q.push(4*n+1);
    for(int i=1;i<=4*n+2;i++) inq[i]=0,d[i]=1e9;
    inq[4*n+1]=1;d[4*n+1]=0;
    while(!q.empty()){
        int u=q.front();q.pop();inq[u]=0;
        for(int i=head[u];i;i=nex[i]){
            int v=to[i];
            if(d[v]>d[u]+w[i]){
                d[v]=d[u]+w[i];
                if(!inq[v]){inq[v]=1;q.push(v);}
            }
        }
    }
}
int id(int x,int y){
    return (x-1)*4+y;
}
bool inter(point a,point b,int x){
    //seg[x][1].a.print();seg[x][1].b.print();cout<<endl;
    return intersect_segment(a,b,seg[x][1].a,seg[x][1].b)||intersect_segment(a,b,seg[x][2].a,seg[x][2].b);
}
int main(){

    while(1){
        n=read();
            if(n==-1) return 0;
        init();
        for(int i=1;i<=n;i++){
            double x,y1,y2,y3,y4;
            scanf("%lf%lf%lf%lf%lf",&x,&y1,&y2,&y3,&y4);
            seg[i][1]=segment(point(x,y1),point(x,y2));
            seg[i][2]=segment(point(x,y3),point(x,y4));
          //  seg[i][1].a.print();seg[i][1].b.print();cout<<endl;
            p[i][1]=point(x,y1);p[i][2]=point(x,y2);
            p[i][3]=point(x,y3);p[i][4]=point(x,y4);
        }
        for(int i=1;i<=n;i++){
            for(int z=1;z<=4;z++)
            for(int k=i+1;k<=n;k++)
            for(int e=1;e<=4;e++){
                int ok=1;
                for(int r=i+1;r<=k-1;r++){
                    if(!inter(p[i][z],p[k][e],r)){
                        ok=0;break;
                    }
                }
                if(ok){
                    addedge(id(i,z),id(k,e),dis(p[i][z],p[k][e]));
                }
            }
        }
        for(int i=1;i<=n;i++){
            for(int k=1;k<=4;k++){
                int ok=1;
                for(int r=1;r<i;r++){
                    if(!inter(point(0,5),p[i][k],r)){
                        ok=0;break;
                    }
                }
                if(ok) addedge(4*n+1,id(i,k),dis(point(0,5),p[i][k]));
            }
        }
        for(int i=1;i<=n;i++){
            for(int k=1;k<=4;k++){
                int ok=1;
                for(int r=i+1;r<=n;r++){
                    if(!inter(p[i][k],point(10,5),r)){
                        ok=0;break;
                    }
                }
                if(ok) addedge(id(i,k),4*n+2,dis(p[i][k],point(10,5)));
            }
        }
        int ok=1;
        for(int i=1;i<=n;i++){
            if(!inter(point(0,5),point(10,5),i)) ok=0;
        }
        if(ok){
            printf("10.00\n");continue;
        }
        spfa();
        printf("%.2f\n",d[4*n+2]);
    }
    return 0;
}
