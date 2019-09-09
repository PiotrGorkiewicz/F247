#include "f247_gui_sdl2_environment.cpp"
#include "f247_branched.cpp"
#include "f247_getch.cpp"
#include "f247_aud_portaudio.cpp"
#include "f247_db_sqlite.cpp"
#include "f247_sig_gen_dual_cos.cpp"

int main(int argc, char** argv)

    {

    // Creation of the runnable objects
    F247_GUI_SDL2_ENVIRONMENT obj_environment("obj_environment");
    F247_SIG_GEN_DUAL_COS     obj_gen_ton("obj_gen_ton");
    F247_SIG_GEN_DUAL_COS     obj_gen_mod("obj_gen_mod");
    F247_AUD_PORTAUDIO        obj_aud("obj_aud");
    F247_DB_SQLITE            obj_db("obj_db");

    // Parameters for generators
    obj_gen_ton.signal_period_num=44100;  //sampling frequency
    obj_gen_ton.signal_period_den=3000;   //tone frequency
    obj_gen_ton.peakL.val=32767;          //tone peak
    obj_gen_ton.peakR.val=32767;          //tone peak
    obj_gen_mod.signal_period_num=44100;  //sampling frequency
    obj_gen_mod.signal_period_den=1;      //phase modulation frequency
    obj_gen_mod.peakL.val=3.14;           //phase modulation peak
    obj_gen_mod.peakR.val=3.14;           //phase modulation peak

    // Connection of the signals
    obj_gen_ton.LRphase.Connect( &(obj_gen_mod.valL) );
    obj_aud.inpL.Connect( &(obj_gen_ton.valL) );
    obj_aud.inpR.Connect( &(obj_gen_ton.valR) );

    // Creation of the tree objects for allocation+freeing and clocking
    F247_BRANCHED node_environment("node_environment");
    F247_BRANCHED node_gen_ton("node_gen_ton");
    F247_BRANCHED node_gen_mod("node_gen_mod");
    F247_BRANCHED node_aud("node_aud");
    F247_BRANCHED node_db("node_db");

    // Assigning runnable objects to the tree objects
    node_environment.AttachRunnable(&obj_environment);
    node_gen_ton.AttachRunnable(&obj_gen_ton);
    node_gen_mod.AttachRunnable(&obj_gen_mod);
    node_aud.AttachRunnable(&obj_aud);
    node_db.AttachRunnable(&obj_db);
   
    // Creation of the tree for 
    node_environment.AttachMinorAtEnd(&node_aud);
    node_environment.AttachMinorAtEnd(&node_db);
    node_environment.AttachMinorAtEnd(&node_gen_ton);
    node_environment.AttachMinorAtEnd(&node_gen_mod);

    // Assigning clock
    obj_aud.ConnectUpdateTime(&node_environment);

    // Allocation the tree
    node_environment.ResetResults();
    node_environment.RunDownwards(&F247_ALLOCATABLE::act_allocate,NULL);

    obj_aud.SetUpdateTimeOn();

    printf("001\n");fflush(stdout);

    F247_GETCH_GetchWait();

    printf("002\n");fflush(stdout);
    
    obj_aud.SetUpdateTimeOff();

    node_environment.DiveRunUpwards(&F247_ALLOCATABLE::act_free,NULL);

    return 0;

    }

