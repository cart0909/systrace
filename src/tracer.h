#ifndef TRACER_H
#define TRACER_H
/*
 * Source Code
 * https://android.googlesource.com/platform/frameworks/native/+/5b38a1d/include/utils/Trace.h
 * https://android.googlesource.com/platform/frameworks/native/+/jb-dev/libs/utils/Trace.cpp
 */
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

class Tracer {
public:
    Tracer();
    static void TraceCounter(const char* name, int32_t value);
    static void TraceBegin(const char* name);
    static void TraceEnd();

private:
    static void Init();
    static int sTraceFD;
};

class ScopedTrace {
public:
    ScopedTrace(const char* name);
    ~ScopedTrace();
};

#endif // TRACER_H
