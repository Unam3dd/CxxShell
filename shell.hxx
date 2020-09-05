#include <iostream>

#ifdef _WIN32
    #include <windows.h>

    namespace shell
    {
        typedef struct ShellStdio{
            std::string output;
            int size;

        } ShellStdio;

        class Shell{
            public:
                void SpawnShell(std::string process);
                void SpawnShellCustomStd(std::string process,HANDLE hStdin, HANDLE hStdout, HANDLE hStderr);
                std::string ExecuteShellCommand(std::string command,int size);
                std::string ExecutePowerShellCommand(std::string command,int size);
                ShellStdio *ExecShellCommand(std::string command, ShellStdio *s);
        };
    }
#endif