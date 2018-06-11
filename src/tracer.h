#ifndef TRACER_H
#define TRACER_H
/*
 * Source Code
 * https://android.googlesource.com/platform/frameworks/native/+/5b38a1d/include/utils/Trace.h
 * https://android.googlesource.com/platform/frameworks/native/+/jb-dev/libs/utils/Trace.cpp
 */
#include <fcntl.h>
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

class Tracer {
public:
    inline Tracer() { Init(); }

    static inline void TraceCounter(const char* name, int32_t value)
    {
        char buf[1024];
        snprintf(buf, 1024, "C|%d|%s|%d", getpid(), name, value);
        write(sTraceFD, buf, strlen(buf));
    }

    static inline void TraceBegin(const char* name)
    {
        char buf[1024];
        size_t len = snprintf(buf, 1024, "B|%d|%s", getpid(), name);
        write(sTraceFD, buf, len);
    }

    static inline void TraceEnd()
    {
        char buf = 'E';
        write(sTraceFD, &buf, 1);
    }

private:
    static inline void Init()
    {
        const char* const traceFileName = "/sys/kernel/debug/tracing/trace_marker";
        sTraceFD = open(traceFileName, O_WRONLY);
        if (sTraceFD == -1) {
            std::cout << "error opening trace file: " << strerror(errno) << " (" << errno << ")" << std::endl;
            // sEnabledTags remains zero indicating that no tracing can occur
        }
    }

    static int sTraceFD;
};

class ScopedTrace {
public:
    inline ScopedTrace(const char* name)
    {
        Tracer::TraceBegin(name);
    }

    inline ~ScopedTrace()
    {
        Tracer::TraceEnd();
    }
};
#endif // TRACER_H
