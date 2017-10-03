//Greedy Algorithm
//O(N)

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    
    int km, numberOfStops, gasRemaining, numberOfStops;
    vector<int> stopsMustTake;
    stopsMustTake.push_back(0);
    cout << "How far can a full gas tank go?\n";
    cin >> km;
    cout << "How many number of stops are there?\n";
    cin >> numberOfStops;
    int stops[numberOfStops];
    cout << "At what km from the start is there stops?\n";
    for(int i = 0; i < numberOfStops; ++i)
    {
        cin >> stops[i];
    }
    gasRemaining = km;
    for(int i = 1; i < numberOfStops; ++i)
    {
        if (gasRemaining - stops[i] + stops[i - 1] <= 0)
        {
            stopsMustTake.push_back(stops[i - 1]);
            gasRemaining = km;
        }
        gasRemaining = gasRemaining - stops[i] + stops[i - 1];
    }
    for(int i = 0; i < stopsMustTake.size(); i++)
    {
        cout << "Must take stop at KM " << stopsMustTake[i]<< "\n";
    }
}