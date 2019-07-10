#include <vector>
#include "IBazierFunc.h"
#include <atltypes.h>
#include <map>

class CBazierDrawFast:public IBazierFunc
{
public:
   CBazierDrawFast();
   BOOL Init(int nx, int ny, CPoint point[4]);
   int funcGetYByX(int x);
   int funcGetXByY(int y);
private:
   //std::vector<std::vector<BYTE> > m_vecBytes;
   int m_nMostY;
   int m_nMostX;
   //std::map<int, int> m_mapYByX;
   std::vector<int> m_mapYByX;
   //std::map<int, int> m_mapXByY;
   std::vector<int> m_mapXByY;
};