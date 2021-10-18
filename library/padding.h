#ifndef __PADDING_H_
#define __PADDING_H_
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


#define		ZY_PADDING_ERR_SUCCESS		0
#define		ZY_PADDING_ERR_FAILED		-1
#define		ZY_PADDING_ERR_PARAMETER	-2

#define		PADDING_ADD		0   //add padding mode
#define		PADDING_REMOVE	1	//remove padding mode

	int zy_padding_iso9797_m1(unsigned char mode, int block_size, unsigned char* input, int inlen, unsigned char* output, int* outlen);
	int zy_padding_iso9797_m2(unsigned char mode, int block_size, unsigned char* input, int inlen, unsigned char* output, int* outlen);

#ifdef __cplusplus 
}
#endif //__cplusplus 
#endif // !__PADDING_H_
