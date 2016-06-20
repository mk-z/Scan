/*************************************************************************
 ** 版权保留(C), 2001-2013, 浙江大华技术股份有限公司.
 ** 版权所有.
 **
 ** $Id$
 **
 ** 功能描述   :   PTCP可靠传输对外接口类定义
 **
 ** 修改历史     : 2013年11月13日 fu_yanlong Create
*************************************************************************/

#ifndef __INCLUDE_DAHUA_TOU_DEFS_H__
#define __INCLUDE_DAHUA_TOU_DEFS_H__

// WIN32 Dynamic Link Library
#ifdef _MSC_VER

#ifdef TOU_DLL_BUILD
#define  TOU_API _declspec(dllexport)
#elif defined TOU_DLL_USE
#define  TOU_API _declspec(dllimport)
#else
#define TOU_API
#endif

#else //_MSC_VER

#define TOU_API

#endif //_MSC_VER



#ifdef  __cplusplus

namespace Dahua{
namespace Tou{

#ifndef DISALLOW_ASSIGN
#define DISALLOW_ASSIGN(TypeName) \
  void operator=(const TypeName&)
#endif

// A macro to disallow the evil copy constructor and operator= functions
// This should be used in the private: declarations for a class
#ifndef DISALLOW_COPY_AND_ASSIGN
#define DISALLOW_COPY_AND_ASSIGN(TypeName)    \
  TypeName(const TypeName&);                    \
  DISALLOW_ASSIGN(TypeName)
#endif

// Alternative, less-accurate legacy name.
#ifndef DISALLOW_EVIL_CONSTRUCTORS
#define DISALLOW_EVIL_CONSTRUCTORS(TypeName) \
  DISALLOW_COPY_AND_ASSIGN(TypeName)
#endif

// A macro to disallow all the implicit constructors, namely the
// default constructor, copy constructor and operator= functions.
//
// This should be used in the private: declarations for a class
// that wants to prevent anyone from instantiating it. This is
// especially useful for classes containing only static methods.
#ifndef DISALLOW_IMPLICIT_CONSTRUCTORS
#define DISALLOW_IMPLICIT_CONSTRUCTORS(TypeName) \
  TypeName();                                    \
  DISALLOW_EVIL_CONSTRUCTORS(TypeName)
#endif

}//Tou
}//Dahua  

#endif //__cplusplus
  
#endif  //__INCLUDE_DAHUA_TOU_DEFS_H__

