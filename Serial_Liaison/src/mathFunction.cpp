#include "mathFunction.h"
#include <unordered_map>

std::unordered_map<uint8_t, char> asciiTable;

int checkValue09(int ascii)
{
  int valeur_num = -1;
  switch (ascii)
  {
    case 48 :
      valeur_num = 0;
    break;

    case 49 :
      valeur_num = 1;
    break;

    case 50 :
      valeur_num = 2;
    break;

    case 51 :
      valeur_num = 3;
    break;

    case 52 :
      valeur_num = 4;
    break;

    case 53 :
      valeur_num = 5;
    break;

    case 54 :
      valeur_num = 6;
    break;

    case 55 :
      valeur_num = 7;
    break;

    case 56 :
      valeur_num = 8;
    break;

    case 57 :
      valeur_num = 9;
    break;
  }
  return valeur_num;
}

int convert09ToAscii(int number)
{
  return number + 48;
}
char convertCharToAscii(int c)
{
  return asciiTable.at(c);
}

void initAsciiTable()
{
    asciiTable[0] = '\0';
    asciiTable[7] = '\a';
    asciiTable[8] = '\b';
    asciiTable[9] = '\t';
    asciiTable[10] = '\n';
    asciiTable[11] = '\v';
    asciiTable[12] = '\f';
    asciiTable[13] = '\r';
    asciiTable[27] = '\e';
    asciiTable[32] = ' ';
    asciiTable[33] = '!';
    asciiTable[34] = '"';
    asciiTable[35] = '#';
    asciiTable[36] = '$';
    asciiTable[37] = '%';
    asciiTable[38] = '&';
    asciiTable[39] = '\'';
    asciiTable[40] = '(';
    asciiTable[41] = ')';
    asciiTable[42] = '*';
    asciiTable[43] = '+';
    asciiTable[44] = ',';
    asciiTable[45] = '-';
    asciiTable[46] = '.';
    asciiTable[47] = '/';
    asciiTable[48] = '0';
    asciiTable[49] = '1';
    asciiTable[50] = '2';
    asciiTable[51] = '3';
    asciiTable[52] = '4';
    asciiTable[53] = '5'; 
    asciiTable[54] = '6';
    asciiTable[55] = '7';
    asciiTable[56] = '8';
    asciiTable[57] = '9';
    asciiTable[58] = ':';
    asciiTable[59] = ';';
    asciiTable[60] = '<';
    asciiTable[61] = '=';
    asciiTable[62] = '>';
    asciiTable[63] = '?';
    asciiTable[64] = '@';
    asciiTable[65] = 'A';
    asciiTable[66] = 'B';
    asciiTable[67] = 'C';
    asciiTable[68] = 'D';
    asciiTable[69] = 'E';
    asciiTable[70] = 'F';
    asciiTable[71] = 'G';
    asciiTable[72] = 'H';
    asciiTable[73] = 'I';
    asciiTable[74] = 'J';
    asciiTable[75] = 'K';
    asciiTable[76] = 'L';
    asciiTable[77] = 'M';
    asciiTable[78] = 'N';
    asciiTable[79] = 'O';
    asciiTable[80] = 'P';
    asciiTable[81] = 'Q';
    asciiTable[82] = 'R';
    asciiTable[83] = 'S';
    asciiTable[84] = 'T';
    asciiTable[85] = 'U';
    asciiTable[86] = 'V';
    asciiTable[87] = 'W';
    asciiTable[88] = 'X';
    asciiTable[89] = 'Y';
    asciiTable[90] = 'Z';
    asciiTable[91] = '[';
    asciiTable[92] = '\\';
    asciiTable[93] = ']';
    asciiTable[94] = '^';
    asciiTable[95] = '_';
    asciiTable[96] = '`';
    asciiTable[97] = 'a';
    asciiTable[98] = 'b';
    asciiTable[99] = 'c';
    asciiTable[100] = 'd';
    asciiTable[101] = 'e';
    asciiTable[102] = 'f';
    asciiTable[103] = 'g';
    asciiTable[104] = 'h';
    asciiTable[105] = 'i';
    asciiTable[106] = 'j';
    asciiTable[107] = 'k';
    asciiTable[108] = 'l';
    asciiTable[109] = 'm';
    asciiTable[110] = 'n';
    asciiTable[111] = 'o';
    asciiTable[112] = 'p';
    asciiTable[113] = 'q';
    asciiTable[114] = 'r';
    asciiTable[115] = 's';
    asciiTable[116] = 't';
    asciiTable[117] = 'u';
    asciiTable[118] = 'v';
    asciiTable[119] = 'w';
    asciiTable[120] = 'x';
    asciiTable[121] = 'y';
    asciiTable[122] = 'z';
    asciiTable[123] = '{';
    asciiTable[124] = '|';
    asciiTable[125] = '}';
    asciiTable[126] = '~';

}