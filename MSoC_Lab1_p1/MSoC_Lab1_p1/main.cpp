

#include <systemc.h>
#include "Counter.h"
#include "Stimulus.h"
#include "Display.h"

int sc_main( int argc, char** argv ) {

    /*-	Signal Declaration	-*/
    sc_time	        SIM_TIME( 500, SC_NS );
    sc_clock        clk ("clk", 10 );
    sc_signal<int>	Value;
    sc_signal<bool>	Enable;
    sc_signal<bool>	UpDown;
    sc_signal<bool> Reset;
    
    /*-	Instantiation and Net Connection	-*/
    Counter iCounter( "iCounter" );
    iCounter.iclk( clk );
    iCounter.Reset( Reset );
    iCounter.Enable( Enable );
    iCounter.UpDown( UpDown );
    iCounter.Value( Value );
    
    Stimulus iStimulus( "iStimulus"	);
    iStimulus.iclk( clk );
    iStimulus.Enable( Enable );
    iStimulus.Reset( Reset );
    iStimulus.UpDown( UpDown );
    
    Display iDisplay( "iDisplay");
    iDisplay.Value( Value );

    /*-	Run Simulation	-*/
    sc_start( SIM_TIME );

    /*-	Clean Up	-*/	
    return 0;

}



