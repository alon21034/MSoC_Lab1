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
    sensitive << iclk.pos();
}

void Stimulus::stimulus_thread(void) {
    cout << "stimulus thread" << endl;
    sc_time DELAY(1,SC_NS);
    unsigned PTS=25;
    unsigned DELTA = 2;
    for (unsigned t=0;t<PTS;t++) {
        double data = 0.0;
        if ((t-10) <= DELTA || (10-t) <= DELTA ) data = 1.0; // impulse
        orig_in.write(data);
        data_in.write(data);
        wait(DELAY);
    }//endfor
}//end stimulus_thread()