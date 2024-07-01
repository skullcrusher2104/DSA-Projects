/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"


//#include<iostream>


UnlimitedInt* half(UnlimitedInt* i){
    std::string answer="";
    int x;
    int carry=0;
    int* n=i->get_array();
    for(int j=0;j<i->get_size()-1;j++){
        x=(n[j]+carry)/2;
        carry=((n[j]+carry)%2)*10;
        answer+=static_cast<char>('0'+x);
    }
    x=(n[i->get_size()-1]+carry)/2;
    answer+=static_cast<char>('0'+x);
    while(answer[0]=='0'){
        answer.erase(answer.begin());
    }
    UnlimitedInt* i3 = new UnlimitedInt(answer);
    return i3;
}

UnlimitedInt* quotient_finder(UnlimitedInt* dividend, UnlimitedInt* divisor, UnlimitedInt* lower_limit, UnlimitedInt* upper_limit){
    UnlimitedInt* left=lower_limit;
    UnlimitedInt* right=upper_limit;
    UnlimitedInt* result = new UnlimitedInt(0);
    UnlimitedInt* constant = new UnlimitedInt(1);
    while(UnlimitedInt::sub(right,left)->get_sign()>-1){
        UnlimitedInt* mid=UnlimitedInt::add(left,half(UnlimitedInt::sub(right,left)));
        if(UnlimitedInt::sub(dividend,UnlimitedInt::mul(divisor,mid))->get_sign()==0){
            return mid;
        }
        else if(UnlimitedInt::sub(dividend,UnlimitedInt::mul(divisor,mid))->get_sign()==-1){
            right = UnlimitedInt::sub(mid,constant);
        }
        else{
            result=mid;
            left=UnlimitedInt::add(mid,constant);
        }
    }
    return result;
}

UnlimitedInt::UnlimitedInt(){
    sign=0;
    size=1;
    capacity=1;
    unlimited_int = new int[1];
    unlimited_int[0]=0;
}

UnlimitedInt::UnlimitedInt(std::string s){
    if(s[0]=='0' && s.size()==1){
        sign=0;
        size=1;
        capacity=1;
        unlimited_int = new int[1];
        unlimited_int[0]=0;
    }
    else if(s[0]=='-'){
        sign=-1;
        size=s.size()-1;
        capacity=size;
        unlimited_int = new int[size];
        for(int i=1;i<size+1;i++){
            unlimited_int[i-1]=s[i]-'0';
        }
    }
    else{
        sign=1;
        size=s.size();
        capacity=size;
        unlimited_int = new int[size];
        for(int i=0;i<size;i++){
            unlimited_int[i]=s[i]-'0';
        }
    }
}

UnlimitedInt::UnlimitedInt(int i){
    if(i==0){
        sign=0;
        size=1;
        capacity=1;
        unlimited_int = new int[1];
        unlimited_int[0]=0;
    }
    else if(i<0){
        sign=-1;
        size=0;
        int magnitude=-i;
        while(magnitude>0){
            size++;
            magnitude/=10;
        }
        unlimited_int = new int[size];
        i=-i;
        int index=size-1;
        while(i>0){
            unlimited_int[index]=i%10;
            index--;
            i/=10;
        }
    }
    else{
        sign=1;
        size=0;
        int magnitude=i;
        while(magnitude>0){
            size++;
            magnitude/=10;
        }
        unlimited_int = new int[size];
        int index=size-1;
        while(i>0){
            unlimited_int[index]=i%10;
            index--;
            i/=10;
        }
    }
}

UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz){
    unlimited_int=ulimited_int;
    sign=sgn;
    size=sz;
    capacity=cap;
}

UnlimitedInt::~UnlimitedInt(){
    sign=0;
    size=0;
    capacity=0;
    delete[] unlimited_int;
}

int UnlimitedInt::get_size(){
    return size;
}

int* UnlimitedInt::get_array(){
    return unlimited_int;
}

int UnlimitedInt::get_sign(){
    return sign;
}

int UnlimitedInt::get_capacity(){
    return capacity;
}

std::string UnlimitedInt::to_string(){
    if(sign==0){
        return "0";
    }
    else if(sign==-1){
        std::string number="-";
        //number+=static_cast<char>(45);
        for(int i=0;i<size;i++){
            number+=static_cast<char>('0'+unlimited_int[i]);
        }
        return number;
    }
    else{
        std::string number="";
        for(int i=0;i<size;i++){
            number+=static_cast<char>('0'+unlimited_int[i]);
        }
        return number;
    }
}

UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2){
    int i1_sign=i1->get_sign();
    int i2_sign=i2->get_sign();
    if(i1_sign==1 && i2_sign==-1){
        std::string s=i2->to_string();
        s.erase(s.begin());
        UnlimitedInt* new_i2 = new UnlimitedInt(s);
        UnlimitedInt* i3=sub(i1,new_i2);
        delete new_i2;
        return i3;
    }
    else if(i1_sign==-1 && i2_sign==1){
        std::string s=i1->to_string();
        s.erase(s.begin());
        UnlimitedInt* new_i1 = new UnlimitedInt(s);
        UnlimitedInt* i3=sub(i2,new_i1);
        delete new_i1;
        return i3;
    }
    else if(i1_sign==1 && i2_sign==1){
        std::string answer="";
        int i1_index=i1->get_size()-1;
        int i2_index=i2->get_size()-1;
        int carry=0;
        while(i1_index>=0 && i2_index>=0){
            int x;
            x=i1->get_array()[i1_index] + i2->get_array()[i2_index] + carry;
            if(x>=10){
                carry=1;
                x=x%10;
                answer=static_cast<char>('0'+x)+answer;
            }
            else{
                carry=0;
                answer=static_cast<char>('0'+x)+answer;
            }
            i1_index--;
            i2_index--;
        }
        while(i1_index>=0){
            int x;
            x=i1->get_array()[i1_index]+carry;
            if(x>=10){
                carry=1;
                x=x%10;
                answer=static_cast<char>('0'+x)+answer;
            }
            else{
                carry=0;
                answer=static_cast<char>('0'+x)+answer;
            }
            i1_index--;
        }
        while(i2_index>=0){
            int x;
            x=i2->get_array()[i2_index]+carry;
            if(x>=10){
                carry=1;
                x=x%10;
                answer=static_cast<char>('0'+x)+answer;
            }
            else{
                carry=0;
                answer=static_cast<char>('0'+x)+answer;
            }
            i2_index--;
        }
        if(carry==1){
            answer='1'+answer;
        }
        UnlimitedInt* i3 = new UnlimitedInt(answer);
        return i3;
    }
    else{
        std::string answer="";
        int i1_index=i1->get_size()-1;
        int i2_index=i2->get_size()-1;
        int carry=0;
        if(i1->sign==0){
            UnlimitedInt* i3 = new UnlimitedInt(i2->to_string());
            return i3;
        }
        if(i2->sign==0){
            UnlimitedInt* i3 = new UnlimitedInt(i1->to_string());
            return i3;
        }
        while(i1_index>=0 && i2_index>=0){
            int x;
            x=i1->get_array()[i1_index] + i2->get_array()[i2_index] + carry;
            if(x>=10){
                carry=1;
                x=x%10;
                answer=static_cast<char>('0'+x)+answer;
            }
            else{
                carry=0;
                answer=static_cast<char>('0'+x)+answer;
            }
            i1_index--;
            i2_index--;
        }
        while(i1_index>=0){
            int x;
            x=i1->get_array()[i1_index]+carry;
            if(x>=10){
                carry=1;
                x=x%10;
                answer=static_cast<char>('0'+x)+answer;
            }
            else{
                carry=0;
                answer=static_cast<char>('0'+x)+answer;
            }
            i1_index--;
        }
        while(i2_index>=0){
            int x;
            x=i2->get_array()[i2_index]+carry;
            if(x>=10){
                carry=1;
                x=x%10;
                answer=static_cast<char>('0'+x)+answer;
            }
            else{
                carry=0;
                answer=static_cast<char>('0'+x)+answer;
            }
            i2_index--;
        }
        if(carry==1){
            answer='1'+answer;
        }
        answer='-'+answer;
        UnlimitedInt* i3 = new UnlimitedInt(answer);
        return i3;
    }
}

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2){
    int i1_sign=i1->get_sign();
    int i2_sign=i2->get_sign();
    if(i2_sign==0){
        UnlimitedInt* i3 = new UnlimitedInt(i1->to_string());
        return i3;
    }
    if(i1_sign==0){
        if(i2_sign==1){
            UnlimitedInt* i3 = new UnlimitedInt('-'+i1->to_string());
            return i3;
        }
        else{
            std::string s=i2->to_string();
            s.erase(s.begin());
            UnlimitedInt* i3 = new UnlimitedInt(s);
            return i3;
        }
    }
    else if(i1_sign==1 && i2_sign==-1){
        std::string s=i2->to_string();
        s.erase(s.begin());
        UnlimitedInt* new_i2 = new UnlimitedInt(s);
        UnlimitedInt* i3=add(i1,new_i2);
        delete new_i2;
        return i3;
    }
    else if(i1_sign==-1 && i2_sign==1){
        UnlimitedInt* new_i2 = new UnlimitedInt('-'+i2->to_string());
        UnlimitedInt* i3=add(i1,new_i2);
        delete new_i2;
        return i3;
    }
    else if(i1_sign==1 && i2_sign==1){
        int i1_index=i1->get_size()-1;
        int i2_index=i2->get_size()-1;
        int* n1=i1->get_array();
        int* n2=i2->get_array();
        int* old_i1 = new int[i1_index+1];
        int* old_i2 = new int[i2_index+1];
        for(int j=0;j<i1_index+1;j++){
            old_i1[j]=n1[j];
        }
        for(int j=0;j<i2_index+1;j++){
            old_i2[j]=n2[j];
        }
        std::string answer="";
        if(i1_index>i2_index){
            while(i1_index>=0 && i2_index>=0){
                int x;
                if(old_i1[i1_index]>=old_i2[i2_index]){
                    x=old_i1[i1_index]-old_i2[i2_index];
                    answer=static_cast<char>('0'+x)+answer;
                }
                else{
                    old_i1[i1_index-1]-=1;
                    x=old_i1[i1_index]+10-old_i2[i2_index];
                    answer=static_cast<char>('0'+x)+answer;
                    if(old_i1[i1_index-1]==-1){
                        int i=i1_index-1;
                        while(old_i1[i]<=0){
                            old_i1[i]=9;
                            i--;
                        }
                        old_i1[i]-=1;
                    }
                }
                i1_index--;
                i2_index--;
            }
            while(i1_index>0){
                answer=static_cast<char>('0'+old_i1[i1_index])+answer;
                i1_index--;
            }
            if(old_i1[i1_index]>0){
                answer=static_cast<char>('0'+old_i1[i1_index])+answer;
            }
            delete[] old_i1;
            delete[] old_i2;
            UnlimitedInt* i3 = new UnlimitedInt(answer);
            return i3;
        }
        else if(i1_index<i2_index){
            while(i1_index>=0 && i2_index>=0){
                int x;
                if(old_i2[i2_index]>=old_i1[i1_index]){
                    x=old_i2[i2_index]-old_i1[i1_index];
                    answer=static_cast<char>('0'+x)+answer;
                }
                else{
                    old_i2[i2_index-1]-=1;
                    x=old_i2[i2_index]+10-old_i1[i1_index];
                    answer=static_cast<char>('0'+x)+answer;
                    if(old_i2[i2_index-1]==-1){
                        int i=i2_index-1;
                        while(old_i2[i]<=0){
                            old_i2[i]=9;
                            i--;
                        }
                        old_i2[i]-=1;
                    }
                }
                i1_index--;
                i2_index--;
            }
            while(i2_index>0){
                answer=static_cast<char>('0'+old_i2[i2_index])+answer;
                i2_index--;
            }
            if(old_i2[i2_index]>0){
                answer=static_cast<char>('0'+old_i2[i2_index])+answer;
            }
            delete[] old_i1;
            delete[] old_i2;
            answer='-'+answer;
            UnlimitedInt* i3 = new UnlimitedInt(answer);
            return i3;
        }
        else{
            bool greater=false;
            int j=0;
            for(j=0;j<i1_index+1;j++){
                if(n1[j]>n2[j]){
                    greater=true;
                    break;
                }
                else if(n1[j]==n2[j]){
                    continue;
                }
                else{
                    greater=false;
                    break;
                }
            }
            if(j==i1_index+1){
                delete[] old_i1;
                delete[] old_i2;
                UnlimitedInt* i3 = new UnlimitedInt("0");
                return i3;
            }
            if(greater){
                while(i1_index>=0 && i2_index>=0){
                    int x;
                    if(old_i1[i1_index]>=old_i2[i2_index]){
                        x=old_i1[i1_index]-old_i2[i2_index];
                        answer=static_cast<char>('0'+x)+answer;
                    }
                    else{
                        old_i1[i1_index-1]-=1;
                        x=old_i1[i1_index]+10-old_i2[i2_index];
                        answer=static_cast<char>('0'+x)+answer;
                        if(old_i1[i1_index-1]==-1){
                            int i=i1_index-1;
                            while(old_i1[i]<=0){
                                old_i1[i]=9;
                                i--;
                            }
                            old_i1[i]-=1;
                        }
                    }
                    i1_index--;
                    i2_index--;
                }
                // while(i1_index>0){
                //     answer=static_cast<char>('0'+old_i1[i1_index])+answer;
                //     i1_index--;
                // }
                // if(old_i1[i1_index]>0){
                //     answer=static_cast<char>('0'+old_i1[i1_index])+answer;
                // }
                while(answer[0]=='0'){
                    answer.erase(answer.begin());
                }
                delete[] old_i1;
                delete[] old_i2;
                UnlimitedInt* i3 = new UnlimitedInt(answer);
                return i3;
            }
            else{
                while(i1_index>=0 && i2_index>=0){
                    int x;
                    if(old_i2[i2_index]>=old_i1[i1_index]){
                        x=old_i2[i2_index]-old_i1[i1_index];
                        answer=static_cast<char>('0'+x)+answer;
                    }
                    else{
                        old_i2[i2_index-1]-=1;
                        x=old_i2[i2_index]+10-old_i1[i1_index];
                        answer=static_cast<char>('0'+x)+answer;
                        if(old_i2[i2_index-1]==-1){
                            int i=i2_index-1;
                            while(old_i2[i]<=0){
                                old_i2[i]=9;
                                i--;
                            }
                            old_i2[i]-=1;
                        }
                    }
                    i1_index--;
                    i2_index--;
                }
                // while(i2_index>0){
                //     answer=static_cast<char>('0'+old_i2[i2_index])+answer;
                //     i2_index--;
                // }
                // if(old_i2[i2_index]>0){
                //     answer=static_cast<char>('0'+old_i2[i2_index])+answer;
                // }
                while(answer[0]=='0'){
                    answer.erase(answer.begin());
                }
                delete[] old_i1;
                delete[] old_i2;
                answer='-'+answer;
                UnlimitedInt* i3 = new UnlimitedInt(answer);
                return i3;
            }
        }
    }
    else{
        std::string s=i2->to_string();
        s.erase(s.begin());
        UnlimitedInt* new_i2 = new UnlimitedInt(s);
        UnlimitedInt*i3=add(new_i2,i1);
        delete new_i2;
        return i3;
    }
}

UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2){
    int i1_size=i1->get_size();
    int i2_size=i2->get_size();
    int* n1=i1->get_array();
    int* n2=i2->get_array();
    if(i1->sign==0){
        UnlimitedInt* i3 = new UnlimitedInt(0);
        return i3;
    }
    if(i2->sign==0){
        UnlimitedInt* i3 = new UnlimitedInt(0);
        return i3;
    }
    if(i1_size>=i2_size){
        UnlimitedInt* i3 = new UnlimitedInt(0);
        int zeroes=0;
        for(int j=i2_size-1;j>=0;j--){
            std::string answer="";
            int x;
            int carry=0;
            for(int k=i1_size-1;k>0;k--){
                x=n1[k]*n2[j]+carry;
                carry=x/10;
                x%=10;
                answer=static_cast<char>('0'+x)+answer;
            }
            x=n1[0]*n2[j]+carry;
            answer=static_cast<char>('0'+x%10)+answer;
            if(x/10>0){
                answer=static_cast<char>('0'+x/10)+answer;
            }
            for(int r=0;r<zeroes;r++){
                answer+="0";
            }
            zeroes++;
            UnlimitedInt* n = new UnlimitedInt(answer);
            i3 = add(n,i3);
        }
        if((i1->sign==1 && i2->sign==1)||(i1->sign==-1 && i2->sign==-1)){
            i3->sign=1;
            return i3;
        }
        else{
            i3->sign=-1;
            return i3;
        }
    }
    else{
        UnlimitedInt* i3 = new UnlimitedInt(0);
        int zeroes=0;
        for(int j=i1_size-1;j>=0;j--){
            std::string answer="";
            int x;
            int carry=0;
            for(int k=i2_size-1;k>0;k--){
                x=n2[k]*n1[j]+carry;
                carry=x/10;
                x%=10;
                answer=static_cast<char>('0'+x)+answer;
            }
            x=n2[0]*n1[j]+carry;
            answer=static_cast<char>('0'+x%10)+answer;
            if(x/10>0){
                answer=static_cast<char>('0'+x/10)+answer;
            }
            for(int r=0;r<zeroes;r++){
                answer+="0";
            }
            zeroes++;
            UnlimitedInt* n = new UnlimitedInt(answer);
            i3 = add(n,i3);
        }
        if((i1->sign==1 && i2->sign==1)||(i1->sign==-1 && i2->sign==-1)){
            i3->sign=1;
            return i3;
        }
        else{
            i3->sign=-1;
            return i3;
        }
    }
}

// UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2){
//     if(i1->sign==0){
//         UnlimitedInt* quotient = new UnlimitedInt(0);
//         return quotient;
//     }
//     if((i1->sign==1 && i2->sign==1)){
//         UnlimitedInt* n = new UnlimitedInt(i1->to_string());
//         UnlimitedInt* quotient = new UnlimitedInt(0);
//         UnlimitedInt* constant = new UnlimitedInt(1);
//         // while(n->get_size()>i2->get_size()){
//         //     n=sub(n,i2);
//         //     quotient=add(quotient,constant);
//         // }
//         // if(n->get_size()<i2->get_size()){
//         //     delete n;
//         //     delete constant;
//         //     return quotient;
//         // }
//         // while(true){
//         //     int* n1=n->get_array();
//         //     int* n2=i2->get_array();
//         //     bool greater=false;
//         //     int j=0;
//         //     for(j=0;j<n->size;j++){
//         //         if(n1[j]>n2[j]){
//         //             greater=true;
//         //             break;
//         //         }
//         //         else if(n1[j]==n2[j]){
//         //             continue;
//         //         }
//         //         else{
//         //             greater=false;
//         //             break;
//         //         }
//         //     }
//         //     if(j==n->size){
//         //         n=sub(n,i2);
//         //         quotient=add(quotient,constant);
//         //         continue;
//         //     }
//         //     if(greater){
//         //         n=sub(n,i2);
//         //         quotient=add(quotient,constant);
//         //     }
//         //     else{
//         //         break;
//         //     }
//         // }
//         // delete n;
//         // delete constant;
//         // return quotient;
//         while(sub(n,i2)->sign>=0){
//             // std::string s;
//             // s=i2->to_string();
//             // for(int i=0;i<s.size();i++){                 // divide has the problem
//             //     std::cout<<s[i];
//             // }
//             // std::cout<<"\n";
//             // std::cout<<"divide me hai prob"<<"\n";
//             // UnlimitedInt* x=new UnlimitedInt(n->to_string());
//             n=sub(n,i2);
//             // if(sub(x,n)->sign>0){
//             //     std::cout<<"decreased <<";
//             // }
//             quotient=add(quotient,constant);
//         }
//         // if(sub(n,i2)->sign==0){
//         //     quotient=add(quotient,constant);
//         // }
//         return quotient;
//     }
//     else if(i1->sign==-1 && i2->sign==1){
//         std::string s=i1->to_string();
//         s.erase(s.begin());
//         UnlimitedInt* new_i1 = new UnlimitedInt(s);
//         UnlimitedInt* quotient=div(new_i1,i2);
//         UnlimitedInt* constant= new UnlimitedInt(1);
//         if(sub(mul(quotient,i2),new_i1)->sign==0){
//             delete new_i1;
//             delete constant;
//             quotient->sign=-1;
//             return quotient;
//         }
//         else{
//             quotient=add(quotient,constant);
//             delete new_i1;
//             delete constant;
//             quotient->sign=-1;
//             return quotient;
//         }
//     }
//     else if(i1->sign==1 && i2->sign==-1){
//         std::string s=i2->to_string();
//         s.erase(s.begin());
//         UnlimitedInt* new_i2 = new UnlimitedInt(s);
//         UnlimitedInt* quotient=div(i1,new_i2);
//         UnlimitedInt* constant= new UnlimitedInt(1);
//         if(sub(mul(quotient,new_i2),i1)->sign==0){
//             delete new_i2;
//             delete constant;
//             quotient->sign=-1;
//             return quotient;
//         }
//         else{
//             quotient=add(quotient,constant);
//             delete new_i2;
//             delete constant;
//             quotient->sign=-1;
//             return quotient;
//         }
//     }
//     else{
//         // UnlimitedInt* n = new UnlimitedInt;
//         // n=i1;
//         // n->sign=1;
//         // UnlimitedInt* new_i2=i2;
//         // new_i2->sign=1;
//         // UnlimitedInt* quotient = new UnlimitedInt(0);
//         // UnlimitedInt* constant = new UnlimitedInt(1);
//         // while(n->get_size()>new_i2->get_size()){
//         //     n=sub(n,new_i2);
//         //     quotient=add(quotient,constant);
//         // }
//         // if(n->get_size()<new_i2->get_size()){
//         //     return quotient;
//         // }
//         // while(true){
//         //     int* n1=n->get_array();
//         //     int* n2=new_i2->get_array();
//         //     bool greater=false;
//         //     int j=0;
//         //     for(j=0;j<n->size;j++){
//         //         if(n1[j]>n2[j]){
//         //             greater=true;
//         //             break;
//         //         }
//         //         else if(n1[j]==n2[j]){
//         //             continue;
//         //         }
//         //         else{
//         //             greater=false;
//         //             break;
//         //         }
//         //     }
//         //     if(j==n->size){
//         //         n=sub(n,new_i2);
//         //         quotient=add(quotient,constant);
//         //     }
//         //     if(greater){
//         //         n=sub(n,new_i2);
//         //         quotient=add(quotient,constant);
//         //     }
//         //     else{
//         //         break;
//         //     }
//         // }
//         // return quotient;
//         std::string s1=i1->to_string();
//         std::string s2=i2->to_string();
//         s1.erase(s1.begin());
//         s2.erase(s2.begin());
//         UnlimitedInt* new_i1 = new UnlimitedInt(s1);
//         UnlimitedInt* new_i2 = new UnlimitedInt(s2);
//         UnlimitedInt* i3 = div(new_i1,new_i2);
//         delete new_i1;
//         delete new_i2;
//         return i3;
//     }
// }

UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2){
    if(i1->sign==0){
        UnlimitedInt* quotient = new UnlimitedInt(0);
        return quotient;
    }
    if(i2->size==1 && i2->get_array()[0]==1 && i2->get_sign()==1){
        return i1;
    }
    if(i2->size==1 && i2->get_array()[0]==1 && i2->get_sign()==-1){
        return new UnlimitedInt('-'+i1->to_string());
    }
    if(i1->sign==1 && i2->sign==1){
        int x=sub(i1,i2)->get_sign();
        if(x==0){
            return new UnlimitedInt(1);
        }
        else if(x==-1){
            return new UnlimitedInt(0);
        }
        else{
            UnlimitedInt* answer = half(i1);
            UnlimitedInt* prev_answer = new UnlimitedInt(i1->to_string());
            while(sub(mul(answer,i2),i1)->get_sign()==1){
                prev_answer=answer; 
                answer=half(answer);
            }
            return quotient_finder(i1,i2,answer,prev_answer);
        }
    }
    else if(i1->sign==-1 && i2->sign==1){
        std::string s=i1->to_string();
        s.erase(s.begin());
        UnlimitedInt* new_i1 = new UnlimitedInt(s);
        UnlimitedInt* quotient=div(new_i1,i2);
        UnlimitedInt* constant= new UnlimitedInt(1);
        if(sub(mul(quotient,i2),new_i1)->sign==0){
            delete new_i1;
            delete constant;
            quotient->sign=-1;
            return quotient;
        }
        else{
            quotient=add(quotient,constant);
            delete new_i1;
            delete constant;
            quotient->sign=-1;
            return quotient;
        }   
    }
    else if(i1->sign==1 && i2->sign==-1){
        std::string s=i2->to_string();
        s.erase(s.begin());
        UnlimitedInt* new_i2 = new UnlimitedInt(s);
        UnlimitedInt* quotient=div(i1,new_i2);
        UnlimitedInt* constant= new UnlimitedInt(1);
        if(sub(mul(quotient,new_i2),i1)->sign==0){
            delete new_i2;
            delete constant;
            quotient->sign=-1;
            return quotient;
        }
        else{
            quotient=add(quotient,constant);
            delete new_i2;
            delete constant;
            quotient->sign=-1;
            return quotient;
        }
    }
    else{
        std::string s1=i1->to_string();
        std::string s2=i2->to_string();
        s1.erase(s1.begin());
        s2.erase(s2.begin());
        UnlimitedInt* new_i1 = new UnlimitedInt(s1);
        UnlimitedInt* new_i2 = new UnlimitedInt(s2);
        UnlimitedInt* i3 = div(new_i1,new_i2);
        delete new_i1;
        delete new_i2;
        return i3;
    }
}

UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2){
    if(i1->sign==1 && i2->sign==1){
        
        return sub(i1,mul(div(i1,i2),i2));
    }
    else if(i1->sign==-1 && i2->sign==1){
        std::string s=i1->to_string();
        s.erase(s.begin());
        UnlimitedInt* new_i1 = new UnlimitedInt(s);
        UnlimitedInt* r=sub(new_i1,mul(div(new_i1,i2),i2));
        // std::string hello=r->to_string();
        // std::cout<<"new wala r: ";
        // for(int i=0;i<hello.size();i++){
        //     std::cout<<hello[i];
        // }
        // std::cout<<"\n";
        if(r->get_sign()==0){
            return r;
        }
        r=sub(i2,r);
        delete new_i1;
        //r->sign=1;
        return r;
    }
    else if(i1->sign==1 && i2->sign==-1){
        std::string s=i2->to_string();
        s.erase(s.begin());
        UnlimitedInt* new_i2 = new UnlimitedInt(s);
        UnlimitedInt* r=sub(i1,mul(div(i1,new_i2),new_i2));
        //r->sign=1;
        if(r->get_sign()==0){
            return r;
        }
        r=sub(new_i2,r);
        delete new_i2;
        return r;
    }
    else{
        std::string s1=i1->to_string();
        s1.erase(s1.begin());
        std::string s2=i2->to_string();
        s2.erase(s2.begin());
        UnlimitedInt* new_i1 = new UnlimitedInt(s1);
        UnlimitedInt* new_i2 = new UnlimitedInt(s2);
        UnlimitedInt* r=sub(new_i1,mul(div(new_i1,new_i2),new_i2));
        //r->sign=1;
        delete new_i1;
        delete new_i2;
        return r;
    }
}



// int main(){
//     UnlimitedInt u;
//     UnlimitedInt* u1 = new UnlimitedInt(945);
//     UnlimitedInt* u2 = new UnlimitedInt(3);
//     /* UnlimitedInt* u5 = new UnlimitedInt(2);
//     UnlimitedInt* u3=u.add(u1,u2);
//     UnlimitedInt* u4=u.mul(u1,u5);
//     UnlimitedInt* u6=u.sub(u3,u4);
//     std::cout<<u3->get_size()<<"\n";
//     int *hello=u3->get_array();
//     std::string s=u3->to_string();
//     for(int i=0;i<s.size();i++){
//         std::cout<<s[i];
//     }
//     std::cout<<"\n";
//     std::cout<<u3->get_sign()<<"\n";
//     std::cout<<"u1"<<"\n";
//     std::cout<<u1->get_sign()<<"\n";
//     int *hello1=u1->get_array();
//     int *hello2=u2->get_array();
//     for(int i=0;i<u1->get_size();i++){
//         std::cout<<hello1[i];
//     }
//     std::cout<<"\n";
//     std::cout<<"u2"<<"\n";
//     for(int i=0;i<u2->get_size();i++){
//         std::cout<<hello2[i];
//     }
//     std::cout<<"\n"; */
//     UnlimitedInt* u3=u.add(u1,u2);
//     UnlimitedInt* u4=u.sub(u1,u2);
//     UnlimitedInt* u5=u.mul(u1,u2);
//     UnlimitedInt* u6=u.div(u1,u2);
//     UnlimitedInt* u7=u.mod(u1,u2);
//     std::string s3=u3->to_string();
//     std::string s4=u4->to_string();
//     std::string s5=u5->to_string();
//     std::string s6=u6->to_string();
//     std::string s7=u7->to_string();
//     std::cout<<"sum"<<"\n";
//     std::cout<<"sign: "<<u3->get_sign()<<"\n";
//     for(int i=0;i<s3.size();i++){
//         std::cout<<s3[i];
//     }
//     std::cout<<"\n";
//     std::cout<<"diff"<<"\n";
//     std::cout<<"sign: "<<u4->get_sign()<<"\n";
//     for(int i=0;i<s4.size();i++){
//         std::cout<<s4[i];
//     }
//     std::cout<<"\n";
//     std::cout<<"product"<<"\n";
//     std::cout<<"sign: "<<u5->get_sign()<<"\n";
//     for(int i=0;i<s5.size();i++){
//         std::cout<<s5[i];
//     }
//     std::cout<<"\n";
//     std::cout<<"div"<<"\n";
//     std::cout<<"sign: "<<u6->get_sign()<<"\n";
//     for(int i=0;i<s6.size();i++){
//         std::cout<<s6[i];
//     }
//     std::cout<<"\n";
//     std::cout<<"mod"<<"\n";
//     std::cout<<"sign: "<<u7->get_sign()<<"\n";
//     for(int i=0;i<s7.size();i++){
//         std::cout<<s7[i];
//     }
//     std::cout<<"\n";
// }