#include <iostream>
#include <time.h>
#include <string>
#include <io.h>
#include <fcntl.h>

using namespace std;

const wstring chars = L"abcdefghijklmnopqrstuvwxyzйцукенгшщзхъэждлорпавыфячсмитьбю";


int lev_iter(wstring &s1, wstring &s2) 
{
    int n1 = s1.length() + 1, n2 = s2.length() + 1;
    int **mtr = new int * [n1];
    int add, tmp, dist;

    for (int i = 0; i < n1; i++) 
    {
        mtr[i] = new int [n2];
        mtr[i][0] = i;
    }

    for (int i = 1; i < n2; i++)
        mtr[0][i] = i;

    for (int i = 1; i < n1; i++)
        for (int j = 1; j < n2; j++)
        {
            add = 0;
            if (s1[i - 1] != s2[j - 1])
                add = 1;

            tmp = 1 + min(mtr[i - 1][j], mtr[i][j - 1]);
            mtr[i][j] = min(tmp, mtr[i - 1][j - 1] + add);
        }

    dist = mtr[n1 - 1][n2 - 1];

    for (int i = 0; i < n1; i++)
        delete[] mtr[i];
    delete[] mtr;

    return dist;
}


int dl_iter(wstring &s1, wstring &s2) 
{
    int n1 = s1.length() + 1, n2 = s2.length() + 1;
    int **mtr = new int * [n1];
    int add, tmp, dist;

    for (int i = 0; i < n1; i++) 
    {
        mtr[i] = new int [n2];
        mtr[i][0] = i;
    }

    for (int i = 1; i < n2; i++)
        mtr[0][i] = i;

    for (int i = 1; i < n1; i++)
        for (int j = 1; j < n2; j++)
        {
            add = 0;
            if (s1[i - 1] != s2[j - 1])
                add = 1;

            tmp = 1 + min(mtr[i - 1][j], mtr[i][j - 1]);
            tmp = min(tmp, mtr[i - 1][j - 1] + add);

            if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1])
                tmp = min(tmp, mtr[i - 2][j - 2] + 1);

            mtr[i][j] = tmp;
        }

    dist = mtr[n1 - 1][n2 - 1];

    for (int i = 0; i < n1; i++)
        delete[] mtr[i];
    delete[] mtr;

    return dist;
}


int dl_rec2(wstring &s1, int n1, wstring &s2, int n2)
{
    int dist;
    if (n1 * n2 == 0)
    {
        if (n1 != 0)
            dist = n1;
        else
            dist = n2;
    }
    else
    {
        int add = 0;
        if (s1[n1 - 1] != s2[n2 - 1])
            add = 1;

        dist = 1 + min(dl_rec2(s1, n1 - 1, s2, n2), dl_rec2(s1, n1, s2, n2 - 1));
        dist = min(dist, dl_rec2(s1, n1 - 1, s2, n2 - 1) + add);

        if (n1 > 1 && n2 > 1 && s1[n1 - 1] == s2[n2 - 2] && s1[n1 - 2] == s2[n2 - 1])
            dist = min(dist, dl_rec2(s1, n1 - 2, s2, n2 - 2) + 1);
    }
    return dist;
}

int dl_rec(wstring &s1, wstring &s2) 
{
    return dl_rec2(s1, s1.length(), s2, s2.length());
}


int dl_rec_cache2(wstring &s1, int n1, wstring &s2, int n2, int **mtr)
{
    int dist;
    if (mtr[n1][n2] != -1)
        dist = mtr[n1][n2];
    else
    {
        int add = 0;
        if (s1[n1 - 1] != s2[n2 - 1])
            add = 1;
        dist = 1 + min(dl_rec_cache2(s1, n1 - 1, s2, n2, mtr), dl_rec_cache2(s1, n1, s2, n2 - 1, mtr));
        dist = min(dist, dl_rec_cache2(s1, n1 - 1, s2, n2 - 1, mtr) + add);
        if (n1 > 1 && n2 > 1 && s1[n1 - 1] == s2[n2 - 2] && s1[n1 - 2] == s2[n2 - 1])
            dist = min(dist, dl_rec_cache2(s1, n1 - 2, s2, n2 - 2, mtr) + 1);
        mtr[n1][n2] = dist;
    }
    return dist;
}
int dl_rec_cache(wstring &s1, wstring &s2) 
{
    int n1 = s1.length() + 1, n2 = s2.length() + 1;
    int **mtr = new int * [n1];
    for (int i = 0; i < n1; i++) 
    {
        mtr[i] = new int [n2];
        mtr[i][0] = i;
    }
    for (int i = 1; i < n2; i++)
        mtr[0][i] = i;
    for (int i = 1; i < n1; i++)
        for (int j = 1; j < n2; j++)
            mtr[i][j] = -1;
    n1--;
    n2--;
    dl_rec_cache2(s1, n1, s2, n2, mtr);
    int dist = mtr[n1][n2];

    for (int i = 0; i <= n1; i++)
        delete[] mtr[i];
    delete[] mtr;
    return dist;
}

// замеры
wstring str_gen(int n) {
    wstring s = L"";

    for (int i = 0; i < n; i++)
        s += (chars[rand() % (sizeof(chars) - 1)]);

    return s;
}

double test(wstring &s1, wstring &s2, int (*f)(wstring &, wstring &))
{
    clock_t start;
    double time = 0;

    start = clock();
    for (int i = 0; i < 500; i++)
    {
        f(s1, s2);
    }

    time += clock() - start;
    time *= 2000.0;
    time /= (double)CLOCKS_PER_SEC;
    return time;
}


int main(void)
{
    setbuf(stdout, NULL);
    _setmode(_fileno(stdout), _O_U8TEXT);
    _setmode(_fileno(stdin), _O_U8TEXT);

    int p = 1, n;
    wstring s1;
    wstring s2;
    double t1, t2, t3, t4;

    while (0 != p)
    {
        wcout << L"\nМеню\n"
        "1. Расстояние Левенштейна итеративно\n"
        "2. Расстояние Дамерау-Левенштейна итеративно\n"
        "3. Расстояние Дамерау-Левенштейна рекурсивно\n"
        "4. Расстояние Дамерау-Левенштейна рекурсивно с кешем\n"
        "5. Все методы сразу\n"
        "6. Сравнение по времени\n"
        "0. Exit\n";
        wcin >> p;

        if (1 <= p && p <= 5)
        {
            wcout << L"Введите первое слово: ";
            wcin >> s1;
            wcout << L"Введите второе слово: ";
            wcin >> s2;

            if (1 == p)
                n = lev_iter(s1, s2);
            else if (2 == p)
                n = dl_iter(s1, s2);
            else if (3 == p)
                n = dl_rec(s1, s2);
            else if (4 == p)
                n = dl_rec_cache(s1, s2);
            else
                wcout << lev_iter(s1, s2) << " " << dl_iter(s1, s2) << " " << dl_rec(s1, s2) << " " << dl_rec_cache(s1, s2) <<"\n";

            if (5 != p)
                wcout << L"Расстояние = " << n << "\n";
        }
        else if (6 == p)
        {
            wprintf(L"%s\t%s\t%s\t\t%s\t\t%s\n", "len", "lev_iter", "dl_iter", "dl_rec", "dl_rec_cache");
            for (int i = 5; i <= 10; i++)
            {
                s1 = str_gen(i);
                s2 = str_gen(i);
                t1 = test(s1, s2, lev_iter);
                t2 = test(s1, s2, dl_iter);
                t3 = test(s1, s2, dl_rec);
                t4 = test(s1, s2, dl_rec_cache);
                wprintf(L"%d\t%f\t%f\t%f\t%f\n", i, t1, t2, t3, t4);
            }
            wprintf(L"\n");

            wprintf(L"%s\t%s\t%s\t\t%s\t\t%s\n", "len", "lev_iter", "dl_iter", "dl_rec", "dl_rec_cache");
            for (int i = 20; i <= 100; i += 10)
            {
                s1 = str_gen(i);
                s2 = str_gen(i);
                t1 = test(s1, s2, lev_iter);
                t2 = test(s1, s2, dl_iter);
                t4 = test(s1, s2, dl_rec_cache);
                wprintf(L"%d\t%f\t%f\t%s\t\t%f\n", i, t1, t2, "---", t4);
            }
            wprintf(L"\n");
        }
    }
    return 0;
}
