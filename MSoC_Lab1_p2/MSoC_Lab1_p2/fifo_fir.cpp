//BEGIN fifo_fir.cpp
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See fifo_fir.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "fifo_fir.h"
#include <fstream>
#include <iomanip>
#include <cmath>

extern unsigned errors;
using std::cout;
using std::cerr;
using std::fixed;
using std::setw;
using std::setfill;
using std::setprecision;
using std::endl;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
fifo_fir::fifo_fir(sc_module_name _name, char* _cfg_filename) :
sc_module(_name),
    m_cfg_filename(_cfg_filename),
    m_taps(0),
    m_tap(0)
{
    SC_THREAD(sc_fifo_ex_thread);
    dont_initialize();
    sensitive << clk.pos();
    
    data = new double[12];
    for(unsigned i = 0 ; i < 13 ; ++i ) {
        data[i] = 0.0;
    }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Read coefficients from configuration file and initialize pipe to zero
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    ifstream cfg_file(m_cfg_filename);
    if (!cfg_file) {
        cerr << "ERROR: Problem opening " << m_cfg_filename << " for input." << endl;
        errors++;
        return;
    }//endif
    cfg_file >> m_taps;
    if (m_taps < 1) {
        cerr << "ERROR: Number of taps must be greater than zero!" << endl;
        errors++;
        return;
    }//endif
    // Allocate memory
    m_pipe  = new double[m_taps];
    m_coeff = new double[m_taps];
    for (unsigned tap=0;tap!=m_taps;tap++) {
        if (cfg_file.eof()) {
            cerr << "ERROR: Too few coefficients when reading [" << tap << "]." << endl;
            errors++;
            return;
        }//endif
        cfg_file >> m_coeff[tap];
        m_pipe[tap] = 0;
    }//endfor
}//end fifo_fir()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Processes
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void fifo_fir::sc_fifo_ex_thread(void) {
    for(;;) {
        unsigned coeff = (m_taps-1-m_tap); // used to index coeffiecients
        // read next piece of data
        double input = data_in->read();
        
        double result = 0;
    
        m_pipe[m_tap++] = input;
        if (m_tap == m_taps) m_tap = 0; // wrap
        
        for (unsigned tap=0;tap!=m_taps;tap++,coeff++) {
            if (coeff == m_taps) coeff = 0; // wrap
        }//endfor
        
        result = data[8] + data[9] * m_coeff[2] + data[10] * m_coeff[1] + data[11] * m_coeff[0];
        data[11] = data[10];
        data[10] = data[9];
        data[9] = data[7];
        data[8] = data[3] + data[4] * m_coeff[5] + data[5] * m_coeff[4] + data[6] * m_coeff[3];
        data[7] = data[6];
        data[6] = data[5];
        data[5] = data[4];
        data[4] = data[2];
        data[3] = input*m_coeff[8] + data[0] * m_coeff[7] + data[1] * m_coeff[6];
        data[2] = data[1];
        data[1] = data[0];
        data[0] = input;
        
        data_out->write(result);
    }//endforever
}//end sc_fifo_ex_thread()

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//END $Id: fifo_fir.cpp,v 1.2 2004/02/02 12:36:18 dcblack Exp $
