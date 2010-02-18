
#ifndef __MEMORYBLOCK_QMAT_HPP__
#define __MEMORYBLOCK_QMAT_HPP__


#include <qmlib/qmat/qmat.hpp>

/** \file
 * \brief Memory block management for qmatrix
 * \ingroup qmat
 */

QM_NAMESPACE2(math)


class refcount  {
public:
	refcount():m_references(0){}
	
	int references() const { return m_references;}

	int addReference()  {++m_references; return m_references;}
	
	int removeReference()  {
		--m_references;
		return m_references;
	}
private:
	int m_references;
};


/** \brief Memory block used in qmatrix
 * \ingroup qmat
 */
template<typename T>
class memoryblock : public refcount {
public:
	typedef T	type;
	
	memoryblock():m_data(0),m_length(0) {}
	memoryblock(unsigned length)		{allocate(length);}
	~memoryblock(){deallocate();}
	
	unsigned  size() 		const 	{ return m_length; }
	unsigned  length() 		const 	{ return m_length; }
	
	type  operator [] (unsigned i) 	const	{ QMAT_PRECONDITION(i<m_length,"Out of Bound"); return m_data[i];}
	type& operator [] (unsigned i) 			{ QMAT_PRECONDITION(i<m_length,"Out of Bound"); return m_data[i];}
	type* data() {return m_data;}
protected:
	type*			m_data;
	unsigned		m_length;
	
	void allocate(unsigned length);
	void deallocate();
	
	// hide these ones
	memoryblock(const memoryblock<type>&){}
    void operator=(const memoryblock<type>&){}
};



template<typename T>
void memoryblock<T>::allocate(unsigned length)  {
	m_data 	  = 0;
	m_length  = length;
	if(m_length == 0) return;
	
	//unsigned long numBytes = dim * sizeof(numtype);
	m_data = new type[m_length];
}

template<typename T>
void memoryblock<T>::deallocate()  {
	if(m_length > 0) delete [] m_data;
	m_length = 0;
	m_data 	 = 0;
}


/** \brief Memory block reference used in qmatrix
 * \ingroup qmat
 */
template<typename T>
class memoryblockRef  {
public:
	typedef T						type;
	typedef memoryblock<type>		blocktype;
	typedef memoryblockRef<type>	myself;
	
	memoryblockRef():m_data(0),m_block(0){}
	memoryblockRef(type* data):m_data(data),m_block(0){}
	
	explicit memoryblockRef(unsigned length)  {
		m_block = new memoryblock<type>(length);
		m_block->addReference();
		m_data = m_block->data();
	}
	
	~memoryblockRef()  {
		blockRemoveReference();
	}
	
    int numReferences() const    {
    	return m_block ? m_block->references() : 0;
    }

	bool get_owndata() const {
		if(m_data && !m_block) return false;
		else return false;
	}
    
    type* data() const {return m_data;}
    
protected:
    type* 	m_data;
    
    void initialblock(unsigned size)  {
    	m_block = new memoryblock<type>(size);
    	m_block->addReference();
    	m_data = m_block->data();
    }
    void initialblock(myself& rhs)  {
    	m_block = rhs.m_block;
    	if(m_block)  {
    		m_block->addReference();
    		m_data = m_block->data();
    	}
		else {
			m_data = rhs.m_data;
		}
    }
    void newblock(unsigned size)  {
        blockRemoveReference();
        if(size) this->initialblock(size);
    }
    void changeblock(myself& rhs)  {
    	blockRemoveReference();
    	this->initialblock(rhs);
    }
    
	static void swapblockref(memoryblockRef& lhs,memoryblockRef& rhs)  {
		QMAT_PRECONDITION(lhs.m_block != rhs.m_block,"You are trying to swap the same memory block");
		blocktype* te = lhs.m_block;
		lhs.m_block   = rhs.m_block;
		rhs.m_block   = te;
		if(lhs.m_block)	lhs.m_data  = lhs.m_block->data();
		else lhs.m_data = 0;
		if(rhs.m_block) rhs.m_data  = rhs.m_block->data();
		else rhs.m_data = 0;
	}
	
	template<class Archive>
	void save_data(Archive& ar, unsigned size) const {
		unsigned i;
		for(i=0;i<size;i++)
			ar & m_data[i];
	}
	
	template<class Archive>
	void load_data(Archive& ar, unsigned size) {
		this->newblock(size);
		if(m_block)  {
			unsigned i;
			for(i=0;i<size;i++)
				ar & m_data[i];
		}
	}
private:
    memoryblock<type>* 	m_block;
    
    void blockRemoveReference()  {
    	if(m_block)  {
    		int refcount = m_block->removeReference();
    		if (refcount == 0)	delete m_block;
    		m_block = 0;
    		m_data  = 0;
    	}
    }
};

	
QM_NAMESPACE_END2

#endif // __MEMORYBLOCK_QMAT_HPP__
