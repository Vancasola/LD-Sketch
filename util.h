#pragma once
/*
 * common.hpp
 * - common stuff shared by all files
 */

#ifndef __common_hpp__
#define __common_hpp__

#include <stdio.h>
#include <stdint.h>

#define MIN(x, y) x < y ? x : y
#define MAX(x, y) x > y ? x : y

 /*
  * Convert IP (in network order) to string
  */
inline char* ip2a(uint32_t ip, char* addr) {
	/*
	sprintf(addr, "%d.%d.%d.%d", ip & 0xff, (ip >> 8) & 0xff, (ip >> 16) &
		0xff, (ip >> 24) & 0xff);
		*/
	//sprintf(addr, "%d.%d.%d.%d", (ip >> 24) & 0xff, (ip >> 16) & 0xff,(ip >> 8) & 0xff, ip & 0xff );
	sprintf(addr, "%d.%d.%d.%d", ip & 0xff, (ip >> 8) & 0xff, (ip >> 16) &
            0xff, (ip >> 24) & 0xff);
	return addr;
}

/**
 * IP flow key
 * */
typedef struct __attribute__ ((__packed__)) flow_key {
    uint32_t src_ip;
    uint32_t dst_ip;
    uint16_t src_port;
    uint16_t dst_port;
    uint8_t protocol;
} flow_key_t;

/**
 *input data
 * */
typedef struct __attribute__ ((__packed__)) Tuple {
    flow_key_t key;
    uint32_t size;
} tuple_t;

#endif
