//
//  Stimulus.h
//  MSoC_Lab1_p2
//
//  Created by Lee Haw on 13/3/26.
//  Copyright (c) 2013年 Lee Haw. All rights reserved.
//

#ifndef __MSoC_Lab1_p2__Stimulus__
#define __MSoC_Lab1_p2__Stimulus__

#include <iostream>
#include <systemc.h>

SC_MODULE(Stimulus) {
    
    sc_in_clk iclk;
    sc_port<sc_fifo_out_if<double> > orig_in;
    sc_port<sc_fifo_out_if<double> > data_in;
    
    SC_HAS_PROCESS( Stimulus );
    Stimulus(sc_module_name name);
    
    void stimulus_thread(void);
};

#endif /* defined(__MSoC_Lab1_p2__Stimulus__) */
