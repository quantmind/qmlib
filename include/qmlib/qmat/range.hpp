
#ifndef __RANGE_QMAT_HPP__
#define __RANGE_QMAT_HPP__


#include <qmlib/qmat/qmat.hpp>



QM_NAMESPACE2(math)

// Examples: 
// Vector<double> x(7);
// Range::all()                    [0,1,2,3,4,5,6]
// Range(3,5)                      [3,4,5]
// Range(3,Range::toEnd)           [3,4,5,6]
// Range(Range::fromStart,3)       [0,1,2,3]
// Range(1,5,2);                   [1,3,5]

enum { fromStart = INT_MIN, toEnd = INT_MIN };

class range_iterator;

// Class Range
class range {
public:
	
	class range_iterator  {
	public:
		range_iterator(int start, int step):m_pos(start),m_step(step){}
		range_iterator(int end):m_pos(end){}
		void operator ++ () {m_pos += m_step;}
		bool operator != (const range_iterator& rhs) const {return m_pos != rhs.m_pos;}
		int pos() const {return m_pos;}
	private:
		int m_pos,m_step;
	};
	
	typedef int 			numtype;
	typedef range_iterator	iterator;
	typedef range_iterator	const_iterator;
	
	range() :m_first(0),m_last(0),m_stride(1){}
	
	range(const range& r):m_first(r.m_first),m_last(r.m_last),m_stride(r.m_stride){}

	explicit range(int slicePosition)  {
		m_first  = slicePosition;
		m_last   = slicePosition;
		m_stride = 1;
	}

	range(int first, int last, int stride=1){this->setup(first,last,stride);}

	int first() const  {return m_first;}
	int last()  const  {return m_last;}
	
	range_iterator begin() {return range_iterator(m_first,m_stride);}
	range_iterator end()   {return range_iterator(m_last);}
	
	unsigned length(int =0) const	{
		return (m_last - m_first) / m_stride + 1;
	}

	int stride() const  { return m_stride; }

	bool isAscendingContiguous() const    {
		return ((m_first < m_last) && (m_stride == 1) || (m_first == m_last));
	}

    static range all() { return range(fromStart,toEnd,1); }

    bool isUnitStride() const 	{ return m_stride == 1; }

    // Operators
    range operator-(int shift) const  { 
    	QM_REQUIRE(m_first != fromStart && m_last != toEnd,"Cannot shift");
    	return range(m_first - shift, m_last - shift, m_stride);  
    }

   	range operator+(int shift) const  { 
   		QM_REQUIRE(m_first != fromStart && m_last != toEnd,"Cannot shift");
   		return range(m_first + shift, m_last + shift, m_stride); 
   	}
   	
   	range& operator = (const range& rhs) {m_first = rhs.m_first; m_last = rhs.m_last; m_stride = rhs.m_stride; return *this;}

   	int operator[](unsigned i) const  {return m_first + i * m_stride;}
   	int operator()(unsigned i) const  {return m_first + i * m_stride;}

   	void setup(int first, int last, int stride=1)  {
   		QMAT_PRECONDITION((first < last) && (stride > 0) ||
   						  (first > last) && (stride < 0) ||
   						  (first == last), "Invalid range.");
   		QMAT_PRECONDITION((last-first) % stride == 0,	"the stride must evenly divide the range");
   		m_first  = first;
   		m_last   = last;
   		m_stride = stride;
   	}
private:
	int m_first, m_last, m_stride;
};


QM_NAMESPACE_END2


#endif // __RANGE_QMAT_HPP__
