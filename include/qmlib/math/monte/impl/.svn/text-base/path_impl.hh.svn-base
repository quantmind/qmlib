
#ifndef __PATH_IMPL_QM_HPP__
#define __PATH_IMPL_QM_HPP__



QM_NAMESPACE2(math)


inline PATH   multipath::get_drift(bool annualised) const  {
	QM_REQUIRE(this->numpaths()>0,"Too few paths");
	PATH pa(new path(this->grid()));
	qm_real mo;
	for(unsigned t=0;t<timedim();t++)  {
		mo = 0;
		for(const_iterator it = this->begin(); it != this->end(); ++it)
			mo += (*it)->get(t);
		mo /= this->numpaths();
		if(annualised) mo /= this->grid()->time(t);
		pa->set(t,mo);
	}
	return pa;
}

inline PATH   multipath::get_stdev(bool annualised) const  {
	QM_REQUIRE(this->numpaths()>1,"Too few paths");
	PATH pa(new path(this->grid()));
	qm_real v,mo,va;
	for(unsigned t=0;t<timedim();t++)  {
		mo = 0;
		va = 0;
		for(const_iterator it = this->begin(); it != this->end(); ++it)  {
			v   = (*it)->get(t);
			mo += v;
			va += v*v;
		}
		mo /= this->numpaths();
		va  = (va - this->numpaths()*mo*mo)/(this->numpaths()-1);
		if(annualised) va /= this->grid()->time(t);
		pa->set(t,std::sqrt(va));
	}
	return pa;
}

inline PATH diffusion_path::copy() const  {
	PATH pa(new diffusion_path(grid()));
	path_holder ho = pa->pathholder();
	ho = pathholder();
	return pa;
}
inline PATH jumping_path::copy() const  {
	PATH pa(new jumping_path(grid()));
	jumping_path* pap = static_cast<jumping_path*>(pa.get());
	for(jump_container::const_iterator it=m_jumping.begin();it!=m_jumping.end();++it)
		pap->addjump(it->key(),it->value());
	return pa;
}

inline Paths Paths::copy() const  {
	Paths mp(grid(),numpaths());
	for(const_iterator it=this->begin();it!=this->end();++it)
		mp.push_back(it->copy());
	return mp;
}



QM_NAMESPACE_END2


#endif	//	__PATH_IMPL_QM_HPP__
