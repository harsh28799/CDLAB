
#include<bits/stdc++.h>
using namespace std;

class CFG
{
    char s;
    vector <char> t;
    vector <char> n;
    vector <pair<char, string>> p;

    unordered_map <char, vector <char>> first;
    unordered_map <char, vector <char>> follow;

    unordered_map <char, int> myMapT;
    unordered_map <char, int> myMapN;
    string arr[25][25];

    bool checkPresence(vector <char>, char);
    void makeSetFirst();
    void processFirst();
    void makeSetFollow();
    void processFollow();
    void associateNonAndTerminal();
    void fillTable();

public:
    CFG(char , vector <char>, vector <char>, vector <pair<char, string>>);
    CFG();

    void getData();
    void process();
    void showData();
    void display();
};

CFG::CFG(char s, vector <char> t, vector <char> n, vector <pair<char, string>> p)
{
    this->s=s;
    this->t=t;
    this->n=n;
    this->p=p;

    int x=n.size();
    int y=t.size()+1;
    for(int i=0;i<x;i++)
    {
        for(int j=0;j<y;j++)
            arr[i][j]="";
    }
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

void CFG::display()
{
    cout<<"Non Terminal\t"<<"Start\t\t"<<"Follow\t"<<endl;
    for(int i=0;i<n.size();i++)
    {
        cout<<n[i]<<"\t\t";
        vector <char> temp1=first[n[i]];
        vector <char> temp2=follow[n[i]];
        for(int j=0;j<temp1.size();j++)
            cout<<temp1[j]<<" ";
        cout<<"\t\t";
        if(temp2.size()==0)
            cout<<"NA";
        for(int j=0;j<temp2.size();j++)
            cout<<temp2[j]<<" ";
        cout<<endl;
    }

    cout<<endl;
    cout<<endl;

    for(auto it=myMapT.begin();it!=myMapT.end();it++)
        cout<<it->first<<"=="<<it->second<<endl;
    cout<<endl;

    for(auto it=myMapN.begin();it!=myMapN.end();it++)
        cout<<it->first<<"=="<<it->second<<endl;
    cout<<endl;

    int x=n.size();
    int y=t.size()+1;
    cout<<"XX\t";
    for(int i=1;i<=y;i++)
        cout<<i-1<<"\t";
    cout<<endl;
    cout<<"_______________________________________________________________________________________"<<endl;
    for(int i=0;i<x;i++)
    {
        cout<<i<<"|\t";
        for(int j=0;j<y;j++)
            cout<<arr[i][j]<<"\t";
        cout<<endl;
    }

}

void CFG::process()
{
    makeSetFirst();
    processFirst();
    makeSetFollow();
    processFollow();
    associateNonAndTerminal();
    fillTable();
}

bool CFG::checkPresence(vector <char> x, char y)
{
    for(int i=0;i<x.size();i++)
    {
        if(x[i]==y)
            return true;
    }
    return false;
}

void CFG::makeSetFirst()
{
    for(int i=0;i<t.size();i++)
        first[t[i]].push_back(t[i]);
    for(int i=0;i<n.size();i++)
        first[n[i]]={};
    first['E'].push_back('E');
}

void CFG::processFirst()
{
    bool flag1=true;
    while(flag1==true)
    {
        flag1=false;
        int num1=p.size();
        for(int i=0;i<num1;i++)
        {
            char left=p[i].first;
            string str=p[i].second;
            int x=0;
            bool flag2=true;
            while(flag2==true)
            {
                flag2=false;
                vector <char> temp=first[str[x]];
                for(int j=0;j<temp.size();j++)
                {
                    if(temp[j]=='E')
                    {
                        flag2=true;
                        continue;
                    }
                    if(!checkPresence(first[left],temp[j]))
                    {
                        first[left].push_back(temp[j]);
                        flag1=true;
                    }
                }
                if(flag2==true)
                {
                    x++;
                    if(x>=str.length())
                    {
                        if(!checkPresence(first[left],'E'))
                        {
                            first[left].push_back('E');
                            flag1=true;
                        }
                        break;
                    }
                }
            }
        }
    }
}

void CFG::makeSetFollow()
{
    for(int i=0;i<t.size();i++)
        follow[t[i]].push_back(t[i]);
    for(int i=0;i<n.size();i++)
        follow[n[i]]={};
    follow[s].push_back('$');
}

void CFG::processFollow()
{
    bool flag1=true;
    while(flag1==true)
    {
        flag1=false;
        int num1=n.size();
        for(int i=0;i<num1;i++)
        {
            char ch=n[i];
            int num2=p.size();
            for(int j=0;j<num2;j++)
            {
                char ch1=p[j].first;
                string str=p[j].second;
                int num3=str.length();
                for(int k=0;k<num3;k++)
                {
                    bool flag3=true;
                    if(str[k]==ch)
                    {
                        flag3=false;
                        bool flag2=true;
                        while(flag2==true)
                        {
                            flag2=false;
                            k++;
                            if(k==num3)
                            {
                                vector <char> temp1=follow[ch];
                                vector <char> temp2=follow[ch1];
                                for(int l=0;l<temp2.size();l++)
                                {
                                    if(!checkPresence(temp1,temp2[l]))
                                    {
                                        temp1.push_back(temp2[l]);
                                        flag1=true;
                                    }
                                }
                                follow[ch]=temp1;
                            }
                            else
                            {
                                vector <char> temp1=follow[ch];
                                vector <char> temp2=first[str[k]];
                                for(int l=0;l<temp2.size();l++)
                                {
                                    if(temp2[l]=='E')
                                    {
                                        flag2=true;
                                        continue;
                                    }
                                    if(!checkPresence(temp1,temp2[l]))
                                    {
                                        temp1.push_back(temp2[l]);
                                        flag1=true;
                                    }
                                }
                                follow[ch]=temp1;
                            }
                        }
                    }
                }
            }
        }
    }
}

void CFG::associateNonAndTerminal()
{
    int i;
    for(i=0;i<n.size();i++)
        myMapN[n[i]]=i;
    for(int i=0;i<t.size();i++)
        myMapT[t[i]]=i;
    myMapT['$']=i;
}

void CFG::fillTable()
{
    bool flag=false;
    int num1=p.size();
    for(int i=0;i<num1;i++)
    {
        char left=p[i].first;
        char right=p[i].second[0];
        if(right=='E')
        {
            vector <char> temp=follow[left];
            for(int j=0;j<temp.size();j++)
            {
                int x=myMapN[left];
                int y=myMapT[temp[j]];
                if(arr[x][y]=="")
                    arr[x][y]=p[i].second;
                else
                {
                    flag=true;
                    break;
                }
            }
        }
        else
        {
            vector <char> temp=first[right];
            for(int j=0;j<temp.size();j++)
            {
                if(temp[j]=='E')
                    continue;
                int x=myMapN[left];
                int y=myMapT[temp[j]];
                if(arr[x][y]=="")
                    arr[x][y]=p[i].second;
                else
                {
                    flag=true;
                    break;
                }
            }
        }
        if(flag==true)
        {
            cout<<endl<<"Not a LL1 Grammer"<<endl<<endl;
            break;
        }
    }
    if(flag==false)
        cout<<endl<<"A LL1 Grammer"<<endl<<endl;
}

int main()
{
    char s1='S';
    vector <char> t1{'a','b','c','d','g','h'};
    vector <char> n1{'S','A','B','C'};
    vector <pair<char, string>> p1{make_pair('S',"ACB"), make_pair('S',"Cbb"), make_pair('S',"Ba"), make_pair('A',"da"), make_pair('A',"BC"), make_pair('B',"g"), make_pair('B',"E"), make_pair('C',"h"), make_pair('C',"E")};
    CFG obj1(s1, t1, n1, p1);
    obj1.process();
    obj1.showData();
    obj1.display();
    cout<<endl<<endl;

    char s2='A';
    vector <char> t2{'*','+','(',')','x'};
    vector <char> n2{'A','B','C','D','F'};
    vector <pair<char, string>> p2{make_pair('A',"BC"), make_pair('C',"+BC"), make_pair('C',"E"), make_pair('B',"FD"), make_pair('D',"*FD"), make_pair('D',"E"), make_pair('F',"(A)"), make_pair('F',"x")};
    CFG obj2(s2, t2, n2, p2);
    obj2.process();
    obj2.showData();
    obj2.display();
    cout<<endl<<endl;

    char s3='S';
    vector <char> t3{'a','b','c'};
    vector <char> n3{'A','B','C','S'};
    vector <pair<char, string>> p3{make_pair('S',"ABC"), make_pair('A',"a"), make_pair('A',"E"), make_pair('B',"b"), make_pair('B',"E"), make_pair('C',"c")};
    CFG obj3(s3, t3, n3, p3);
    obj3.process();
    obj3.showData();
    obj3.display();
    cout<<endl<<endl;

    char s4='A';
    vector <char> t4{'a','b','c','d','e','f','g','h','i'};
    vector <char> n4{'A'};
    vector <pair<char, string>> p4{make_pair('A',"abc"), make_pair('A',"def"), make_pair('A',"ghi")};
    CFG obj4(s4, t4, n4, p4);
    obj4.process();
    obj4.showData();
    obj4.display();
    cout<<endl<<endl;

    char s5='S';
    vector <char> t5{'a','b','c','f','g','h'};
    vector <char> n5{'S','B','C','D','F','G'};
    vector <pair<char, string>> p5{make_pair('S',"aBDh"), make_pair('B',"cC"), make_pair('C',"bC"), make_pair('C',"E"), make_pair('D',"GF"), make_pair('G',"g"), make_pair('G',"E"), make_pair('F',"f"), make_pair('F',"E")};
    CFG obj5(s5, t5, n5, p5);
    obj5.process();
    obj5.showData();
    obj5.display();
    cout<<endl<<endl;

    char s6='S';
    vector <char> t6{'a','b','d','g'};
    vector <char> n6{'S','A','B','C','D'};
    vector <pair<char, string>> p6{make_pair('S',"A"), make_pair('A',"aBC"), make_pair('C',"dC"), make_pair('C',"E"), make_pair('B',"b"), make_pair('D',"g")};
    CFG obj6(s6, t6, n6, p6);
    obj6.process();
    obj6.showData();
    obj6.display();
    cout<<endl<<endl;

    char s7='S';
    vector <char> t7{'a'};
    vector <char> n7{'S','A'};
    vector <pair<char, string>> p7{make_pair('S',"A"), make_pair('S',"a"), make_pair('A',"a")};
    CFG obj7(s7, t7, n7, p7);
    obj7.process();
    obj7.showData();
    obj7.display();
    cout<<endl<<endl;

    return 0;
}
