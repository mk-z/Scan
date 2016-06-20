
#ifndef _DLL_AACENC_H_
#define _DLL_AACENC_H_


#if defined(_WIN32) && !defined(__MINGW32__)
# ifndef AACENCAPI
#  define AACENCAPI __stdcall
# endif
#else
# ifndef AACENCAPI
#  define AACENCAPI
# endif
#endif

//初始化
void	AACENCAPI	AAC_Enc_Init();

/*
	打开编码通道，返回编码句柄
	参数：
		nSampleRate：	采样率
		nChannels：		音频通道数
		nBitrate：		编码码率
		nBufSize：		编码器内部缓冲大小
	返回：0：失败	其他：成功
*/
void*	AACENCAPI	AAC_Enc_Open(unsigned long nSampleRate, unsigned int nChannels,int nBitrate,int nBufSize);

/*
	编码
	参数：
		handle：		通道句柄
		pSrc：			PCM数据指针
		nSrcLen：		PCM数据大小
		pDst：			输出数据地址
		nDstLen：		编码后数据大小
	返回：<0：失败		1：成功
		
*/
int		AACENCAPI	AAC_Enc_Encode(void* handle,unsigned char* pSrc,unsigned int nSrcLen,
								   unsigned char* pDst,unsigned int* nDstLen);

/*
	关闭编码通道：
	参数：
		handle：		编码通道句柄
	返回：-1：参数错误		1：成功
		
*/
int		AACENCAPI	AAC_Enc_Close(void* handle);

//反初始化
void	AACENCAPI	AAC_Enc_DeInit();




#endif /* _DLL_AACENC_H_ */
