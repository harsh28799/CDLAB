#include<bits/stdc++.h>
using namespace std;

class CFG
{
    char count='1';
    char s;
    vector <char> t;
    vector <char> n;
    vector <pair<char, string>> p;

    void eachNonTerminal(char x);
    void insertNonTerminal();

public:
    CFG(char , vector <char>, vector <char>, vector <pair<char, string>>);
    CFG();

    void getData();
    void process();
    void showData();
};

CFG::CFG(char s, vector <char> t, vector <char> n, vector <pair<char, string>> p)
{
    this->s=s;
    this->t=t;
    this->n=n;
    this->p=p;
}

CFG::CFG()
{
    getData();
}

void CFG::getData()
{
    cout<<"Enter the start state"<<endl;
    cin>>s;
    int num;
    cout<<"Enter the number of non terminals:"<<endl;
    cin>>num;
    cout<<"Enter the non terminals:"<<endl;
    for(int i=0;i<num;i++)
    {
        int temp;
        cin>>temp;
        t.push_back(temp);
    }
    cout<<"Enter the number of terminals:"<<endl;
    cin>>num;
    cout<<"Enter the terminals:"<<endl;
    for(int i=0;i<num;i++)
    {
        int temp;
        cin>>temp;
        n.push_back(temp);
    }
    cout<<"Enter the number of productions:"<<endl;
    cin>>num;
    cout<<"Enter the productions:"<<endl;
    for(int i=0;i<num;i++)
    {
        char ch;
        string str;
        cin>>ch>>str;
        p.push_back(make_pair(ch, str));
    }
}

void CFG::showData()
{
    cout<<"Star State:\t"<<s;
    cout<<endl;
    cout<<"Non terminals:\t";
    for(int i=0;i<n.size();i++)
        cout<<n[i]<<" ";
    cout<<endl;
    cout<<"Terminals:\t";
    for(int i=0;i<t.size();i++)
        cout<<t[i]<<" ";
    cout<<endl;
    cout<<"Productions:\t"<<endl;
    for(int i=0;i<p.size();i++)
        cout<<p[i].first<<"-->"<<p[i].second<<endl;
    cout<<endl;
}

void CFG::eachNonTerminal(char x)
{
    int num=p.size();
    vector <string> one;
    vector <string> two;
    for(int i=0;i<num;i++)
    {
        char ch=p[i].first;
        string str=p[i].second;
        if(ch==x)
        {
            if(str[0]==x&&str.length()>1)
                one.push_back(str.substr(1));
            else
                two.push_back(str);
        }
    }

    if(!one.empty())
    {
        for(int i=0;i<num;i++)
        {
            if(p[i].first==x)
            {
                p.erase(p.begin()+i);
                num=num-1;
                i--;
            }
        }
        for(int i=0;i<two.size();i++)
        {
            string str=two[i];
            str.push_back(count);
            p.push_back(make_pair(x,str));
        }
        for(int i=0;i<one.size();i++)
        {
            string str=one[i];
            str.push_back(count);
            p.push_back(make_pair(count,str));
        }
        p.push_back(make_pair(count,"E"));

        count=count+1;
    }

}

void CFG::insertNonTerminal()
{
    char ch='1';
    while(ch<count)
            n.push_back(ch++);
}

void CFG::process()
{
    for(int i=0;i<n.size();i++)
        eachNonTerminal(n[i]);
    insertNonTerminal();
}

int main()
{
    char s1='S';
    vector <char> t1{'a','b','c','d','e','f','g','h'};
    vector <char> n1{'S'};
    vector <pair<char, string>> p1{make_pair('S',"Sab"),make_pair('S',"Scd"),make_pair('S',"Sef"),make_pair('S',"g"),make_pair('S',"h")};
    CFG obj1(s1, t1, n1, p1);
    obj1.process();
    obj1.showData();
    cout<<endl<<endl;

    char s2='A';
    vector <char> t2{'a','b','c','d','e'};
    vector <char> n2{'A','B','C'};
    vector <pair<char, string>> p2{make_pair('A',"AaB"),make_pair('A',"B"),make_pair('B',"Bbc"),make_pair('B',"C"),make_pair('C',"cAd"),make_pair('C',"e")};
    CFG obj2(s2, t2, n2, p2);
    obj2.process();
    obj2.showData();
    cout<<endl<<endl;

    char s3='S';
    vector <char> t3{'a','b'};
    vector <char> n3{'S','A','B'};
    vector <pair<char, string>> p3{make_pair('S',"AaB"),make_pair('A',"SAc"),make_pair('A',"a"),make_pair('B',"Ba"),make_pair('B',"b")};
    CFG obj3(s3, t3, n3, p3);
    obj3.process();
    obj3.showData();
    cout<<endl<<endl;

    return 0;
}
