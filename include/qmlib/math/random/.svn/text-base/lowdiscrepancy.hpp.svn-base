/********************************************************************************
 * qmlib/rndgen/lowdiscrepancy.hpp
 *
 * Copyright (C) 2007-2008 Luca Sbardella <luca.sbardella@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Suggestions:          quant.mind@gmail.com
 * Bugs:                 quant.mind@gmail.com
 *
 * For more information, please see the quantmind Home Page:
 *    http://www.quantmind.com
 *
 *******************************************************************************/


#ifndef __LOW_DISCREPANCY_QM_HPP__
#define __LOW_DISCREPANCY_QM_HPP__



#include <qmlib/math/random/sobol.hpp>


//
/// \file
/// \ingroup random
/// \brief Sobol low discrepancy number generator




QM_NAMESPACE2(math)


    
/// \brief Sobol sequence with Unit initialization
/// \ingroup random
class sobol0: public dsequence< SobolGenerator<0> >  {
public:
   	typedef dsequence< SobolGenerator<0> > base_type;
   	sobol0(qm_Size maxDim = 10000, qm_Size seed = 0):base_type(maxDim,seed){}
   	qm_string tostring() const {return "Sobol - Unit initialization";}
};
    
/// \brief Sobol sequence with Regularity breacking initialization (Jaeckel)
/// \ingroup random
class sobol1: public dsequence< SobolGenerator<1> >  {
public:
   	typedef dsequence< SobolGenerator<1> > base_type;
   	sobol1(qm_Size maxDim = 10000, qm_Size seed = 0):base_type(maxDim,seed){}
   	qm_string tostring() const {return "Sobol - Regularity breacking initialization";}
};
    
/// \brief Sobol sequence with Regularity breacking initialization (Jaeckel)
/// \ingroup random
class sobol2: public dsequence< SobolGenerator<2> >  {
public:
   	typedef dsequence< SobolGenerator<2> > base_type;
   	sobol2(qm_Size maxDim = 10000, qm_Size seed = 0):base_type(maxDim,seed){}
   	qm_string tostring() const {return "Sobol - Sobol-Levitan initialization";}
};
   
/// \brief Sobol sequence with Regularity breacking initialization (Jaeckel)
/// \ingroup random
class sobol3: public dsequence< SobolGenerator<3> >  {
public:
   	typedef dsequence< SobolGenerator<3> > base_type;
   	sobol3(qm_Size maxDim = 10000, qm_Size seed = 0):base_type(maxDim,seed){}
   	qm_string tostring() const {return "Sobol - Sobol-Levitan-Lemieux initialization";}
};

/** \brief Halton numbers
 * \ingroup random
 */
class halton: public dsequence< HaltonGenerator >  {
public:
   	typedef dsequence< HaltonGenerator > base_type;
   	halton(qm_Size maxDim = 1000):base_type(maxDim,0){}
   	qm_string tostring() const {return "Halton low-discrepancy numbers generator";}
}; 

    
    
template<class G>
inline dsequence<G>::dsequence(qm_Size maxDim, qm_Size seed):m_generator(maxDim,seed){}
        

template<class G>
inline qm_real dsequence<G>::nextUniform(qm_Size n, qm_Size dim) const  {
  	return m_generator.point(n,dim);
}



QM_NAMESPACE_END2


#endif	//	__LOW_DISCREPANCY_QM_HPP__

