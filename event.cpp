#include "event.h"
#include <iomanip>
#include <iostream>
#include "settings.h" 

namespace seneca {

    Event::Event(const char* name, const std::chrono::nanoseconds& duration)
        : m_name(name), m_duration(duration) {}

    std::ostream& operator<<(std::ostream& os, const Event& event) {
        static int counter = 1;

        // Getting the duration value in the correct unit
        long long durationValue = 0;
        if (g_settings.m_time_units == "seconds")
            durationValue = std::chrono::duration_cast<std::chrono::seconds>(event.m_duration).count();
        else if (g_settings.m_time_units == "milliseconds")
            durationValue = std::chrono::duration_cast<std::chrono::milliseconds>(event.m_duration).count();
        else if (g_settings.m_time_units == "microseconds")
            durationValue = std::chrono::duration_cast<std::chrono::microseconds>(event.m_duration).count();
        else // default to nanoseconds
            durationValue = event.m_duration.count();

        // Setting width based on unit
        int durationWidth = 11;
        if (g_settings.m_time_units == "seconds")
            durationWidth = 2;
        else if (g_settings.m_time_units == "milliseconds")
            durationWidth = 5;
        else if (g_settings.m_time_units == "microseconds")
            durationWidth = 8;

        os << std::right << std::setw(2) << counter << ": "
           << std::right << std::setw(40) << event.m_name << " -> "
           << std::right << std::setw(durationWidth) << durationValue << " "
           << g_settings.m_time_units;

        ++counter;
        return os;
    }

}
