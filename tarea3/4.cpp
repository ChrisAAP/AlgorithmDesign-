//Backtracking Algorithm
//O(N^2)
#include <iostream>
#include <vector>

using namespace std;

int main() 
{

    int Women[4][4], Men[4][4];
    bool estable = false;
    int MM[4];
    bool HM[4];
    std::fill_n(MM, 4, -1);
    std::fill_n(HM, 4, false);

    int H1[4] = {2,1,0,3}, H2[4] = {1,3,0,2}, H3[4] = {2,0,3,1}, H4[4] = {3,1,2,0};
    
    int M1[4] = {0,2,1,3}, M2[4] = {2,3,1,0}, M3[4] = {1,2,3,0}, M4[4] = {3,1,0,2};
    
    for (int i = 0; i < 4; i++)
    {
        Women[0][i] = M1[i];
        Women[1][i] = M2[i];
        Women[2][i] = M3[i];
        Women[3][i] = M4[i];
        
        Men[0][i] = H1[i];
        Men[1][i] = H2[i];
        Men[2][i] = H3[i];
        Men[3][i] = H4[i];
    }
    
    int i = 0;
    int j = 0;
    
    while (!estable)
    {
        if (HM[i] == false)
        {
            int t = Men[i][j];
            if (MM[t] == -1)
            {
                MM[t] = i;
                HM[i] = true;
                i++;
                j = 0;
            }
            else
            {
                int h1 = MM[t];
                for (int k = 0; k < 4; k++)
                {
                    if (Women[t][k] == i)
                    {
                        MM[t] = i;
                        HM[i] = true;
                        HM[h1] = false;
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
            if (HM[j] == true) estable = true;
            else
            {
                estable = false;
                i = j;
                break;
            }
        }
    }
    cout << "M H" << "\n";
    for (int i = 0; i < 4; i++) cout << i << " " << MM[i] << "\n";
}