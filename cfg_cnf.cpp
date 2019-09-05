#include<bits/stdc++.h>
using namespace std;

class CFG
{
    char s;
    vector <char> t;
    vector <char> n;
    vector <pair<char, string>> p;

    void allPattern(vector <string> &s, string str, string curr, char ch, int index);
    void removeRedundant();

    void introduceStart();
    void removeNull();
    void removeUnit();
    void makeCNF();

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

void CFG::process()
{
    introduceStart();
    removeNull();
    removeUnit();
    makeCNF();
}

void CFG::allPattern(vector <string> &s, string str, string curr, char ch, int index)
{
    if(index==str.length())
    {
        s.push_back(curr);
        return;
    }
    if(str[index]!=ch)
    {
        curr.push_back(str[index]);
        allPattern(s, str, curr, ch, index+1);
    }
    else
    {
        allPattern(s, str, curr, ch, index+1);
        curr.push_back(str[index]);
        allPattern(s, str, curr, ch, index+1);
    }
}

void CFG::removeRedundant()
{
    set <pair<char, string>> mySet;
    vector <pair<char, string>> temp;
    for(int i=0;i<p.size();i++)
        mySet.insert(p[i]);
    for(auto it=mySet.begin();it!=mySet.end();it++)
        temp.push_back(*it);
    p=temp;
}

void CFG::introduceStart()
{
    string start="";
    start.push_back(s);
    s='P';
    n.push_back(s);
    p.insert(p.begin(),make_pair('P',start));
}

void CFG::removeNull()
{
    bool indicate=true;
    while(indicate==true)
    {
        indicate=false;
        int y=p.size();
        for(int i=0;i<y;i++)
        {
            string temp=p[i].second;
            if(p[i].first==s)
                continue;
            if(temp.compare("E")==0)
            {
                char ch=p[i].first;
                p.erase(p.begin()+i);
                int x=p.size();
                for(int j=0;j<x;j++)
                {
                    bool flag=false;
                    string str=p[j].second;
                    for(int k=0;k<str.length();k++)
                    {
                        if(str[k]==ch)
                        {
                            flag=true;
                            break;
                        }
                    }
                    if(flag==true)
                    {
                        vector <string> s;
                        allPattern(s, str, "", ch, 0);
                        for(int k=0;k<s.size();k++)
                        {
                            if(p[j].first==s[k][0]&&s[k].length()==1)   continue;
                            if(s[k].length()==0)
                                p.push_back(make_pair(p[j].first, "E"));
                            else
                                p.push_back(make_pair(p[j].first, s[k]));
                        }
                    }
                }
                indicate=true;
                break;
            }
        }
    }
    removeRedundant();
}

void CFG::removeUnit()
{
    bool indicate=true;
    while(indicate==true)
    {
        indicate=false;
        for(int i=0;i<p.size();i++)
        {
            string temp=p[i].second;
            if(temp.length()==1)
            {
                bool flag=false;
                for(int j=0;j<n.size();j++)
                {
                    if(temp[0]==n[j])
                    {
                        flag=true;
                        break;
                    }
                }
                if(flag==true)
                {
                    char ch=p[i].first;
                    string right=p[i].second;
                    p.erase(p.begin()+i);
                    vector <string> inserting;
                    for(int j=0;j<p.size();j++)
                    {
                        if(p[j].first==right[0])
                            inserting.push_back(p[j].second);
                    }
                    for(int j=0;j<inserting.size();j++)
                        p.push_back(make_pair(ch,inserting[j]));
                    indicate=true;
                    break;
                }
            }
        }
    }
    removeRedundant();
}

void CFG::makeCNF()
{
    unordered_map <char, char> myMap1;
    int k=49;
    for(int i=0;i<t.size();i++)
    {
        if(myMap1.find(t[i])==myMap1.end())
            myMap1[t[i]]=k++;
    }

    for(int i=0;i<p.size();i++)
    {
        string right=p[i].second;
        if(right.length()<=1)   continue;
        for(int j=0;j<right.length();j++)
        {
            if(myMap1.find(right[j])!=myMap1.end())
                p[i].second[j]=myMap1[right[j]];
        }
    }

    for(auto it=myMap1.begin();it!=myMap1.end();it++)
    {
        char ch=it->second;
        string str="";
        str.push_back(it->first);
        n.push_back(ch);
        p.push_back(make_pair(ch, str));
    }

    unordered_map <string, char> myMap2;
    k=57;
    bool flag=true;
    int l=p.size();
    for(int i=0;i<l;i++)
    {
        if(p[i].second.length()<=2)  continue;
        else
        {
            char left=p[i].first;
            string temp=p[i].second;
            char first_char=temp[0];
            temp=temp.substr(1);
            if(myMap2.find(temp)!=myMap2.end())
            {
                string to_insert="";
                to_insert.push_back(first_char);
                to_insert.push_back(myMap2[temp]);
                p.erase(p.begin()+i);
                p.push_back(make_pair(left, to_insert));
            }
            else
            {
                myMap2[temp]=k--;
                string to_insert="";
                to_insert.push_back(first_char);
                to_insert.push_back(myMap2[temp]);
                p.erase(p.begin()+i);
                p.push_back(make_pair(left, to_insert));
            }
            i--;
        }
    }

    for(auto it=myMap2.begin();it!=myMap2.end();it++)
    {
        char ch=it->second;
        string str=it->first;
        n.push_back(ch);
        p.push_back(make_pair(ch, str));
    }

}

int main()
{
    char s1='C';
    vector <char> t1{'a','b'};
    vector <char> n1{'A','B','C'};
    vector <pair<char, string>> p1{make_pair('C',"ACA"), make_pair('C',"aB"), make_pair('A',"B"), make_pair('A',"C"), make_pair('B',"b"), make_pair('B',"E")};
    CFG obj1(s1, t1, n1, p1);
    obj1.process();
    obj1.showData();
    cout<<endl<<endl;

    char s2='A';
    vector <char> t2{'o'};
    vector <char> n2{'A','B'};
    vector <pair<char, string>> p2{make_pair('A',"BAB"), make_pair('A',"B"), make_pair('A',"E"), make_pair('B',"oo"), make_pair('B',"E")};
    CFG obj2(s2, t2, n2, p2);
    obj2.process();
    obj2.showData();
    cout<<endl<<endl;

    char s3='S';
    vector <char> t3{'a','b'};
    vector <char> n3{'S','A','B'};
    vector <pair<char, string>> p3{make_pair('S',"ASB"), make_pair('A',"aAS"), make_pair('A',"a"), make_pair('A',"E"), make_pair('B',"SbS"), make_pair('B',"A"), make_pair('B',"bb")};
    CFG obj3(s3, t3, n3, p3);
    obj3.process();
    obj3.showData();
    cout<<endl<<endl;

    char s4='K';
    vector <char> t4{'+','*','(',')','g'};
    vector <char> n4{'K','T','F'};
    vector <pair<char, string>> p4{make_pair('K',"K+T"),make_pair('K',"T"),make_pair('T',"T*F"),make_pair('T',"F"),make_pair('F',"(K)"),make_pair('F',"g")};
    CFG obj4(s4, t4, n4, p4);
    obj4.process();
    obj4.showData();
    cout<<endl<<endl;

    return 0;
}
