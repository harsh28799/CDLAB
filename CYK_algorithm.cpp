#include<bits/stdc++.h>
using namespace std;

class CFG
{
    char s;
    vector <char> t;
    vector <char> n;
    vector <pair<char, string>> p;
    string word;
    int len;

    vector <char> arr[25][25];

    unordered_map <string, vector <char>> myMap;

    void processProduction();
    void cykAlgorithm();
    void fillTable(int x, int y, vector <string> &temp);
    void findNewPair(int w, int x, int y, int z, vector <string> &temp);
    void giveDecision();

public:
    CFG(char , vector <char>, vector <char>, vector <pair<char, string>>, string word);
    CFG();

    void getData();
    void process();
    void display();
    void showData();
};

CFG::CFG(char s, vector <char> t, vector <char> n, vector <pair<char, string>> p, string word)
{
    this->s=s;
    this->t=t;
    this->n=n;
    this->p=p;
    this->word=word;
    this->len=word.length();
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
    cout<<"The string is :"<<word<<endl;
}

void CFG::display()
{
    for(int i=0;i<len;i++)
    {
        for(int j=0;j<len-i;j++)
        {
            vector <char> ch=arr[i][j];
            for(int k=0;k<ch.size();k++)
                cout<<ch[k]<<" ";
            cout<<"\t";
        }
        cout<<endl;
    }
}

void CFG::process()
{
    processProduction();
    cykAlgorithm();
    display();
    giveDecision();
}

void CFG::findNewPair(int w, int x, int y, int z, vector <string> &temp)
{
    vector <char> one=arr[w][x];
    vector <char> two=arr[y][z];
    for(int i=0;i<one.size();i++)
    {
        for(int j=0;j<two.size();j++)
        {
            string str="";
            str.push_back(one[i]);
            str.push_back(two[j]);
            temp.push_back(str);
        }
    }
}

void CFG::fillTable(int x, int y, vector <string> &temp)
{
    vector <char> m;
    for(int i=0;i<temp.size();i++)
    {
        if(myMap.find(temp[i])!=myMap.end())
        {
            vector <char> f=myMap[temp[i]];
            for(int j=0;j<f.size();j++)
            {
                m.push_back(f[j]);
            }
        }
    }
    arr[x][y]=m;
}

void CFG::processProduction()
{
    for(int i=0;i<p.size();i++)
    {
        char ch=p[i].first;
        string str=p[i].second;
        myMap[str].push_back(ch);
    }
}

void CFG::cykAlgorithm()
{
    for(int i=0;i<len;i++)
    {
        string str="";
        str.push_back(word[i]);
        vector <char> f=myMap[str];
        arr[0][i]=f;
    }
    for(int i=1;i<len;i++)
    {
        for(int j=0;j<len-i;j++)
        {
            vector <string> temp;
            for(int k=0;k<i;k++)
            {
                findNewPair(k,j,i-k-1,j+k+1,temp);
            }
            fillTable(i,j,temp);
            cout<<endl;
        }
    }
}

void CFG::giveDecision()
{
    vector <char> ch=arr[len-1][0];
    for(int i=0;i<ch.size();i++)
    {
        if(ch[i]==s)
        {
            cout<<"String can be produced from the given Grammer"<<endl;
            return;
        }
    }
    cout<<"String cannot be produced from the given Grammer"<<endl;
}

int main()
{
    char s1='A';
    vector <char> t1{'a','b'};
    vector <char> n1{'A','B','C'};
    vector <pair<char, string>> p1{make_pair('A',"BC"),make_pair('B',"CC"),make_pair('B',"a"),make_pair('C',"b")};
    string word1="abba";
    CFG obj1(s1, t1, n1, p1,word1);
    obj1.showData();
    obj1.process();
    cout<<endl<<endl;

    char s2='A';
    vector <char> t2{'a','b'};
    vector <char> n2{'A','B','C'};
    vector <pair<char, string>> p2{make_pair('A',"BC"),make_pair('B',"CC"),make_pair('B',"a"),make_pair('C',"b")};
    string word2="bbb";
    CFG obj2(s2, t2, n2, p2,word2);
    obj2.showData();
    obj2.process();
    cout<<endl<<endl;

    char s3='A';
    vector <char> t3{'a','b'};
    vector <char> n3{'A','B','C'};
    vector <pair<char, string>> p3{make_pair('A',"BC"),make_pair('B',"CC"),make_pair('B',"a"),make_pair('C',"b")};
    string word3="ab";
    CFG obj3(s3, t3, n3, p3,word3);
    obj3.showData();
    obj3.process();
    cout<<endl<<endl;

    return 0;
}

