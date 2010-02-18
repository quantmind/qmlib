


#ifndef __BUFFER_QM_HPP__
#define __BUFFER_QM_HPP__

#include <qmlib/corelib/tools/string.hpp>



QM_NAMESPACE


template<typename T>
class base_buffer  {
public:
    base_buffer():m_buffer(0),m_size(0){}
    virtual ~base_buffer(){this->Dispose();}
	
    unsigned size() const {return m_size;}
	T*		 ptr()  const {return m_buffer;}
	qm_string tostring() const {return "buffer (size = " + object_to_string(m_size) + ")";}
protected:
    T*        m_buffer;
    unsigned  m_size;
	virtual void Dispose() {}
};



class void_buffer : public base_buffer<void> {
public:
	typedef base_buffer<void> base_class;
	void_buffer(unsigned siz = 0){Alloca(siz);}
    void Alloca(unsigned siz);
	operator void* ()        {return this->ptr();}
protected:
    void Dispose();
};


template<typename T>
class qm_buffer: public base_buffer<T>  {
public:
	typedef base_buffer<T>  base_class;
    qm_buffer(unsigned siz = 0){Alloca(siz);}
    void Alloca(unsigned siz);

	operator T* ()        {return this->ptr();}
	const T& operator [] (unsigned i) const {return m_buffer[i];}
	T& operator [] (unsigned i)  {return m_buffer[i];}

	const T& get_slow(unsigned i) const     {QM_REQUIRE(i<this->size(),"Out of bound"); return (*this)[i];}
	void set_slow(unsigned i, const T& val) {QM_REQUIRE(i<this->size(),"Out of bound"); (*this)[i] = val;}

	void copy(const qm_buffer& buf)  {
		this->Dispose();
		this->Alloca(buf.size());
		for(unsigned i=0;i<buf.size();i++)
			(*this)[i] = buf[i];
	}
protected:
    void Dispose();
};

template<>
class qm_buffer<void>{};





inline void void_buffer::Alloca(unsigned siz)  {
	if(siz > this->size()) {
		this->Dispose();
		this->m_buffer = malloc(siz);
		this->m_size   = siz;
	}
}

inline void void_buffer::Dispose() {
    if(this->m_buffer) free(this->m_buffer);
    this->m_buffer = 0;
    this->m_size   = 0;
}




template<class T>
inline void qm_buffer<T>::Alloca(unsigned siz)  {
	if(siz > this->size()) {
		this->Dispose();
        this->m_buffer = new T[siz];
        this->m_size   = siz;
	}
}

template<class T>
inline void qm_buffer<T>::Dispose() {
    if(this->m_buffer) delete [] this->m_buffer;
    this->m_buffer = 0;
    this->m_size   = 0;
}




QM_NAMESPACE_END


#endif	//	__BUFFER_QM_HPP__
