


inline qm_real livedata::get_mid() const  {
	return m_last;
}

inline void blbcon::SecurityConnection()  {
    Display* disp = 0;
    bb_identify(disp,m_id);
    bb_setuser(m_connection,m_id);
}


/// Return codes
/// 1  already disconnected, do nothing
/// 0  disconnected ok
/// -1 failed to disconnect
inline int blbcon::disconnect()  {
    // Not connected, return
	if(m_connection == 0) return 1;

//	m_stop = 1;
//	this->shutdown();
//#ifdef	USE_BOOST_THREAD
    // close the thread
//	m_thread->join();
    //m_thread = QM_SMART_PTR(boost::thread)();
//#endif	//	USE_BOOST_THREAD

	if(bb_disconnect(m_connection) == ExitOK)  {
		m_connection = 0;
		return 0;
	}
		//m_log->info("Disconnected");
	//m_log->error("Failed Disconnecting from Bloomberg API");
    m_connection = 0;
	return -1;
}


/// Return codes
/// 1  already connected
/// 0  started ok
/// -1 winsock error
/// -2 connection failed
inline int blbcon::connect(unsigned port)  {
    //
    // Already connected
	if(m_connection) return 1;

#ifdef WIN32
    WSADATA wver;
    WORD i = MAKEWORD(1,1);
    int rcode = WSAStartup(i, &wver);
	if(rcode != 0 || LOBYTE(wver.wVersion) != 1 || HIBYTE(wver.wVersion) !=1)
		return -1;
#endif

    m_connection = bb_connect(port);
    
    //m_Connection = bb_connect_asynch(BLP_PORT);
    //
	if(m_connection)  {
		this->SecurityConnection();
//#	ifdef	USE_BOOST_THREAD
//		m_thread = QM_SMART_PTR(boost::thread)(new boost::thread(thread_adapter(&blb::do_thread, this)));
//#	else
//		_beginthreadex(0,0,do_thread,(void*)this,0,0);
//#	endif	//	USE_BOOST_THREAD
		bb_sock = bb_getsocket(m_connection);
		return 0;
	}
	else
		return -2;
}