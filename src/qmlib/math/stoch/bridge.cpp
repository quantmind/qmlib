
#include <qmlib/math/tools/brownian_bridge.hpp>


QM_NAMESPACE2(math)


BrownianBridge::BrownianBridge(unsigned siz):
	m_index(siz),m_left(siz),m_right(siz),
	m_leftWeight(siz),m_rightWeight(siz),m_stdev(siz) {
	QM_REQUIRE(siz>0,"There must be at least a step");
	doit();
}

void BrownianBridge::doit() {
	unsigned steps = this->size();
	indextype map(steps);
	for(unsigned i=0;i<steps;++i) map[i] = 0;
	
	unsigned i,j,k,l;
	qm_real den,rw;
	
	map[steps-1] = 1;
	m_index[0]   = steps-1;
	m_stdev[0]   = std::sqrt(qm_real(steps));
	m_left[0]  = m_right[0]  = 0;
	m_leftWeight[0] = m_rightWeight[0] = 0.; 
	for(j=0,i=1;i<steps;++i)  {
		while(map[j]) ++j;
		k = j;
		while(!map[k]) ++k;
		l = j + ((k-1-j)>>1);
		map[l] = i;
		den    = 1./(k+1.-j);
		rw     = (l+1.-j)*den;
		m_index[i] = l;
		m_left[i]  = j;
		m_right[i] = k;
		m_leftWeight[i]  = (k-l)*den;
		m_rightWeight[i] = rw;
		m_stdev[i]		 = std::sqrt(rw*(k-l));
		j = k+1;
		if(j>=steps) j=0;
	}
}


QM_NAMESPACE_END2