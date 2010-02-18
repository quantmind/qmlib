
#ifndef __BROWNIAN_BRIDGE_IMPL_QM_HPP__
#define __BROWNIAN_BRIDGE_IMPL_QM_HPP__



#include <qmlib/qmat/qmatrix.hpp>


QM_NAMESPACE2(math)

class BrownianBridge;
typedef QM_SMART_PTR(BrownianBridge)	BROWNIAN_BRIDGE;

/** The brownian bridge
 */
class BrownianBridge : public basedes {
public:
	typedef qmatrix<unsigned>  indextype;
	typedef qmatrix<qm_real>   weighttype;
	typedef weighttype		   pathtype;
	
	BrownianBridge(unsigned siz);
	unsigned size() const {return m_index.size();}
	
	qm_string tostring() const {return "Brownian bridge size: " + object_to_string(this->size());}
	
	const indextype&  index()      const {return m_index;}
	const indextype&  leftIndex()  const {return m_left;}
	const indextype&  rightIndex() const {return m_right;}
	const weighttype& stdev()      const {return m_stdev;}
	const weighttype& leftWeight() const {return m_leftWeight;}
	const weighttype& righWeight() const {return m_rightWeight;}
	/** \brief Build a path
	 * 
	 * \note No bound check
	 */
	template<class C>
	void buildPath(C& path, unsigned c, const pathtype& normalVariates) const;
protected:
	indextype	 m_index,m_left,m_right;
	weighttype	 m_leftWeight,m_rightWeight,m_stdev;
	void doit();
};


template<class C>
void BrownianBridge::buildPath(C& path, unsigned c, const pathtype& normalVariates) const  {
	unsigned i,j,k,l;
	unsigned steps = this->size();
	path(steps-1,c) = m_stdev[0]*normalVariates[0];
	for(i=1;i<steps;i++)  {
		j = m_left[i];
		k = m_right[i];
		l = m_index[i];
		if(j) path(l,c) = m_leftWeight[i]*path(j-1,c) + m_rightWeight[i]*path(k,c) + m_stdev[i]*normalVariates[i];
		else  path(l,c) = m_rightWeight[i]*path(k,c) + m_stdev[i]*normalVariates[i];
	}
}



QM_NAMESPACE_END2

#endif	// __BROWNIAN_BRIDGE_IMPL_QM_HPP__

