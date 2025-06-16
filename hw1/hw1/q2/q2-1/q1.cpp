#include <iostream>
#include <algorithm>
#include <stdlib.h>
using namespace std;

class Grade
{
public:
    int ch, en, math, sc, social;

    Grade() {};

    Grade(int ch, int en, int math, int sc, int social)
    {
        this->ch = ch;
        this->en = en;
        this->math = math;
        this->sc = sc;
        this->social = social;
    };

    bool satisfy1() const
    {
        return ch >= 90 && en >= 90 && math >= 90 && sc >= 90 && social >= 90;
    }

    int getTotal() const
    {
        return ch + en + math + sc + social;
    }
};

bool compare(const Grade &left, const Grade &right)
{
    if (left.getTotal() != right.getTotal())
    {
        return left.getTotal() > right.getTotal();
    }
    if (left.ch != right.ch)
    {
        return left.ch > right.ch;
    }
    if (left.en != right.en)
    {
        return left.en > right.en;
    }
    if (left.math != right.math)
    {
        return left.math > right.math;
    }
    if (left.sc != right.sc)
    {
        return left.sc > right.sc;
    }
    return left.social > right.social;
}

int main()
{
    int n;
    cin >> n;

    Grade *stu = (Grade *)calloc(n, sizeof(Grade));
    for (int i = 0; i < n; i++)
    {
        int ch, en, math, sc, social;
        cin >> ch >> en >> math >> sc >> social;
        stu[i] = Grade(ch, en, math, sc, social);
    }

    int begin = 0;
    for (int i = 0; i < n; i++)
    {
        if (stu[i].satisfy1())
        {
            swap(stu[begin], stu[i]);
            begin++;
        }
    }

    sort(stu, stu + begin, compare);
    sort(stu + begin, stu + n, compare);
    for (int i = 0; i < n; i++)
    {
        cout << stu[i].ch << " " << stu[i].en << " " << stu[i].math << " " << stu[i].sc << " " << stu[i].social << '\n';
    }

    return 0;
}
