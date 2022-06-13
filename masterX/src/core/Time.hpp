#pragma once

namespace mx
{
    class Time
    {
    public:
        Time(float seconds = 0.0f)
            : m_seconds(seconds)
        {}

        float seconds() const { return m_seconds; }
        float miliseconds() const { return m_seconds * 1000.0f; }

        operator float() const { return m_seconds; }

        static Time fromMiliseconds(float miliseconds)
        {
            return Time(miliseconds * 0.001f);
        }

    private:
        float m_seconds;
    };
}