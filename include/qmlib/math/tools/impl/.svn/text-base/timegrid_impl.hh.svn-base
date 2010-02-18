
#ifndef __TIMEGRID_IMPL_QM_HPP__
#define __TIMEGRID_IMPL_QM_HPP__



QM_NAMESPACE2(math)


inline BROWNIAN_BRIDGE timegrid::bridge() const  {
	if(!m_brownian_bridge || m_brownian_bridge->size() != this->length())  {
		QM_REQUIRE(this->length() > 1,"Time grid too small");
		noConst().m_brownian_bridge = BROWNIAN_BRIDGE(new BrownianBridge(this->length()-1));
	}
	return m_brownian_bridge;
}

inline qm_real timegrid::dtmax() const  {
	qm_real dtm = 0;
	for(unsigned i=1;i<this->length();i++)
		dtm = std::max(dtm,this->dt(i,1));
	return dtm;
}


QM_NAMESPACE_END2


#endif  //  __TIMEGRID_IMPL_QM_HPP__

