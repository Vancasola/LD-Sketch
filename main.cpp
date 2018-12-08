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
char* ip2a(uint32_t ip, char* addr);
//@ip:include src and dst ip, 64 bit
void Print_Ip(unsigned long long* ip)
{
	//unsigned long long * iptemp = new unsigned long long;
	unsigned int * src = new unsigned int;
	unsigned int * dst = new unsigned int;
	char * ipk = new  char[5];
	ipk[4] = '\0';
	//*ip = (0x0100a8c00200a8c0);//源目的ip，逆序
	*dst = (0xffffffff)&(*ip);//目的ip
	*src = (*ip) >> 32;//源ip

	printf("src==%s ", ip2a(*src, ipk));
	printf("dst==%s\n", ip2a(*dst, ipk));
	return;
}
#define heavy_key_number 5
#define key_number 5
unsigned int LDSketch_find(LDSketch_t* tbl, const unsigned char* key, int start_bit,
	int end_bit, int row_no);
int main(int argc, char** argv) {
	LDSketch_t* lds = LDSketch_init(10, 4, 1, 64, 1024*1024, 0);
	//dyn_tbl_key_t key;
	
	//unsigned char * key = new unsigned char[key_number*4+1];
	//unsigned char * tempkey = new unsigned char[5];
	//tempkey[4] = '\0';
	//unsigned char * ptr = key;
	char * ipk = new  char[5];
	ipk[4] = '\0';
	printf("%s\n", ip2a(0x0100a8c0,ipk));
	
	/*for (int i = 0; i < 4*key_number; i+=4)
	{
		key[i] = (0xc0);
		key[i+1] = (0xa8);
		key[i + 2] = (0x00);
		key[i + 3] = (0x00) + i/4+1;
		printf("\nkey==%0xd\n", );
		tempkey[0] = key[i];
		tempkey[1] = key[i+1];
		tempkey[2] = key[i+2];
		tempkey[3] = key[i+3];
		LDSketch_update(lds, tempkey, 1024 * 1024);
	}*/
	//ip2a(0x0100a8c0, ipk);
	unsigned char * key = new unsigned char[9];
	unsigned long long * iptemp = new unsigned long long ;
	unsigned int * src = new unsigned int;
	unsigned int * dst = new unsigned int;
	*iptemp = (0x0100a8c00200a8c0);//源目的ip，逆序

	Print_Ip(iptemp);
	/**dst = (0xffffffff)&(*iptemp);//目的ip
	*src = (*iptemp) >> 32;//源ip
	printf("src==%llx\n", *dst);
	printf("src==%s\n", ip2a(*src,ipk));
	*iptemp = (*iptemp) >> 32;
	printf("dst==%s\n\n\n\n\n", ip2a(*dst, ipk));
	*key = (0x0100a8c00200a8c0);*/
	
	
	//printf("%lx", *key);
	unsigned int ipi = *(key); //& 0xffffffff;
	//printf("%x", ipi);
							   //printf("src==%s ",ip2a(ipi, ipk));
	//ipi = ipi << 32;
	//printf("%x", ipi);
	//printf("dst==%s ",ip2a(ipi,ipk ));
		*iptemp = (0x0100a8c00200a8c0);
		key = (unsigned char *)iptemp;
		LDSketch_update(lds, key, 1024 * 1024);//插入key值
		*iptemp = (0x0100a8c00300a8c0);
		key = (unsigned char *)iptemp;
		LDSketch_update(lds, key, 1024 * 1024);//插入key值
		*iptemp = (0x0100a8c00400a8c0);
		key = (unsigned char *)iptemp;
		LDSketch_update(lds, key, 1024 * 1024);//插入key值
		*iptemp = (0x0100a8c00500a8c0);
		key = (unsigned char *)iptemp;
		LDSketch_update(lds, key, 1024 * 1024);//插入key值
		*iptemp = (0x0100a8c00600a8c0);
		key = (unsigned char *)iptemp;
		LDSketch_update(lds, key, 1024 * 1024);//插入key值
		*iptemp = (0x0100a8c00700a8c0);
		key = (unsigned char *)iptemp;
		LDSketch_update(lds, key, 1024 * 1024);//插入key值
		/*key = (unsigned char *)"baaaaaaa";
		LDSketch_update(lds, key, 1024 * 1024);//插入key值
		key = (unsigned char *)"caaaaaaa";
		LDSketch_update(lds, key, 1024 * 1024);//插入key值
		key = (unsigned char *)"daaaaaaa";
		LDSketch_update(lds, key, 1024 * 1024);//插入key值
		key = (unsigned char *)"eaaaaaaa";
		LDSketch_update(lds, key, 1024 * 1024);//插入key值
		key = (unsigned char *)"faaaaaaa";
		LDSketch_update(lds, key, 1024 * 1024);//插入key值
		*/
	/*long long up ;上界下界
	long long low;
	for (int i = 0; i < 6; i++)
	{
		long long up = LDSketch_up_estimate(lds, key[i]);
		long long low = LDSketch_low_estimate(lds, key[i]);
		printf("up==%lld low==%lld\n", up, low);
	}*/

	//long long re = LDSketch_up_estimate(lds, key[0]);
	long long value = 0ll;
	long long *pvalue = new long long [10];
	//long long *vals = new long long[6];
	//for(int i=0;i<6;++i)vals[i]=0;
	int  num_key = 0 ;
	unsigned char* rekey = new unsigned char[6*8];

	LDSketch_get_heavy_keys(lds,1024*1024, rekey, pvalue, &num_key);
	printf("%d\n", num_key);
	unsigned char *ptr_key = rekey;
	Print_Ip(((unsigned long long *)rekey));
	/*for (int i = 0; i < 8 * num_key; )
	{
		//if (rekey[i] != NULL)
			printf("%c", rekey[i]);
		i++;
		if (i % 8 == 0)printf("\n");
	}*/
	//rekey[num_key * 4] = '\0';
	char result_key[5];
	result_key[4] = '\0';
	unsigned int ip;
	
	/*for (int i = 0; i < num_key; i+=4)
	{
		result_key[i]= rekey[i];
		result_key[i+1] = rekey[i+1];
		result_key[i+2] = rekey[i+2];
		result_key[i+3] = rekey[i+3];
		ip = (unsigned int)result_key;
		printf("%s", ip2a(ip,result_key));
		//ptr = (int*)result_key;
		
	}*/
	unsigned char * ptr_rekey = rekey;
	for (int i = 0; i < 6; i++)
	{
		printf("key == ");
		Print_Ip(((unsigned long long *)ptr_rekey));
		printf("value == %lld\n", pvalue[i]);
		ptr_rekey += 8;
	}
	/*for (int i = 0; i < 5; i++)
	{
		printf("key == %s value == %lld\n",rekey,pvalue[i]);
	}*/
	//printf("num_key == %d\n", num_key);
	//printf("value == %lld\n ", value);
	//printf("%s", rekey);
	//LDSketch_update(lds, key2, 64);//插入key值
	LDSketch_write_plaintext(lds, "output.txt");//输出sketch的内容
	dyn_tbl_print(lds->tbl[0], "dyns.txt");
	LDSketch_destroy(lds);
	system("PAUSE");
	
	return 0;
}
