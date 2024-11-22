#include<bits/stdc++.h>
#include<string>
using namespace std;

class BigInt
{
    string digit;
public:


    // constructor
    BigInt(unsigned long long nr=0);
    BigInt(BigInt &);
    BigInt(const char*);
    BigInt(string&);
   

   // helper functions
   friend bool Null(const BigInt &);
   friend int Length(const BigInt &);
   int operator[](const int)const;

   //comparison operator
    friend bool operator==(const BigInt &, const BigInt &);
    friend bool operator!=(const BigInt &, const BigInt &);
 
    friend bool operator>(const BigInt &, const BigInt &);
    friend bool operator>=(const BigInt &, const BigInt &);
    friend bool operator<(const BigInt &, const BigInt &);
    friend bool operator<=(const BigInt &, const BigInt &);

    //pre - post increment and decrement
    BigInt &operator++();
    BigInt operator++(int temp);
    BigInt &operator--();
    BigInt operator--(int temp);

    //Arithmentic addition and subtraction
    friend BigInt &operator+=(BigInt &, const BigInt &);
    friend BigInt operator+(const BigInt &, const BigInt &);
    friend BigInt operator-(const BigInt &, const BigInt &);
    friend BigInt &operator-=(BigInt &, const BigInt &);

    //multiplication and division
    friend BigInt &operator*=(BigInt &, const BigInt &);
    friend BigInt operator*(const BigInt &, const BigInt &);
    friend BigInt &operator/=(BigInt &, const BigInt &);
    friend BigInt operator/(const BigInt &, const BigInt &);

    //Modulo
    friend BigInt operator%(const BigInt &, const BigInt &);
    friend BigInt &operator%=(BigInt &, const BigInt &);

    //insertion and extraction operator overloading 
    friend ostream &operator<<(ostream &,const BigInt &);
    friend istream &operator>>(istream &, BigInt &);

    // fibonacci and factorial
    friend BigInt NthFibonacci(int n);
    friend BigInt Factorial(int n);
};

// default as well parametrized 
BigInt::BigInt(unsigned long long nr)
{
   do{
    digit.push_back(nr%10);
    nr/=10;
   }while(nr);
}

//copy constructor
BigInt:: BigInt(BigInt & num)
{
    digit=num.digit;
}


//parametried
BigInt:: BigInt(const char *arr)
{
    digit="";
   for(int i=strlen(arr)-1;i>=0;i--)
   {
      if(!isdigit(arr[i]))
         throw("ERROR");
       int ch=arr[i]-'0';
       digit.push_back(arr[i]-'0');
   }
   
}


//parametrized
BigInt:: BigInt(string&s)
{
    digit="";
    for(int i=s.size()-1;i>=0;i--)
    {
        if(!isdigit(s[i]))
           throw("ERROR");
        digit.push_back(s[i]-'0');

            
    }

}

bool Null(const BigInt& a){
    if(a.digit.size() == 1 && a.digit[0] == 0)
        return true;
    return false;
}


int Length(const BigInt & a)
{
    return a.digit.size();
}



int BigInt::operator[](const int index)const{
    if(digit.size() <= index || index < 0)
        throw("ERROR");
    return digit[index];
}


bool operator==(const BigInt &a, const BigInt &b){
    return a.digit == b.digit;
}


bool operator!=(const BigInt & a,const BigInt &b){
    return !(a == b);
}


bool operator<(const BigInt&a,const BigInt&b){
    int n = Length(a), m = Length(b);
    if(n != m)
        return n < m;
    while(n--){
        if(a.digit[n] != b.digit[n])
            return a.digit[n] < b.digit[n];
    }
    return false;
}


bool operator>(const BigInt &a, const BigInt &b)
{
    return !(a<b);
}


bool operator>=(const BigInt&a,const BigInt&b){
    return !(a < b);
}


bool operator<=(const BigInt&a,const BigInt&b){
    return !(a > b);
}


BigInt &BigInt::operator++(){
    int i, n = digit.size();
    for (i = 0; i < n && digit[i] == 9;i++)
        digit[i] = 0;
    if(i == n)
        digit.push_back(1);
    else
        digit[i]++;
    return *this;
}


BigInt BigInt::operator++(int temp){
    BigInt aux;
    aux = *this;
    ++(*this);
    return aux;
}


BigInt &BigInt::operator--(){
    if(digit[0] == 0 && digit.size() == 1)
        throw("UNDERFLOW");
    int i, n = digit.size();
    for (i = 0; digit[i] == 0 && i < n;i++)
        digit[i] = 9;
    digit[i]--;
    if(n > 1 && digit[n - 1] == 0)
        digit.pop_back();
   return *this;
}


BigInt BigInt::operator--(int temp){
    BigInt aux;
    aux = *this;
    --(*this);
    return aux;
}







//Addition and Subtraction

BigInt &operator+=(BigInt &a, const BigInt &b)
{
   int t = 0, s, i;                         //t=carry
    int n = Length(a), m = Length(b);
    if(m > n)
        a.digit.append(m - n, 0);
    n = Length(a);
    for (i = 0; i < n;i++){
        if(i < m)
            s = (a.digit[i] + b.digit[i]) + t;
        else
            s = a.digit[i] + t;
        t = s / 10;
        a.digit[i] = (s % 10);
    }
    if(t)
        a.digit.push_back(t);
    return a;
}


BigInt operator+(const BigInt &a, const BigInt &b){
    BigInt temp;
    temp = a;
    temp += b;
    return temp;
}


BigInt &operator-=(BigInt&a,const BigInt &b){
    if(a < b)
        throw("UNDERFLOW");
    int n = Length(a), m = Length(b);
    int i, t = 0, s;
    for (i = 0; i < n;i++){
        if(i < m)
            s = a.digit[i] - b.digit[i]+ t;
        else
            s = a.digit[i]+ t;
        if(s < 0)
            s += 10,
            t = -1;
        else
            t = 0;
        a.digit[i] = s;
    }
    while(n > 1 && a.digit[n - 1] == 0)
        a.digit.pop_back(),
        n--;
    return a;
}


BigInt operator-(const BigInt& a,const BigInt&b){
    BigInt temp;
    temp = a;
    temp -= b;
    return temp;
}







//Multiplication and division


BigInt &operator*=(BigInt &a, const BigInt &b)
{
    if(Null(a) || Null(b)){
        a = BigInt();
        return a;
    }
    int n = a.digit.size(), m = b.digit.size();
    vector<int> v(n + m, 0);
    for (int i = 0; i < n;i++)
        for (int j = 0; j < m;j++){
            v[i + j] += (a.digit[i] ) * (b.digit[j]);
        }
    n += m;
    a.digit.resize(v.size());
    for (int s, i = 0, t = 0; i < n; i++)
    {
        s = t + v[i];
        v[i] = s % 10;
        t = s / 10;
        a.digit[i] = v[i] ;
    }
    for (int i = n - 1; i >= 1 && !v[i];i--)
            a.digit.pop_back();
    return a;
}


BigInt operator*(const BigInt&a,const BigInt&b){
    BigInt temp;
    temp = a;
    temp *= b;
    return temp;
}


BigInt &operator/=(BigInt& a,const BigInt &b){
    if(Null(b))
        throw("Arithmetic Error: Division By 0");
    if(a < b){
        a = BigInt();
        return a;
    }
    if(a == b){
        a = BigInt(1);
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Length(a), m = Length(b);
    vector<int> cat(n, 0);
    BigInt t;
    for (i = n - 1; t * 10 + a.digit[i]  < b;i--){
        t *= 10;
        t += a.digit[i] ;
    }
    for (; i >= 0; i--){
        t = t * 10 + a.digit[i];
        for (cc = 9; cc * b > t;cc--);
        t -= cc * b;
        cat[lgcat++] = cc;
    }
    a.digit.resize(cat.size());
    for (i = 0; i < lgcat;i++)
        a.digit[i] = cat[lgcat - i - 1];
    a.digit.resize(lgcat);
    return a;
}

BigInt operator/(const BigInt &a,const BigInt &b){
    BigInt temp;
    temp = a;
    temp /= b;
    return temp;
}

BigInt &operator%=(BigInt& a,const BigInt &b){
    if(Null(b))
        throw("Arithmetic Error: Division By 0");
    if(a < b){
        return a;
    }
    if(a == b){
        a = BigInt();
        return a;
    }
    int i, lgcat = 0, cc;
    int n = Length(a), m = Length(b);
    vector<int> cat(n, 0);
    BigInt t;
    for (i = n - 1; t * 10 + a.digit[i] < b;i--){
        t *= 10;
        t += a.digit[i];
    }
    for (; i >= 0; i--){
        t = t * 10 + a.digit[i];
        for (cc = 9; cc * b > t;cc--);
        t -= cc * b;
        cat[lgcat++] = cc;
    }
    a = t;
    return a;
}
BigInt operator%(const BigInt &a,const BigInt &b){
    BigInt temp;
    temp = a;
    temp %= b;
    return temp;
}
 





// NthFibonaccii
BigInt NthFibonacci(int n){
    BigInt a(1), b(1), c;
    if(!n)
        return c;
    n--;
    while(n--){
        c = a + b;
        b = a;
        a = c;
    }
    return b;
}


//Factorial
BigInt Factorial(int n){
    BigInt f(1);
    for (int i = 2; i <= n;i++)
        f *= i;
    return f;
}

// insertion ans extraction

istream &operator>>(istream &in,BigInt&a){
    string s;
    in >> s;
    int n = s.size();
    for (int i = n - 1; i >= 0;i--){
        if(!isdigit(s[i]))
            throw("INVALID NUMBER");
        a.digit[n - i - 1] = s[i];
    }
    return in;
}


ostream &operator<<(ostream &out,const BigInt &a){
    for (int i = a.digit.size() - 1; i >= 0;i--)
        cout << (short)a.digit[i];
    return cout;
}

int main()
{
    BigInt First(123);
    BigInt second("1234567894578");
    string B="1238645743";
    BigInt third(B);
    BigInt fourth(B);

    cout<<"First Bigint is"<<"="<<First<<endl;
    cout<<"Second Bigint is"<<"="<<second<<endl;;
    cout<<"Third Bigint is"<<"="<<third<<endl;
    cout<<"fourth Bigint is"<<"="<<fourth<<endl<<endl;

    cout<<"------------Relatinal operator------------"<<endl;
    cout<<"is first greater than second"<<"      ->    "<<First<<">"<<second<<"   ->   "<<(First>second)<<endl;
    cout<<"is third equal to fourth    "<<"      ->    "<<third<<">"<<fourth<<"   ->   "<<(third==fourth)<<endl<<endl;
     BigInt a(1234);
     BigInt b(9876);
    if(a>b)
      cout<<"first is greater then second";
    else
       cout<<"second is greater then first"<<endl;

    cout<<"summation of above two numbers is"<<"->";
    a+=b;
    cout<<a<<endl;
    cout<<"--------sum with int----------"<<endl;
    cout<<a+123456767895322<<endl;

    cout<<"multiplication of above two numbers is"<<"->";
    a*=b;
    cout<<a<<endl<<endl;

    cout<<"------------fibonacci--------------"<<endl;
    
    for(int i=90;i<100;i++)
    {
        cout<<"fibonacci of "<<i<<" is  ->  ";
        cout<<NthFibonacci(i)<<endl;
    }

cout<<endl<<endl;
 cout<<"------------factorial--------------"<<endl;
    
    for(int i=90;i<100;i++)
    {
        cout<<"factorial of "<<i<<" is  ->  ";
        cout<<Factorial(i)<<endl;
    }
     

    return 0;
}

