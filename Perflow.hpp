//
//  Perflow.hpp
//  LDSketch
//
//  Created by 周政演 on 2019/3/6.
//  Copyright © 2019 none. All rights reserved.
//

#ifndef Perflow_hpp
#define Perflow_hpp


#include <stdio.h>
#include "dyn_tbl.hpp"

struct Perflow
{
    std::unordered_map<dyn_tbl_key_t, long long, dyn_tbl_key_hash, dyn_tbl_key_eq> array;

    /// expansion parameter: T
    long long T;

    /// length of keys
    unsigned int lgn;
};

Perflow* Perflow_init(long long T, unsigned int lgn);

void Perflow_destroy(Perflow* per_flow);

void Perflow_get_heavy_key(Perflow* per_flow, long long thresh, unsigned char* keys, int* num_key);

void Perflow_update(Perflow* per_flow, unsigned char* key_str, int val);

#endif /* Perflow_hpp */
