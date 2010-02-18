

#include <qmlib/python/pyconfig.hpp>
#include <qmlib/python/log_wrap.hpp>
#include <qmlib/python/timeserie_wrap.hpp>
#include <qmlib/bloomberg/blb.hpp>


QM_NAMESPACE2(bloomberg)

template<class F, class LR, class HR, class L>
bool blb<F,LR,HR,L>::m_loaded_fields = false;

template<>
inline int blbFeed<boost::python::object,LIVEDATA>::get_datatype() {return 1;}
template<>
inline void blbFeed<boost::python::object,LIVEDATA>::initdata() {m_data = LIVEDATA(new livedata);}

QM_NAMESPACE_END2




QM_NAMESPACE2(python)



struct livedata_pickle_suite : boost::python::pickle_suite  {
    static  boost::python::tuple
    getinitargs(QM_FROM_NAMESPACE2(bloomberg)livedata const& w) {
        return boost::python::make_tuple(w.get_last(),w.get_bid(),w.get_ask(),w.get_open(),w.get_volume());
    }
};



template<class F, class T>
void doblbfeed(const qm_string& fname)  {
	using namespace boost::python;
	QM_USING_NAMESPACE2(bloomberg);

	typedef blbFeedBase		blbFeedb;
	typedef blbFeed<F,T>	blbFeedp;
	
	register_ptr_to_python<QM_SMART_PTR(blbFeedp)>();

	class_<blbFeedp, bases<blbFeedb> >(fname.c_str(), "Bloomberg feed object", no_init)
		.add_property("data",		&blbFeedp::get_data,"Data available")
		.add_property("type",		&blbFeedp::get_datatype,"Data type. 0 - historical, 1 - live")
		.add_property("localtype",	&blbFeedp::get_localtype, &blbFeedp::set_localtype,"")
		;
}



void blb_wrap()  {

    using namespace boost::python;
	QM_USING_NAMESPACE2(bloomberg);
	typedef blb<qm_list,LIVEDATA,qm_list,object>	blbp;
	typedef blbp::blbfeedr							blbfeedr;
	typedef blbFeedBase								blbFeedp;
	typedef QM_SMART_PTR(blbp)						BLB;
	typedef QM_SMART_PTR(blbFeedp)					BLBFEED;
	typedef QM_SMART_PTR(blbfeedr)					BLBFEEDR;

	register_ptr_to_python<BLB>();
	register_ptr_to_python<BLBFEEDR>();
	register_ptr_to_python<LIVEDATA>();

	return_value_policy<copy_const_reference> ccr;

	class_<blbcon>("blbcon","Bloomberg connection manager")
		.def("connect",			&blbcon::connect,arg("PORT"),"Connect to Bloomberg API")
		.def("disconnect",		&blbcon::disconnect,"Disconnect from Bloomberg API")
		;

	//typedef blbloop_wrap<blbloop>	blbloopw;
	//class_<blbloopw, boost::noncopyable>("blbloop","Bloomberg main loop")
	//	.def("__call__",			&blbloop::start,"start loop")
	//	.def("received",			pure_virtual(&blbloop::received),"Signal the arrival of new data")
	//	.add_property("connection",	&blbloop::get_connection, &blbloop::set_connection)
	//		.add_property("buffer",		&blbloop::get_buffer,"Return the data buffer")
	//	;

	class_<livedata>("livedata","live data",init<optional<qm_real,qm_real,qm_real,qm_real,qm_real> >())
		.def("__str__",			&livedata::tostring)
		.def("__repr__",		&livedata::tostring)
		.add_property("last",	&livedata::get_last, &livedata::set_last)
		.add_property("mid",	&livedata::get_mid)
		.add_property("bid",	&livedata::get_bid, &livedata::set_bid)
		.add_property("ask",	&livedata::get_ask, &livedata::set_ask)
		.add_property("open",	&livedata::get_open, &livedata::set_open)
		.add_property("volume",	&livedata::get_volume, &livedata::set_volume)
		.def_pickle(livedata_pickle_suite())
		;

	class_<blbFeedp>("BlbFeedBase", "Base Bloomberg feed object", no_init)
		.def("__str__",             make_function(&blbFeedp::ticker,ccr))
		.def("__repr__",            make_function(&blbFeedp::ticker,ccr))
		.add_property("ticker",     make_function(&blbFeedp::ticker,ccr),"Feed ticker")
		.add_property("reqid",      &blbFeedp::reqid,"Request ID")
		;

    class_<blbp, boost::noncopyable>("blb", "Handle to Bloomberg API", no_init)
		.def("live",            &blbp::get_live_feed,arg("ticker"),"subscribe to a live feed")
		.def("history",			&blbp::get_hist_feed,args("ticker","startDate","endDate","fields"),"Daily History Request")
		.def("static",			&blbp::get_data_feed,args("ticker","fields"),"Static Data Request")
		.add_property("connection",	&blbp::get_connection,"Connection handler")
		.def("response",		&blbp::responce,"Decode the data buffer")
		.def("clear",			&blbp::clear,"Clear the Handler")
		;

	class_<blbfeedr>("BlbFeedReturn", "Base Bloomberg feed object", no_init)
		.add_property("data",      &blbfeedr::get_data,"data")
		;

	doblbfeed<object,LIVEDATA>("liveBlbFeed");
	doblbfeed<object,qm_list>("histBlbFeed");

	def("blb", &blbp::create, arg("RateFactoryObject"));
#ifdef BB_USING_DLL
	def("fields",			&blbp::fields<boost::python::dict,qm_list>);
#endif //	BB_USING_DLL
}


QM_NAMESPACE_END2


