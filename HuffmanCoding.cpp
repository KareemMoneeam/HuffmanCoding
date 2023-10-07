#include <bits/stdc++.h>
#define ll long long
using namespace std;
map<char,string>table;
string decode(map<char,string>& tbl);
int main()
{
    string text; cin>>text;
    double n=text.size();


    map<string,double>probability;
    for(int i=0 ; i<text.size() ; i++){
        int cnt = count(text.begin(),text.end(),text[i]);
        string key;key=text[i];
        probability[key]=-1*(cnt/n);
    }

    multimap<double,string>st;      ///aaabbbbbccccccddddee ///{-0.02,"f"},{-0.14,"d"},{-0.15,"c"},{-0.17,"a"},{-0.22,"b"},{-0.3,"e"}
    for(auto p : probability){
        st.insert({p.second,p.first});
    }

    map<char,int>mp;
    while(st.size()>2)
    {
        auto it=--st.end();

        string txt=(*--it).second;
        txt+=(*++it).second;

        double n=((*it).first);
        n+=((*--it).first);

        st.erase(--st.end());
        st.erase(--st.end());

        st.insert({n,txt});
        for(auto ch:txt){mp[ch]++;}
    }


    //for(auto ch:st){cout<<ch.first<<"-"<<ch.second<<"    ";} cout<<endl;
    string initial ="0";
    for(auto s : st)
    {
        string encode1=s.second;
        while(encode1.size()>1)
        {

            char ch1=encode1[0], ch2=encode1[encode1.size()-1];
            if(mp[ch1]<mp[ch2]){
                encode1=encode1.substr(1,encode1.size());
                table[ch1]=initial+"0";
                initial+="1";
            }
            else if(mp[ch2]<mp[ch1]){
                encode1=encode1.substr(0,encode1.size()-1);
                table[ch2]=initial+"1";
                initial+="0";
            }
            else if(mp[ch2]==mp[ch1]){
                table[ch1]=initial+"0";
                table[ch2]=initial+"1";
                break;
            }
        }
        initial="1";
    }
    for(auto t:table){cout<<t.first<<":"<<t.second<<endl;}
    cout<<decode(table);


}

string decode(map<char,string>& tbl)
{
    string text,result=""; cin>>text;
    string code;
    for(auto ch:text)
    {
        code+=ch;
        for(auto row:tbl)
        {
            if(row.second==code)
            {
                result+=row.first;
                code="";
                break;
            }
        }
    }
    return result;
}