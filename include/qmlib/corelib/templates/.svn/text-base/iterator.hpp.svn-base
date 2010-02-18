

#ifndef   __ITERATORS_QM_HPP__
#define   __ITERATORS_QM_HPP__
//
//
#include <qmlib/corelib/tools/string.hpp>
#include <boost/numeric/ublas/detail/iterator.hpp>


/*! \defgroup containers Several container templates

    Ordered vector, dataserie, timeserie etc..

    @{
*/



/// \file
/// \brief Definition of some generic Containers
/// \ingroup patterns


QM_NAMESPACE

template<class T>
struct iteratorTraits {};




template<class C>
class random_access_const_iterator : public boost::numeric::ublas::container_const_reference<C>  {
public:
	typedef T										container_type;
	typedef iteratorTraits<container_type>			iterator_traits;		
	typedef typename iterator_traits::value_type	value_type;
	
	const_iterator(const container_type& c, unsigned i = 0):m_data(&c),m_it(i) { }
	const_iterator(const const_iterator& rhs):m_vec(rhs.m_vec),m_it(rhs.m_it) { }

    const_iterator& operator ++ () {
    	++m_it;
        return *this;
    }
    const_iterator &operator -- () {
    	--m_it;
        return *this;
    }
    const_iterator &operator += (unsigned i) {
        	--m_it;
            return *this;
        }
    const_iterator &operator = (const const_iterator &it) {
    	m_data = it.m_data;
    	m_it   = it.m_it;
        return *this;
    }
    bool operator == (const const_iterator &it) const {
    	return m_data == it.m_data && mit == it.m_it;
    }
    bool operator != (const const_iterator &it) const {
    	return !(*this == it);
    }
protected:
	const container_type* m_data;
	unsigned m_it;
};


QM_NAMESPACE_END


#endif	//	__ITERATORS_QM_HPP__



