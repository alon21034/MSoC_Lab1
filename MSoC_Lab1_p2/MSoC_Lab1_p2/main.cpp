//BEGIN main.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See fifo_fir.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <iostream>
using std::cout;
using std::endl;

#include <systemc.h>
#include <string.h>
#include "fifo_fir.h"
#include "Stimulus.h"
#include "Result.h"

using namespace std;

unsigned errors = 0;


int sc_main(int argc, char* argv[]) {
    //sc_set_time_resolution(1,SC_PS);
    //sc_set_default_time_unit(1,SC_NS);
    
    string simulation_name = "/Users/leehaw/Documents/MSoC_workspace/Lab1/code/Sample_Code/fifo_fir//fifo_fir.cfg";
    
    sc_time SIM_TIME( 500, SC_NS );
    
    sc_clock clk("clk", 10);
    sc_signal<int> orig_in;
    sc_signal<int> data_in;
    sc_signal<int> data_out;
    
    fifo_fir sc_fifo_ex_i("sc_fifo_ex_i");
    Stimulus iStimulus("iStimulus");
    Result iResult("iResult");
    
    iStimulus.clk(clk);
    iStimulus.orig_in(orig_in);
    iStimulus.data_in(data_in);
    
    iResult.orig_in(orig_in);
    iResult.data_out(data_out);
    
    cout << "INFO: Starting "<<simulation_name<<" simulation" << endl;
    if (errors == 0) sc_start(SIM_TIME);
    cout << "INFO: Exiting "<<simulation_name<<" simulation" << endl;
    cout << "INFO: Simulation " << simulation_name
        << " " << (errors?"FAILED":"PASSED")
        << " with " << errors << " errors"
        << endl;
    return errors?1:0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: main.cpp,v 1.1 2003/11/24 17:21:26 dcblack Exp $
