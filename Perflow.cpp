//
//  Perflow.cpp
//  LDSketch
//
//  Created by Vancasola on 2019/3/6.
//  Copyright © 2019 none. All rights reserved.
//

#include "Perflow.hpp"
std::unordered_map<dyn_tbl_key_t, long long, dyn_tbl_key_hash, dyn_tbl_key_eq> array;

Perflow* Perflow_init(long long T, unsigned int lgn)
{
    Perflow* ret = new Perflow;
    ret->lgn = lgn;
    return ret;
}

void Perflow_destroy(Perflow* per_flow)
{
    delete per_flow;
}

void Perflow_get_heavy_key(Perflow* per_flow, long long thresh, unsigned char* keys, int* num_key)
{
    //for(std::unordered_map<dyn_tbl_key_t, long long>::iterator it = dyn_tbl->array.begin(); it != dyn_tbl->array.end(); ++it) {
    int n = 0;
    for (auto it = per_flow->array.begin(); it != per_flow->array.end(); ++it) {
        if (abs(it->second) >= thresh) {
            memcpy(keys + n * per_flow->lgn / 8, it->first.key, per_flow->lgn / 8);
            n++;
            // dyn_tbl_key_t key = it->first;
            // ret.insert(key);
        }
    }
    *num_key = n;
}

void Perflow_update(Perflow* per_flow, unsigned char* key_str, int val)
{
    dyn_tbl_key_t key;
    memcpy(key.key, key_str, per_flow->lgn / 8);
    if (per_flow->array.find(key) != per_flow->array.end()) {
        per_flow->array[key] += val;
    }
    else {
        per_flow->array[key] = val;
    }
}
