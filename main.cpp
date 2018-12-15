/*1. 输出sketch的内容 ok
	2. 更新sketch，插入key值 ok
	3. 输出dyn_tbl的内容，证明成功插入key ok
	4. 插入一个key，其value超过阈值ok
	5. 成功报出超过阈值的key ok
	6. 不断插入key，输出l，证明其l会动态变化ok
	7. 输出key值的上界和下界ok
	8. 使用pcap成功抓包ok
	9. 分析包的形式，考虑导入到sketch的方法
	10. 将key值存入sketch
	11. 考虑一边获取流量，一边更新的方法（死循环更新值）
	12. 使用pacp抓包，sketch存入
	13. 真实环境下，设定阈值，报出heavy hitter
	14. 真实环境下，查看l的变化情况
*/
#include "LDSketch.hpp"
#include "extract.h"
#include "hash.h"
using namespace std;
//@ip:include src and dst ip, 64 bit

#define heavy_key_number 5
#define key_number 5
void Print_Ip(unsigned long long* ip)
{
	//unsigned long long * iptemp = new unsigned long long;
	unsigned int * src = new unsigned int;
	unsigned int * dst = new unsigned int;
	char * ipk = new  char[5];
	ipk[4] = '\0';
	//*ip = (0x0100a8c00200a8c0);//源目的ip，逆序
	*dst = (0xffffffff)&(*ip);//目的ip
	*src = ((*ip) >> 32);//源ip
	//printf("\nThe input is :%llx\n", *ip);
	//printf("src==%s ", ip2a(*src, ipk));
	//printf("dst==%s\n", ip2a(*dst, ipk));
	printf("%s\n", ip2a(*src, ipk), ip2a(*dst, ipk));
	return;
}
int main(int argc, char** argv) {
	LDSketch_t* lds = LDSketch_init(10000, 4, 1, 64, 1024 * 1024, 0);
	char * ipk = new  char[5];
	ipk[4] = '\0';
	//printf("%s\n", ip2a(0x0100a8c0,ipk));

	unsigned char * key = new unsigned char[9];
	unsigned long long * iptemp = new unsigned long long;
	unsigned int * src = new unsigned int;
	unsigned int * dst = new unsigned int;

	/*
	*iptemp = (0x0100a8c00200a8c0);//源目的ip，逆序
	Print_Ip(iptemp);
	*/

	string str = "06:55:46.304503 ARP, Request who-has 192.168.198.2 tell 192.168.198.131, length 46";
	string result = "";
	result = Extract(str);
	//	cout <<  result << endl;
	//cout << "string == " << str << endl;
	//printf("convert to hex:%llxh\n", Convert_IP(result));
	//printf("the length is :%d\n\n\n", Convert_length(str));
	unsigned int ipi = *(key); //& 0xffffffff;
	//*iptemp = (0x0100a8c00200a8c0);
	
	
	*iptemp = Convert_IP(result);
	key = (unsigned char *)iptemp;
	long long v = Convert_length(str);
	//LDSketch_update(lds, key, 1024 * 1024);//插入key值
	LDSketch_update(lds, key, 1024*1024);//插入key值
	
	long long value = 0ll;
	long long *pvalue = new long long[10];
	int  num_key = 0;
	unsigned char* rekey = new unsigned char[6 * 8];
	//LDSketch_get_heavy_keys(lds, 1024 * 1024, rekey, pvalue, &num_key);

	LDSketch_get_heavy_keys(lds,1024*1024, rekey, pvalue, &num_key);
	

	/*
	ouput the heavy key's results
	printf("%d\n", num_key);
	unsigned char *ptr_key = rekey;
	Print_Ip(((unsigned long long *)rekey));
	*/


	//ouput the heavy hey
	unsigned char * ptr_rekey = rekey;
	for (int i = 0; i < num_key; i++)
	{
		printf("key == ");
		Print_Ip(((unsigned long long *)ptr_rekey));
		printf("value == %lld\n", pvalue[i]);
		ptr_rekey += 8;
	}

	//output
	LDSketch_write_plaintext(lds, "output.txt");//输出sketch的内容
	//dyn_tbl_print(lds->tbl[0], "dyns.txt");

	LDSketch_destroy(lds);
	system("PAUSE");
	return 0;
}
