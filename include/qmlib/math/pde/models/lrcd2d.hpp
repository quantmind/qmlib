


template<class T>
struct rcd_2d_operators  {
	typedef	structured_grid<2>						gridtype;
	typedef QM_SMART_PTR(gridtype)					GRIDTYPE;
	typedef T										numtype;
	typedef first_centered<numtype,2,1,2>			first_der_type_x;
	typedef first_centered<numtype,2,2,2>			first_der_type_y;
	typedef second_centered<numtype,2,1,2>			second_der_type_x;
	typedef second_centered<numtype,2,2,2>			second_der_type_y;
	typedef structured_operator<first_der_type_x>	first_der_types_x;
	typedef structured_operator<first_der_type_y>	first_der_types_y;
	typedef structured_operator<second_der_type_x>	second_der_types_x;
	typedef structured_operator<second_der_type_y>	second_der_types_y;
	typedef blocktridiagonal						lhsstructure;
};




/// \brief Linear Two dimensional Reaction Convection Diffusion PDE
template<typename T, class C>
class pdemodel<T,C,rcd_2d_operators> : public pdemodel_base<T, typename rcd_2d_operators<T>::gridtype >  {
public:
	typedef pdemodel<T,C,rcd_2d_operators>				model;
	typedef T											numtype;
	typedef rcd_2d_operators<numtype>					operators;
	typedef typename operators::gridtype				gridtype;
	typedef typename operators::GRIDTYPE				GRIDTYPE;
	typedef typename operators::lhsstructure			lhsstructure;
	typedef typename operators::first_der_types_x		first_der_types_x;
	typedef typename operators::first_der_types_y		first_der_types_y;
	typedef typename operators::second_der_types_x		second_der_types_x;
	typedef typename operators::second_der_types_y		second_der_types_y;
	typedef pdemodel_base<T,gridtype>					base_class;
	typedef C											coeftype;
	typedef model_coefficent<coeftype,gridtype>			coef_type;
	typedef typename coef_type::ret_type				coef_expr;
	typedef qmatrix<numtype>							qmat;
	typedef qmatrix<numtype,lhsstructure>				lhstype;
	
	static const bool timedependent = coef_type::timedependent;
	static const bool islinear      = true;
	
	
	pdemodel(const GRIDTYPE& gr, const coeftype& diff_x, const coeftype& diff_y,
			 const coeftype& conv_x, const coeftype& conv_y, const coeftype& mixd,
			 const coeftype& reaction):base_class(gr), m_fder_x(gr),m_fder_y(gr),
			 						   m_sder_x(gr),m_sder_y(gr),
			 						   m_diff_x(diff_x,gr),m_diff_y(diff_y,gr),m_mixd(mixd,gr),
			 						   m_conv_x(conv_x,gr),m_conv_y(conv_y,gr),
			                           m_reac(reaction,gr),m_lhsdone(false)  {
		this->setup();
		m_fderx.resize(this->points());
	}
	
	qm_real  dtmax()  const {return m_dtmax;}

	const qmat& rhs(const qmat& unk, qm_real t) {
		m_fderx = m_fder_x(unk,t);
		//this->m_rhs = m_reac(t)*unk + m_conv_x(t)*m_fder_x  + m_conv_y(t)*m_fder_y(unk,t);
					//+ m_diff_x(t)*m_sder_x(unk,t) + m_diff_y(t)*m_sder_y(unk,t);
					//+ m_mixd(t)*m_fder_y(m_fderx,t); 
		return this->m_rhs; 
	}
	
	template<class expr>
	const qmat& rhs(const matrix_expr<expr>& unk, qm_real t) {
		m_fderx = m_fder_x(unk,t);
		this->m_rhs = m_reac(t)*unk + m_conv_x(t)*m_fder_x  + m_conv_y(t)*m_fder_y(unk,t)
					+ m_diff_x(t)*m_sder_x(unk,t) + m_diff_y(t)*m_sder_y(unk,t) +
		            + m_mixd(t)*m_fder_y(m_fderx,t); 
		return this->m_rhs; 
	}
	
	lhstype& lhs(qm_real t) {
		this->LHS(t);
		return m_lhs;
	}
	
	const lhstype& get_lhs() {return this->lhs(0);}
	
	void clear() {m_lhsdone = false;}
	
	template<timeschemes tmethod>
	time_marching_result solve(qm_real dt, unsigned N)  {
		typedef typename timescheme_traits<tmethod,model>::marchingtype marchingtype;
		marchingtype tmet;
		return time_marching::advance(tmet, *this, dt, N);
	}
	
	void LHS(qm_real t) {
		if(!m_lhsdone || timedependent)  {
			if(!m_lhsdone)  {
				m_lhs.resize(this->points(),this->points());
				m_lhs = 0;
				m_lhsdone = true;
			}
			m_fder_x.lhs(m_conv_x(t),m_lhs);
			m_fder_y.lhs(m_conv_x(t),m_lhs);
			m_sder_x.lhs(m_diff_x(t),m_lhs);
			m_sder_y.lhs(m_diff_y(t),m_lhs);
			//m_fder_y.lhs(m_mixd(t))
			//m_lhs.add_to_diagonal(m_reac(t));
		}
	}
	
protected:
	first_der_types_x	m_fder_x;
	first_der_types_y	m_fder_y;
	second_der_types_x	m_sder_x;
	second_der_types_y	m_sder_y;
	lhstype				m_lhs;
	qmat				m_fderx;
	coef_type 			m_diff_x,m_diff_y,m_mixd,m_conv_x,m_conv_y,m_reac;
	bool				m_lhsdone;
	qm_real 			m_dtmax;
	
	void setup()  {
		/*
		unsigned N  = this->points();
		qm_real v,cov,dif,dtc,dtd,dtm;
		qm_real big = std::numeric_limits<qm_real>::max();
		m_dtmax = big;
		GRIDTYPE gr = this->grid();
		for(unsigned i=0;i<N;i++)  {
			v = gr->volume_fast(i);
			cov = std::fabs(m_conv(i,0));
			dif = m_diff(i,0);
			dtc = cov > 0 ? v/cov 		: big;
			dtd = dif > 0 ? 0.5*v*v/dif : big;
			dtm = std::min(dtc,dtd);
			m_dtmax  = std::min(m_dtmax,dtm);
		}
		if(m_dtmax == big) m_dtmax = 1.0;
		*/
	}
	
};
