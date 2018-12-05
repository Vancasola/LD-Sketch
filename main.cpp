#include "LDSketch.hpp"
unsigned int LDSketch_find(LDSketch_t* tbl, const unsigned char* key, int start_bit,
	int end_bit, int row_no);
int main(int argc, char** argv) {
	/*1. 输出sketch的内容 ok
	2. 更新sketch，插入key值 ok
	3. 输出dyn_tbl的内容，证明成功插入key ok
	4. 插入一个key，其value超过阈值
	5. 成功报出超过阈值的key
	6. 不断插入key，输出l，证明其l会动态变化
	*/

	LDSketch_t* lds = LDSketch_init(20, 4, 1, 64, 1024*1024, 1);
	//uint64_t key_int = 0x0102030405060708;
	//unsigned char* key = (unsigned char*)&key_int;
	unsigned char* key[6] = { (unsigned char *)"a",
							(unsigned char *)"b",
							(unsigned char *)"c",
									(unsigned char *)"d",
									(unsigned char *)"e",
									(unsigned char *)"f" };
	//unsigned char* key2 = (unsigned char *)"abcdef";
	for (int i = 0; i < 6; i++)
	{
		//int t = 'a';
		LDSketch_update(lds, key[i], 1024 * 1024);//插入key值
	}
	//LDSketch_update(lds, key2, 64);//插入key值
	LDSketch_write_plaintext(lds, "output.txt");//输出sketch的内容
	LDSketch_destroy(lds);
	system("PAUSE");
	//dyn_tbl_print(lds->tbl[1], "dyn.txt");
	/*int j, k;
	for (j = 0; j < lds->h; ++j) {
		k = LDSketch_find(lds, key, 0, lds->lgn - 1, j);
		//tbl->T[j*tbl->w+k] += val;
		printf("%d ", k);
		//dyn_tbl_update(sk->tbl[j*sk->w + k], key, val);
	}*/
	
	return 0;
}
