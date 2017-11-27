#include "tracer.h"
#include <iostream>
static Tracer gTracer;
int Tracer::sTraceFD = -1;

Tracer::Tracer()
{
    Init();
}

void Tracer::Init()
{
    const char* const traceFileName = "/sys/kernel/debug/tracing/trace_marker";
    sTraceFD = open(traceFileName, O_WRONLY);
    if (sTraceFD == -1) {
        std::cout << "error opening trace file: " << strerror(errno) << " (" << errno << ")" << std::endl;
        // sEnabledTags remains zero indicating that no tracing can occur
    }
}

void Tracer::TraceCounter(const char* name, int32_t value)
{
    char buf[1024];
    snprintf(buf, 1024, "C|%d|%s|%d", getpid(), name, value);
    write(sTraceFD, buf, strlen(buf));
}

void Tracer::TraceBegin(const char* name)
{
    char buf[1024];
    size_t len = snprintf(buf, 1024, "B|%d|%s", getpid(), name);
    write(sTraceFD, buf, len);
}

void Tracer::TraceEnd()
{
    char buf = 'E';
    write(sTraceFD, &buf, 1);
}

ScopedTrace::ScopedTrace(const char* name)
{
    Tracer::TraceBegin(name);
}

ScopedTrace::~ScopedTrace()
{
    Tracer::TraceEnd();
}
