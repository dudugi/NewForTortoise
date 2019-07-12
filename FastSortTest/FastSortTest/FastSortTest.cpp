// FastSortTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <iostream>


using namespace std;

enum
{
   MAXC = 200,
};

int select(vector<int> &a, int s, int e)
{
   //a[s]为主元
   int i = s;
   int j = s + 1;
   for (j = s + 1; j <= e; ++j)
   {
      if (a[j] <= a[s])
      {
         ++i;
         swap(a[j], a[i]);
      }
   }
   swap(a[s], a[i]);
   return i;
}

void FastSort(vector<int> &a, int s, int e)
{
   if (s >= e)
   {
      return;
   }

   int m = select(a, s, e);

   FastSort(a, s, m - 1);

   FastSort(a, m + 1, e);
}

int _tmain(int argc, _TCHAR* argv[])
{
   vector<int> vec(200,0);
   srand(time(NULL));
   for_each(vec.begin(), vec.end(),[](int &i)
   {
      i = rand();
   }
   );

   auto funcPrintAll = [](const vector<int> &vec)
   {
      for_each(vec.begin(), vec.end(),[](const int &i)
      {
         cout << i << " ";
      }
      );
      cout << endl;
   };

   funcPrintAll(vec);
   auto vec2 = vec;
   FastSort(vec2, 0, vec2.size() - 1);
   
   funcPrintAll(vec2);
   sort(vec.begin(), vec.end());

   if (vec == vec2)
   {
      cout << "ok" << endl;
   }
   system(("pause"));

	return 0;
}

