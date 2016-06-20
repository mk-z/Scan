/* 
 *you can often just use CReadWriteMutexLock simply, as CSingleLock
 *
 * extract from MSDN:
 * After a thread has ownership of a critical section, it can make additional calls
 *   to EnterCriticalSection or TryEnterCriticalSection without blocking its execution.
 *   This prevents a thread from deadlocking itself while waiting for a critical
 *  section that it already owns.
 *   (but, in the CReadWriteMutex, it may cause problem. for example, ThreadA-R;ThreadA-UR;
 *     ThreadB-R;ThreadB-W... will do work normally, but if no ThreadA-UR: ThreadA-R;ThreadB-R;
 *     ThreadB-W... will cause ThreadB locked-infinite, unless you call UnRead() twice in ThreadA:
 * 	ThreadB can't have the opportunity to call UnRead().
 *  second example: ThreadB-W,ThreadA-R,(ThreadA-W),ThreadB-R,... cause deadlock, when ThreadA is
 * 	the first one to read, so (ThreadA-W). A own R-lock and wait W-Lock, while B own W-lock and
 * 	wait R-lock.
 *   so, you'd never use Read-Lock and Write-Lock with the same CReadWriteMutex without Unlock
 *     between,in the same thread. because there are two locks indeed.)
 * 
 * If a thread calls LeaveCriticalSection when it does not have ownership of the
 *   specified critical section object, an error occurs that may cause another
 *   thread using EnterCriticalSection to wait indefinitely.
 *   (test result: the following EnterCriticalSection deadlocked even in the same thread.)
*/

#ifndef NVCM_READWRITEMUTEX_H
#define NVCM_READWRITEMUTEX_H

#include "Global.h"

NAMESPACE_BEGIN(Tools)

class Mutex {
public:
	Mutex();
	~Mutex();

	void Lock(bool bReEnter = true);	//
	bool TryLock(int timeout = 0);
	void Unlock();

private:
#ifdef OS_WIN32
	CRITICAL_SECTION m_CritSec;
#endif

#ifdef OS_LINUX
	pthread_mutex_t m_handle;
#endif

	DISABLE_COPY(Mutex)
};
class CAutoLock
{
public:
	CAutoLock(Mutex *mtx) : m_mutex(mtx) {
		m_mutex->Lock();
	}

	~CAutoLock() {
		m_mutex->Unlock();
	}

private:
	Mutex *m_mutex;
};

class CReadWriteMutex  
{
protected:
	int m_nReadCount;
	Mutex m_CrtRead;
	Mutex m_CrtWrite;
	
	// CRITICAL_SECTION m_CrtRead;
	// CRITICAL_SECTION m_CrtWrite; 

public:
	CReadWriteMutex();
	virtual ~CReadWriteMutex();
	virtual void UnRead(	);	
	virtual void Read(bool bReEnter = true); //
	virtual void Write(bool bReEnter = true); //
	virtual void UnWrite();

	// No copies do not implement
protected: 
	CReadWriteMutex( const CReadWriteMutex &rhs );
	CReadWriteMutex& operator=( const CReadWriteMutex &rhs );
};

class CReadWriteMutexLock
{
public:
	CReadWriteMutexLock( CReadWriteMutex& Mutex,
		bool bWrite = true,		//
		bool bAutoLock = true,	//
		bool bReEnter = true	//
		);
	virtual ~CReadWriteMutexLock();
	virtual void Lock( bool bWrite );
	virtual void Lock(){ Lock( m_bWrite ); };
	virtual void Unlock();
	
protected:
	CReadWriteMutex& m_Mutex;
	bool m_bWrite;
	bool m_bLocked;
};

NAMESPACE_END

#endif // !defined(NVCM_READWRITEMUTEX_H)

