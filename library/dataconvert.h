#ifndef __DATACONVERT_H_
#define __DATACONVERT_H_
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	void zy_hex2string(char* dst, unsigned char* src, int len);
	void zy_string2hex(unsigned char* pdst, char* src, int len);

#ifdef __cplusplus 
}
#endif //__cplusplus 
#endif // !__DATACONVERT_H_
