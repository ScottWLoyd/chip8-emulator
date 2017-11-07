#include <windows.h>
#include <stdio.h>
#include <stdlib.h>


#ifdef DEBUG
#define Assert(Expression) if(!(Expression)) {*(int *)0 = 0;}
#else
#define Assert(Expression)
#endif

#define global static
#define internal static

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Input
{ 
    bool Keys[16];   
};

#include "utils.cpp"
#include "chip.cpp"

/* 
 * Types
 */
struct win32_offscreen_buffer
{
    // Pixels are alwasy 32-bits wide, Memory Order BB GG RR XX
    BITMAPINFO Info;
    void *Memory;
    int Width;
    int Height;
    int Pitch;
};

struct win32_window_dimension
{
    int Width;
    int Height;
};


/*
 * Globals
 */
global bool GlobalRunning = false;
global win32_offscreen_buffer GlobalBackbuffer;
global int GlobalDisplayScalar = 8;

internal win32_window_dimension
Win32GetWindowDimension(HWND Window)
{
    win32_window_dimension Result;
    
    RECT ClientRect;
    GetClientRect(Window, &ClientRect);
    Result.Width = ClientRect.right - ClientRect.left;
    Result.Height = ClientRect.bottom - ClientRect.top;

    return(Result);
}


internal void
RenderBackbuffer(Chip* chip, win32_offscreen_buffer *Buffer)
{
    float ScaleFactor = GlobalDisplayScalar;

    u8* Row = (u8*)Buffer->Memory;
    for (int Y=0; Y<Buffer->Height; Y++)
    {
        u32* Pixel = (u32*)Row;
        for (int X=0; X<Buffer->Width; X++)
        {
            int ScaleY = Y / ScaleFactor;
            int ScaleX = X / ScaleFactor;

            int DisplayIndex = ScaleY*chip->DisplayWidth + ScaleX;
            //Assert(DisplayIndex < 2048);
            u32 Color = chip->Display[DisplayIndex] ? 0xFF00FF00 : 0xFF000000;
            *Pixel++ = Color;
        }

        Row += Buffer->Pitch;        
    }
}


internal void
Win32ResizeDIBSection(win32_offscreen_buffer *Buffer, int Width, int Height)
{
    if(Buffer->Memory)
    {
        VirtualFree(Buffer->Memory, 0, MEM_RELEASE);
    }

    Buffer->Width = Width;
    Buffer->Height = Height;

    int BytesPerPixel = 4;

    Buffer->Info.bmiHeader.biSize = sizeof(Buffer->Info.bmiHeader);
    Buffer->Info.bmiHeader.biWidth = Buffer->Width;
    Buffer->Info.bmiHeader.biHeight = -Buffer->Height;
    Buffer->Info.bmiHeader.biPlanes = 1;
    Buffer->Info.bmiHeader.biBitCount = 32;
    Buffer->Info.bmiHeader.biCompression = BI_RGB;

    int BitmapMemorySize = (Buffer->Width*Buffer->Height)*BytesPerPixel;
    Buffer->Memory = VirtualAlloc(0, BitmapMemorySize, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
    Buffer->Pitch = Width*BytesPerPixel;
}


internal void
Win32DisplayBufferInWindow(win32_offscreen_buffer *Buffer,
                           HDC DeviceContext, int WindowWidth, int WindowHeight)
{
    int OffsetX = 10;
    int OffsetY = 10;

    PatBlt(DeviceContext, 0, 0, WindowWidth, OffsetY, BLACKNESS);
    PatBlt(DeviceContext, 0, OffsetY + Buffer->Height, WindowWidth, WindowHeight, BLACKNESS);
    PatBlt(DeviceContext, 0, 0, OffsetX, WindowHeight, BLACKNESS);
    PatBlt(DeviceContext, OffsetX + Buffer->Width, 0, WindowWidth, WindowHeight, BLACKNESS);

    StretchDIBits(DeviceContext,
                  /*
                  X, Y, Width, Height,
                  X, Y, Width, Height,
                  */
                  OffsetX, OffsetY, Buffer->Width, Buffer->Height,
                  0, 0, Buffer->Width, Buffer->Height,
                  Buffer->Memory,
                  &Buffer->Info,
                  DIB_RGB_COLORS, SRCCOPY);
}


internal void
Win32ProcessKeyboardMessage(bool* Key, bool IsDown)
{
    *Key = IsDown;
}


internal void
Win32ProcessPendingMessages(Input* InputState)
{
    MSG Message;
    while(PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
    {
        switch(Message.message)
        {
            case WM_QUIT:
            {
                GlobalRunning = false;
            } break;
            
            case WM_SYSKEYDOWN:
            case WM_SYSKEYUP:
            case WM_KEYDOWN:
            case WM_KEYUP:
            {
                u32 VKCode = (u32)Message.wParam;

                bool WasDown = ((Message.lParam & (1 << 30)) != 0);
                bool IsDown = ((Message.lParam & (1 << 31)) == 0);
                if(WasDown != IsDown)
                {
                    if(VKCode == 'X')
                    {
                        Win32ProcessKeyboardMessage(&InputState->Keys[0], IsDown);
                    }
                    else if(VKCode == '1')
                    {
                        Win32ProcessKeyboardMessage(&InputState->Keys[1], IsDown);
                    }                    
                    else if(VKCode == '2')
                    {
                        Win32ProcessKeyboardMessage(&InputState->Keys[2], IsDown);
                    }
                    else if(VKCode == '3')
                    {
                        Win32ProcessKeyboardMessage(&InputState->Keys[3], IsDown);
                    }
                    else if(VKCode == 'Q')
                    {
                        Win32ProcessKeyboardMessage(&InputState->Keys[4], IsDown);
                    }
                    else if(VKCode == 'W')
                    {
                        Win32ProcessKeyboardMessage(&InputState->Keys[5], IsDown);
                    }
                    else if(VKCode == 'E')
                    {
                        Win32ProcessKeyboardMessage(&InputState->Keys[6], IsDown);
                    }
                    else if(VKCode == 'A')
                    {
                        Win32ProcessKeyboardMessage(&InputState->Keys[7], IsDown);
                    }
                    else if(VKCode == 'S')
                    {
                        Win32ProcessKeyboardMessage(&InputState->Keys[8], IsDown);
                    }
                    else if(VKCode == 'D')
                    {
                        Win32ProcessKeyboardMessage(&InputState->Keys[9], IsDown);
                    }
                    else if(VKCode == 'Z')
                    {
                        Win32ProcessKeyboardMessage(&InputState->Keys[0xA], IsDown);
                    }
                    else if(VKCode == 'C')
                    {
                        Win32ProcessKeyboardMessage(&InputState->Keys[0xB], IsDown);
                    }
                    else if(VKCode == '4')
                    {
                        Win32ProcessKeyboardMessage(&InputState->Keys[0xC], IsDown);
                    }
                    else if(VKCode == 'R')
                    {
                        Win32ProcessKeyboardMessage(&InputState->Keys[0xD], IsDown);
                    }
                    else if(VKCode == 'F')
                    {
                        Win32ProcessKeyboardMessage(&InputState->Keys[0xE], IsDown);
                    }
                    else if(VKCode == 'V')
                    {
                        Win32ProcessKeyboardMessage(&InputState->Keys[0xF], IsDown);
                    }
                    
                    if(IsDown)
                    {
                        bool AltKeyWasDown = (Message.lParam & (1 << 29));
                        if((VKCode == VK_F4) && AltKeyWasDown)
                        {
                            GlobalRunning = false;
                        }
                    }
                }

            } break;

            default:
            {
                TranslateMessage(&Message);
                DispatchMessageA(&Message);
            } break;
        }
    }
}


internal LRESULT CALLBACK
Win32MainWindowCallback(HWND Window,
                        UINT Message,
                        WPARAM WParam,
                        LPARAM LParam)
{       
    LRESULT Result = 0;

    switch(Message)
    {
        case WM_CLOSE:
        {
            GlobalRunning = false;
        } break;

        case WM_ACTIVATEAPP:
        {
        } break;

        case WM_DESTROY:
        {
            GlobalRunning = false;
        } break;

        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
        case WM_KEYDOWN:
        case WM_KEYUP:
        {            
            Assert(!"Keyboard input came in through a non-dispatch message!");
        } break;
        
        case WM_PAINT:
        {
            PAINTSTRUCT Paint;
            HDC DeviceContext = BeginPaint(Window, &Paint);
            win32_window_dimension Dimension = Win32GetWindowDimension(Window);
            Win32DisplayBufferInWindow(&GlobalBackbuffer, DeviceContext,
                                       Dimension.Width, Dimension.Height);
            EndPaint(Window, &Paint);
        } break;

        default:
        {
            Result = DefWindowProcA(Window, Message, WParam, LParam);
        } break;
    }
    
    return(Result);
}

internal char* 
GetRomName(char* CommandLine)
{
    while (char* Quote = strstr(CommandLine, "\""))
    {
        for (int i=(int)(Quote - CommandLine); i<strlen(CommandLine); i++)
        {
            CommandLine[i] = CommandLine[i+1];
        }
    }

    return CommandLine;
}


int CALLBACK
WinMain(HINSTANCE Instance,
        HINSTANCE PrevInstance,
        LPSTR CommandLine,
        int ShowCode)
{    

    int Width = 64 * GlobalDisplayScalar;
    int Height = 32 * GlobalDisplayScalar;

    WNDCLASSA WindowClass = {};
    
    WindowClass.style = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
    WindowClass.lpfnWndProc = Win32MainWindowCallback;
    WindowClass.hInstance = Instance;
    WindowClass.lpszClassName = "Chip8 Emulator";
    
    if(RegisterClassA(&WindowClass))
    {
        HWND Window =
            CreateWindowExA(
                0,
                WindowClass.lpszClassName,
                "Chip8 Emulator",
                WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                Width,
                Height,
                0,
                0,
                Instance,
                0);
        if(Window)
        {
            HDC DeviceContext = GetDC(Window);

            Chip chip = {0};
            InitChip(&chip);
            Win32ResizeDIBSection(&GlobalBackbuffer, Width, Height);

            // Resize the window to fit the client area
            RECT ClientRect, WindowRect;
            POINT SizeDiff;
            GetClientRect(Window, &ClientRect);
            GetWindowRect(Window, &WindowRect);
            SizeDiff.x = (WindowRect.right - WindowRect.left) - ClientRect.right;
            SizeDiff.y = (WindowRect.bottom - WindowRect.top) - ClientRect.bottom;
            MoveWindow(Window, WindowRect.left, WindowRect.top, Width + SizeDiff.x + 20, Height + SizeDiff.y + 20, TRUE);

            LoadRom(&chip, GetRomName(CommandLine));
            chip.PC = 0x200;

            Input input = {0};

            GlobalRunning = true;
            
            while(GlobalRunning)
            {
                // TODO: limit this to 60 HZ? or account for
                // the delay timer decrementing at 60 hz some 
                // other way

                MSG Message;

                // Input
                Win32ProcessPendingMessages(&input);
                
                // Update
                Run(&chip, &input);

                // Render
                RenderBackbuffer(&chip, &GlobalBackbuffer);
                win32_window_dimension Dimension = Win32GetWindowDimension(Window);
                Win32DisplayBufferInWindow(&GlobalBackbuffer, DeviceContext, Dimension.Width, Dimension.Height);

                //Sleep(16.667);
            }
        }
        else
        {
            // TODO(scott): Logging
        }
    }
    else
    {
        // TODO(scott): Logging
    }
    
    return(0);
}
