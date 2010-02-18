





#ifndef   __FFT_RESULTS_CHARACTERISTIC_QM_HPP__
#define   __FFT_RESULTS_CHARACTERISTIC_QM_HPP__


#include <qmlib/math/options/black.hpp>
#include <qmlib/qmat/qmatrix.hpp>


/**\file
 * \brief Characteristic function plugin for istochastic processes
 * \ingroup fourier
 */



QM_NAMESPACE2(math)



/** \brief FFT characteristic transform results
 * \ingroup fourier
 * 
 * Template class which handles the output of a characteristic transform
 * calculation
 */
template<class T>
class fftcharresult: public basedes  {
public:
	typedef T								numtype;
	typedef qmatrix<T>						rdatatype;
	typedef std::pair<unsigned,unsigned>	rangetype;
	
	fftcharresult(unsigned N, unsigned D, qm_real b, qm_real L, qm_real duu,
				  qm_real tex, qm_real tse, qm_real tma, qm_real tau);
	
	qm_string tostring() const;
	unsigned size() const {return m_data.rows();}
	unsigned dim() const {return m_data.cols();}
	
	numtype  operator () (unsigned i,unsigned j) const {return m_data(i,j);}
	numtype& operator () (unsigned i,unsigned j) {return m_data(i,j);}
	
	numtype value(qm_real val, unsigned i) const;
	
	unsigned numfactors() const;
	
	/// \brief Calculate the implied Black volatility
	///
	virtual qm_real impliedblack(qm_real val) const {QM_FAIL("Not available for this results");}
	
	qm_real bval() const {return m_b;}
	qm_real dx()   const {return m_dx;}
	qm_real Lval() const {return 0.5*m_dx*this->size();}
	qm_real du()   const {return m_du;}
	qm_real betanopi() const {return 0.5*m_du*m_dx;}
	qm_real beta()     const {return betanopi()/PI;}
	qm_real xv(unsigned i) const {return m_b+i*m_dx;}
	qm_real expiry()   const {return m_tex;}
	qm_real settle()   const {return m_tse;}
	qm_real maturi()   const {return m_tma;}
	qm_real tau()      const {return m_tau;}
	SENSITIVITY sens(const qdate& dte, const qm_string& code, qm_real dval) const;
	
	/// \brief Calculate the domain value from index
	///
	///@param i index in the fourier array of values
	virtual qm_real domainvalue(unsigned i) const {return this->xv(i);}
	
	/// \brief the multiplier of the transform
	///
	///@param i index in the fourier array of values
	virtual qm_real multiplier(unsigned i) const {return 1.;}

	template<class L>
	L ulist(unsigned nf) const {
		L l;
		qm_real dd = this->du();
		rangetype ra = this->range(nf);
		for(unsigned i=ra.first;i<ra.second;i++)
			l.append(i*dd);
		return l;
	}
	template<class L>
	L xlist(unsigned nf) const {
		L l;
		rangetype ra = this->range(nf);
		for(unsigned i=ra.first;i<ra.second;i++)
			l.append(this->xv(i));
		return l;
	}
	template<class L>
	L dlist(unsigned nf) const {
		L l;
		rangetype ra = this->range(nf);
		for(unsigned i=ra.first;i<ra.second;i++)
			l.append(this->domainvalue(i));
		return l;
	}
	template<class L>
	L ylist(unsigned nf, unsigned d) const {
		L l;
		QM_REQUIRE(d<this->dim(),"Out of dimension");
		rangetype ra = this->range(nf);
		for(unsigned i=ra.first;i<ra.second;i++)
			l.append((*this)(i,d));
		return l;
	}
protected:
	rdatatype m_data;
	qm_real   m_b;
	qm_real   m_dx;
	qm_real	  m_du;
	qm_real   m_tex,m_tse,m_tma,m_tau;
	unsigned  m_numfactors;
	
	/// \brief Calculate the transformed strike from domain value strike
	///
	///@param dval strike in real domain
	///@return strike in the transformed domain
	virtual qm_real xvalue(qm_real dval)    const {return dval;}
	
	rangetype range(unsigned nf) const;
	unsigned locate(qm_real dval, qm_real& u) const;
	unsigned countfactors() const;
};


/** \brief FFT result for options
 * \ingroup fourier
 */
class fftoptionresult: public fftcharresult<qm_real>  {
public:
	fftoptionresult(unsigned N, unsigned D, qm_real b, qm_real L, qm_real du,
					qm_real tex, qm_real tse, qm_real tma, qm_real tau,
					qm_real expa):
		fftcharresult<qm_real>(N,D,b,L,du,tex,tse,tma,tau),m_expa(expa){}
		
	qm_real domainvalue(unsigned i) const {
		return m_expa*std::exp(this->xv(i));
	}
	qm_real multiplier(unsigned i) const {
		return m_expa;
	}
	
	/// \brief Calculate the implied Black volatility
	///
	///@param val the strike in theunderlying domain (real strike)
	///@return the implied black volatility
	qm_real impliedblack(qm_real val) const;
protected:
	qm_real 	 m_expa;
	fwdblackcall m_black;
	qm_real xvalue(qm_real dval) const {return std::log(dval/m_expa);}
	
	virtual qm_real makeprice(qm_real pr) const {return pr;}
};





QM_NAMESPACE_END2

#include <qmlib/math/fourier/impl/fftres_impl.hh>

#endif	//	__FFT_RESULTS_CHARACTERISTIC_QM_HPP__

