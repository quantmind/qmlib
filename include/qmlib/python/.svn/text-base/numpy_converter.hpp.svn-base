//
/// \file
/// \brief Automatic converstion to and from numpy array
//
#ifndef __NUMPY_CONVERTERS_QM_H__
#define __NUMPY_CONVERTERS_QM_H__



#include <qmlib/python/converters.hpp>
#include <numpy/arrayobject.h>



QM_NAMESPACE2(python)



template< typename T >
struct get_dtype  {
	static const char * name() { throw std::logic_error( "get_dtype not specialised for this type" ); }
};


#define DECLARE_DTYPE_FOR( type, dtype )					\
template< > struct get_dtype< type > {						\
	static const char * name() { return dtype; }			\
	static const int size = sizeof(type);					\
};

DECLARE_DTYPE_FOR( double, "float64" )
DECLARE_DTYPE_FOR( float, "float32" )
DECLARE_DTYPE_FOR( int, "int32" )
DECLARE_DTYPE_FOR( unsigned, "uint32" )
DECLARE_DTYPE_FOR( long, "int64" )
DECLARE_DTYPE_FOR( unsigned long, "uint64" )

	
	
	

/// \brief Implementation of automatic conversion from numpy to a c++ array_type
template<class MultiArray>
struct numpy_multi_array_converter  {
	typedef MultiArray										multi_array_t;									
	typedef typename multi_array_t::numtype					numtype;
	typedef get_dtype<numtype>								pytype;
	typedef numpy_multi_array_converter<multi_array_t>		myself;
	typedef std::vector< std::size_t > 						shape_t;
	
	
	static void register_to_python()  {
		boost::python::to_python_converter< multi_array_t, myself >();
	}

	static void register_from_python()	{
		boost::python::converter::registry::push_back(
			&myself::convertible,
			&myself::construct,
			boost::python::type_id< multi_array_t >()
		);
	}
	
	static void register_to_and_from_python()  {
		register_from_python();
		register_to_python();
	}
	
  	static void	get_shape(boost::python::object& obj, shape_t& shape ) {
    	using namespace boost::python;
    	shape.clear();
    	object py_shape = obj.attr( "shape" );
    	const std::size_t N = len( py_shape );
    	for( std::size_t i = 0; N != i; ++i ) shape.push_back( extract<std::size_t>( py_shape[ i ] ) );
    }
	
	/// \brief Check if object is a numpy array
    static void* convertible(PyObject* obj)  {
		using namespace boost::python;
		try {
			shape_t shape;
			object ob(handle<>(borrowed(obj)));
			get_shape( ob, shape);
			if(multi_array_t::dimensionality < shape.size()) return 0;
		}
		catch( ... )  {
			return 0;
		}
		return obj;
    }
    
    /// \brief costruct a multi_array_t from a numpy array
    static void construct(PyObject* obj, boost::python::converter::rvalue_from_python_stage1_data* data)  {
		using namespace boost::python;

		//get the storage
        typedef converter::rvalue_from_python_storage<multi_array_t>  storage_t;
        storage_t * the_storage = reinterpret_cast<storage_t*>( data );
        //void * memory_chunk = the_storage->storage.bytes;

		//new placement
		object py_obj( handle<>( borrowed( obj ) ) );
		shape_t shape;
		get_shape( py_obj, shape );
		PyArray_Descr* descr = PyArray_DESCR(obj);
		multi_array_t* a;
		// if Datatype are the same, do not copy the data, just use it
		if(descr->elsize == pytype::size)  {
			numtype*   dta = (numtype*)PyArrayObject(obj)->data;
			a   = new multi_array_t(shape,dta);
		}
		else  {
			a   = new multi_array_t(shape);
			copy_from_numpy(*a, py_obj);
		}
        data->convertible = (void*)a;
    }
    
    /// \brief Construct a numpy array from a multi_array_t
	static PyObject* convert(const multi_array_t& c_array)  {
		using namespace boost::python;

		object numpy = object( handle<>( ::PyImport_Import( object( "numpy").ptr() ) ) );
		if( ! numpy  ) throw std::logic_error( "Could not import numpy" );
		object array_function = numpy.attr( "empty" );
		if(!array_function) throw std::logic_error( "Could not find array function" );

		//create a numpy array to put it in
		unsigned dim = c_array.num_dimensions(); 
		if(dim==2 && c_array.cols() == 1) dim = 1;
		
		boost::python::list extents;
		for(unsigned d = 0; d < dim; d++)
			extents.append(c_array.length(d));

		object result( array_function(extents,numpy.attr("dtype")( pytype::name() ) ) );
		
		if(dim == 1)
			copy_to_numpy_vector(c_array, result);
		else	
			copy_to_numpy(c_array, result);
		//copy the elements	
		//index i( c_array.num_dimensions(), 0 );
		//do	{
		//	boost::python::list numpy_index;
		//	for(unsigned dim = 0; c_array.num_dimensions() != dim; ++dim ) 
		//		numpy_index.append( i[dim] );
		//	result[ tuple( numpy_index ) ] = c_array( i );
		//}
		//while( increment_index( i, c_array ) );

		return incref( result.ptr() );
	}
    

private:

  	// To iterate over entries in num_dimensions independent fashion
    typedef std::vector< typename multi_array_t::index >  index;

    static void copy_from_numpy(multi_array_t& m, boost::python::object npy)  {
		for(unsigned i=0;i<m.rows();++i)
			for(unsigned j = 0; j < m.cols(); ++j )
				m(i,j) = boost::python::extract<numtype>( npy[boost::python::make_tuple( i, j ) ] );
    }
    
    static void copy_to_numpy(const multi_array_t& m, boost::python::object npy)  {
		for(unsigned i=0;i<m.rows();++i)
			for(unsigned j = 0; j < m.cols(); ++j )
				npy[boost::python::make_tuple( i, j ) ] = m(i,j);
    }
    
    static void copy_to_numpy_vector(const multi_array_t& m, boost::python::object npy)  {
		for(unsigned i=0;i<m.rows();++i)
			npy[boost::python::make_tuple( i ) ] = m(i);
    }
    
    // Iterates over entries in num_dimensions independent fashion
    static bool	increment_index(index& i, const multi_array_t& c_array ) 	{
    	//for( unsigned dim = 0; i.size() != dim; ++dim )    	{
    	//	++i[dim];
    	//	if( i[dim] != c_array.length(dim)) return true;
    	//	else i[dim] = 0;
    	//}
    	return false;
    }

};

    
 
QM_NAMESPACE_END2



#endif // __NUMPY_CONVERTERS_QM_H__

