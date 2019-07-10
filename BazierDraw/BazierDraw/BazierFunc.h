#include <vector>
#include "IBazierFunc.h"

class CBazierFunc:public IBazierFunc
{
public:
   CBazierFunc();
   BOOL Init(int nx, int ny, CPoint point[4]);
   int funcGetYByX(int x);
   int funcGetXByY(int y);
private:
   std::vector<std::vector<BYTE> > m_vecBytes;
   int m_nMostY;
   int m_nMostX;
};