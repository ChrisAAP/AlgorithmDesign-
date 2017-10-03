//Backtracking Algorithm
//O(N^2)
#include <iostream>
#include <vector>

using namespace std;

int main() 
{

    int Women[4][4], Men[4][4];
    bool estable = false;
    int WM[4];
    bool MM[4];
    std::fill_n(WM, 4, -1);
    std::fill_n(MM, 4, false);
    //Example 
    //The following example uses the following data to show the preferences for men
    //and women
    //The answer should show 
    //W M
    //0 0
    //1 1
    //2 2
    //3 3
    int M1[4] = {2,1,0,3}, M2[4] = {1,3,0,2}, M3[4] = {2,0,3,1}, M4[4] = {3,1,2,0};
    
    int W1[4] = {0,2,1,3}, W2[4] = {2,3,1,0}, W3[4] = {1,2,3,0}, W4[4] = {3,1,0,2};
    
    for (int i = 0; i < 4; i++)
    {
        Women[0][i] = W1[i];
        Women[1][i] = W2[i];
        Women[2][i] = W3[i];
        Women[3][i] = W4[i];
        
        Men[0][i] = M1[i];
        Men[1][i] = M2[i];
        Men[2][i] = M3[i];
        Men[3][i] = M4[i];
    }
    
    int i = 0;
    int j = 0;
    
    while (!estable)
    {
        if (MM[i] == false)
        {
            int t = Men[i][j];
            if (WM[t] == -1)
            {
                WM[t] = i;
                MM[i] = true;
                i++;
                j = 0;
            }
            else
            {
                int h1 = WM[t];
                for (int k = 0; k < 4; k++)
                {
                    if (Women[t][k] == i)
                    {
                        WM[t] = i;
                        MM[i] = true;
                        MM[h1] = false;
                        i++;
                        j = 0;
                        break;
                    }
                    if (Women[t][k] == h1)
                    {
                        j++;
                        break;
                    }
                }
            }
        }
        else break;
        for (int j = 0; j < 4; j++)
        {
            if (MM[j] == true) estable = true;
            else
            {
                estable = false;
                i = j;
                break;
            }
        }
    }
    cout << "W M" << "\n";
    for (int i = 0; i < 4; i++) cout << i << " " << WM[i] << "\n";
}