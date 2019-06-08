#include "LDSketch.hpp"
#include "extract.h"
#include "hash.h"
#include "util.h"
#include <fstream>
#include <ctime>
#include <string.h>
#include "Perflow.hpp"
using namespace std;
//@ip:include src and dst ip, 64 bit
//tcpdump -nn -t -q
#define heavy_key_number 5000
#define DATASET "/home/sdn/SKETCH/dataset/test/caida_s.txt"
unsigned int l=0;
#define LGN 104
#define THRESHOLD 223444//108068
#define WIDTH 1
#define HEITH 1
#define TOTAL_PKTS 200000
#define OUPUT_HITTER "/home/sdn/SKETCH/results/hitter/LDSketch.txt"
#define OUPUT_CHANGER "/home/sdn/SKETCH/results/changer/LDSketch.txt"
#define OUPUT_SIZE "/home/sdn/SKETCH/results/hitter/sketch_size.txt"
/*
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
    printf("src:%s dst:%s\n", ip2a(*src, ipks), ip2a(*dst, ipkd));
    return;
}
 */
/*
 from string to src and dst:
 string temp ="ARP, Request who-has 192.168.1.112 tell 192.168.1.1, length 28";
 extract:
 (Extract(temp))
 192.168.1.112 192.168.1.1 28
 print src and dst:string src(ex,0,ex.find(' ')), tex(ex,ex.find(' ')+1,ex.size()),dst(tex,0,ex.find(' ')-1);
 unsigned long ip_src = Convert_IP(src), ip_dst = Convert_IP(dst);
 unsigned long long ip=ip_src;
 ip = (ip << 32) + ip_dst;
 Print_Ip(&ip);
 print length:
 Convert_length(ex)
 */
/*
int main(int argc, char** argv){
    //read file
    ifstream infile;
    //string filename = "/Users/vancasola/Desktop/traffic.txt";
    string filename = "/home/sdn/dataset/test/caida_s.txt";
    infile.open(filename);
    if(!infile)cout<<"can't open the file"<<endl;
    //init bucket
    unsigned int l=0;
    int lgn = 104;
    long long T = 20*1024;
    unsigned char *key = new unsigned char[8];
    unsigned char *keys = new unsigned char[8*heavy_key_number];
    int num_key = 0;
    int w=10000,h=4;
    long long thresh_abs = 20*1024;
    unsigned int tbl_id = 0;
    //dyn_tbl_t* ld = dyn_tbl_init(l, lgn, T);
    LDSketch_t* lds = LDSketch_init(w, h, l, lgn, thresh_abs, tbl_id);
    tuple_t t;
    string line;
    getline(infile,line);
            char p[100] ;
            strcpy(p,line.c_str());
            read_flowkey( p, &t);
    LDSketch_update(lds, (unsigned char*)&(t.key), (uint64_t)t.size);
    FILE* f = fopen("/home/sdn/dataset/detect_results/LDSketch.txt","w");
    //for(int i=0;i<1;i++)
    //{

        print_tuple(f, &t);
    //}
    infile.close();
    return 0;
    //update ld_bucket
    unsigned int total_pkts = 100000,current_pkts = 0;
    string data = "",ex = "";
    long long val=0ll;
    unsigned long long ip = 0ll;
    time_t start = clock(),end;
    while(current_pkts<=total_pkts){
        //get key,value
        getline(infile,data);
        ex = Extract(data);
        if(ex=="!")continue;
        val = Convert_length(ex);
        if (val <= 0)continue;
        ip = Get_key(ex);
        key = (unsigned char *)(&ip);
        //cout << action;
        LDSketch_update(lds, key, val);
        current_pkts++;
        if (current_pkts%1000==0)cout<<current_pkts<<endl;
    }
    end = clock();
    cout<<"lds:update time:"<<((double)(end-start))/CLOCKS_PER_SEC<<endl;
    //-----------get and print heavy key--------
    long long *vals = new long long [heavy_key_number];
    num_key = 0;
    
    LDSketch_get_heavy_keys(lds, thresh_abs,  keys, vals, &num_key);
    unsigned char * pkeys = keys;
    return 0;
    string ldname = "/Users/vancasola/Desktop/ld_result.txt";
    ofstream outld;
    outld.open(ldname);
    if (!outld)cout<<"can't open output file"<<endl;
    cout<<"num_key"<<num_key<<endl;
    for (int i = 0; i < num_key; i++)
    {
        outld<<Print_Heavy_Key(((unsigned long long *)pkeys))<<endl;
        //Print_Ip(((unsigned long long *)pkeys));
        pkeys += 8;
    }
    outld<<num_key<<endl;
    infile.close();
    //init per_flow*/
/*
    unsigned char *pf_keys = new unsigned char[8*heavy_key_number];
    int pf_num_key = 0;
    Perflow* pf = Perflow_init(T,lgn);
    //update per_flow
    infile.open(filename);
    total_pkts = TOTAL_PKTS;
    current_pkts = 0;
    while(current_pkts<=total_pkts){
        //get key,value
        string data = "";
        getline(infile,data);
        string ex = Extract(data);
        int val = Convert_length(ex);
        if (val<=0)continue;
        unsigned long long ip = Get_key(ex);
        key = (unsigned char *)(&ip);
        //update
        Perflow_update(pf, key, val);
        current_pkts++;
    }
    Perflow_get_heavy_key(pf, 10, pf_keys, &pf_num_key);
    infile.close();
 */
    //print ld_bucket

    /*
    //print pf
    cout<<"*******"<<endl;
    unsigned char * pf_pkeys = pf_keys;
    for (int i = 0; i < pf_num_key; i++)
    {
        printf("key == ");
        Print_Ip(((unsigned long long *)pf_keys));
        pf_keys += 8;
    }

    //printf("\nkeys%llx\n", *(unsigned long long*)(keys));
    //cout<<ld->total<<" "<<ld->max_len<<" "<<ld->array.size()<<endl;
    cout<<"pf_num_Key "<<pf_num_key<<endl;
    cout<<"pf_length "<<pf->array.size()<<endl;
    */
    //Print_Ip((unsigned long long *)keys);
    //delete
    /*delete [] keys;
    LDSketch_destroy(lds);
    return 0;
}*/
/*
int main(int argc, char** argv) {
	LDSketch_t* lds = LDSketch_init(10000, 4, 1, 64, 1024 * 1024, 0);
	char * ipk = new  char[5];
	ipk[4] = '\0';

    string temp ="ARP, Request who-has 192.168.1.112 tell 192.168.1.1, length 28";
    temp = "IP 58.247.214.140.8080 > 192.168.1.110.49189: tcp 183";
    cout<<(Extract(temp))<<endl<<endl;
    string ex = Extract(temp);
    string src(ex,0,ex.find(' ')), tex(ex,ex.find(' ')+1,ex.size()),dst(tex,0,ex.find(' ')-1);
    unsigned long ip_src = Convert_IP(src), ip_dst = Convert_IP(dst);
    unsigned long long ip=ip_src;
    ip = (ip << 32) + ip_dst;
    printf("src:%x\n", ip_src);
    printf("dst:%x\n", ip_dst);
    printf("ip:%x\n", ip);

    Print_Ip(&ip);
    printf("\nlength:%u\n", Convert_length(ex));
    //printf("%s\n",ip2a(,ipk))

	unsigned char * key = new unsigned char[9];
	unsigned long long * iptemp = new unsigned long long;
	//unsigned int * src = new unsigned int;
	//unsigned int * dst = new unsigned int;

	//string str = "06:55:46.304503 ARP, Request who-has 192.168.198.2 tell 192.168.198.131, length 1146000000";
	string str = "";
	string result = "";
	//*iptemp = (0x0100a8c00200a8c0);
	long long v = 0ll;
	//*iptemp = Convert_IP(result);
	
	while (1)
	{
		str = "";
		getline(cin, str);
		if (str == "quit")break;
		if (str == "") {  continue; }
        cout<<str<<endl;
		result = Extract(str);
		*iptemp = Convert_IP(result);
		key = (unsigned char *)iptemp;
		v = Convert_length(str);
		//LDSketch_update(lds, key, 1024 * 1024);//插入key值
		LDSketch_update(lds, key, v);//插入key值
		//long long value = 0ll;
		long long *pvalue = new long long[10];
		int  num_key = 0;
		unsigned char* rekey = new unsigned char[heavy_key_number * 8];
		//LDSketch_get_heavy_keys(lds, 1024 * 1024, rekey, pvalue, &num_key);
		LDSketch_get_heavy_keys(lds, 200, rekey, pvalue, &num_key);
		unsigned char * ptr_rekey = rekey;
		//printf("%llx\n", *(unsigned long long*)*ptr_rekey);printf("!!!");
		if (num_key == 0)continue;
		else
		for (int i = 0; i < num_key; i++)
		{
			printf("key == ");
			Print_Ip(((unsigned long long *)ptr_rekey));
			printf("value == %lld\n", pvalue[i]);
			ptr_rekey += 8;
		}
	}
	cout << "!!!" << endl;
	LDSketch_write_plaintext(lds, "output.txt");//输出sketch的内容
	//dyn_tbl_print(lds->tbl[0], "dyns.txt");
	LDSketch_destroy(lds);
	system("PAUSE");	
	
	return 0;
	//	cout <<  result << endl;
	//cout << "string == " << str << endl;
	//printf("convert to hex:%llxh\n", Convert_IP(result));
	//printf("the length is :%d\n\n\n", Convert_length(str));
	//unsigned int ipi = *(key); //& 0xffffffff;

	ouput the heavy key's results
	printf("%d\n", num_key);
	unsigned char *ptr_key = rekey;
	Print_Ip(((unsigned long long *)rekey));

	//ouput the heavy hey
}
*/

/*
//******************************HEAVY HITTER******************************
int main(int argc, char** argv){
    //read file
    ifstream infile;
    //string filename = "/Users/vancasola/Desktop/traffic.txt";
    string filename = DATASET;
    infile.open(filename);
    if(!infile)cout<<"can't open the file"<<endl;
    //init bucket
    unsigned int l=0;
    int lgn = LGN;
    long long T = THRESHOLD;
    unsigned char *key = new unsigned char[lgn/8];
    unsigned char *keys = new unsigned char[(lgn/8)*heavy_key_number];
    int num_key = 0;
    int w = WIDTH;
    int h = HEITH;
    long long thresh_abs = THRESHOLD;//20*1024;
    unsigned int tbl_id = 0;
    //dyn_tbl_t* ld = dyn_tbl_init(l, lgn, T);
    LDSketch_t* lds = LDSketch_init(w, h, l, lgn, thresh_abs, tbl_id);
    tuple_t t;
    string line;
    
    //update ld_bucket
    unsigned int total_pkts = TOTAL_PKTS,current_pkts = 0;
    string data = "",ex = "";
    uint16_t val=0;
    unsigned long long ip = 0ll;
    time_t start = clock(),end;
    while(current_pkts<=total_pkts){
        //get key,value
        if(current_pkts>=total_pkts)break;
        getline(infile,line);
        char p[100] ;
        strcpy(p,line.c_str());
        read_flowkey( p, &t);
        LDSketch_update(lds, (unsigned char*)&(t.key), (uint64_t)t.size);
        current_pkts++;

    }
    end = clock();
    cout<<"lds:update time:"<<((double)(end-start))/CLOCKS_PER_SEC<<endl;
    //-----------get and print heavy key--------
    long long *vals = new long long [heavy_key_number];
    num_key = 0;
    
    LDSketch_get_heavy_keys(lds, thresh_abs,  keys, vals, &num_key);
    unsigned char * pkeys = keys;

    FILE* f = fopen(OUPUT_HITTER,"w");
    if(f==NULL)printf("can't open the file");
    cout<<"num_key"<<num_key<<endl;
    for (int i = 0; i < num_key; i++)
    {
        memcpy(&t, pkeys, sizeof(flow_key_t));
        t.size = vals[i];
        //printf("2:%lu %lu\n",vals[i], t.size);
        print_tuple(f, &t);
        //Print_Ip(((unsigned long long *)pkeys));
        pkeys += lgn/8;
    }
    LDSketch_Print_Size(lds);
    int Size = LDSketch_Size(lds);
    cout<<"size:"<<Size<<"B "<<Size/1024<<" "<<"KB"<<endl;
    //FILE* fos = fopen(OUPUT_SIZE,"w+");
    //if(fos==NULL)cout<<"cannot open the file"<<endl;
    //fprintf(fos, "LD: %d ", Size);
    //fclose(fos);
    fclose(f);
    infile.close();
    return 0;
}*/




//******************************HEAVY CHANGER******************************
int main(int argc, char** argv){
    //read file
    ifstream infile;
    //string filename = "/Users/vancasola/Desktop/traffic.txt";
    string filename = DATASET;
    infile.open(filename);
    if(!infile)cout<<"can't open the file"<<endl;
    //init bucket
    unsigned int l=0;
    int lgn = LGN;
    long long T = THRESHOLD;
    unsigned char *key = new unsigned char[lgn/8];
    unsigned char *keys = new unsigned char[(lgn/8)*heavy_key_number];
    int num_key = 0;
    int w = WIDTH;
    int h = HEITH;
    long long thresh_abs = THRESHOLD;//20*1024;
    unsigned int tbl_id = 0;
    //dyn_tbl_t* ld = dyn_tbl_init(l, lgn, T);
    LDSketch_t* lds1 = LDSketch_init(w, h, l, lgn, thresh_abs, tbl_id);
    LDSketch_t* lds2 = LDSketch_init(w, h, l, lgn, thresh_abs, tbl_id);

    tuple_t t;
    string line;
    
    //update ld_bucket
    unsigned int total_pkts = TOTAL_PKTS,current_pkts = 0;
    string data = "",ex = "";
    uint16_t val=0;
    unsigned long long ip = 0ll;
    time_t start = clock(),end;
    while(current_pkts<=0.5*total_pkts){
        //get key,value
        if(current_pkts>=total_pkts)break;
        getline(infile,line);
        char p[100] ;
        strcpy(p,line.c_str());
        read_flowkey( p, &t);
        LDSketch_update(lds1, (unsigned char*)&(t.key), (uint64_t)t.size);
        current_pkts++;

    }
    end = clock();
    while(current_pkts<=total_pkts){
        //get key,value
        if(current_pkts>=total_pkts)break;
        getline(infile,line);
        char p[100] ;
        strcpy(p,line.c_str());
        read_flowkey( p, &t);
        LDSketch_update(lds2, (unsigned char*)&(t.key), (uint64_t)t.size);
        current_pkts++;

    }
    end = clock();
    cout<<"lds:update time:"<<((double)(end-start))/CLOCKS_PER_SEC<<endl;
    //-----------get and print heavy key--------
    long long *vals = new long long [heavy_key_number];
    num_key = 0;


    LDSketch_get_heavy_changers(lds1, lds2, thresh_abs,  keys, vals, &num_key);
    unsigned char * pkeys = keys;

    FILE* f = fopen(OUPUT_CHANGER,"w");
    if(f==NULL)printf("can't open the file");
    cout<<"num_key"<<num_key<<endl;
    
    for (int i = 0; i < num_key; i++)
    {
        memcpy(&t, pkeys, sizeof(flow_key_t));
        t.size = vals[i];
        //printf("2:%lu %lu\n",vals[i], t.size);
        print_tuple(f, &t);
        //Print_Ip(((unsigned long long *)pkeys));
        pkeys += lgn/8;
    }
    LDSketch_Print_Size(lds1);
    printf("--------------------\n");
    LDSketch_Print_Size(lds2);
    printf("--------------------\n");
    int Size = LDSketch_Size(lds1);
    Size += LDSketch_Size(lds2);
    cout<<"Total length:"<<LDSketch_Total_Length(lds1)+LDSketch_Total_Length(lds1)<<endl;
    cout<<"size:"<<Size<<"B "<<Size/1024<<" "<<"KB"<<endl;
    //FILE* fos = fopen(OUPUT_SIZE,"w+");
    //if(fos==NULL)cout<<"cannot open the file"<<endl;
    //fprintf(fos, "LD: %d ", Size);
    //fclose(fos);
    fclose(f);
    infile.close();
    
    return 0;
}