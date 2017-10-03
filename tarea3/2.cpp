//Greedy Algorithm
//O(N)
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int main()
{
    vector<string> p, line;
    vector<float> l;
    float L = 20, b = 1, length = 0, linelength = 0, extra, expanding, reducing;
    int i = 0, j;
    bool printed = true;

    p.push_back("Moonlight");
    l.push_back(9);
    p.push_back("drowns");
    l.push_back(6);
    p.push_back("out");
    l.push_back(3);
    p.push_back("all");
    l.push_back(3);
    p.push_back("but");
    l.push_back(3);
    p.push_back("the");
    l.push_back(3);
    p.push_back("brightest");
    l.push_back(9);
    p.push_back("lights");
    l.push_back(6);

    for(j = 0; j < p.size(); j++)
    {
        if(printed)
        {
            i = j;
            printed = false;
            line.clear();
            length = 0;
        }
        length += l[j];
        linelength = length + ((j - i) * b);
        if(linelength > L)
        {
            extra = linelength - L;
            reducing = b - (extra / (j - i));
            expanding = b + (L - ((length - l[j]) + (b * (j - i - 1)))) / (j - i - 1);
            
            if(((fabs(expanding - b) * (j - i - 1)) > (fabs(reducing - b) * (j - i))) && reducing > 0)
            {
                line.push_back(p[j]);
                for(auto x : line){
                    cout << x << " ";
                }
                cout << reducing << "r";
                cout << "\n";
                printed = true;               
            }
            else
            {
                for(auto x : line)
                {
                    cout << x << " ";
                }
                cout << expanding << "a";
                cout << "\n";
                j--;
                printed = true;
                }
        }
        line.push_back(p[j]);
    }
    for(auto x : line)
    {
        cout << x << " ";
    }
    cout << "\n";
}