#include "dataconvert.h"

void zy_hex2string(char* dst, unsigned char* src, int len)
{
	char  table[] = { "0123456789ABCDEF" };
	unsigned char  tmb;
	int   ind;
	int   i, j;
	//====================
	for (i = 0, j = 0; i < len; i++)
	{
		tmb = src[i];
		ind = (tmb >> 4) & 0x0F;
		dst[j] = table[ind];
		j++;
		//
		ind = tmb & 0x0F;
		dst[j] = table[ind];
		j++;
	}
}

void zy_string2hex(unsigned char* pdst, char* src, int len)
{
	int  i, j;
	unsigned char table[] = { 0X00,0X01,0X02,0X03,0X04,0X05,0X06,0X07,0X08,0X09,0X0A,0X0B,0X0C,0X0D,0X0E,0X0F,
		0X00,0X0A,0X0B,0X0C,0X0D,0X0E,0X0F };
	unsigned char tmb, tmc;
	char* buf = malloc(len);
	//
	if (len > 1024) return;
	//
	memset(buf, 0, len);
	memcpy(buf, src, len);
	//×ªÎª´óÐ´
	for (i = 0; i < len; i++)
	{
		if (buf[i] >= 0x61)	buf[i] -= 0x20;
	}
	//
	for (i = 0, j = 0; i < len; i += 2, j++)
	{
		tmb = buf[i] - 0x30;
		//
		if (tmb <= 0x16)
		{
			tmc = table[tmb];
		}
		else
		{
			tmc = 0x00;  //0xFF
		}
		//
		tmc <<= 4;
		//
		if (i + 1 != len)
		{
			//
			tmb = buf[i + 1] - 0x30;
			if (tmb <= 0x16)
			{
				tmb = table[tmb];
			}
			else
			{
				tmb = 0x00;  //0x0F
			}
			//
			tmc += tmb;
		}
		else
		{
			tmc += 0x00;  //0x0F
		}
		//
		pdst[j] = tmc;
		//
	}
}
