



QM_NAMESPACE2(math)

class a13;

class a13integrator  {
	friend class a13;
	typedef characteristic<3u>  chartype;
	typedef chartype::rmat		rmat;
public:
	void set(const parameters& pa) {
		kr		 = pa[0]->get_value();
		km		 = pa[1]->get_value();
		kv		 = pa[2]->get_value();
		theta 	 = pa[3]->get_value();
		sig 	 = pa[4]->get_value();
		alphar 	 = pa[5]->get_value();
		alpham 	 = pa[6]->get_value();
		etar	 = pa[7]->get_value();
		etam	 = pa[8]->get_value();
		etav	 = pa[9]->get_value();
		srm		 = pa[10]->get_value();
		smr		 = pa[11]->get_value();
		srv		 = pa[12]->get_value();
		smv		 = pa[13]->get_value();
		sig2     = sig*sig;
		etar2    = etar*etar;
		etam2    = etam*etam;
		etav2    = etav*etav;
		alphar2  = alphar*alphar;
		alpham2  = alpham*alpham;
		kk		 = kr/(km - kr);
		thkm     = theta*km;
	}
	template<typename T>
	void b12(qm_real tau, tinyvec<T,3u>& x, const T& h0, const T& h1) const {
		x[0] = (h0*std::exp(-kr*tau) - mm)/kr;
		x[1] = kk*(x[0] + mkm) + h1*std::exp(-km*tau);
	}
	//
	template<typename T>
	T rhs(const tinyvec<T,3u>& x) const {
		T d0 = etar*(    x[0] + smr*x[1]);
		T d1 = etam*(srm*x[0] +     x[1]);
		T d2 = etav*(srv*x[0] + smv*x[1] + x[2]);
		return 0.5*(d0*d0 + d1*d1 + d2*d2) - kv*x[2];
	}
	//
	template<typename T>
	T aval(const tinyvec<T,3u>& b) const {
		T dir = alphar*(b[0] + smr*b[1]);
        T dim = alpham*(srm*b[0] + b[1]);
        return 0.5*(dir*dir + dim*dim) + thkm*b[1] + sig2*kv*b[2];
	}
	template<typename T>
	void vals(const tinyvec<T,3u>& u, affine_exponent<T,3u>* expo, qm_real dtt) const {
		typedef tinyvec<T,3u> tvec;
		qm_real Ten     = expo->t1 - expo->t0;
		unsigned TS(std::max(1,int(std::ceil(Ten/dtt))));
		
		qm_real  dt     = Ten/TS;
		expo->n	   	    = TS;
		mm		   	    = 0.01*expo->disc();
		mkm    		    = mm/km;
		
		tvec	 b0;
		tvec     b1(u);
		T	     a  = 0;
		
		T  		 h0     = kr*b1[0] + mm;
		T   	 h1     = b1[1] - kk*(b1[0] + mkm);
		qm_real  dti    = 1./dt;
		unsigned totite = 0;
		qm_real  tau    = 0;
		
		T	rhs_n,rhs_c,db,lhs,jac;
		qm_real dxa;
		unsigned ite;
		
		// integration in tau in [0,t1-t0]
		for(unsigned n=0;n<TS;n++)  {
			tau  += dt;
			b0    = b1;
			b12(tau,b1,h0,h1);							// Calculate b1 and b2
			rhs_n = rhs(b0);							// Right hand side at t0
			ite   = 0;
			dxa   = 1;
			while(dxa > m_a13->tolerance())  {
				ite++;
				QM_REQUIRE(ite<=m_a13->odemaxiter(),"Too many iterations in Newthon-Raphson solver for a13. dx = "+object_to_string(dxa));
				rhs_c 	= rhs(b1);
				jac   	= etav2*(srv*b1[0] + smv*b1[1] + b1[2]) - kv;
				lhs     = dti - 0.5*jac;
				db		=(0.5*(rhs_n+rhs_c) - (b1[2]-b0[2])*dti)/lhs;
				b1[2]  += db;
				dxa     = change(b1[2],db);
			}
			totite += ite;
			a += 0.5*dt*(aval(b0)+aval(b1));
		}
		expo->itern = totite;
		expo->a = a;
		expo->b = b1;
	}
private:
	qm_real kr,km,kv,theta,sig,alphar,alpham,etar,etam,etav,srm,smr,srv,smv;
	qm_real sig2,kk,thkm,etar2,etam2,etav2,alphar2,alpham2;
	mutable qm_real mkm,mm;
	chartype	*m_a13;
	a13integrator():m_a13(0){};
	void set(chartype* c) {m_a13 = c;}
};




QM_NAMESPACE_END2

