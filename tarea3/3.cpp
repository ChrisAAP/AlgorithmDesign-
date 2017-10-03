//Dynamic Programming Algorithm
//O(N*M)
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

int main()
{
    int x,x1,x2;
    vector<int> sequence1, sequence2;
    //Example
    //For the following sequences the longest common subsecuence is 1, 3, 5
    //vector<int> sequence1{1, 3, 2, 5};
    //vector<int> sequence2{2, 1, 3, 5};
    
    cout << "Size of the first sequence:\n";
    cin >> x1;
    cout << "Size of the second sequence:\n";
    cin >> x2;
    cout << "Insert first sequence :\n";
    for(int i = 0; i < x1; ++i)
    {
        cin >> x;
        sequence1.push_back(x);
    }
    cout << "Insert second sequence :\n";
    for(int i = 0; i < x2; ++i)
    {
        cin >> x;
        sequence2.push_back(x);
    }
    vector<pair <int,int>> data;
    stack<int> lcs;
    data.resize(sequence2.size(),make_pair(0,0));
    int currentNum, lastIteration;
    for(int i = 0; i < sequence1.size(); ++i)
    {
        currentNum = 0;
        lastIteration = -1;
        for(int j = 0; j < sequence2.size(); ++j)
        {
            if(sequence1[i] == sequence2[j] && currentNum + 1 > data[j].first)
            {
                data[j].first = currentNum+1;
                data[j].second = lastIteration;
            }
            if(sequence1[i] > sequence2[j] && data[j].first > currentNum)
            {
                currentNum = data[j].first;
                lastIteration = j;
            }
        }
    }
    pair<int,int> topData = make_pair(INT32_MIN,-1);
    int index = -1;

    for(vector<pair <int,int>>::iterator it = data.begin(); it != data.end(); ++it)
    {
        if(topData.first < (*it).first)
        {
            topData = *it;
            index = it - data.begin();
        }
    }
    int keepPrinting = topData.first;
    pair<int,int> forPrint = topData;
    while(keepPrinting > 0)
    {
        lcs.push(sequence2[index]);
        --keepPrinting;
        index = forPrint.second;
        forPrint = data[index];
    }
    while(!lcs.empty())
    {
        cout << lcs.top() << " ";
        lcs.pop();
    }
    cout << "\n";
}