/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"

//#include <iostream> // dont forget to remove later;

UnlimitedInt* gcd(UnlimitedInt* i1, UnlimitedInt* i2){
    //std::cout<<"yay ";
    //std::cout<<"sign: "<<UnlimitedInt::sub(i1,i2)->get_sign()<<"\n";
    if(i2->get_sign()==0){
        return i2;
    }
    UnlimitedInt* r=UnlimitedInt::mod(i1,i2);
    if(r->get_sign()==0){
        return new UnlimitedInt(i2->to_string());
    }
    else{
        return gcd(i2,r);
    }
    // if(UnlimitedInt::sub(i1,i2)->get_sign()>=0){
    // UnlimitedInt* r=UnlimitedInt::mod(i1,i2);
    //     if(r->get_sign()==0){
    //         return new UnlimitedInt(i2->to_string());
    //     }
    //     else{
    //         return gcd(i2,r);
    //     }
    // }
    // else{
    //     return gcd(i2,i1);
    // }
    //return new UnlimitedInt(1);
}

UnlimitedRational::UnlimitedRational(){
    p = new UnlimitedInt(0);
    q = new UnlimitedInt(1);
}

UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den){
    int s1=num->get_sign();
    int s2=den->get_sign();
    if(s1==0 && s2!=0){
        //std::cout<<"hi"<<"\n";
        p = new UnlimitedInt(0);
        q = new UnlimitedInt(1);
    }
    else if(s2==0){
        p = new UnlimitedInt(0);
        q = new UnlimitedInt(0);
    }
    else{
        p=num;
        q=den;
    }
    // else if(s1==1 && s2==1){
    //     p=num;
    //     q=den;
    //     // UnlimitedInt* g=gcd(num,den);
    //     // if(g->get_size()==1 && g->get_array()[0]==1){
    //     //     p=num;
    //     //     q=den;
    //     // }
    //     // else{
    //     //     p=UnlimitedInt::div(num,g);
    //     //     q=UnlimitedInt::div(den,g);
    //     // }
    // }
    // else if(s1==-1 && s2==1){
    //     p=num;
    //     q=den;
    //     // std::string s = num->to_string();
    //     // s.erase(s.begin());
    //     // UnlimitedInt* x = new UnlimitedInt(s);
    //     // UnlimitedInt* g=gcd(x,den);
    //     // p=UnlimitedInt::div(num,g);
    //     // q=UnlimitedInt::div(den,g);
    //     // delete x;
    // }
    // else if(s1==1 && s2==-1){

    //     p=num;
    //     q=den;
    //     // std::string s = den->to_string();
    //     // s.erase(s.begin());
    //     // UnlimitedInt* y = new UnlimitedInt(s);
    //     // UnlimitedInt* g=gcd(num,y);
    //     // p=UnlimitedInt::div(num,g);
    //     // q=UnlimitedInt::div(den,g);
    //     // delete y;
    // }
    // else{

    //     p=num;
    //     q=den;
    //     // std::string sn = num->to_string();
    //     // sn.erase(sn.begin());
    //     // UnlimitedInt* x = new UnlimitedInt(sn);
    //     // std::string sd = den->to_string();
    //     // sd.erase(sd.begin());
    //     // UnlimitedInt* y = new UnlimitedInt(sd);
    //     // UnlimitedInt* g=gcd(x,y);
    //     // p=UnlimitedInt::div(num,g);
    //     // q=UnlimitedInt::div(den,g);
    //     // delete x;
    //     // delete y;
    // }
}

UnlimitedRational::~UnlimitedRational(){
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational::get_p(){
    return p;
}

UnlimitedInt* UnlimitedRational::get_q(){
    return q;
}

std::string UnlimitedRational::get_p_str(){
    return p->to_string();
}

std::string UnlimitedRational::get_q_str(){
    return q->to_string();
}

std::string UnlimitedRational::get_frac_str(){
    return p->to_string()+"/"+q->to_string();
}

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* n1 = i1->get_p();
    UnlimitedInt* n2 = i2->get_p();
    UnlimitedInt* d1 = i1->get_q();
    UnlimitedInt* d2 = i2->get_q();
    if(d1->get_sign()==0 || d2->get_sign()==0){
        UnlimitedInt* x = new UnlimitedInt(0);
        UnlimitedInt* y = new UnlimitedInt(0);
        UnlimitedRational* frac = new UnlimitedRational(x,y);
        //delete x;
        return frac;
    }
    else{
        UnlimitedInt* u = new UnlimitedInt();
        UnlimitedInt* num = u->add(u->mul(n1,d2),u->mul(n2,d1));
        UnlimitedInt* den = u->mul(d1,d2);
        // std::string s1=num->to_string();
        // std::string s2=den->to_string();
        // for(int i=0;i<s1.size();i++){
        //     std::cout<<s1[i];
        // }
        // std::cout<<"\n";
        // for(int i=0;i<s2.size();i++){
        //     std::cout<<s2[i];
        // }
        // std::cout<<"\n";
        UnlimitedInt* g=gcd(num,den);
        // std::string s=g->to_string();
        // for(int i=0;i<s.size();i++){
        //     std::cout<<s[i];
        // }
        // std::cout<<"\n";
        //UnlimitedInt* g= new UnlimitedInt(1);
        if(g->get_size()==1 && g->get_array()[0]==1){
            UnlimitedRational* frac = new UnlimitedRational(num,den);
            delete u;
            // delete num;
            // delete den;
            return frac;
        }
        num=u->div(num,g);
        den=u->div(den,g);
        UnlimitedRational* frac = new UnlimitedRational(num,den);
            delete u;
            // delete num;
            // delete den;
        return frac;
    }
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* n1 = i1->get_p();
    UnlimitedInt* n2 = i2->get_p();
    UnlimitedInt* d1 = i1->get_q();
    UnlimitedInt* d2 = i2->get_q();
    if(d1->get_sign()==0 || d2->get_sign()==0){
        UnlimitedInt* x = new UnlimitedInt(0);
        UnlimitedInt* y = new UnlimitedInt(0);
        UnlimitedRational* frac = new UnlimitedRational(x,y);
        //delete x;
        return frac;
    }
    else{
        UnlimitedInt* u = new UnlimitedInt();
        UnlimitedInt* num = u->sub(u->mul(n1,d2),u->mul(n2,d1));
        UnlimitedInt* den = u->mul(d1,d2);
        // std::string s=d2->to_string();
        // for(int i=0;i<s.size();i++){
        //     std::cout<<s[i];
        // }
        // std::cout<<"\n";
        // std::string s=num->to_string();
        // for(int i=0;i<s.size();i++){
        //     std::cout<<s[i];
        // }
        // std::cout<<"\n";
        UnlimitedInt* g=gcd(num,den);
        if(g->get_size()==1 && g->get_array()[0]==1){
            UnlimitedRational* frac = new UnlimitedRational(num,den);
            delete u;
            // delete num;
            // delete den;
            return frac;
        }
        num=u->div(num,g);
        den=u->div(den,g);
        UnlimitedRational* frac = new UnlimitedRational(num,den);
        delete u;
        //     // delete num;
        //     // delete den;
        return frac;
    }
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* n1 = i1->get_p();
    UnlimitedInt* n2 = i2->get_p();
    UnlimitedInt* d1 = i1->get_q();
    UnlimitedInt* d2 = i2->get_q();
    if(d1->get_sign()==0 || d2->get_sign()==0){
        UnlimitedInt* x = new UnlimitedInt(0);
        UnlimitedInt* y = new UnlimitedInt(0);
        UnlimitedRational* frac = new UnlimitedRational(x,y);
        //delete x;
        return frac;
    }
    else{
        UnlimitedInt* u = new UnlimitedInt();
        UnlimitedInt* num = u->mul(n1,n2);
        UnlimitedInt* den = u->mul(d1,d2);
        UnlimitedInt* g=gcd(num,den);
        if(g->get_size()==1 && g->get_array()[0]==1){
            UnlimitedRational* frac = new UnlimitedRational(num,den);
            delete u;
            // delete num;
            // delete den;
            return frac;
        }
        num=u->div(num,g);
        den=u->div(den,g);
        UnlimitedRational* frac = new UnlimitedRational(num,den);
            delete u;
            // delete num;
            // delete den;
            return frac;
    }
}

UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* n1 = i1->get_p();
    UnlimitedInt* n2 = i2->get_p();
    UnlimitedInt* d1 = i1->get_q();
    UnlimitedInt* d2 = i2->get_q();
    if(d1->get_sign()==0 || d2->get_sign()==0){
        UnlimitedInt* x = new UnlimitedInt(0);
        UnlimitedInt* y = new UnlimitedInt(0);
        UnlimitedRational* frac = new UnlimitedRational(x,y);
        //delete x;
        return frac;
    }
    else{
        UnlimitedInt* u = new UnlimitedInt();
        UnlimitedInt* num = u->mul(n1,d2);
        UnlimitedInt* den = u->mul(d1,n2);
        UnlimitedInt* g=gcd(num,den);
        if(g->get_size()==1 && g->get_array()[0]==1){
            UnlimitedRational* frac = new UnlimitedRational(num,den);
            delete u;
            // delete num;
            // delete den;
            return frac;
        }
        num=u->div(num,g);
        den=u->div(den,g);
        UnlimitedRational* frac = new UnlimitedRational(num,den);
            delete u;
            // delete num;
            // delete den;
            return frac;
    }
}





// int main(){
//     UnlimitedInt* n1 = new UnlimitedInt(4);
//     UnlimitedInt* d1 = new UnlimitedInt(1);
//     UnlimitedInt* n2 = new UnlimitedInt(4);
//     UnlimitedInt* d2 = new UnlimitedInt(0);
//     UnlimitedRational* u1 = new UnlimitedRational();
//     UnlimitedRational* i1 = new UnlimitedRational(n1,d1);
//     UnlimitedRational* i2 = new UnlimitedRational(n2,d2);
//     std::cout<<"num1: "<<"\n";
//     std::string s1=i1->get_frac_str();
//     for(int i=0;i<s1.size();i++){
//         std::cout<<s1[i];
//     }
//     std::cout<<"\n";
//     std::cout<<"num2: "<<"\n";
//     std::string s2=i2->get_frac_str();
//     for(int i=0;i<s2.size();i++){
//         std::cout<<s2[i];
//     }
//     std::cout<<"\n";
//     UnlimitedRational* i3 = u1->add(i1,i2);
//     UnlimitedRational* i4 = u1->sub(i1,i2);
//     UnlimitedRational* i5 = u1->mul(i1,i2);
//     UnlimitedRational* i6 = u1->div(i1,i2);
//     std::cout<<"sum: "<<"\n";
//     std::string s3=i3->get_frac_str();
//     for(int i=0;i<s3.size();i++){
//         std::cout<<s3[i];
//     }
//     std::cout<<"\n";
//     std::cout<<"diff: "<<"\n";
//     std::string s4=i4->get_frac_str();
//     for(int i=0;i<s4.size();i++){
//         std::cout<<s4[i];
//     }
//     std::cout<<"\n";
//     std::cout<<"product: "<<"\n";
//     std::string s5=i5->get_frac_str();
//     for(int i=0;i<s5.size();i++){
//         std::cout<<s5[i];
//     }
//     std::cout<<"\n";
//     std::cout<<"div: "<<"\n";
//     std::string s6=i6->get_frac_str();
//     for(int i=0;i<s6.size();i++){
//         std::cout<<s6[i];
//     }
//     std::cout<<"\n";

//     UnlimitedInt* v=gcd(n1,d1);
//     std::string s=v->to_string();
//     for(int i=0;i<s.size();i++){
//         std::cout<<s[i];
//     }
//     std::cout<<"\n";

// }

// int main(){
//     UnlimitedInt* u=new UnlimitedInt();
//     UnlimitedInt* i1 = new UnlimitedInt(4);
//     UnlimitedInt* i2 = new UnlimitedInt(0);
//     std::cout<<"\n";
//     std::string s5=i2->to_string();
//     for(int i=0;i<s5.size();i++){
//         std::cout<<s5[i];
//     }
//     std::cout<<"\n";

//     UnlimitedRational* i3 = new UnlimitedRational(i1,i2);
//     std::string s3=i3->get_frac_str();
//     for(int i=0;i<s3.size();i++){
//         std::cout<<s3[i];
//     }
//     std::cout<<"\n";
//     std::string s2=i2->to_string();
//     for(int i=0;i<s2.size();i++){
//         std::cout<<s2[i];
//     }
//     std::cout<<"\n";
//     UnlimitedInt* g = gcd(i1,i2);
//     std::string s=g->to_string();
//     for(int i=0;i<s.size();i++){
//         std::cout<<s[i];
//     }
//     std::cout<<"\n";
// }