//
//  Stimulus.cpp
//  MSoC_Lab1_p2
//
//  Created by Lee Haw on 13/3/26.
//  Copyright (c) 2013年 Lee Haw. All rights reserved.
//

#include "Stimulus.h"

Stimulus::Stimulus(sc_module_name name)
    :sc_module(name) {
        
    SC_THREAD( stimulus_thread );
        dont_initialize();
    sensitive << clk.pos();
}

void Stimulus::stimulus_thread(void) {
    sc_time DELAY(1,SC_NS);
    unsigned PTS=25;
    unsigned START = 8;
    unsigned STOP = 12;
    for (unsigned t=0;t<PTS;t++) {
        double data = 0.0;
        if ((t <= STOP) && (t >= START) ) data = 1.0; // impulse
        orig_in->write(data);
        data_in->write(data);
        wait(DELAY);
    }//endfor
}//end stimulus_thread()