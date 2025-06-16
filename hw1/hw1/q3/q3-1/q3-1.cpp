#include <iostream>
#include <cmath>
using namespace std;
struct vec
{
    long long x;
    long long y;
};

int main()
{
    vec v1, v2;
    cin >> v1.x >> v1.y;
    cin >> v2.x >> v2.y;

    // long long product = v1.x * v2.x + v1.y * v2.y;
    double magV1 = sqrt(v1.x * v1.x + v1.y * v1.y);
    double magV2 = sqrt(v2.x * v2.x + v2.y * v2.y);

    double cross = v1.x * v2.y - v1.y * v2.x;
    if (cross < 0)
    {
        cout << "false\n";
    }
    else if (cross > 0)
    {
        cout << "true\n";
    }
    else
    {
        if (magV1 < magV2)
        {
            cout << "true\n";
        }
        else
        {
            cout << "false\n";
        }
    }
}