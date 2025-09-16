#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H

#include "event.h"     
#include <cstddef> // For size_t
#include <ostream> // For std::ostream

namespace seneca {

    class Logger {
        Event* m_events{};
        size_t m_count{};
        size_t m_capacity{};

        void resize();

    public:
        Logger();
        ~Logger();

        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        Logger(Logger&&);
        Logger& operator=(Logger&&);

        void addEvent(const Event& event);

        friend std::ostream& operator<<(std::ostream& os, const Logger& logger);
    };

}

#endif
