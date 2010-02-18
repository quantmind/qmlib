


#ifndef   __THREAD_QM_HPP__
#define   __THREAD_QM_HPP__



#include <qmlib/definitions.hpp>
#include <boost/thread.hpp>


QM_NAMESPACE


class thread_adapter  {
public:
    thread_adapter(void (*func)(void*), void* param): _func(func), _param(param) {}
    void operator()() const { _func(_param); }
private:
    void (*_func)(void*);
	void* _param;
};


}


#endif  //  __THREAD_QM_HPP__

