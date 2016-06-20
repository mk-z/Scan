
#include "StdAfx.h"
#include "ReadWriteMutex.h"

#ifdef OS_LINUX
#include <pthread.h>
#endif

NAMESPACE_BEGIN(Tools)

#ifdef OS_WIN32
Mutex::Mutex() { InitializeCriticalSection(&m_CritSec); }
Mutex::~Mutex() { DeleteCriticalSection( &m_CritSec ); }

void Mutex::Lock(bool bReEnter) 
{ 
	EnterCriticalSection(&m_CritSec); 
	if(bReEnter == false)
	{
		m_CritSec.OwningThread = NULL;
	}
}

bool Mutex::TryLock(int timeout) { 
	Lock();  return true; 
//	return TryEnterCriticalSection(*m_CritSec);
}

void Mutex::Unlock() {LeaveCriticalSection(&m_CritSec);}
#endif

#ifdef OS_LINUX
Mutex::Mutex() {
//	pthread_mutexattr_t attr;
//	attr.__mutexkind = PTHREAD_MUTEX_RECURSIVE_NP;
//	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
//	pthread_mutex_init(&m_handle, &attr);
	//	
	pthread_mutex_init(&m_handle, NULL);
}

Mutex::~Mutex() {
	pthread_mutex_destroy(&m_handle);
}

void Mutex::Lock(bool bReEnter) {
	pthread_mutex_lock(&m_handle);
}

bool Mutex::TryLock(int timeout) {
	pthread_mutex_lock(&m_handle);
	return true;
}

void Mutex::Unlock() {
	pthread_mutex_unlock(&m_handle);
}

#endif

CReadWriteMutex::CReadWriteMutex()
{
	m_nReadCount = 0;
}

CReadWriteMutex::~CReadWriteMutex()
{
}

void CReadWriteMutex::UnRead()
{
	m_CrtRead.Lock();
	//	assert( m_nReadCount > 0 );
	if( --m_nReadCount == 0)
	{
		m_CrtWrite.Unlock();
	}

	m_CrtRead.Unlock();
}

void CReadWriteMutex::Read(bool bReEnter)
{
	m_CrtRead.Lock();
	if( m_nReadCount++ == 0)
	{
		m_CrtWrite.Lock(bReEnter);
	}

	m_CrtRead.Unlock();
}
void CReadWriteMutex::Write(bool bReEnter)
{
	m_CrtWrite.Lock();
}

void CReadWriteMutex::UnWrite()
{
	m_CrtWrite.Unlock();
}

CReadWriteMutexLock::CReadWriteMutexLock( CReadWriteMutex& Mutex,
	bool bWrite, bool bAutoLock , bool bReEnter)
	: m_Mutex( Mutex ), m_bWrite( bWrite ), m_bLocked( bAutoLock )
{
	if( bAutoLock ) m_bWrite ? m_Mutex.Write(bReEnter) : m_Mutex.Read(bReEnter);
}

CReadWriteMutexLock::~CReadWriteMutexLock()
{
	if( m_bLocked ) Unlock();
}

void CReadWriteMutexLock::Lock( bool bWrite )
{
//	assert( !m_bLocked );
	m_bWrite = bWrite;
	m_bWrite ? m_Mutex.Write() : m_Mutex.Read();
	m_bLocked = true;
}
void CReadWriteMutexLock::Unlock()
{
//	assert( m_bLocked );
	m_bWrite ? m_Mutex.UnWrite() : m_Mutex.UnRead();
	m_bLocked = false;
}

NAMESPACE_END


