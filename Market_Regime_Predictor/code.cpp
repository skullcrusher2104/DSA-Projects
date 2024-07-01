#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
typedef  long double db;
const db PI = 3.14159265358979323846;
const db e = exp(1.0);
const db error = 1e-8;

db N(db y, db mu, db var){
    db c,x;
    c=1/(sqrt(2*PI*var));
    x=-0.5*((y-mu)/var)*((y-mu));
    return c*pow(e,x);
}

int main(){
    vector<vector<db> > A(2,vector<db>(2));
    cin>>A[0][0]>>A[0][1]>>A[1][0]>>A[1][1];
    db pi0,pi1;
    cin>>pi0>>pi1;
    int T;
    cin>>T;
    vector<db>Y(T);
    for(int i=0;i<T;i++){
        cin>>Y[i];
    }
    vector<db> alpha0(T),alpha1(T),beta0(T),beta1(T),gamma0(T),gamma1(T),e00(T-1),e01(T-1),e10(T-1),e11(T-1);
    db mu0=0, mu1=0, var0=1,var1=1;
    bool bear0=false;
    int times=500;
    bool converged=false;
    while(!converged && times--){
        db A0=alpha0[0],A1=alpha1[0];
        alpha0[0]=pi0*N(Y[0],mu0,var0);
        alpha1[0]=pi1*N(Y[0],mu1,var1);
        if(abs(alpha0[0]-A0)<error && abs(alpha1[0]-A1)<error)converged=true;
        else converged=false;
        for(int i=1;i<T;i++){
            db f0=N(Y[i],mu0,var0), f1=N(Y[i],mu1,var1);
            db a0=alpha0[i],a1=alpha1[i];
            alpha0[i]=f0*(alpha0[i-1]*A[0][0]+alpha1[i-1]*A[1][0]);
            alpha1[i]=f1*(alpha0[i-1]*A[0][1]+alpha1[i-1]*A[1][1]);
            if(abs(alpha0[i]-a0)<error && abs(alpha1[i]-a1)<error)converged=true;
            else converged=false;
        }
        beta0[T-1]=1, beta1[T-1]=1;
        for(int i=T-2;i>=0;i--){
            db f0=N(Y[i+1],mu0,var0), f1=N(Y[i+1],mu1,var1);
            db b0=beta0[i],b1=beta1[i];
            beta0[i]=f0*(beta0[i+1]*A[0][0])+f1*(beta1[i+1]*A[0][1]);
            beta1[i]=f0*(beta0[i+1]*A[1][0])+f1*(beta1[i+1]*A[1][1]);
            if(abs(beta0[i]-b0)<error && abs(beta1[i]-b1)<error)converged=true;
            else converged=false;
        }
        db munum0=0, munum1=0, varnum0=0, varnum1=0, den0=0, den1=0;
        for(int i=0;i<T;i++){
            db ab0=alpha0[i]*beta0[i];
            db ab1=alpha1[i]*beta1[i];
            db g0=gamma0[i],g1=gamma1[i];
            gamma0[i]=ab0/(ab0+ab1);
            gamma1[i]=ab1/(ab0+ab1);
            if(abs(gamma0[i]-g0)<error && abs(gamma1[i]-g1)<error)converged=true;
            else converged=false;
            den0+=gamma0[i];
            den1+=gamma1[i];
            munum0+=gamma0[i]*Y[i];
            munum1+=gamma1[i]*Y[i];
        }
        mu0=munum0/den0, mu1=munum1/den1;
        for(int i=0;i<T;i++){
            varnum0+=gamma0[i]*(Y[i]-mu0)*(Y[i]-mu0);
            varnum1+=gamma1[i]*(Y[i]-mu1)*(Y[i]-mu1);
        }
        var0=varnum0/den0, var1=varnum1/den1;
        db p=0,q=0,r=0,s=0;
        for(int i=0;i<T-1;i++){
            db d1=alpha0[i]*A[0][0]*beta0[i+1]*N(Y[i+1],mu0,var0);
            db d2=alpha0[i]*A[0][1]*beta1[i+1]*N(Y[i+1],mu1,var1);
            db d3=alpha1[i]*A[1][0]*beta0[i+1]*N(Y[i+1],mu0,var0);
            db d4=alpha1[i]*A[1][1]*beta1[i+1]*N(Y[i+1],mu1,var1);
            db d=d1+d2+d3+d4;
            e00[i]=d1/d, e01[i]=d2/d, e10[i]=d3/d, e11[i]=d4/d;
            p+=e00[i], q+=e01[i], r+=e10[i], s+=e11[i];
        }
        pi0=gamma0[0], pi1=gamma1[0];
        den0-=gamma0[T-1], den1-=gamma1[T-1];
        A[0][0]=p/den0,  A[0][1]=q/den0, A[1][0]=r/den1, A[1][1]=s/den1;
        if(mu0<mu1){
            bear0=true;
        }
        else{
            bear0=false;
        }
    }
    for(int i=0;i<T;i++){
        if(bear0){
            if(gamma0[i]>gamma1[i]){
                cout<<"Bear"<<endl;
                continue;
            }
            cout<<"Bull"<<endl;
            continue;
        }
        if(gamma1[i]>gamma0[i]){
            cout<<"Bear"<<endl;
            continue;
        }
        cout<<"Bull"<<endl;
        continue;
    }
}