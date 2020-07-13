#define RUN 5
#define ADVANCED false

#if (RUN == 1)
    #include "001_blink.hpp"
#elif (RUN == 2)
    #include "002_flash.hpp"
#elif (RUN == 3)
    #include "003_train.hpp"
#elif (RUN == 4)
    #if ADVANCED
        #include "004b_onoff_blink.hpp"
    #else
        #include "004a_onoff_blink.hpp"
    #endif
#elif (RUN == 5)
    #if ADVANCED
        #include "005b_blink_speed.hpp"
    #else
        #include "005a_blink_speed.hpp"
    #endif
#endif
