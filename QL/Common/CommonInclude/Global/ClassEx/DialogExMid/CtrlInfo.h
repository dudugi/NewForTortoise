#pragma once


//�ؼ���Ϣ���������������Զ�onsize add by lida 2018/05/17

//static��checkbox �ؼ�Ҫ����ƫ��5��λ�ã��������������ܺ������ؼ�����

class ctrl_info      
{
public:
   ctrl_info()
   {
      m_hwnd      = nullptr;     
      m_iRow      = 0;        
      m_iIndex    = 0;      
      m_iWidth    = 0;      
      m_iHeight   = 0;    
      m_ideltx    = 0;
      m_idelty    = 0;
      m_iuse_rt_width = 0;
      m_iuse_rt_height = 0;
      m_iXBeilv = 1;//ʣ���ȵļ���֮��
      m_iYBeilv = 1;//ʣ��߶ȵļ���֮��
   };
   ~ctrl_info()
   {
      m_hwnd      = nullptr;     
      m_iRow      = 0;        
      m_iIndex    = 0;      
      m_iWidth    = 0;      
      m_iHeight   = 0;    
      m_ideltx    = 0;
      m_idelty    = 0;
      m_iuse_rt_width = 0;
      m_iuse_rt_height = 0;
      m_iXBeilv = 1;//ʣ���ȵļ���֮��
      m_iYBeilv = 1;//ʣ��߶ȵļ���֮��
   };

public:
   enum
   {
      idelt_top = 5,       //�ϼ��
      idelt_bottom = 5,    //�¼��
      idelt_left = 5,      //��
      idelt_right = 5,     //��
      ilast_height = -1,   //ʹ������ʣ��߶�������ǰ�߶�
      ilast_width = -1,    //ʹ������ʣ����������ǰ���
      iUseOldSize = -1000  //ʹ�þɵĿ�Ȼ�߶�
   };

public:
   HWND     m_hwnd;        //�ؼ����
   int      m_iRow;        //�к�
   int      m_iIndex;      //��������ʾ��˳��
   int      m_iWidth;      //��
   int      m_iHeight;     //��
   int      m_ideltx;      //�������ǰ�ؼ�����һ�ؼ�֮��ļ��
   int      m_idelty;      //������ؼ��Ϳؼ�����֮��ļ��

   int      m_iuse_rt_width;
   int      m_iuse_rt_height;

   float m_iXBeilv;//ʣ���ȵļ���֮�� yangjr2018/6/25
   float m_iYBeilv;//ʣ��߶ȵļ���֮�� yangjr 2018/6/25
};