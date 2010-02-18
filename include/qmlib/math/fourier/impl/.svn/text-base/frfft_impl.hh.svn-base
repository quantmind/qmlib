


#ifndef   __FRACTIONAL_FFT_IMPL_QM_HPP__
#define   __FRACTIONAL_FFT_IMPL_QM_HPP__



QM_NAMESPACE2(math)


template<typename T>
inline frfft<1u,T>::frfft(unsigned N, unsigned D, unsigned meth) {
	QM_REQUIRE(meth<4,"Method can be bewteen 0 and 3");
	QM_REQUIRE(N>2 && 2*(N/2) == N,"Dimension must be even and bigger equal four");
	QM_REQUIRE(D>0,"no fourier transform");
	m_fftmethod = (fftmethod)meth;
	FOURIERTYPE fu;
	for(unsigned i=0;i<D;i++)  {
		fu = FOURIERTYPE(new fouriertype(N));
		m_rffts.push_back(fu);
		p_rffts.push_back(fu.get());
	}
	this->makefrfft(0);	
	unsigned C = this->dsize();
	m_z.resize(C,1);
	m_weights.resize(C,1);
	this->calcweights();
}

template<typename T>
inline void frfft<1u,T>::makefrfft(unsigned p) {
	if(p<2 && this->frft())  {
		unsigned N = this->dsize();
		m_cfft1 = CFOURIERTYPE(new cfouriertype(2*N));
		m_cfft2 = CFOURIERTYPE(new cfouriertype(2*N));
		p_cfft1 = m_cfft1.get();
		p_cfft2 = m_cfft2.get();
	}
}


template<typename T>
inline void frfft<1u,T>::calcweights()  {
	unsigned N = m_weights.rows();
	if(!N) return;
	
	if(this->trapez())  {
		m_weights = 1.;
		m_weights[0]   = 0.5;
		m_weights[N-1] = 0.5;
	}
	else  {
		qm_real mm       = 1./3.;
		m_weights[0]   = mm;
		m_weights[N-1] = mm;
		for(unsigned n=1;n<N-1;n++) {
			m_weights[n] = 1. + mm;
			mm *= -1.;
		}
	}
}


template<typename T>
inline void frfft<1u,T>::set_method(unsigned i)  {
	QM_REQUIRE(i<4,"Method must be between 0 and 3");
	unsigned prec = (unsigned)m_fftmethod; 
	m_fftmethod = (fftmethod)i;
	this->calcweights();
	this->makefrfft(prec);
}

template<typename T>
inline void frfft<1u,T>::invert(qm_real beta) {
	if(this->frft())
		this->invertfrft(beta);
	else  {
		unsigned k,K;
		fouriertype *pf;
		qm_complex  y;
		for(iterator it=m_rffts.begin();it!=m_rffts.end();++it)  {
			pf = it->get();
			K  = pf->dsize();
			darraytype& dft = pf->ddata();
			for(k=0;k<K;k++)  {
				y = qm_complex(dft[k][0],dft[k][1]);
				applyweight(y,k);
				dft[k][0] = y.real();
				dft[k][1] = y.imag();
			}
			pf->inverse();
		}
	}
}

template<>
inline void frfft<1u,qm_real>::applyweight(qm_complex& x, unsigned m) const {
	//x *= m_weights[m];
}
template<>
inline void frfft<1u,qm_complex>::applyweight(qm_complex& x, unsigned m) const {
	x *= m_weights[m];
}


template<typename T>
inline typename frfft<1u,T>::CFOURIERTYPE
frfft<1u,T>::zdft(qm_real beta, bool transf) {
	QM_REQUIRE(this->frft(),"Not available with current integration method");
	this->zdata(beta,transf);
	return m_cfft2;
}

template<typename T>
inline void frfft<1u,T>::zdata(qm_real beta, bool transf) {
	unsigned N  = this->dsize();
	unsigned N2 = 2*N;
	unsigned m,n;
	qm_complex z1 = 1;
	darraytype& idata2 = p_cfft2->idata();
	
	// get the z1 vector
	for(m=0;m<N;m++)  {
		m_z[m]		 = z1;
		idata2.set(m,z1);
		n  = m+1;
		z1 = std::exp(qm_complex(0,n*n*beta));
		idata2.set(N2-n,z1);
	}
	if(transf) p_cfft2->direct();
}


template<typename T>
inline void frfft<1u,T>::invertfrft(qm_real beta) {
	unsigned N  = this->dsize();
	unsigned N2 = 2*N;
	unsigned m;
	qm_real  sc = 1./N2;
	qm_complex psi,y1,z1;
	qm_complex zero(0);
	darraytype& idata1 = p_cfft1->idata();
	darraytype& ddata1 = p_cfft1->ddata();
	darraytype& ddata2 = p_cfft2->ddata();
	
	this->zdata(beta,true);
	
	// Now loop around all transforms
	//   divide them by z1, do direct fft and
	//   multiply it by the direct FFT in p_cff2
	for(iterator it=m_rffts.begin();it!=m_rffts.end();++it)  {
		fouriertype* f   = it->get();
		darraytype& dft  = f->ddata();
		
		for(m=0;m<N;m++)  {
			psi = dft.get(m)/m_z[m];
			applyweight(psi,m);
			idata1.set(m,psi);
			idata1.set(m+N,zero);
		}
		p_cfft1->direct();
		
		for(m=0;m<N2;m++)  {
			y1 = ddata1.get(m);
			z1 = ddata2.get(m);
			y1*= z1*sc;
			ddata1.set(m,y1);
		}
		p_cfft1->inverse();
		
		// Put the vector into results
		wrapfrft(f->idata(),idata1,N);
	}
}


template<>
inline void frfft<1u,double>::wrapfrft(frfft<1u,double>::iarraytype& idft,
									   const frfft<1u,double>::darraytype& idata,
									   unsigned N)  {
	qm_complex y1;
	unsigned N2 = 2*N-1;
	for(unsigned m=0;m<N;m++)  {
		y1  = idata.get(m)/m_z(m);
		idft[m]    = y1.real();
		idft[N2-m] = y1.imag();
	}
}

template<>
inline void frfft<1u,qm_complex>::wrapfrft(frfft<1u,qm_complex>::iarraytype& idft,
								   	       const frfft<1u,qm_complex>::darraytype& idata,
								   	       unsigned N)  {
	qm_complex y1;
	for(unsigned m=0;m<N;m++)  {
		y1  = idata.get(m)/m_z(m);
		idft.set(m,y1);
	}
}

QM_NAMESPACE_END2



#endif  //  __FRACTIONAL_FFT_IMPL_QM_HPP__

