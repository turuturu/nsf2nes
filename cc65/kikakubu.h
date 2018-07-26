
/////////////////////////////////////////////////////////////////////////////////
// 2010.11.30 ver 0.14
// 企画で使うなり個人で使うなり似るなり焼くなりお好きにどうぞ。
// -----------------------------------------------------------------------------
// なん実企画部
// http://www37.atwiki.jp/kikakubu4/
/////////////////////////////////////////////////////////////////////////////////
#define REGIST_PPU_CTRL1 (char*)0x2000
#define REGIST_PPU_CTRL2 (char*)0x2001
#define REGIST_PPU_STS   (char*)0x2002
#define REGIST_SPR_ADR   (char*)0x2003
#define REGIST_SPR_GRA   (char*)0x2004
#define REGIST_SCROLL    (char*)0x2005
#define REGIST_ADR       (char*)0x2006
#define REGIST_GRA       (char*)0x2007
#define REGIST_DMA       (char*)0x4014
#define JOYPAD           (char*)0x4016
#define JOYPAD2          (char*)0x4017
#define BTN_A            0x80
#define BTN_B            0x40
#define BTN_SELECT       0x20
#define BTN_START        0x10
#define BTN_UP           0x08
#define BTN_DOWN         0x04
#define BTN_LEFT         0x02
#define BTN_RIGHT        0x01
#define GUN_TRIGGER      0x10
#define GUN_HIT          0x08
#define MIC_USE          0x04
 
unsigned char padinfo[2][2];
unsigned char padother;
 
//コントローラ確認
void CheckPad()
{
    unsigned char i,j,ret;
    *JOYPAD = 1;
    *JOYPAD = 0;
    padother= 0;
    for(i=0; i < 2; i++) {
        padinfo[i][1] = padinfo[i][0];
        padinfo[i][0]= 0;
        for(j=0; j < 8; j++) {
            ret = *(JOYPAD + i);
            padinfo[i][0] <<= 1;
            padinfo[i][0] += ((ret & 0x01) | ((ret & 0x02) >> 1));
            padother |= (ret & 0x0F);
        }
    }
}
 
//ボタン押しっぱなし　player:0=1P , 1=2P
char ButtonDown(unsigned char player,unsigned char btn)
{
    if(padinfo[player][0] & btn) {
        return 1;
    } else {
        return 0;
    }
}
 
//ボタン押す
char ButtonPush(unsigned char player,unsigned char btn)
{
    if((padinfo[player][0] & btn) && ! (padinfo[player][1] & btn)) {
        return 1;
    } else {
        return 0;
    }
}
 
//マイク・光線銃など
char ControlOther(unsigned char btn)
{
    if(padother & btn) {
        return 1;
    } else {
        return 0;
    }
}
 
// PPUコントロールレジスタの初期化
void InitPPU()
{
    *REGIST_PPU_CTRL1 = 0x00;
    *REGIST_PPU_CTRL2 = 0x00;
}
 
// PPUコントロールレジスタの設定
void SetPPU(unsigned char flag1,unsigned char flag2)
{
    *REGIST_PPU_CTRL1 = flag1;
    *REGIST_PPU_CTRL2 = flag2;
}
 
// スクロール設定
void SetScroll(unsigned char x, unsigned char y)
{
    *REGIST_SCROLL = x;
    *REGIST_SCROLL = y;
}
 
//背景設定（繰り返し）
void FillBackground(unsigned char address1, unsigned char address2, unsigned char val, unsigned char cnt)
{
    char i;
 
    *REGIST_ADR = address1;
    *REGIST_ADR = address2;
    for (i = 0; i < cnt; i++)
    {
        *REGIST_GRA = val;
    }
}
 
//背景設定
void SetBackground(unsigned char address1, unsigned char address2, unsigned char *bg, unsigned char cnt)
{
    char i;
 
    *REGIST_ADR = address1;
    *REGIST_ADR = address2;
    for (i = 0; i < cnt; i++)
    {
        *REGIST_GRA = *(bg + i);
    }
}
 
//座標から背景のアドレス計算
void GetBackgroundAddress(unsigned char screen, unsigned char x, unsigned char y, char *ret)
{
    unsigned int pos;
 
    switch (screen) {
    case 0:        //左下
        pos = 0x2000;
        break;
    case 1:        //右下
        pos = 0x2800;
        break;
    case 2:        //左上
        pos = 0x2400;
        break;
    case 3:        //右上
        pos = 0x2c00;
        break;
    }
 
    pos += y * 0x20 + x;
    *(ret + 0) = (pos & 0xff00) >> 8;
    *(ret + 1) =  pos & 0x00ff;
}
 
//属性設定（繰り返し）
void FillAttribute(unsigned char address1, unsigned char address2, unsigned char val, unsigned char cnt)
{
    FillBackground(address1,address2,val,cnt);
}
 
//属性設定
void SetAttribute(unsigned char address1, unsigned char address2, unsigned char *atr, unsigned char cnt)
{
    SetBackground(address1,address2,atr,cnt);
}
 
//パレット設定
void SetPalette(unsigned char *palette,unsigned char sprite)
{
    char i;
 
    *REGIST_ADR = 0x3f;
    if (sprite) {
        *REGIST_ADR = 0x10;
    } else {
        *REGIST_ADR = 0x00;
    }
 
    for (i = 0; i < 16; i++)
    {
        *REGIST_GRA = *(palette + i);
    }
}
 
//スプライト設定
void SetSprite(unsigned char first,unsigned char x,unsigned char y,unsigned char index,unsigned char flag)
{
    if (first) {
        *REGIST_SPR_ADR=0x00;
    }
    *REGIST_SPR_GRA=y;
    *REGIST_SPR_GRA=index;
    *REGIST_SPR_GRA=flag;
    *REGIST_SPR_GRA=x;
}
 
//DMA転送領域初期化
void InitDMA(unsigned char *address)
{
    unsigned char i;
    for(i=0; i < 256; i++) {
        *(address + i)=0;
    }
}
 
//DMA転送準備
void SetDMA(unsigned char *address,unsigned char first,unsigned char x,unsigned char y,unsigned char index,unsigned char flag)
{
    static unsigned char cnt;
    if (first) { cnt = 0; }
    *(address + cnt + 0)=y;
    *(address + cnt + 1)=index;
    *(address + cnt + 2)=flag;
    *(address + cnt + 3)=x;
    cnt+=4;
}
 
//DMA転送
void SendDMA(unsigned char address)
{
    *REGIST_DMA = address;
}
 
//VBlank待ち
void VBlank()
{
    while (! (*REGIST_PPU_STS & 0x80) );
}
 
//０爆弾待ち
void ZeroSprite()
{
    while (  (*REGIST_PPU_STS & 0x40) );
    while (! (*REGIST_PPU_STS & 0x40) );
}
 
