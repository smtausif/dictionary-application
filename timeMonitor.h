#ifndef SENECA_TIMEMONITOR_H
#define SENECA_TIMEMONITOR_H

#include <string>
#include <chrono>
#include "event.h"  

namespace seneca {

    class TimeMonitor {
        std::string m_name{};
        std::chrono::steady_clock::time_point m_start{};

    public:
        void startEvent(const char* name);
        Event stopEvent();
    };

}

#endif
