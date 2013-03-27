//
//  Result.cpp
//  MSoC_Lab1_p2
//
//  Created by Lee Haw on 13/3/26.
//  Copyright (c) 2013年 Lee Haw. All rights reserved.
//

#include "Result.h"
#include <iomanip.h>

Result::Result(sc_module_name name)
    :sc_module(name) {
    
    SC_THREAD(results_thread);
    dont_initialize();
    sensitive << clk.pos();
}

void Result::results_thread(void) {
    for(unsigned i=0;;i++) {
        double data =  orig_in->read();
        double result =  data_out->read();
        cout << "DATA: "
        << "["  << setw(2) << sc_time_stamp() << "]"
        << "= " << setw(9) << fixed << setprecision(5) << data
        << " "  << setw(9) << fixed << setprecision(5) << result
        << endl;
    }
}