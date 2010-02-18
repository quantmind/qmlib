/********************************************************************************
 * qmlib/math/rndgen.hpp
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


#ifndef __RNDGEN_QM_HPP__
#define __RNDGEN_QM_HPP__


#include <qmlib/math/random/base.hpp>
//#include <qmlib/arrays.hpp>
#include <qmlib/math/stat/all.hpp>


/*! \ingroup random Random Number Library

    Random number generation, using quasirandom generators 
    and low discrepancy numbers

    @{
*/

//
/// \file
/// \brief Base classes for Random number generation

QM_NAMESPACE2(math)


/// \brief Interface class for random number generator
class rndgen : public basedes {
public:
    /// \brief generate a uniform random number in [0,1]
    /// @param idx Index indicating the position in sample set of a montecarlo method
    /// @param dim Dimension associated with idx
    /// @return A uniform random number in [0,1]
    virtual qm_real nextUniform(qm_Size idx = 0, qm_Size dim = 0) const {QM_FAIL("nextUniform not implemented");}
   
    /// \brief generate a standard normal variate
    /// @param idx Index indicating the position in sample set of a montecarlo method
    /// @param dim Dimension associated with idx
    /// @return A standard normal variate in \f$(-\infty,\infty)\f$
    qm_real nextNormalVariate(qm_Size idx = 0, qm_Size dim = 0) const;
    
    /// \brief generate a poisson time arrival
    /// @param lambda the integrated inetnsity
    /// @param idx Index indicating the position in sample set of a montecarlo method
    /// @param dim Dimension associated with idx
    /// @return A poisson arrival
    qm_real nextArrival(qm_Size idx = 0, qm_Size dim = 0) const;
    
    virtual unsigned maxdimension() const {return std::numeric_limits<unsigned>::infinity();}
protected:
   	/// \brief seed initializer
   	qm_uns_long   initialseed() const;
};




/// \brief Base class for low discrepancy sequence
class lowDiscrepacySequence: public rndgen  {
public:
	lowDiscrepacySequence():m_idx(0){}
protected:
    qm_uns_long  m_startdim;
    qm_uns_long  m_idx;
};


/// \brief Interface class for quasi-random (pseudo-random) number generator
class quasiRandomNumber: public rndgen  {
public:
	quasiRandomNumber(){}
};
    //
    //
    /*
    /// \brief Ecuyer Random number generator
    ///
    /// Plain and simple quasiRandomNumber generator
    /// \ingroup math
    class Ecuyer: public quasiRandomNumber  {
      mutable qm_uns_long m_seed;
    public:
QMDLL Ecuyer(qm_long seed = 0);
QMDLL qm_real nextUniform(qm_Size n = 0, qm_Size dim = 0) const;
    };
	*/
    
    
    
/// \brief Mersenne Twister quasiRandomNumber generator of period 2**19937-1
/// \note For more details see http://en.wikipedia.org/wiki/Mersenne_twister and
/// http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
///
/// Mersenne Twister(MT) is a pseudorandom number generating algorithm developped
/// by Makoto Matsumoto  and Takuji Nishimura (alphabetical order) in 1996/1997.
///  - Far longer period and far higher order of equidistribution than any other implemented
///    generators. (It is proved that the period is 2^19937-1, and 623-dimensional
///    equidistribution property is assured.)
class MersenneTwister: public quasiRandomNumber  {
public:
	
	// if the given seed is 0, a random seed will be chosen based on clock()
    explicit MersenneTwister(qm_uns_long seed = 0);
    explicit MersenneTwister(const qm_ulvector& seeds);
    //
    // divide by 2^32
    qm_real nextUniform(qm_Size n = 0, qm_Size dim = 0) const  {return (qm_real(this->nextInt32()) + 0.5)/4294967296.0;}
    //
    // return  a random number on [0,0xffffffff]-interval
    qm_uns_long nextInt32() const;
    
    qm_string tostring() const {return "Mersenne Twister Random number generar";}
    
private:
	static const qm_Size           N 		  = 624;
    static const qm_Size           M 		  = 397;
	static const qm_uns_long       MATRIX_A   = 0x9908b0dfUL;  /* constant vector a */
	static const qm_uns_long       UPPER_MASK = 0x80000000UL;  /* most significant w-r bits */
	static const qm_uns_long       LOWER_MASK = 0x7fffffffUL;  /* least significant r bits */
	//
	void    seedInitialization(qm_uns_long seed);
	mutable qm_ulvector  mt;
	mutable qm_Size      mti;
};
    
    
/// \brief Seed generator for random number generator
/// \ingroup random
class SeedGenerator  {
public:
  	SeedGenerator();
   	qm_uns_long get() const {return m_rng.nextInt32();}
private:
  	MersenneTwister  m_rng;
   	void initialize();
};
    
    
    
template<class G>
class dsequence: public lowDiscrepacySequence  {
public:
  	dsequence(qm_Size maxDim, qm_Size seed);
   	qm_real nextUniform(qm_Size n, qm_Size dim) const;
   	unsigned maxdimension() const {return m_generator.dimension();} 
protected:
   	G	m_generator;
};



/// \brief Base class for low Discrepacy Sequence Generator
class lowDiscrepacySequenceGenerator  {
public:
  	typedef std::vector<qm_real>        samples;
   	typedef std::vector<samples>  	    vector_samples;
   	
   	lowDiscrepacySequenceGenerator(qm_Size dim, qm_Size start):m_dimensionality(dim),m_start(start){}
   	virtual ~lowDiscrepacySequenceGenerator(){}
   	
   	qm_Size dimension()		  const { return m_dimensionality;}
   	qm_Size sequenceCounter() const { return m_sequence.size();}
   	/// \brief A point in the sample space
   	/// @param n point in the sequence
   	/// @param dim dimensionality of the point
   	/// @return a point in the sample space [1,big number]x[1,dimension]
   	qm_real point(qm_Size n, qm_Size dim) const;
   	
protected:
   	qm_Size                   m_dimensionality;
   	qm_Size					  m_start;
   	mutable vector_samples    m_sequence;
   	
   	/// \brief generate the next sequence of points for all dimensions
   	virtual void nextSequence() const = 0;
};




inline qm_real rndgen::nextNormalVariate(qm_Size idx, qm_Size dim) const {
	normal_dist nd;
	return nd.icumulative(this->nextUniform(idx,dim));
}

inline qm_real rndgen::nextArrival(qm_Size idx, qm_Size dim) const {
	return -std::log(this->nextUniform(idx,dim));
}

QM_NAMESPACE_END2


#endif  //  __RNDGEN_QM_HPP__

/*! @} */

