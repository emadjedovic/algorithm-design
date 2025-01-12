#include <iostream>
#include <vector>
using namespace std;

double MaxMinAverage(vector<int> a, int k)
{
    vector<vector<double>> dp(a.size(), vector<double>(k + 1)); // dp[i][j] - a[0:i] u j dijelova
    int trenutna_suma = 0;
    for (int i = 0; i < a.size(); i++)
    {
        trenutna_suma += a[i];
        dp[i][1] = double(trenutna_suma) / (i + 1);
    }
    for (int j = 2; j <= k; j++)
    {
        for (int i = j - 1; i < a.size(); i++)
        {
            int trenutna_suma = a[i];
            double maksimalniMinimum = 0;
            for (int t = i - 1; t >= j - 2; t--)
            {
                double rez = min(dp[t][j - 1], double(trenutna_suma) / (i - t));
                if (rez > maksimalniMinimum)
                {
                    maksimalniMinimum = rez;
                }
                trenutna_suma += a[t];
            }
            dp[i][j] = maksimalniMinimum;
        }
    }
    return dp[a.size() - 1][k];
}

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    cout << MaxMinAverage(a, k) << endl;
}