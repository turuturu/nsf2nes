#include "kikakubu.h"

#define DMA (char*)0x0700

void DrawString(char x, char y,char *str,char len)
{
  char pos[2];
  GetBackgroundAddress(0, x, y, pos);
  VBlank();
  SetBackground(*(pos + 0), *(pos + 1), str, len);
  SetScroll( 0, 0 );
}

void ClearScreen()
{
  unsigned char i,first,pos[2];
  first = 1;
  for (i = 0; i < 64; i++)
  {
    SetDMA( DMA,first, 0, 240, 0, 0);
    first = 0;
  }
  for (i = 0; i < 30; i++)
  {
    GetBackgroundAddress(0, 0, i, pos);
    VBlank();
    FillBackground(*(pos + 0),*(pos + 1),0,32);
    SetScroll( 0, 0 );
  }
}

void ShowScreen(char ShowFlag)
{
	if (ShowFlag == 1) {
		*(char*)0x2000 = 0x88;
		*(char*)0x2001 = 0x1e;
	} else {
		*(char*)0x2000 = 0x00;
		*(char*)0x2001 = 0x00;
	}
}
void Render()
{
  DrawString( 11, 14,"HELLO WORLD", 11);
  DrawString( 7, 17,"POWERED BY TURUTURU", 19);
}

//NMI割り込み
void NMIProc(void){
}
// メイン処理
void NesMain(){
  const char palettebg[] = {
      0x1f, 0x21, 0x30, 0x30, //kuro ao usuao shiro
      0x1f, 0x21, 0x30, 0x30, //kuro ao usuao shiro
      0x1f, 0x21, 0x30, 0x30, //kuro ao usuao shiro
      0x1f, 0x21, 0x30, 0x30 //kuro ao usuao shiro
  };
  const char palettesp[] = {
      0x0f, 0x09, 0x19, 0x30, //kuro midori usumidori shiro
      0x0f, 0x0f, 0x10, 0x21,//kuro kuro haiiro mizuiro
      0x0f, 0x09, 0x19, 0x21,
      0x0f, 0x15, 0x27, 0x30 //kuro aka orennge shiro
  };

	ShowScreen(0);
  SetPalette((char *)palettebg,0);
  SetPalette((char *)palettesp,1);
	//ClearScreen();

  Render();
	ShowScreen(1);
  while (1) {
    //CheckPad();
  }
}
