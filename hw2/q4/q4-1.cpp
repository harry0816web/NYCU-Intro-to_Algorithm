#include <iostream>
#include <vector>
#include <stack>
#include <map>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    int cnt = 0;
    vector<pair<int, int>> num(n);

    // Read the input permutation
    for (int i = 0; i < n; i++)
    {
        cin >> num[i].first;
        num[i].second = i;
    }

    vector<int> left_border(n, -1);
    vector<int> right_border(n, -1);

    // map num to their idx so that we can check their position
    map<int, int> idx;
    for (int i = 0; i < n; i++)
    {
        idx[num[i].first] = num[i].second;
    }
    stack<pair<int, int>> st;

    // left border for each num
    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && st.top().first < num[i].first)
        {
            st.pop();
        }
        if (!st.empty())
        {
            left_border[num[i].second] = st.top().second;
        }
        st.push(num[i]);
    }

    // clear for another side
    while (!st.empty())
    {
        st.pop();
    }

    // right borders for each num
    for (int i = n - 1; i >= 0; i--)
    {
        while (!st.empty() && st.top().first < num[i].first)
        {
            st.pop();
        }
        if (!st.empty())
        {
            right_border[num[i].second] = st.top().second;
        }
        st.push(num[i]);
    }
    for (int i = 0; i < n; i++)
    {
        cout << left_border[i] << ' ' << right_border[i] << '\n';
    }
    for (int i = 1; i < n - 1; i++)
    {
        int leftborder = (left_border[i] == -1) ? 0 : left_border[i];
        int rightborder = (right_border[i] == -1) ? n - 1 : right_border[i];

        // left interval is smaller
        if (i - leftborder <= rightborder - i)
        {
            for (int j = leftborder; j < i; j++)
            {
                int target = num[i].first - num[j].first;
                auto it = idx.find(target);
                // check if target is in nums, if so , check if its id lies in (i,rightborder]
                if (it != idx.end())
                {
                    if (idx[target] > i && idx[target] <= rightborder)
                    {
                        cnt++;
                    }
                }
            }
        }
        // right interval is smaller
        else
        {
            for (int k = i + 1; k <= rightborder; k++)
            {
                int target = num[i].first - num[k].first;
                auto it = idx.find(target);
                if (it != idx.end())
                {
                    if (idx[target] < i && idx[target] >= leftborder)
                    {
                        cnt++;
                    }
                }
            }
        }
    }

    cout << cnt << '\n';

    return 0;
}
