#include <ControlWord.h>


ControlWord::ControlWord()
{
    controlWordMap = new QMap<QString, QString>(
    {
        { "CP", "0" },    //Increment PC
        { "EP", "0" },    //Enable PC
        { "LP_", "1" },   //Load PC

        { "LI_", "1"},    //Load IR

        { "EIP1", "0" },  //Enable Input Port 1
        { "EIP2", "0" },  //Enable Input Port 2

        { "LA_", "1" },   //Load Accumulator
        { "EA", "0" },    //Enable Accumulator
        { "LT_", "1" },   //Load Temp
        { "ET", "0" },    //Enable Temp
        { "LB_", "1" },   //Load B
        { "EB", "0"},     //Enable B
        { "LC_", "1" },   //Load C
        { "EC", "0" },    //Enable C
        { "LF", "0"},     //Load flag
        { "EU", "0" },    //Enable ALU
        { "ALU", "00000" },   //ALU Control flags
        { "JC", "000" },    //Jump Control flags

        { "LM_", "1" },   //Load RAM (MAR)
        { "EM_", "1" },   //Enable RAM
        { "LR_", "1" },   //Load RAM from MDR
        { "LMDR_", "1" }, //Load Memory Data Register
        { "EMDR", "0" },  //Enable Memory Data Register

        { "LO3_", "1" },  //Load Output port 3
        { "LO4_", "1" },  //Load Output port 4

        { "UB", "0" },    //take bus upper byte if on or output to bus upper byte
        { "CLR", "0" },   //Clear bus value when outputting to bus
        { "RTNA", "0" }   //Return Address => Marks whether to make MAR point to 0xFFFE or 0xFFFF for pc contents in memory
    });
}
