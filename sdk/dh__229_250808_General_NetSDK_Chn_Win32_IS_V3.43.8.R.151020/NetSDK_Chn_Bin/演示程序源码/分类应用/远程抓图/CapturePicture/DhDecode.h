/////////////////////////////////////////////////////////////////////////////
//Function£ºDecode mpeg4 I frame file to .BMP file.
//parameter£º
//desFile----------Destination .bmp file.
//srcFile----------I frame of source mpeg4
//Return:
//  1--------------Succeeded
//  0--------------Failed
_declspec(dllimport) int IFrameToBmp(char *desFile,char *srcFile);

//////////////////////////////////////////////////////////////////////////////
//Decode mpeg4 I frame buffer and then output. The call party to create and release output memory, Its size shall contain the decoded data.
//output --------- Output memory created b call party. Outlen inputs memory length.
//outlen ---------  Byte amount after decoding.
//image ---------- BMP video data before decoding.
//inlen   ----------Video data length.
//////////////////////////////////////////////////////////////////////////////
_declspec(dllimport) int IBufferToMEM(unsigned char *output, int *outLen,unsigned char *image,int inlen);


/////////////////////////////////////////////////////////////////////////////
//Function£ºDecode mpeg4 I frame video and then save as .bmp file.
//desFile --------- The saved file name after decoding.
//image  ---------- I frame video data before decoding.
//len       ---------- I frame video length.
_declspec(dllimport) int IBufferToBmp(char *desFile,unsigned char *image,int len);
