#include "extract.h"
#include "math.h"
/*
	Extract is used to extrat the packet capture infomation
	the string's formation
	is like:"192.168.198.2 192.168.198.131 length 46"
*/
unsigned int strtoint(string str)
{
    unsigned int i = 0, value = 0;
    int pos = str.size()-1;
    while(1)
    {
        if(pos<0)break;
        value += (str[pos] - '0')*pow(10,i);
        i++;
        pos--;
    }
    
    return value;
}
string Extract(string &str)
{
	string src = "", dst = "";
	string length = "";
	string result = "";
	smatch sm;
	//regex for src ipv4 match
	auto it = str.cbegin();
	regex_search(it, str.cend(), sm, regex("(2(5[0-5]{1}|[0-4]\\d{1})|[0-1]?\\d{1,2})(\\.(2(5[0-5]{1}|[0-4]\\d{1})|[0-1]?\\d{1,2})){3}"));
	result += sm.str();
	result += " ";
	//regex for src ipv4 match
	it = sm.suffix().first;
	regex_search(it, str.cend(), sm, regex("(2(5[0-5]{1}|[0-4]\\d{1})|[0-1]?\\d{1,2})(\\.(2(5[0-5]{1}|[0-4]\\d{1})|[0-1]?\\d{1,2})){3}"));
	result += sm.str();
	result += " ";
	//regex for length value match
    it = sm.suffix().first;
	regex_search(it, str.cend(), sm, regex("length [0-9]+"));
    if (sm.str()=="")
    {
        regex_search(it, str.cend(), sm, regex("tcp [0-9]+"));
    }
    if (sm.str()=="")
    {
        //cout<<"ERROR"<<endl;
        return "!";
    }
    it = sm.str().cbegin();
    regex_search(it, str.cend(), sm, regex("[0-9]+"));
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
    unsigned int pos = 0;

    while(pos<str.size())
    {
        while(str[pos]!='.')
        {
            if (pos>=str.size())break;
            temp += str[pos++];
        }
        result += strtoint(temp);
        temp.erase();
        if(pos>=str.size())break;
        result = result<<8;
        pos++;
    }
    return result;
}
/*
	Convert_length is used to extract the pakcet's length
*/
long long Convert_length(string &str)
{
    
	unsigned int end = str.size()-1, start = str.size()-1;
    string temp = "";
	unsigned int value = 0;
	string length_str = "";
    while(str[start--]!=' ');
    start+=2;
    for(;start<=end;start++)temp += str[start];
    value = strtoint(temp);
	return value;
}


unsigned long long Get_key(string ex)
{
    string src(ex,0,ex.find(' ')), tex(ex,ex.find(' ')+1,ex.size()),dst(tex,0,ex.find(' ')-1);
    unsigned long ip_src = Convert_IP(src), ip_dst = Convert_IP(dst);
    unsigned long long ip=ip_src;
    ip = (ip << 32) + ip_dst;
    return ip;
}

void Print_Ip(unsigned long long* ip)
{
    unsigned int * src = new unsigned int;
    unsigned int * dst = new unsigned int;
    char * ipks = new  char[5];
    ipks[4] = '\0';
    char * ipkd = new  char[5];
    ipkd[4] = '\0';
    *dst = (0xffffffff)&(*ip);//目的ip
    *src = ((*ip) >> 32);//源ip
    printf("%s-%s\n", ip2a(*src, ipks), ip2a(*dst, ipkd));
    return;
}
string Print_Heavy_Key(unsigned long long* ip)
{
    unsigned int * src = new unsigned int;
    unsigned int * dst = new unsigned int;
    string result = "";
    char * ipks = new  char[5];
    ipks[4] = '\0';
    char * ipkd = new  char[5];
    ipkd[4] = '\0';
    *dst = (0xffffffff)&(*ip);//目的ip
    *src = ((*ip) >> 32);//源ip
    result += ip2a(*src, ipks);
    result += "-";
    result += ip2a(*dst, ipkd);
    return result;
}
void read_flowkey(char* line, tuple_t* p) {
    unsigned int ip1, ip2, ip3, ip4, ip5, ip6, ip7, ip8;
    sscanf(line, "%u.%u.%u.%u-%hu-%u.%u.%u.%u-%hu-%hu:%hu",
        &ip1, &ip2, &ip3, &ip4,
        &p->key.src_port,
        &ip5, &ip6, &ip7, &ip8,
        &p->key.dst_port, 
        &p->key.protocol,
        &p->size);
    p->key.src_ip = (ip4 << 24) | (ip3 << 16) | (ip2 <<8) | ip1;
    p->key.dst_ip = (ip8 << 24) | (ip7 << 16) | (ip6 <<8) | ip5;
}
void print_tuple(FILE* f, tuple_t* t) {
    char ip1[30], ip2[30];
    fprintf(f, "%s(%u) <-> %s(%u) %u %d\n",
            ip2a(t->key.src_ip, ip1), t->key.src_port,
            ip2a(t->key.dst_ip, ip2), t->key.dst_port,
            t->key.protocol, t->size
            );
}