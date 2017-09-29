

struct Chip
{
    u8 Memory[4096];
    u8 V[16];
    u16 I;
    u16 PC;

    u16 FontIndex[16];

    u16 Stack[24];
    u8 StackPointer;

    u8 DelayTimer;
    u8 SoundTimer;

    u8 Keys[16];

    u8* Display;
    u32 DisplayHeight;
    u32 DisplayWidth;
};

internal void
InitChip(Chip* chip)
{
    for (int i=0; i<16; i++)
    {
        chip->FontIndex[i] = i*5;
    }

    // -- 0 --
    chip->Memory[chip->FontIndex[0x0]] = 0xF0;
    chip->Memory[chip->FontIndex[0x0] + 1] = 0x90;
    chip->Memory[chip->FontIndex[0x0] + 2] = 0x90;
    chip->Memory[chip->FontIndex[0x0] + 3] = 0x90;
    chip->Memory[chip->FontIndex[0x0] + 4] = 0xF0;

    // -- 1 -- 
    chip->Memory[chip->FontIndex[0x1]] = 0x20;
    chip->Memory[chip->FontIndex[0x1] + 1] = 0x60;
    chip->Memory[chip->FontIndex[0x1] + 2] = 0x20;
    chip->Memory[chip->FontIndex[0x1] + 3] = 0x20;
    chip->Memory[chip->FontIndex[0x1] + 4] = 0x70;

    // -- 2 -- 
    chip->Memory[chip->FontIndex[0x2]] = 0xF0;
    chip->Memory[chip->FontIndex[0x2] + 1] = 0x10;
    chip->Memory[chip->FontIndex[0x2] + 2] = 0xF0;
    chip->Memory[chip->FontIndex[0x2] + 3] = 0x80;
    chip->Memory[chip->FontIndex[0x2] + 4] = 0xF0;

    // -- 3 -- 
    chip->Memory[chip->FontIndex[0x3]] = 0xF0;
    chip->Memory[chip->FontIndex[0x3] + 1] = 0x10;
    chip->Memory[chip->FontIndex[0x3] + 2] = 0xF0;
    chip->Memory[chip->FontIndex[0x3] + 3] = 0x10;
    chip->Memory[chip->FontIndex[0x3] + 4] = 0xF0;

    // -- 4 -- 
    chip->Memory[chip->FontIndex[0x4]] = 0x90;
    chip->Memory[chip->FontIndex[0x4] + 1] = 0x90;
    chip->Memory[chip->FontIndex[0x4] + 2] = 0xF0;
    chip->Memory[chip->FontIndex[0x4] + 3] = 0x10;
    chip->Memory[chip->FontIndex[0x4] + 4] = 0x10;

    // -- 5 -- 
    chip->Memory[chip->FontIndex[0x5]] = 0xF0;
    chip->Memory[chip->FontIndex[0x5] + 1] = 0x80;
    chip->Memory[chip->FontIndex[0x5] + 2] = 0xF0;
    chip->Memory[chip->FontIndex[0x5] + 3] = 0x10;
    chip->Memory[chip->FontIndex[0x5] + 4] = 0xF0;

    // -- 6 -- 
    chip->Memory[chip->FontIndex[0x6]] = 0xF0;
    chip->Memory[chip->FontIndex[0x6] + 1] = 0x80;
    chip->Memory[chip->FontIndex[0x6] + 2] = 0xF0;
    chip->Memory[chip->FontIndex[0x6] + 3] = 0x90;
    chip->Memory[chip->FontIndex[0x6] + 4] = 0xF0;

    // -- 7 -- 
    chip->Memory[chip->FontIndex[0x7]] = 0xF0;
    chip->Memory[chip->FontIndex[0x7] + 1] = 0x10;
    chip->Memory[chip->FontIndex[0x7] + 2] = 0x20;
    chip->Memory[chip->FontIndex[0x7] + 3] = 0x40;
    chip->Memory[chip->FontIndex[0x7] + 4] = 0x40;

    // -- 8 -- 
    chip->Memory[chip->FontIndex[0x8]] = 0xF0;
    chip->Memory[chip->FontIndex[0x8] + 1] = 0x90;
    chip->Memory[chip->FontIndex[0x8] + 2] = 0xF0;
    chip->Memory[chip->FontIndex[0x8] + 3] = 0x90;
    chip->Memory[chip->FontIndex[0x8] + 4] = 0xF0;

    // -- 9 -- 
    chip->Memory[chip->FontIndex[0x9]] = 0xF0;
    chip->Memory[chip->FontIndex[0x9] + 1] = 0x90;
    chip->Memory[chip->FontIndex[0x9] + 2] = 0xF0;
    chip->Memory[chip->FontIndex[0x9] + 3] = 0x10;
    chip->Memory[chip->FontIndex[0x9] + 4] = 0xF0;

    // -- A -- 
    chip->Memory[chip->FontIndex[0xA]] = 0xF0;
    chip->Memory[chip->FontIndex[0xA] + 1] = 0x90;
    chip->Memory[chip->FontIndex[0xA] + 2] = 0xF0;
    chip->Memory[chip->FontIndex[0xA] + 3] = 0x90;
    chip->Memory[chip->FontIndex[0xA] + 4] = 0x90;

    // -- B -- 
    chip->Memory[chip->FontIndex[0xB]] = 0xE0;
    chip->Memory[chip->FontIndex[0xB] + 1] = 0x90;
    chip->Memory[chip->FontIndex[0xB] + 2] = 0xE0;
    chip->Memory[chip->FontIndex[0xB] + 3] = 0x90;
    chip->Memory[chip->FontIndex[0xB] + 4] = 0xE0;

    // -- C -- 
    chip->Memory[chip->FontIndex[0xC]] = 0xF0;
    chip->Memory[chip->FontIndex[0xC] + 1] = 0x80;
    chip->Memory[chip->FontIndex[0xC] + 2] = 0x80;
    chip->Memory[chip->FontIndex[0xC] + 3] = 0x80;
    chip->Memory[chip->FontIndex[0xC] + 4] = 0xF0;

    // -- D -- 
    chip->Memory[chip->FontIndex[0xD]] = 0xE0;
    chip->Memory[chip->FontIndex[0xD] + 1] = 0x90;
    chip->Memory[chip->FontIndex[0xD] + 2] = 0x90;
    chip->Memory[chip->FontIndex[0xD] + 3] = 0x90;
    chip->Memory[chip->FontIndex[0xD] + 4] = 0xE0;

    // -- E -- 
    chip->Memory[chip->FontIndex[0xE]] = 0xF0;
    chip->Memory[chip->FontIndex[0xE] + 1] = 0x80;
    chip->Memory[chip->FontIndex[0xE] + 2] = 0xF0;
    chip->Memory[chip->FontIndex[0xE] + 3] = 0x80;
    chip->Memory[chip->FontIndex[0xE] + 4] = 0xF0;

    // -- F -- 
    chip->Memory[chip->FontIndex[0xF]] = 0xF0;
    chip->Memory[chip->FontIndex[0xF] + 1] = 0x80;
    chip->Memory[chip->FontIndex[0xF] + 2] = 0xF0;
    chip->Memory[chip->FontIndex[0xF] + 3] = 0x80;
    chip->Memory[chip->FontIndex[0xF] + 4] = 0x80;

    chip->DisplayHeight = 32;
    chip->DisplayWidth = 64;
    chip->Display = (u8*)malloc(chip->DisplayHeight * chip->DisplayWidth);
    memset(chip->Display, 0, chip->DisplayHeight * chip->DisplayWidth);
}

internal void 
Run(Chip* chip, Input* input)
{
    // fetch opcode
    u16 Opcode = (chip->Memory[chip->PC] << 8) | chip->Memory[chip->PC+1];


    // decode opcode
    switch(Opcode & 0xF000)
    {
        case 0x0000: 
        {
            if (Opcode == 0x00E0) // 00E0: Clears the screen.
            {
                memset(chip->Display, 0, chip->DisplayWidth*chip->DisplayHeight);

                chip->PC += 2;

                DPrint("Clearing the screen\n");
            }
            else if (Opcode == 0x00EE) // 00EE: Returns from a subroutine.
            {
                int ReturnAddress = chip->Stack[--chip->StackPointer];

                chip->PC = ReturnAddress;

                DPrint("Returning from subroutine to %04X\n", ReturnAddress);
            }
            else
            {
                char Buffer[16];
                sprintf(Buffer, "%04X: ", Opcode);
                OutputDebugString(Buffer);
                exit(0);
            }
        } break;

        case 0x1000: // 1NNN: Jumps to address NNN.
        {
            int Address = Opcode & 0x0FFF;

            chip->PC = Address;

            DPrint("Jumping to address %04X\n", Address);
        } break;

        case 0x2000: // 2NNN: Calls subroutine at NNN.
        {
            u16 Address = (u16)(Opcode & 0x0FFF);
            chip->Stack[chip->StackPointer++] = chip->PC + 2;
            chip->PC = Address;

            DPrint("Calling subroutine at %04X\n", Address);
        } break;

        // 3XNN :Skips the next instruction if VX equals NN. (Usually the next 
        // instruction is a jump to skip a code block)
        case 0x3000: 
        {
            int X = (Opcode & 0x0F00) >> 8;
            u8 N = (Opcode & 0x00FF);

            if (chip->V[X] == N)
            {
                DPrint("Skipping instruction (VX (%d) == N (%d)\n", chip->V[X], N);
                chip->PC += 4;
            }
            else
            {                
                DPrint("NOT Skipping instruction (VX (%d) != N (%d)\n", chip->V[X], N);
                chip->PC += 2;
            }
        } break;

        case 0x4000: // 4XNN: Skips the next instruction if VX does not equal NN.
        {
            int X = (Opcode & 0x0F00) >> 8;
            u8 N = (Opcode & 0x00FF);

            if (chip->V[X] != N)
            {
                DPrint("Skipping instruction (VX (%d) != N (%d)\n", chip->V[X], N);
                chip->PC += 4;
            }
            else
            {
                DPrint("Skipping instruction (VX (%d) == N (%d)\n", chip->V[X], N);
                chip->PC += 2;
            }
        } break;

        case 0x6000: // 6XNN: Sets VX to NN.
        {
            u8 X = (u8)((Opcode & 0x0F00) >> 8);
            u8 N = (u8)(Opcode & 0x00FF);
            chip->V[X] = N;

            DPrint("Setting VX (%d) to N (%d)\n", X, N);

            chip->PC += 2;
        } break;

        case 0x7000: // 7XNN: Adds NN to VX. (Carry flag is not changed)
        {
            int X = (Opcode & 0x0F00) >> 8;
            u8 N = (u8)(Opcode & 0x00FF);

            DPrint("Adding N (%d) to VX (%d) = %d\n", N, chip->V[X], (u8)(chip->V[X] + N));
            chip->V[X] = (u8)((chip->V[X] + N) & 0x00FF);

            chip->PC += 2;
        } break;

        case 0x8000:
        {
            switch(Opcode & 0x000F)
            {
                case 0x0000: // 8XY0: Store the value of VY in VX
                {
                    int X = (Opcode & 0x0F00) >> 8;
                    int Y = (Opcode & 0x00F0) >> 4;

                    DPrint("Storing V%d (%d) in V%d\n", Y, chip->V[Y], X);
                    chip->V[X] = chip->V[Y];

                    chip->PC += 2;
                } break;

                case 0x0002: // 8XY2: Set VX = VX AND VY
                {
                    int X = (Opcode & 0x0F00) >> 8;
                    int Y = (Opcode & 0x00F0) >> 4;

                    DPrint("Setting VX to VX (%d) AND VY (%d) = %d\n", chip->V[X], chip->V[Y], (u8)(chip->V[X] & chip->V[Y]));
                    chip->V[X] = (u8)(chip->V[X] & chip->V[Y]);

                    chip->PC += 2;
                } break;

                case 0x0003: // 8XY3: Sets VX to VX xor VY.
                {
                    int X = (Opcode & 0x0F00) >> 8;
                    int Y = (Opcode & 0x00F0) >> 4;
                    DPrint("XOR'ing V%d (%d) and V%d (%d) = %d\n", X, chip->V[X], Y, chip->V[Y], (u8)(chip->V[X] ^ chip->V[Y]));

                    chip->V[X] = (u8)(chip->V[X] ^ chip->V[Y]);

                    chip->PC += 2;
                } break;

                case 0x0004: // 8XY4: Set VX = VX + VY, Set VF = carry
                {
                    int X = (Opcode & 0x0F00) >> 8;
                    int Y = (Opcode & 0x00F0) >> 4;

                    DPrint("Setting VX to VX (%d) + VY (%d) = %d, Carry = %d\n", chip->V[X], chip->V[Y], (u8)(chip->V[X] + chip->V[Y]), chip->V[0xF]);
                    
                    if (chip->V[Y] > 0xFF - chip->V[X])
                    {
                        chip->V[0xF] = 1;
                    }
                    else
                    {
                        chip->V[0xF] = 0;
                    }

                    chip->V[X] = (u8)((chip->V[X] + chip->V[Y]) & 0xFF);

                    chip->PC += 2;
                } break;

                case 0x0005: // 8XY5: Set VX to VX - VY, Set VF = NOT borrow                
                {
                    int X = (Opcode & 0x0F00) >> 8;
                    int Y = (Opcode & 0x00F0) >> 4;

                    if (chip->V[X] > chip->V[Y])
                    {
                        chip->V[0xF] = 1;
                    }
                    else
                    {
                        chip->V[0xF] = 0;                        
                    }
                    chip->V[X] = (u8)((chip->V[X] - chip->V[Y]) & 0xFF);    
                    
                    DPrint("Setting V%d to V%d (%d) - V%d (%d) = %d, Borrow = %d\n", X, X, chip->V[X], Y, chip->V[Y], (u8)(chip->V[X] - chip->V[Y]), chip->V[0xF]);

                    chip->PC += 2;
                } break;

                // 8XY6: Set VF if the LSB of VX is 1, Set VX = (VX >> 1)
                // Other possible interpretation: Shifts VY right by one and 
                // copies the result to VX. VF is set to the value of the least 
                // significant bit of VY before the shift.
                case 0x0006: 
                {
                    int X = (Opcode & 0x0F00) >> 8;
                    u8 Value = chip->V[X];

                    if (Value & 0x01)
                    {
                        chip->V[0xF] = 1;
                    }

                    chip->V[X] = (u8)(Value >> 1);

                    chip->PC += 2;
                } break;

                default:
                    
                    char Buffer[16];
                    sprintf(Buffer, "Unimplemented Opcode: %04X!\n", Opcode);
                    OutputDebugString(Buffer);
                    exit(0);
            }

        } break;

        case 0xA000: // ANNN: Sets I to the address NNN.
        {
            u16 Address = Opcode & 0x0FFF;
            chip->I = Address;

            DPrint("Set I to address %04X\n", Address);
            chip->PC += 2;
        } break;

        // CXNN: Sets VX to the result of a bitwise and operation on a random 
        // number (Typically: 0 to 255) and NN.
        case 0XC000: 
        {
            int X = (Opcode & 0x0F00) >> 8;
            u8 N = (u8)(Opcode & 0x00FF);
            u8 Random = (u8)(rand() % 256);
            chip->V[X] = Random & N;

            DPrint("Set VX (%d) to (%d AND %d) = %d\n", X, Random, N, Random & N);

            chip->PC += 2;
        } break;
        

        // DXYN: Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels 
        // and a height of N pixels. Each row of 8 pixels is read as bit-coded starting 
        // from memory location I; I value doesn’t change after the execution of this instruction. 
        // As described above, VF is set to 1 if any screen pixels are flipped from set to unset 
        // when the sprite is drawn, and to 0 if that doesn’t happen
        case 0xD000: 
        {
            int X = chip->V[(Opcode & 0x0F00) >> 8];
            int Y = chip->V[(Opcode & 0x00F0) >> 4];
            int Height = (Opcode & 0x000F);

            chip->V[0xF] = 0;

            for (int y=0; y<Height; y++)
            {
                int line = chip->Memory[chip->I + y];
                for (int x=0; x<8; x++)
                {
                    int pixel = line & (0x80 >> x);
                    if (pixel != 0)
                    {
                        int totalX = X + x;
                        int totalY = Y + y;
                        int index = totalY * chip->DisplayWidth + totalX;

                        if (chip->Display[index])
                        {
                            chip->V[0xF] = 1;
                        }

                        chip->Display[index] ^= 1;
                    }
                }
            }

            chip->PC += 2;
        } break;

        case 0xE000:
        {
            switch (Opcode & 0x00FF)
            {
                case 0x009E: // EX9E: Skip the next instruction if the key VX is pressed
                {
                    int X = (Opcode & 0x0F00) >> 8;
                    int key = chip->V[X];
                    if (input->Keys[key])
                    {
                        chip->PC += 4;
                    }
                    else
                    {
                        chip->PC += 2;
                    }
                } break;

                // EXA1: Skips the next instruction if the key stored in VX 
                // isn't pressed. (Usually the next instruction is a jump to 
                // skip a code block)
                case 0x00A1: 
                {
                    int key = chip->V[(Opcode & 0x0F00) >> 8];
                    if (!input->Keys[key])                    
                    {
                        DPrint("Skipping next instruction (Key %d not pressed)\n", key);
                        chip->PC += 4;
                    }
                    else
                    {
                        DPrint("Not skipping next instruction (Key %d pressed)\n", key);
                        chip->PC += 2;
                    }
                } break;

                default:                
                    char Buffer[16];
                    sprintf(Buffer, "Unhandled Opcode: %04X\n", Opcode);
                    OutputDebugString(Buffer);
                    exit(0);        
            }
        } break;

        case 0xF000:
        {
            switch(Opcode & 0x00FF)
            {
                case 0x0007: // FX07: Sets VX to the value of the delay timer
                {
                    int X = (Opcode & 0x0F00) >> 8;
                    chip->V[X] = chip->DelayTimer;

                    chip->PC += 2;

                    DPrint("Setting VX (%d) to value of delay timer (%d)\n", X, chip->DelayTimer);
                } break;


                // FX0A: A key press is awaited, and then stored in VX. 
                // (Blocking Operation. All instruction halted until next key event)
                case 0x000A: 
                {
                    int X = (Opcode & 0x0F00) >> 8;

                    bool Pressed = false;
                    for (int i=0; i<16; i++)
                    {
                        if (input->Keys[i])
                        {
                            chip->V[X] = i;
                            Pressed = true;
                            break;
                        }
                    }

                    if (Pressed)
                    {
                        chip->PC += 2;
                    }
                } break;

                case 0x0015: // FX15: Sets the delay timer to VX
                {
                    int X = (Opcode & 0x0F00) >> 8;
                    chip->DelayTimer = chip->V[X];

                    DPrint("Setting the delay timer to VX (%d)\n", chip->V[X]);

                    chip->PC += 2;
                } break;

                case 0x0018: // FX18: Set sound timer to VX
                {
                    int X = (Opcode & 0x0F00) >> 8;
                    DPrint("Setting sound timer to V%d (%d)\n", X, chip->V[X]);
                    chip->SoundTimer = chip->V[X];

                    chip->PC += 2;
                } break;


                case 0x001E: // FX1E: Set I to I + VX
                {
                    int X = (Opcode & 0x0F00) >> 8;
                    chip->I += chip->V[X];

                    DPrint("Incrementing I by %d\n", chip->V[X]);

                    chip->PC += 2;
                } break;

                // FX29: Sets I to the location of the sprite for the character
                // in VX. Characters 0-F (in hexadecimal) are represented by a 
                // 4x5 font.
                case 0x0029:
                {
                    int X = (Opcode & 0x0F00) >> 8;
                    chip->I = chip->FontIndex[chip->V[X]];

                    DPrint("Setting I to location of sprite char VX (%d) (%04X)\n", chip->V[X], chip->I);

                    chip->PC += 2;
                } break;

                // FX33: Stores the binary-coded decimal representation of VX, 
                // with the most significant of three digits at the address in 
                // I, the middle digit at I plus 1, and the least significant 
                // digit at I plus 2. (In other words, take the decimal 
                // representation of VX, place the hundreds digit in memory at 
                // location in I, the tens digit at location I+1, and the ones 
                // digit at location I+2.)
                case 0x0033: 
                {
                    int X = (Opcode & 0x0F00) >> 8;
                    int Value = chip->V[X];
                    int Hunnies = Value / 100;
                    Value -= Hunnies * 100;
                    int Tens = Value / 10;
                    Value -= Tens * 10;
                    chip->Memory[chip->I] = Hunnies;
                    chip->Memory[chip->I + 1] = Tens;
                    chip->Memory[chip->I + 2] = Value;

                    DPrint("Storing BCD of %d (%04X=%d, %04X=%d, %04X=%d)\n", Value, chip->I, Value/100, chip->I+1, (Value%100)/10, chip->I+2, (Value%10));

                    chip->PC += 2;
                } break;

                // FX65: Fills V0 to VX (including VX) with values from  memory 
                // starting at address I. I is increased by 1 for each value 
                // written.
                case 0x0065:
                {
                    int X = (Opcode & 0x0F00) >> 8;
                    for (int i=0; i<=X; i++)
                    {
                        chip->V[i] = chip->Memory[chip->I + i];
                    }
                    DPrint("Filling memory from V0 to V%d with values starting at %04X\n", X, chip->I);

                    chip->PC += 2;
                } break;

                default:
                {
                    char Buffer[16];
                    sprintf(Buffer, "Unhandled Opcode: %04X\n", Opcode);
                    OutputDebugString(Buffer);
                    exit(0);            
                }
            }
        } break;

        default:
        {
            char Buffer[16];
            sprintf(Buffer, "Unhandled Opcode: %04X\n", Opcode);
            OutputDebugString(Buffer);
            exit(0);
        }
    }

    // Decrement the delay timer
    if (chip->DelayTimer)
    {
        chip->DelayTimer--;
    }

    // Decrement the sound timer
    if (chip->SoundTimer)
    {
        chip->SoundTimer--;
        printf("\b");
    }
}

internal void
LoadRom(Chip* chip, char* RomName)
{
    ReadFileResult FileResult = ReadEntireFile(RomName);

    if (FileResult.Success)
    {
        memcpy(chip->Memory + 0x200, FileResult.Contents, FileResult.Size);
    }    
    else
    {
        OutputDebugString("Failed to open supplied ROM!\n");
        exit(0);
    }
}