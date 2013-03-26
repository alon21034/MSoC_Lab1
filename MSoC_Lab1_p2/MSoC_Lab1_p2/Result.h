//
//  Result.h
//  MSoC_Lab1_p2
//
//  Created by Lee Haw on 13/3/26.
//  Copyright (c) 2013年 Lee Haw. All rights reserved.
//

#ifndef __MSoC_Lab1_p2__Result__
#define __MSoC_Lab1_p2__Result__

#include <iostream>
#include <systemc.h>

SC_MODULE(Result) {
    
    sc_in<int> orig_in;
    sc_in<int> data_out;
    
    SC_HAS_PROCESS(Result);
    Result(sc_module_name name);
    
    void process_thread(void);
};

#endif /* defined(__MSoC_Lab1_p2__Result__) */
