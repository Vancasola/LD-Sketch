/*1. ���sketch������ ok
	2. ����sketch������keyֵ ok
	3. ���dyn_tbl�����ݣ�֤���ɹ�����key ok
	4. ����һ��key����value������ֵok
	5. �ɹ�����������ֵ��key ok
	6. ���ϲ���key�����l��֤����l�ᶯ̬�仯ok
	7. ���keyֵ���Ͻ���½�ok
	8. ʹ��pcap�ɹ�ץ��ok
	9. ����������ʽ�����ǵ��뵽sketch�ķ���
	10. ��keyֵ����sketch
	11. ����һ�߻�ȡ������һ�߸��µķ�������ѭ������ֵ��
	12. ʹ��pacpץ����sketch����
	13. ��ʵ�����£��趨��ֵ������heavy hitter
	14. ��ʵ�����£��鿴l�ı仯���
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
	//*ip = (0x0100a8c00200a8c0);//ԴĿ��ip������
	*dst = (0xffffffff)&(*ip);//Ŀ��ip
	*src = (*ip) >> 32;//Դip

	printf("src==%s ", ip2a(*src, ipk));
	printf("dst==%s\n", ip2a(*dst, ipk));
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
	*iptemp = (0x0100a8c00200a8c0);//ԴĿ��ip������
	Print_Ip(iptemp);
	*/
	string str = "06:55:46.304503 ARP, Request who-has 192.168.198.2 tell 192.168.198.131, length 46";
	string result = "";
	result = Extract(str);
	//	cout <<  result << endl;
	cout << "string == " << str << endl;
	printf("convert to hex:%llxh\n", Convert_IP(result));
	printf("the length is :%d\n\n\n", Convert_length(str));
	unsigned int ipi = *(key); //& 0xffffffff;
	//*iptemp = (0x0100a8c00200a8c0);
	*iptemp = Convert_IP(result);

	key = (unsigned char *)iptemp;
	
	//LDSketch_update(lds, key, 1024 * 1024);//����keyֵ
	printf("!");
	LDSketch_update(lds, key, 1024*1024);//����keyֵ
	
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
	printf("*ptr_rekey==%llx\n", *(unsigned long long *)ptr_rekey);
	for (int i = 0; i < num_key; i++)
	{
		printf("key == ");
		Print_Ip(((unsigned long long *)ptr_rekey));
		printf("value == %lld\n", pvalue[i]);
		ptr_rekey += 8;
	}

	//output
	LDSketch_write_plaintext(lds, "output.txt");//���sketch������
	//dyn_tbl_print(lds->tbl[0], "dyns.txt");

	LDSketch_destroy(lds);
	system("PAUSE");
	return 0;
}