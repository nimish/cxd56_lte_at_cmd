#include <nuttx/config.h>
#include <stdio.h>
#include <string>
#include <lte/lte_api.h>

extern "C" {
    int lte_at_cmd_main(int argc, char *argv[]);
}

int lte_at_cmd_main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <command>\n", argv[0]);
        exit(0);
    }

    std::string command = argv[1];
    for (int i = 2; i < argc; i++)
    {
        command += " ";
        command += argv[i];
    }
    
    int new_end = command.find_last_not_of(" \t\n\r");
    if (new_end != -1)
    {
        command.erase(new_end + 1);
    }
    command.erase(0, command.find_first_not_of(" \t\n\r"));

    if (command.find("AT") != 0)
    {   
        // not an AT command
        printf("%s: not an AT command\n", command.c_str());
        return -1;
    }
    command += "\r";
    char *response = new char[LTE_AT_COMMAND_MAX_LEN];
    int resplen = 0;
    lte_send_atcmd_sync(command.c_str(), command.length(), response, LTE_AT_COMMAND_MAX_LEN, &resplen);
    if (resplen > 0)
    {
        printf("%s\n", response);
    } 
    else
    {
        printf("%s: no response\n", command.c_str());
    }
    delete [] response;
    lte_errinfo_t errinfo;
    lte_get_errinfo(&errinfo);
    if (errinfo.err_no != LTE_RESULT_OK)
    {
        printf("ERROR:\n");
        printf("command: %s\n", command.c_str());
        printf("error code: %lu\n", errinfo.err_no);
        printf("error info: %s\n", errinfo.err_string);
        printf("error indicator: %u\n", errinfo.err_indicator);
        printf("error result code: %ld\n", errinfo.err_result_code);
    }
    return EXIT_SUCCESS;
}
