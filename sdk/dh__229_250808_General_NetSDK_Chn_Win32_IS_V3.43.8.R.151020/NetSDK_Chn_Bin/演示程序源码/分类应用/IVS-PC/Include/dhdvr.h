
#ifndef DHDVREXPORT_H
#define DHDVREXPORT_H


#if ((defined(WIN32) || defined(WIN64)) && !(defined(SDK_STATIC)))

#ifdef DHDVR_EXPORTS
#define DHDVR_API __declspec(dllexport)
#else	//#ifdef DHDVR_EXPORTS
#define DHDVR_API __declspec(dllimport)
#endif

#else

#define DHDVR_API

#endif


#include "./kernel/afkplugin.h"

extern "C" DHDVR_API afk_plugin_info_t plugin_info;

#endif /* DHDVREXPORT_H */

