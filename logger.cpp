#include "logger.h"
#include "event.h" 
#include <iostream>

namespace seneca {

    Logger::Logger() = default;

    Logger::~Logger() {
        delete[] m_events;
    }

    Logger::Logger(Logger&& other) {
        *this = std::move(other);
    }

    Logger& Logger::operator=(Logger&& other) {
        if (this != &other) {
            delete[] m_events;
            m_events = other.m_events;
            m_count = other.m_count;
            m_capacity = other.m_capacity;

            other.m_events = nullptr;
            other.m_count = 0;
            other.m_capacity = 0;
        }
        return *this;
    }

    void Logger::resize() {
        size_t newCapacity = (m_capacity == 0) ? 2 : m_capacity * 2;
        Event* temp = new Event[newCapacity];

        for (size_t i = 0; i < m_count; ++i)
            temp[i] = m_events[i];

        delete[] m_events;
        m_events = temp;
        m_capacity = newCapacity;
    }

    void Logger::addEvent(const Event& event) {
        if (m_count == m_capacity)
            resize();

        m_events[m_count++] = event;
    }

    std::ostream& operator<<(std::ostream& os, const Logger& logger) {
        for (size_t i = 0; i < logger.m_count; ++i)
            os << logger.m_events[i] << std::endl;

        return os;
    }

}
