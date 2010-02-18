





#ifndef   __IFFT_CHARACTERISTIC_IMPL_QM_HPP__
#define   __IFFT_CHARACTERISTIC_IMPL_QM_HPP__


QM_NAMESPACE2(math)

template<typename T>
inline ifftchar<T>::ifftchar(unsigned N, unsigned D, qm_real stde,
							 qm_real du, unsigned meth):
		m_stdmul(std::max(stde,0.000001)),
		m_dumin(std::max(du,0.000001)),
		m_frfft(new fouriertype(N,D,meth)){
	p_frfft = m_frfft.get();
}

template<typename T>
inline void ifftchar<T>::set_method(unsigned i) {
	m_frfft->set_method(i);
	this->clear();
}

template<typename T>
inline void ifftchar<T>::set_dumin(qm_real du) {
	if(du>0) {
		m_dumin = du;
		this->clear();
	}
}

template<typename T>
inline void ifftchar<T>::set_stdmul(qm_real st) {
	if(st>0) {
		m_stdmul = st;
		this->clear();
	}
}

QM_NAMESPACE_END2


#endif	//	__IFFT_CHARACTERISTIC_IMPL_QM_HPP__

