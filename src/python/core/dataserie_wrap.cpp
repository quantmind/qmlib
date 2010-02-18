


#include <qmlib/python/pyconfig.hpp>
#include <qmlib/python/timeserie_wrap.hpp>
#include <qmlib/corelib/dates/date.hpp>

QM_NAMESPACE2(python)


void dataserie_wrap()  {
  	
   	using namespace boost::python;
   	
   	//export_ordered_vector<qm_real,qm_real,qm_real,false>("real_ordered_vector","A one dimensional ordered vector of floating point numbers");
   	//export_ordered_vector<qdate,qdate,qdate,false>("date_ordered_vector","A one dimensional ordered vector of date objects");
    
   	export_dataserie<qm_real,false,object>("rdataserie","A data serie with keys given by real numbers for general objects");
   	export_dataserie<qdate,false,object>("dateserie","A keyvalue pair with keys given by dates for general objects");
	export_dataserie<qdate,true,object>("dateserie2","A keyvalue pair with keys given by dates for cash flows. Can have same keys",false);
   	export_dataserie<qdate,false,qm_real>("rdateserie","A keyvalue pair with keys given by dates for general objects");
   	export_timeserie<qdate,qm_real>("rtimeserie","A multidimensional date time-serie of real numbers");
   	export_timeserie<qdate,object>("timeserie","A multidimensional date time-serie of objects");
}
    
QM_NAMESPACE_END2


