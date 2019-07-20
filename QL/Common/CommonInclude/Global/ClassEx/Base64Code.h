#pragma once
/*
 * 2017/09/04 zhangt ����
 * Base64�����㷨��һ��һ�ֻ���64���ɴ�ӡ�ַ�����ʾ���������ݵı�ʾ����.
 * һ����6λ������������ʾһ���ɴ�ӡ�ַ��ķ���.����2��6�η�����64������ÿ6��λΪһ����Ԫ����Ӧĳ���ɴ�ӡ�ַ�
 * �����ֽ�(ÿ���ֽ�8λ)��24��λ����Ӧ��4��Base64�ַ�����3���ֽ���Ҫ��4���ɴ�ӡ�ַ�����ʾ
 * ��Base64�еĿɴ�ӡ�ַ�������ĸA-Z��a-z������0-9����������62���ַ������������ɴ�ӡ�����ڲ�ͬ��ϵͳ�ж���ͬ,����ʹ���ַ�'+'��'/'.
 * 
 * base64�Ķ�Ӧ����Ϊ"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
 * ��ʣ��Ĳ���24λ�Ķ���������,��ʣ��λ������16(2���ֽ�),���ӡһ���Ⱥ�,������8(һ���ֽ�),���ӡ�����Ⱥ�.
 */
#include <string>

class CBase64Code
{
public:
	CBase64Code();
	~CBase64Code();

	/*
	 * @brief	����
	 */
	CString base64Encode(CString strSrc);

	/*
	 * @brief	����
	 */
	CString base64Decode(CString strInput);

	std::string base64_encode(unsigned char const*);
	std::string base64_decode(std::string const& s);

	inline bool is_base64(unsigned char c) 
	{
		return (isalnum(c) || (c == '+') || (c == '/'));
	};

private:
	std::string base64_chars;
};

