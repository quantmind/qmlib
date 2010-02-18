//
//
/// \file
/// \brief blomberg API wrapper code
/// \ingroup python
///
///	Set	BB_USING_DLL to compile with bloomberg dll
/// Set USE_BOOST_THREAD to compile with boost thread
///
/// BB_PLATFORM_WINDOWS_NT ?
///
///


#ifndef   __BLOOMBERG_QM_HPP__
#define   __BLOOMBERG_QM_HPP__


//#include <qmlib/ifeed.hpp>
#include <qmlib/corelib/templates/observer.hpp>
#include <qmlib/corelib/templates/timeserie.hpp>
#include <qmlib/ilog.hpp>
#include <qmlib/buffer.hpp>
#include <bbapi.h>

#ifdef	USE_BOOST_THREAD
#include <boost/thread/mutex.hpp>
#include <qmlib/corelib/tools/thread.hpp>
#endif	//	USE_BOOST_THREAD


QM_NAMESPACE2(bloomberg)


void blb_wrap();

#define BLP_PORT         8194
#define REQUEST_TIMEOUT  300
#define BLB_BUF_SIZE     2048
#define BLB_ID_SIZE      4

class livedata  {
public:
	livedata(qm_real la=0.,
			 qm_real bi=0.,
			 qm_real as=0.,
			 qm_real op=0.,
			 qm_real vo=0.):m_last(la),m_bid(bi),m_ask(as),m_open(op),m_volume(vo){}
	qm_string tostring() const {return "livedata: last " + object_to_string(m_last);}

	qm_real get_last()   const {return m_last;}
	qm_real get_mid()    const;
	qm_real get_bid()    const {return m_bid;}
	qm_real get_ask()    const {return m_ask;}
	qm_real get_open()   const {return m_open;}
	qm_real get_volume() const {return m_volume;}

	void set_last(qm_real v)   {m_last = v;}
	void set_bid(qm_real v)    {m_bid = v;}
	void set_ask(qm_real v)    {m_ask = v;}
	void set_open(qm_real v)   {m_open = v;}
	void set_volume(qm_real v) {m_volume = v;}
protected:
	qm_real m_last, m_bid, m_ask, m_open, m_volume;
};
typedef QM_SMART_PTR(livedata) LIVEDATA;


/** \brief Blooomberg Feed
*   \ingroup python_bloomberg
*	
*	The feed is an observable object so that observers can be updated when
*   updated are received
*/
class blbFeedBase  {
public:
	typedef qm_buffer<long>	fieldlisttype;

	const qm_string&	ticker()     const {return m_ticker;}
	long				reqid()      const {return m_req_id;}
	long				req_mon_id() const {return m_req_mon_id;}
    long				tick_id()    const {return m_tick_id;}
	
	long				m_req_mon_id;
    long				m_tick_id;

	fieldlisttype	    fields;
	
	blbFeedBase(const qm_string& ticker, qm_long req_id):
		m_req_mon_id(0),m_tick_id(0),m_ticker(ticker),m_req_id(req_id){}

protected:
	void initdata(){}
	qm_string		 m_ticker;
	long			 m_req_id;
	fieldlisttype	 m_fields;
};

template<class F, class D>
class blbFeed : public blbFeedBase  {
public:
	typedef F		local_type;
	typedef D		data_type;

	blbFeed(const qm_string& ticker, qm_long req_id):blbFeedBase(ticker,req_id){initdata();}

	data_type			get_data()	 const {return m_data;}
	void				set_data(data_type d) {m_data = d;}
	int					get_datatype() {return 0;}

	local_type			get_localtype() const {return m_lt;}
	void				set_localtype(local_type v) {m_lt = v;}
protected:
	void initdata(){}
	local_type		 m_lt;
	data_type		 m_data;
};



/** \brief Bloomberg data return type
 * \ingroup bloomberg
 *
 * Holder class for data streaming from bloomberg api
 */
template<class T>
class blbret  {
public:
	blbret(T d):m_data(d){}
	T	get_data() const {return m_data;}
protected:
	T m_data;
};


class blbcon {
public:
	blbcon():m_connection(0),m_id(4),m_stop(0){}
	~blbcon(){disconnect();}
	int				connect(unsigned port);
	int				disconnect();
	bb_connect_t*   connection() const {return m_connection;}
	int				get_stop() const {return m_stop;}
	void			set_stop(int v) {m_stop = v;}
	SOCKET			bb_sock;
protected:
	bb_connect_t*		m_connection;
	qm_buffer<int4>		m_id;
	int					m_stop;
	void     SecurityConnection();
};
typedef QM_SMART_PTR(blbcon) BLBCON;






/** \brief Bloomberg API wrapper class
 * \ingroup python_bloomberg
 */
template<class F, class LR, class HR, class L>
class blb : boost::noncopyable {
public:
	typedef F										BLBFEEDRD;
	typedef blbret<BLBFEEDRD>						blbfeedr;
	typedef QM_SMART_PTR(blbfeedr)					BLBFEEDR;

	typedef LR										livedata_type;
	typedef HR										histdata_type;

	typedef blb<F,LR,HR,L>							blb_type;
	typedef QM_SMART_PTR(blb_type)					BLB;

	typedef blbFeed<L,livedata_type>				blb_live_feed_type;
	typedef blbFeed<L,histdata_type>				blb_hist_feed_type;

	typedef QM_SMART_PTR(blb_live_feed_type)		BLBLIVEFEED;
	typedef QM_SMART_PTR(blb_hist_feed_type)		BLBHISTFEED;

	typedef std::map<qm_long,BLBLIVEFEED>			id_container;
	typedef std::map<qm_long,BLBHISTFEED>			id_hist_container;
	typedef std::list<BLBLIVEFEED>					live_list;
	typedef	QM_SMART_PTR(live_list)					LIVE_LIST;

	typedef void_buffer								buffertype;
	typedef qm_buffer<long>							fieldlisttype;				

	typedef bb_msg_headerx_t						bb_header_type;
	typedef bb_decode_headerx_t						bb_decoder_header_type;
	typedef bb_msg_monid_t							bb_monid_type;
	typedef bb_msg_tickx_t							bb_tick_type;
	typedef bb_msg_mhistory_t						bb_history_type;

    ~blb(){}
	static BLB create(BLBCON c) {return BLB(new blb(c));}

    BLBLIVEFEED     get_live_feed(const qm_string& ticker);
	BLBHISTFEED     get_hist_feed(const qm_string& ticker, long startDate, long endDate, const fieldlisttype& fields);
	BLBHISTFEED     get_data_feed(const qm_string& ticker, const fieldlisttype& fields);
	void			clear();

#ifdef	BB_USING_DLL
	template<class D, class L>
	static L		 fields();
#endif	//	BB_USING_DLL

	BLBCON   get_connection() const {return m_connection;}
	//void	 set_connection(BLBCON con) {m_connection = con;}

	BLBFEEDR  responce();
private:
	blb(BLBCON);
	buffertype								 m_buffer;
	qm_buffer<int4>							 m_secTypeList;
	qm_buffer<char>							 m_secName;
	id_container					         m_request_monitor_id;
    id_container					         m_live_tick_id;
	id_hist_container						 m_hist_ids;
	BLBCON									 m_connection;
	fd_set									 read_set, exec_set;
	BLBFEEDR								 m_none;

	static bool								 m_loaded_fields;

	BLBFEEDR	  Decode();
    BLBLIVEFEED   DecodeHeader(bb_header_type* h);
	BLBLIVEFEED   startTickMonitor(BLBLIVEFEED rat, bb_decoder_header_type* p);
	void	      HandleMonitor(bb_monid_type* m);

    LIVE_LIST     UpDateLiveData(bb_tick_type* t);

    BLBHISTFEED   DecodeHistory(bb_history_type* t);
	BLBHISTFEED	  fillData(BLBHISTFEED qp, bb_history_type* t);
	BLBHISTFEED   DecodeStaticData(bb_msg_fieldsx_t *t);
    //
    double   BB_PTOS(double x){return x == BB_VAL_MISSING ? 0 : x;}

//#	ifdef	USE_BOOST_THREAD
//    QM_SMART_PTR(boost::thread)  m_thread;
//    static void do_thread(void* param);
//	boost::mutex m_mutex;
//#	else
//    static unsigned __stdcall do_thread(void* param);
//#	endif	//	USE_BOOST_THREAD
};


#include<qmlib/bloomberg/blb_impl.hpp>
#include<qmlib/bloomberg/con_impl.hh>
#include<qmlib/bloomberg/blbloop.hpp>


QM_NAMESPACE_END2
  
  
#endif  //  __BLOOMBERG_QM_HPP__
