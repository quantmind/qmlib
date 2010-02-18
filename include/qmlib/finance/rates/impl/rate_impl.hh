



#ifndef	__IRATES_IMPL_QM_HH__
#define	__IRATES_IMPL_QM_HH__



QM_NAMESPACE


inline SENSITIVITY irate::sen() const {
	return SENSITIVITY(new sensitivity(this->date(),this->code(),this->length()));
}


inline sensitivities irate::sens() const {
	sensitivities ses(this->sen());
	return ses;
}

inline qm_real idiscountcurve::exprate(qm_real T) const {
	if(T==0) return -std::log(this->dft(0.01))/0.01;
	else if(T<0) return 0;
	else return -std::log(this->dft(T))/T;
}

inline qm_real idiscountcurve::instfwd(qm_real T) const {
	qm_real dt = 0.002;
	qm_real bf = this->fwdt(T,T+dt);
	return std::log(bf)/dt;
}

inline qm_real idiscountcurve::fwdrate(qm_real T1, qm_real T2, qm_real tau) const  {
	qm_real bf = this->fwdt(T1,T2);
	return (bf - 1.)/tau;
}


inline SENSITIVITY idiscountcurve::dcashflow(const CASHFLOW& cfs, bool full) const  {
	if(full)  {
		SENSITIVITY res = this->sen();
		for(CASHFLOW::const_iterator ct = cfs.begin(); ct != cfs.end(); ++ct)  {
			qm_real t = this->dcf(ct->key());
			this->fulldiscount(t,ct->value()->cash(),res);
		}
		return res;
	}
	else  {
		qm_real npv  = 0;
		qm_real pv01 = 0;
		qm_real cexc = 0;
		qm_real b;
		for(CASHFLOW::const_iterator ct = cfs.begin(); ct != cfs.end(); ++ct)  {
			b = this->df(ct->key());
			npv  += b*ct->value()->cash();
			pv01 += b*ct->value()->ntau();
			cexc -= b*ct->value()->notional_exchange();
		}
		return SENSITIVITY(new tinysens(this->date(),this->code(),npv,0.0001*pv01,0,100*cexc/pv01));
	}
}


inline void idiscountcurve::fulldiscount(qm_real T, qm_real cash, SENSITIVITY& res) const  {
	
}


inline SENSITIVITY idiscountcurve::dcash(const qdate& dte, qm_real cash) const {
	return this->dcasht(this->dcf(dte),cash);
}

inline SENSITIVITY idiscountcurve::dcasht(qm_real T, qm_real cash) const {
	SENSITIVITY res = this->sen();
	this->fulldiscount(T,cash,res);
	return res;
}


QM_NAMESPACE_END

#endif	//	__IRATES_IMPL_QM_HH__

