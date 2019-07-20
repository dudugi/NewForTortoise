#pragma once
/*
 * 2017/09/04 zhangt 创建
 * Base64加密算法是一种一种基于64个可打印字符来表示二进制数据的表示方法.
 * 一种用6位二进制数来表示一个可打印字符的方法.由于2的6次方等于64，所以每6个位为一个单元，对应某个可打印字符
 * 三个字节(每个字节8位)有24个位，对应于4个Base64字符，即3个字节需要用4个可打印字符来表示
 * 在Base64中的可打印字符包括字母A-Z、a-z、数字0-9，这样共有62个字符，此外两个可打印符号在不同的系统中而不同,这里使用字符'+'和'/'.
 * 
 * base64的对应序列为"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
 * 在剩余的不足24位的二进制数中,若剩余位数整除16(2个字节),则打印一个等号,若整除8(一个字节),则打印两个等号.
 */
#include <string>

class CBase64Code
{
public:
	CBase64Code();
	~CBase64Code();

	/*
	 * @brief	加密
	 */
	CString base64Encode(CString strSrc);

	/*
	 * @brief	解密
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

