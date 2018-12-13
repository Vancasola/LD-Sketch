#include "extract.h"
/*
	Extract is used to extrat the packet capture infomation
	the string's formation
	is like:"192.168.198.2 192.168.198.131 length 46"
*/
string Extract(string &str)
{
	string src = "", dst = "";
	string length = "";
	string result = "";
	smatch sm;
	//regex for src ipv4 match
	auto it = str.cbegin();
	regex_search(it, str.cend(), sm, regex("(2(5[0-5]{1}|[0-4]\\d{1})|[0-1]?\\d{1,2})(\\.(2(5[0-5]{1}|[0-4]\\d{1})|[0-1]?\\d{1,2})){3}"));
	src = sm.prefix().str();

	result += sm.str();
	result += " ";
	//regex for src ipv4 match
	it = sm.suffix().first;
	regex_search(it, str.cend(), sm, regex("(2(5[0-5]{1}|[0-4]\\d{1})|[0-1]?\\d{1,2})(\\.(2(5[0-5]{1}|[0-4]\\d{1})|[0-1]?\\d{1,2})){3}"));
	dst = sm.prefix().str();
	result += sm.str();
	result += " ";
	//regex for length value match
	it = str.cbegin();
	regex_search(it, str.cend(), sm, regex("length [0-9]+"));
	dst = sm.prefix().str();

	result += sm.str();
	return result;
}
/*
	Convert string to unsigned long long
	the result includes src and det ip address
*/
unsigned long long Convert_IP(string &str)
{
	unsigned long long result = 0ll;
	string temp = "";
	int i = 0, length = str.size(), t = 0;
	int first_in = 1, first_out = 1;//loop flag
	for (i = 0; i < length; i++)
	{
		if (str[i] == 'l')break;
		if (str[i] == ' ')
		{
			result = result << 8;
			result += t;
			t = 0;
			first_out = 1;
			continue;
		}
		if (str[i] == ' ')break;
		if (str[i] != '.')
		{
			if (first_in)
			{
				t += str[i] - '0';
				first_in = 0;
				continue;
			}
			t *= 10;
			t += str[i] - '0';
		}
		else
		{

			if (first_out)
			{
				result += t;
				first_in = 1;
				t = 0;
				first_out = 0;
				continue;
			}
			result = result << 8;
			result += t;
			first_in = 1;
			t = 0;

		}
	}
	
	return result;
}
/*
	Convert_length is used to extract the pakcet's length
*/
long long Convert_length(string &str)
{
	int i = 0, pos = 0, str_len = str.size();
	int first = 1;
	long long value = 0ll;
	string length_str = "";
	pos = str.find("length");
	for (i = pos + 7; i < str.size(); i++)
	{
		if (first)
		{
			value += str[i] - '0';
			first = 0;
		}
		else
		{
			value *= 10;
			value += str[i] - '0';
		}
	}
	return value;
}