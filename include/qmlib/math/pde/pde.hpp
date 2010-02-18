

#ifndef __PDE_MAIN_QM_HPP__
#define __PDE_MAIN_QM_HPP__

#include <qmlib/qmat/qmatrix.hpp>


/*! \defgroup pde Partial Differential Equation Library

    Classes for handling partial differential equations in multidimensions

    @{
*/


/** \file
 *  \brief Base classes for space discretization
 */


QM_NAMESPACE2(math)

class grid {
public:
	virtual ~grid(){}
	
	virtual qm_real minvolume() const {return 1;}
	unsigned dimensions() const {return m_dim;}
protected:
	grid(){}
	grid(unsigned dim):m_dim(dim){}
	unsigned m_dim;
	void checkdim(unsigned dim)  const  {
		QM_REQUIRE(dim >= 1 && dim<=3,"Out of bound in dimension. It must be between 1 and 3");
	}
};

class gridN {
public:
	virtual ~gridN(){}
	virtual  qm_real    minvolume() 					const {return 1;}
	virtual  unsigned   dimensions()    				const {return 1;}
	virtual  unsigned   points()	    				const {return 1;}
	virtual  qm_string  tostring()      				const {return "grid base class";}
	virtual  qm_real    coordinate(unsigned,unsigned) 	const {return 0;}
	virtual  qm_real	volume(unsigned)				const {return 0;}
protected:
	gridN(){}
	void checkdim(unsigned dim)  const  {
		QM_REQUIRE(dim < this->dimensions(),"Out of bound in dimension. It must be between 0 and Dim-1");
	}
};

typedef QM_SMART_PTR(gridN)	GRID;


/*! @} */


	
QM_NAMESPACE_END2


#endif // __PDE_MAIN_QM_HPP__

