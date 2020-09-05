#include "shell.hxx"

#ifdef _WIN32
    void shell::Shell::SpawnShell(std::string process){
    
        PROCESS_INFORMATION pinfo;
        STARTUPINFO sinfo;

        memset(&sinfo,0,sizeof(sinfo));
        memset(&pinfo,0,sizeof(pinfo));

        sinfo.cb = sizeof(sinfo);
        sinfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
        sinfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);
        sinfo.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
        sinfo.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    
        CreateProcessA(NULL,(LPSTR)process.c_str(),NULL,NULL,TRUE,0,NULL,NULL,(LPSTARTUPINFOA)&sinfo,&pinfo);

        WaitForSingleObject(pinfo.hProcess,INFINITE);
        CloseHandle(pinfo.hProcess);
        CloseHandle(pinfo.hThread);
    };

    void shell::Shell::SpawnShellCustomStd(std::string process,HANDLE hStdin, HANDLE hStdout, HANDLE hStderr)
    {
        PROCESS_INFORMATION pinfo;
        STARTUPINFO sinfo;

        memset(&sinfo,0,sizeof(sinfo));
        memset(&pinfo,0,sizeof(pinfo));

        sinfo.cb = sizeof(sinfo);
        sinfo.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
        sinfo.hStdError = hStderr;
        sinfo.hStdInput = hStdin;
        sinfo.hStdOutput = hStdout;
    
        CreateProcessA(NULL,(LPSTR)process.c_str(),NULL,NULL,TRUE,0,NULL,NULL,(LPSTARTUPINFOA)&sinfo,&pinfo);

        WaitForSingleObject(pinfo.hProcess,INFINITE);
        CloseHandle(pinfo.hProcess);
        CloseHandle(pinfo.hThread);
    }

    std::string shell::Shell::ExecuteShellCommand(std::string command,int size)
    {
        FILE *fp;
        char buffer[size];
        std::string return_buffer;

        fp = _popen(command.c_str(),"r");

        if (fp == NULL)
            return std::string("");

        while (fgets(buffer,size,fp) != NULL)
        {
            return_buffer.append(buffer);
        }

        fclose(fp);

        return (return_buffer);
    }

    std::string shell::Shell::ExecutePowerShellCommand(std::string command,int size)
    {
        FILE *fp;
        char buffer[size];
        std::string return_buffer;
        std::string cmd = "powershell.exe -NoProfile -C ";
        cmd.append(command);

        fp = _popen(cmd.c_str(),"r");

        if (fp == NULL)
            return std::string("");

        while (fgets(buffer,size,fp) != NULL)
        {
            return_buffer.append(buffer);
        }

        fclose(fp);

        return (return_buffer);
    }

    shell::ShellStdio *shell::Shell::ExecShellCommand(std::string command, ShellStdio *s)
    {
        FILE *fp;
        char buffer[s->size];

        fp = _popen(command.c_str(),"r");

        if (fp == NULL)
            return s;

        while (fgets(buffer,s->size,fp) != NULL)
        {
            s->output.append(buffer);
        }

        fclose(fp);

        return (s);
    }

#endif