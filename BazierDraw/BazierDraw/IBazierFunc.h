#pragma once
class IBazierFunc
{
public:
   virtual BOOL Init(CPoint point[4]) = 0;
   virtual int funcGetYByX(int x) = 0;
   virtual int funcGetXByY(int y) = 0;
};