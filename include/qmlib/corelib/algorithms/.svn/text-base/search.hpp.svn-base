//
//
#ifndef __ALGORITHM_QM_H__
#define __ALGORITHM_QM_H__
//
//
//
#include <qmlib/definitions.hpp>
//
//
//
QM_NAMESPACE2(algorithm)
	//
	//
	//
	/// \brief a Binary Search Algorithm (BSA)
	/// \ingroup algorithm
	///
	/// It is a technique for finding a particular value in a sorted list.
	/// It makes progressively better guesses, and closes in on the sought value,
	/// by comparing an element halfway with what has been determined to be an element
	/// too low in the list and one too high in the list. A binary search finds the median element in a list,
	/// compares its value to the one you are searching for, and determines if it’s greater than,
	/// less than, or equal to the one you want.
	/// Binary search is a logarithmic algorithm and executes in O(log n) time.
	/// Specifically, 1 + log2N iterations are needed to return an answer.
	/// In most cases it is considerably faster than a linear search.
	template<class T>
	bool bsearch1(qm_long& idx, const T& key, const std::vector<T>& vec)	{
		qm_long num      = vec.size();
		qm_long rangemin = 0;
		qm_long rangemax = num-1;
		qm_long rangemid;
		//
		if(num < 1 || key < vec[0])
		{
			idx = 0;
			return false;
		}
		if(key == vec[0])
		{
			idx = 0;
			return true;
		}
		if(key > vec[rangemax])
		{
			idx = num;
			return false;
		}
		if(key == vec[rangemax])
    	{
    		idx = rangemax;
      		return true;
    	}
    	//
    	while(rangemax > rangemin + 1)  {
    		rangemid = (rangemin + rangemax) / 2;
    		if(key == vec[rangemid])  {
    			idx = rangemid;
    			return true;
    		}
    		else if(key > vec[rangemid])
    			rangemin = rangemid;
    		else
    			rangemax = rangemid;
    	}
    	idx = rangemax;
    	return false;
	}
	
	inline unsigned bsearchfirst(qm_long idx)  { return idx >= 0 ? idx : - idx - 1;}
	
}}
//
//
//
#endif  //  __ALGORITHM_QM_H__
//
