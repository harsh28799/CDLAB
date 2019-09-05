#include<bits/stdc++.h>
using namespace std;

class CFG
{
    char count='1';
    char s;
    vector <char> t;
    vector <char> n;
    vector <pair<char, string>> p;
    vector <char> total;

    void findLeftFactoring();
    void removeLeftFactoring(char left, char right);

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
    for(int i=0;i<t.size();i++)
        total.push_back(t[i]);
    for(int i=0;i<n.size();i++)
        total.push_back(n[i]);
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
    cout<<"Total\t"<<endl;
    for(int i=0;i<total.size();i++)
        cout<<total[i]<<" ";
    cout<<endl;
}

void CFG::removeLeftFactoring(char left, char right)
{
    int num1=p.size();
    vector <string> temp;
    for(int i=0;i<num1;i++)
    {
        char ch=p[i].first;
        string str=p[i].second;
        if(ch==left&&str[0]==right)
        {
            temp.push_back(str.substr(1));
            p.erase(p.begin()+i);
            i--;
        }
        num1=p.size();
    }
    string s="";
    s.push_back(right);
    s.push_back(count);
    p.push_back(make_pair(left,s));
    for(int i=0;i<temp.size();i++)
    {
        if(temp[i].compare("")!=0)
            p.push_back(make_pair(count,temp[i]));
        else
            p.push_back(make_pair(count,"E"));
    }
    n.push_back(count);
    count=count+1;
}

void CFG::findLeftFactoring()
{
        int f=0;
        bool flag=true;
        while(flag==true)
        {
            f++;
            flag=false;
            int num1=n.size();
            for(int i=0;i<num1;i++)
            {
                char left=n[i];
                int num2=total.size();
                for(int j=0;j<num2;j++)
                {
                    int ctr=0;
                    char right=total[j];
                    int num3=p.size();
                    for(int k=0;k<num3;k++)
                    {
                        if(p[k].first==left&&p[k].second[0]==right)
                            ctr++;
                    }
                    if(ctr>1)
                    {
                        removeLeftFactoring(left, right);
                        flag=true;
                    }
                }
            }
        }
        if(f>1)
            cout<<"Left Factoring Possible"<<endl;
        else
            cout<<"No possibility of Left Factoring"<<endl;
}

void CFG::process()
{
    findLeftFactoring();
}

int main()
{
    char s1='S';
    vector <char> t1{'a','b','c','d','e','f'};
    vector <char> n1{'S'};
    vector <pair<char, string>> p1{make_pair('S',"a"),make_pair('S',"ab"),make_pair('S',"abc"),make_pair('S',"abcd"),make_pair('S',"e"),make_pair('S',"f")};
    CFG obj1(s1, t1, n1, p1);
    obj1.process();
    obj1.showData();
    cout<<endl<<endl;

    char s2='S';
    vector <char> t2{'a','b','c','d','e'};
    vector <char> n2{'S','B'};
    vector <pair<char, string>> p2{make_pair('S',"aBbS"),make_pair('S',"aBbSeS"),make_pair('S',"c"),make_pair('S',"d")};
    CFG obj2(s2, t2, n2, p2);
    obj2.process();
    obj2.showData();
    cout<<endl<<endl;

    char s3='K';
    vector <char> t3{'+','*','(',')','g'};
    vector <char> n3{'K','T','F'};
    vector <pair<char, string>> p3{make_pair('K',"K+T"),make_pair('K',"T"),make_pair('T',"T*F"),make_pair('T',"F"),make_pair('F',"(K)"),make_pair('F',"g")};
    CFG obj3(s3, t3, n3, p3);
    obj3.process();
    obj3.showData();
    cout<<endl<<endl;

    return 0;
}
