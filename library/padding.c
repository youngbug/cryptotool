#include "padding.h"

int zy_padding_iso9797_m1(unsigned char mode, int block_size, unsigned char* input, int inlen, unsigned char* output, int* outlen)
{
	int ret = ZY_PADDING_ERR_SUCCESS;
	int padding_len = 0;
	int i = 0;
	int pos = 0;
	if (block_size < 1)
	{
		ret = ZY_PADDING_ERR_PARAMETER;
		goto EXIT;
	}
	if (mode == PADDING_ADD)
	{
		padding_len = block_size - inlen % block_size;
		memcpy(output, input, inlen);
		memset(output + inlen, 0, padding_len);
		*outlen = inlen + padding_len;
	}
	else if (mode == PADDING_REMOVE)
	{
		pos = inlen;
		for (i = 0; i < block_size; i++)
		{
			if (input[pos - 1] == 0x00)
			{
				pos = --pos;
			}
			else
			{
				break;
			}
		}
		memcpy(output, input, pos);
		*outlen = pos;
	}
	else
	{
		ret = ZY_PADDING_ERR_FAILED;
		goto EXIT;
	}

EXIT:
	return ret;
}

int zy_padding_iso9797_m2(unsigned char mode, int block_size, unsigned char* input, int inlen, unsigned char* output, int* outlen)
{
	int ret = ZY_PADDING_ERR_SUCCESS;
	int padding_len = 0;
	int pos = 0;
	int i = 0;
	if (block_size < 1)
	{
		ret = ZY_PADDING_ERR_PARAMETER;
		goto EXIT;
	}
	if (mode == PADDING_ADD)
	{
		padding_len = block_size - inlen % block_size;
		memcpy(output, input, inlen);
		output[inlen] = 0x80;
		memset(output + inlen + 1, 0, padding_len - 1);
		*outlen = inlen + padding_len;
	}
	else if (mode == PADDING_REMOVE)
	{
		pos = inlen;
		for (i = 0; i < block_size; i++)
		{
			if (input[pos - 1] == 0x00)
			{
				pos = --pos;
			}
			else if (input[pos - 1] == 0x80)
			{
				pos = --pos;
				break;
			}
		}
		memcpy(output, input, pos);
		*outlen = pos;
	}
	else
	{
		ret = ZY_PADDING_ERR_FAILED;
		goto EXIT;
	}
EXIT:
	return 0;
}
