#ifndef EVENT_H
#define EVENT_H

namespace Scratch
{
    enum Event_t
    {
        UNKNOWN,

        QUIT
    };

    struct Event
    {
        Event_t type;
    };
}

#endif // EVENT_H
