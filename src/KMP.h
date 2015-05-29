#include<iostream>
#include<cstring>
#include<cctype>
#include<cstdio>
using namespace std;

int v[2002];

void table(string p)
{
    //v[i] :where to go(what to compare next) if mismatch occur at i
    v[0]=0;  //obviously we ll stay at zero only even if its a mismatch
    v[1]=0;  //just think naturally where will u go if mismatch occur at 1

    int cur=0;
    for(int j=2;j<p.size();j++)
    {
        /*
        This is the case for mismatch:if mismatch occur at j we seek to find the first
        occurence of p[j-1] in the pattern such that the sequence preceding j-1(0...j-2)
        locations have alreaddy been matched
        */
        while(cur!=0 && p[cur]!=p[j-1])
        cur=v[cur];

        if(p[cur]==p[j-1]) //Case for match:length of prematched sequence increments by 1
        cur=cur+1;

        v[j]=cur;
    }

}

bool kmp(string p,string text)
{
    table(p);
    int cur=0; //cur: All locations before cur have been matched.
    for(int j=0;j<text.size();j++)
    {
        /*
        Key points:
        1. Mismatch occurs at cur.
        2. Suppose anand is compared with ananandnd.
        3. Mismatch occur at a i.e. cur=4.  anand.
        4. But we shift as above v[cur]=2(and it matches 'a').So now we only compare and.
        5. We have saved our work of starting from beginning.
        6. This was luckily the longest possible one.In general,we try to save even the
        the smaller amount of work unitl we reach index 0 in the pattern.
        */

        while(cur>0 && p[cur]!=text[j])
        cur=v[cur];

        if(p[cur]==text[j])
            if(++cur==p.size())//if all all locations before index p.size() have been matched
                return true;

    }
   // (kmp(p,text)
    return false;
}
