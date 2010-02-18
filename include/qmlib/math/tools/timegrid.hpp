
#ifndef __TIMEGRID_QM_HPP__
#define __TIMEGRID_QM_HPP__
//
#include <qmlib/corelib/templates/timeserie.hpp>
#include <qmlib/corelib/static/all.hpp>
#include <qmlib/math/tools/brownian_bridge.hpp>
//#include <numeric>


/// \file
/// \brief Definition of a timegrid used for time-discretization
/// \ingroup math


QM_NAMESPACE2(math)



class timegrid;
class real_timegrid;
class date_timegrid;
typedef QM_SMART_PTR(timegrid)  	  TIMEGRID;
typedef QM_SMART_PTR(real_timegrid)  RTIMEGRID;
typedef QM_SMART_PTR(date_timegrid)  DTIMEGRID;


/// \brief Base class for time grids
class timegrid  {
public:
	timegrid(){}
	virtual ~timegrid(){}
	qm_real dt_slow0(unsigned i) const {return this->dt_slow(i,1);}

	virtual qm_real time(unsigned i)       				 const {return 0;}
	virtual qm_real time_slow(unsigned i) 				 const {return 0;}
	virtual qm_real dt(unsigned i, unsigned lag)         const {return 0;}
	virtual qm_real dt_slow(unsigned i, unsigned lag)    const {return 0;}
	virtual unsigned length() const 						   {return 0;}
	
	BROWNIAN_BRIDGE bridge() const;
	
	qm_real  dtmax() const;
	qm_real  horizon()  const {return this->time(this->length()-1);}
	template<class L>
	L tolist(unsigned ist) const {
		L lis;
		for(unsigned i = ist; i < this->length(); i++)
			lis.append(this->time(i));
		return lis;
	}
protected:
	BROWNIAN_BRIDGE	m_brownian_bridge;
	
	timegrid& 	noConst() const { return const_cast<timegrid&>(*this); }
};


template<class D>
class timegrid_impl: public timegrid, public dataserie<D,false,qm_real>  {
public:
	typedef dataserie<D,false,qm_real>				container_type;
	typedef typename container_type::value_type		value_type;
	
	timegrid_impl(){}
	const value_type& get_slow(unsigned i)	const {QM_REQUIRE(i<this->size(),"Out of bound"); return (*this)[i];}
	qm_real time(unsigned i)			      const {return (*this)[i].value()  -(*this)[0].value();}
	qm_real time_slow(unsigned i)			  const {return get_slow(i).value() - get_slow(0).value();}
	qm_real dt(unsigned i, unsigned lag = 1)  const {return (*this)[i].value()  - (*this)[i-lag].value();}
	qm_real dt_slow(unsigned i, unsigned lag) const {return get_slow(i).value() - get_slow(i-lag).value();}
	
	unsigned length() const {return this->size();}
};


/// \brief a time grid of year fractions
class real_timegrid : public timegrid_impl<qm_real> {
public:
	real_timegrid(){}
	qm_string tostring() const {return "Year fraction time grid. Length : " + object_to_string(this->length());}
};


/// \brief a date time grid
class date_timegrid : public timegrid_impl<qdate> {
public:	
	date_timegrid():m_dc(new Act365()){}
	date_timegrid(DC dc):m_dc(dc){QM_REQUIRE(m_dc,"Day count is null");}
	qm_string tostring() const {return "Date time grid. Length : " + object_to_string(this->length());}
	DC		  get_dc() const {return m_dc;}
	void	  set_dc(DC dc)  {QM_REQUIRE(dc,"Day count is null"); m_dc = dc;}
private:
	DC				m_dc;
};




QM_NAMESPACE_END2

#include <qmlib/math/tools/impl/timegrid_impl.hh>


#endif  //  __TIMEGRID_QM_HPP__

