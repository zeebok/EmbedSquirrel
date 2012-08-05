// Test run for embedding Squirrel for game scripting

#include <stdarg.h>
#include <stdio.h>

#include <sqrat.h>

#ifdef SQUNICODE
    #define scvprintf vwprintf
#else
    #define scvprintf vprintf
#endif

void helloWorld(void)
{
    printf("Hello World!\n");
}

int main(int argc, char** argv)
{
    using namespace Sqrat;
    HSQUIRRELVM v;
    v = sq_open(1024);

    sq_seterrorhandler(v);

    DefaultVM::Set(v);

    Table myTable(v);
    myTable.Func("printworld", &helloWorld);
    RootTable(v).Bind("MyTable", myTable);

    try
    {
        Script test;
        test.CompileFile(_SC("test.nut"));
        test.Run();
    }
    catch(Exception e)
    {
        printf("There was an error: %s\n", e.Message().c_str());
    }

    //sq_close(v);

    return 0;
}