#include <iostream>
#include <map>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

vector<vector<long long>> matMul(const vector<vector<long long>> &matA, const vector<vector<long long>> &matB, int k)
{
    vector<vector<long long>> matC(k, vector<long long>(k, 0));
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            for (int l = 0; l < k; l++)
            {
                matC[i][j] = (matC[i][j] + matA[i][l] * matB[l][j]) % MOD;
            }
        }
    }
    return matC;
}

vector<vector<long long>> matPow(vector<vector<long long>> &A, long long p, int k)
{
    vector<vector<long long>> result(k, vector<long long>(k, 0));
    for (int i = 0; i < k; i++)
        result[i][i] = 1;

    if (p == 1)
        return A;
    else if (p == 0)
        return result;

    result = matPow(A, p / 2, k);
    result = matMul(result, result, k);
    if (p % 2)
    {
        result = matMul(result, A, k);
    }
    return result;
}

int main()
{
    long long n, m;
    string s;
    cin >> n >> m;
    cin >> s;
    int k;
    cin >> k;

    vector<vector<long long>> mat(26, vector<long long>(26, 0));
    vector<long long> len(26, 0);

    // 初始化轉移矩陣
    for (int i = 0; i < k; i++)
    {
        char c = 'a' + i;
        string temp;
        cin >> temp;
        len[c - 'a'] = 1;

        for (char ch : temp)
        {
            mat[c - 'a'][ch - 'a']++; // 'a'+i 會被替換為這些字元
        }
    }

    vector<vector<long long>> finalMat = matPow(mat, m, 26);

    vector<long long> finalLen(26, 0);
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            finalLen[i] = (finalLen[i] + finalMat[i][j] * len[j]) % MOD;
        }
    }

    long long sum = 0;
    for (char c : s)
    {
        sum = (sum + finalLen[c - 'a']) % MOD;
    }

    cout << sum << '\n';
    return 0;
}
