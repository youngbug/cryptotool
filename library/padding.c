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

int zy_padding_iso9797_m3(unsigned char mode, int block_size, unsigned char* input, int inlen, unsigned char* output, int* outlen)
{
	int ret = ZY_PADDING_ERR_SUCCESS;
	int right_padding_len = 0;
	unsigned bit_len = 0;
	if (block_size < 4)
	{
		ret = ZY_PADDING_ERR_PARAMETER;
		goto EXIT;
	}
	if (mode == PADDING_ADD)
	{
		right_padding_len = block_size - inlen % block_size; //计算右侧填充长度
		memcpy(output + block_size, input, inlen);//空出一个分组的位置给左侧填充
		memset(output + block_size + inlen, 0, right_padding_len); //右侧填充0
		memset(output, 0, block_size);
		//这个函数是按字节实现的，支持的分组至少是4字节
		bit_len = inlen * 8;
		output[block_size - 1] = bit_len & 0xFF;
		output[block_size - 2] = (bit_len >> 8) & 0xFF;
		output[block_size - 3] = (bit_len >> 16) & 0xFF;
		output[block_size - 4] = (bit_len >> 24) & 0xFF;
		*outlen = inlen + right_padding_len + block_size;
	}
	else if (mode == PADDING_REMOVE)
	{
		bit_len = input[block_size - 1] | input[block_size - 2] << 8 | input[block_size - 3] << 16 | input[block_size - 4] << 24;
		*outlen = bit_len / 8;
		memcpy(output, input + block_size, *outlen);
	}
EXIT:
	return 0;
}

int zy_padding_iso9797_m4(unsigned char mode, int block_size, unsigned char* input, int inlen, unsigned char* output, int* outlen)
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
		if (padding_len == block_size)
		{
			padding_len = 0;
		}
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
