#include <stdarg.h>

internal char*
CatStrings(char* first, char* second)
{
    int CombinedLength = strlen(first) + strlen(second);
    char* Result = (char*)malloc(CombinedLength + 1);
    memcpy(Result, first, strlen(first));
    memcpy(Result + strlen(first), second, strlen(second));
    Result[CombinedLength] = '\0';

    return Result;
}


struct ReadFileResult
{
    bool Success;
    u8* Contents;
    u32 Size;
};

internal ReadFileResult
ReadEntireFile(char* Filename)
{
    ReadFileResult Result = {0};

    FILE *File = fopen(Filename, "rb");
    if (File)
    {
        fseek(File, 0, SEEK_END);
        Result.Size = ftell(File);
        fseek(File, 0, SEEK_SET);  

        Result.Contents = (u8*)malloc(Result.Size);
        fread(Result.Contents, Result.Size, 1, File);
        fclose(File);

        Result.Success = true;
    }
    else
    {
        char Buffer[256];
        sprintf(Buffer, "Unable to open file '%s'\n", Filename);
        OutputDebugString(Buffer);
    }

    return Result;
}

internal void
DPrint(char* fmt, ...)
{
#ifdef DEBUG    
    char Buffer[512];

    va_list args;
    va_start(args, fmt);
    vsprintf(Buffer, fmt, args);
    va_end(args);

    OutputDebugString(Buffer);
#endif
}