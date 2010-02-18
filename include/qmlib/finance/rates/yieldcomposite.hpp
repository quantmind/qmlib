//
/// \file
/// \brief Declaration of main interfaces for finance
/// \ingroup rates
//
#ifndef   __YIELD_COMPOSITE_QM_HPP__
#define   __YIELD_COMPOSITE_QM_HPP__
//
//
#include <qmlib/finance/rates/composite_rate.hpp>
#include <qmlib/finance/instrument.hpp>




QM_NAMESPACE2(math)

struct ycsuptraits  {
	typedef qmatrix<multcash,lower_triangular>	lmatrix_type;
	typedef qmatrix<multcash>					omatrix_type;
	typedef qmatrix<qm_real>					rmat;
	typedef qmatrix<qm_real,lower_triangular>	cfmat_type;
	typedef QM_ORDVEC(qdate)					dates_type;
};

QM_NAMESPACE_END2



QM_NAMESPACE2(finance)


enum discount_type  {
	normal_discount = 0,
	log_discount
};

template<discount_type D> struct discount_function  {};

template<>
struct discount_function<normal_discount>  {
	static qm_real df(qm_real   x, qm_real t) {return x;}
	static qm_real dfdx(qm_real x,  qm_real t) {return 1.0;}
	static qm_real fun(qm_real df, qm_real t) {return df;}
};
/// \brief The log discount function
///
/// \f$ {\tt df} = e^{x(t)} \f$
template<>
struct discount_function<log_discount>  {
	static qm_real df(qm_real x,  qm_real t)   {return  std::exp(x);}
	static qm_real dfdx(qm_real x,  qm_real t) {return  std::exp(x);}
	static qm_real fun(qm_real df, qm_real t)  {return  std::log(df);}
};




template<>
class composite_rate_element<isimplediscount>  {
public:
	typedef isimplediscount				element_type;
	typedef qdate						key_type;
	typedef QM_SMART_PTR(element_type)	ELEM;
	
	///composite_rate_element(){}
	//composite_rate_element(const ELEM& el, const qdate& date):elem(el)  {
	//	cf = el->cashflow(date);
	//	QM_REQUIRE(cf.size(),"Empty cash flow in otcir used for a composite rate");
	//}
	static key_type keyval(ELEM el, const qdate& dte) {
		return el->cashflow(dte).back().key();
	}
	static bool valid(ELEM el) {
		return el->rate()->validvalue();
	}
	//const qdate& 	enddate()   const {return cf.back().key();}
	//const qdate& 	startdate() const {return cf.front().key();}
};


/// \brief Composite Yield Curve class template
///
/// @param B Class which define the support for the discount factor curve
/// \ingroup comprates
template<class B, discount_type T>
class yieldcomposite: public idiscountcurve,
                      public composite_rate<isimplediscount> {
public:
	typedef QM_FROM_NAMESPACE2(math)ycsuptraits		ycsuptraits;
	typedef composite_rate<isimplediscount>			composite_type;
	typedef composite_type::element_wrap			element_wrap;
	typedef composite_type::element_type			element_type;
	typedef composite_type::ELEMENT					ELEMENT;
	typedef composite_type::key_type				key_type;
	typedef B										support_type;
	typedef QM_SMART_PTR(support_type)				SUPPORT;
	typedef discount_function<T>					disc_func;
	typedef typename ycsuptraits::cfmat_type		cfmat_type;
	typedef typename ycsuptraits::rmat				rmat;
	//typedef typename support_type::dates_type		dates_type;
	typedef yieldcomposite<B,T>						selftype;
	
	yieldcomposite(const qdate& dte, const qm_string& code):composite_type(dte),m_code(code){}
	
	qdate		date()				  const { return this->referenceDate();}
	unsigned	length()			  const { return this->size();}
	qm_real     dft(qm_real t)		  const;
	qm_string   code()				  const { return m_code;}
	qm_string   name()				  const { return m_code;}
	qm_string   tostring()            const { return this->code() + " Composite Yield Curve";}
	
	/// \brief The Cash flow matrix used to build the discount factor
	cfmat_type 	cfmat();
	rmat		cfoff();
	rmat		offsens();
	//dates_type	offdates()			  const { return m_support.offdates();}
	
	//
	//qm_real		guess(qm_real t)	  const;
	
	//DiscountRes 	dcashflow(const CASHFLOW& cfs, bool full) const;
protected:
	qm_string					m_code;
	SUPPORT						m_support;
	ycsuptraits::lmatrix_type	m_matrix;
	ycsuptraits::omatrix_type	m_offmat;
	ycsuptraits::dates_type		m_odte;
	
	void build_cfmat();
	void build_cfoff();
	void build_offsens();
	
	cfmat_type   	m_cflow;
	rmat			m_cfoff,m_offsens,m_dd;
	
	selftype& 	noConst() const { return const_cast<selftype&>(*this); }
	
	bool addtoinstruments(const key_type& key, const ELEMENT& el);
	
	void	    build();
	void	    refresh();
};



QM_NAMESPACE_END2

#include <qmlib/finance/rates/impl/yieldcomposite_impl.hh>


#endif  //  __YIELD_COMPOSITE_QM_HPP__
//

