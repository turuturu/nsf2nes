#include "kikakubu.h"

#define DMA (char*)0x0700

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
void DrawString(char x, char y,char *str,char len)
{
  char pos[2];
  GetBackgroundAddress(0, x, y, pos);
  //VBlank();
  SetBackground(*(pos + 0), *(pos + 1), str, len);
  SetScroll( 0, 0 );
}

void RenderGarigari()
{
int cur;
  char i;
  char j;
  char pos[2];
unsigned char garigari_moji_nam[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,
  0x0e, 0x0f, 0x00, 0x00,
  0x00, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a,
  0x1b, 0x1c, 0x00, 0x00,
  0x00, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
  0x28, 0x29, 0x2a, 0x00,
  0x00, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35,
  0x36, 0x37, 0x38, 0x00,
  0x00, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x40, 0x41, 0x42, 0x43,
  0x44, 0x45, 0x46, 0x47,
  0x00, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x00, 0x4f, 0x50, 0x51,
  0x52, 0x53, 0x54, 0x55,
  0x00, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f, 0x60,
  0x61, 0x62, 0x63, 0x64,
  0x00, 0x65, 0x00, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e,
  0x6f, 0x70, 0x71, 0x72
};
  cur = 0;
  GetBackgroundAddress(0, 0, 0, pos);
  for(i=0;i<9;i++){
    for(j=0;j<16;j++){
      GetBackgroundAddress(0, j+8, i+8, pos);
      FillBackground(*(pos + 0),*(pos + 1), 0x80 + garigari_moji_nam[cur++],1);
    }
  }
  DrawString( 10, 19,"GARI GARI KUN", 13);
  DrawString( 8, 22,"POWERED BY NEFROCK", 18);
  //VBlank();
  //SetScroll( 0, 0 );
}



int tmpint;
void Render()
{

int cur;
  char i;
  char j;
  char pos[2];
  cur = 0;
  FillBackground(0x20, 0x00, 0x03, 32);
  FillBackground(0x20, 0x20, 0x01, 96);
  FillBackground(0x20, 0x80, 0x01, 128);
  FillBackground(0x21, 0x00, 0x03, 128);
  FillBackground(0x21, 0x80, 0x03, 128);
  FillBackground(0x22, 0x00, 0x03, 64);
  FillBackground(0x22, 0x40, 0x01, 64);
  FillBackground(0x22, 0x80, 0x01, 128);
  FillBackground(0x23, 0x00, 0x01, 32);
  FillBackground(0x23, 0x20, 0x03, 96);
  FillBackground(0x23, 0x80, 0x03, 128);

  FillBackground(0x28, 0x00, 0x03, 32);
  FillBackground(0x28, 0x20, 0x01, 96);
  FillBackground(0x28, 0x80, 0x01, 128);
  FillBackground(0x29, 0x00, 0x03, 128);
  FillBackground(0x29, 0x80, 0x03, 128);
  FillBackground(0x2a, 0x00, 0x03, 64);
  FillBackground(0x2a, 0x40, 0x01, 64);
  FillBackground(0x2a, 0x80, 0x01, 128);
  FillBackground(0x2b, 0x00, 0x01, 32);
  FillBackground(0x2b, 0x20, 0x03, 96);
  FillBackground(0x2b, 0x80, 0x03, 128);
}

void RenderGarigari2()
{
int cur;
  char i;
  char j;
  char pos[2];
unsigned char garigari_moji_nam[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03,
  0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,
  0x0e, 0x0f, 0x00, 0x00,
  0x00, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a,
  0x1b, 0x1c, 0x00, 0x00,
  0x00, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
  0x28, 0x29, 0x2a, 0x00,
  0x00, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35,
  0x36, 0x37, 0x38, 0x00,
  0x00, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x40, 0x41, 0x42, 0x43,
  0x44, 0x45, 0x46, 0x47,
  0x00, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x00, 0x4f, 0x50, 0x51,
  0x52, 0x53, 0x54, 0x55,
  0x00, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f, 0x60,
  0x61, 0x62, 0x63, 0x64,
  0x00, 0x65, 0x00, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e,
  0x6f, 0x70, 0x71, 0x72
};
  cur = 0;
  GetBackgroundAddress(0, 0, 0, pos);
  for(i=0;i<9;i++){
    for(j=0;j<16;j++){
      GetBackgroundAddress(0, j+8, i+8, pos);
      FillBackground(*(pos + 0),*(pos + 1), 0x80 + garigari_moji_nam[cur++],1);
    }
  }
  DrawString( 10, 19,"GARI GARI KUN", 13);
  DrawString( 8, 22,"POWERED BY NEFROCK", 18);
  //VBlank();
  //SetScroll( 0, 0 );

}




//unsigned char songnum;
int songnum;
// メイン処理
void NesReset(){
}

void NesMain()
{

  unsigned char x=0;
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

  songnum = 0x00;
  tmpint = 0;
  //*(char*)0x8000 = 0;

	ShowScreen(0);
  SetPalette((char *)palettebg,0);
  SetPalette((char *)palettesp,1);
  //ClearScreen();
  Render();
  RenderGarigari();
	ShowScreen(1);
  while (1) {

  }
}
//NMI割り込み
void NMIProc(void){

    CheckPad();
    if ( ButtonDown(0, BTN_A) ) {
	    ShowScreen(0);
      VBlank();
      //*(char*)0x8000 = 0;
      //sprintf("%X", songnum);
        //songnum++;
        //__asm__ ("lda %v", songnum);
        //__asm__ ("lda %s", songnum);
        //__asm__ ("jsr #%l", 0x8800);
		//*(char*)0x4015= 0x0f;
	//ShowScreen(0);
       //__asm__ ("lda 0xff");
       //__asm__ ("sta sp");
       //__asm__ ("lda #%b", 2);
       //__asm__ ("lda 3");
       //
        //songnum+=1;
		    //*(char*)0x200 = songnum;
       // __asm__ ("lda $200");
       __asm__ ("lda #$2");
       __asm__ ("sta $200");
       __asm__ ("jmp $E00A");
    }else if ( ButtonDown(0, BTN_B) ) {
	    ShowScreen(0);
      VBlank();
       __asm__ ("lda #$1");
       __asm__ ("sta $200");
       __asm__ ("jmp $E00A");
    }
}
