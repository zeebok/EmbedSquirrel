// Test run for embedding Squirrel for game scripting

#include <stdarg.h>
#include <stdio.h>

#include <squirrel.h>
#include <sqstdio.h>
#include <sqstdaux.h>

#ifdef SQUNICODE
    #define scvprintf vwprintf
#else
    #define scvprintf vprintf
#endif

void printfunc(HSQUIRRELVM v, const SQChar* s, ...)
{
    va_list arglist;
    va_start(arglist, s);
    scvprintf(s, arglist);
    va_end(arglist);
}

void call_foo(HSQUIRRELVM v, int n, float f, const SQChar* s)
{
    int top = sq_gettop(v);
    sq_pushroottable(v);
    sq_pushstring(v, _SC("foo"), -1);
    if(SQ_SUCCEEDED(sq_get(v, -2)))
    {
        sq_pushroottable(v);
        sq_pushinteger(v, n);
        sq_pushfloat(v, f);
        sq_pushstring(v, s, -1);
        sq_call(v, 4, 0, 0);
    }
    sq_settop(v, top);
}

int main(int argc, char** argv)
{
    HSQUIRRELVM v;
    v = sq_open(1024);

    sqstd_seterrorhandlers(v);

    sq_setprintfunc(v, printfunc, NULL);

    sq_pushroottable(v);
    if(SQ_SUCCEEDED(sqstd_dofile(v, _SC("test.nut"), 0, 1)))
    {
        call_foo(v, 1, 2.5, _SC("teststring"));
    }

    sq_pop(v, 1);
    sq_close(v);

    return 0;
}