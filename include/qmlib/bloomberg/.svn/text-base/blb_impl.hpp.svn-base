

template<class F, class LR, class HR, class L>
inline blb<F,LR,HR,L>::blb(BLBCON c):m_connection(c),
						 			 m_secTypeList(1),m_secName(32) {
	QM_REQUIRE(m_connection,"Bloomberg connection is null");
	for(unsigned i=0;i<m_secTypeList.size();++i)
		m_secTypeList[i] = 730;
	//for(unsigned i=0;i<m_fieldList.size();++i)
	//	m_fieldList[i] = i;
}


template<class F, class LR, class HR, class L>
inline void blb<F,LR,HR,L>::clear()  {
	m_request_monitor_id.clear();
	m_live_tick_id.clear();
	m_hist_ids.clear();
	m_loaded_fields = false;
}

/*
#ifdef	USE_BOOST_THREAD
template<class F, class LR, class HR>
inline void blb<F,LR,HR>::do_thread(void* param)  {
    static_cast<blb*>(param)->response_loop();
}
#else
template<class F, class LR, class HR>
inline unsigned __stdcall blb<F,LR,HR>::do_thread(void* param) {
	static_cast<blb*>(param)->response_loop();
	return 1;
}
#endif	//	USE_BOOST_THREAD
*/


//====================================================================
//    Create a Live Data Request
//====================================================================
template<class F, class LR, class HR, class L>
inline typename blb<F,LR,HR,L>::BLBLIVEFEED
blb<F,LR,HR,L>::get_live_feed(const qm_string& ticker)  {

	char* tik = (char*)ticker.c_str();
      
	// The header ID
	//m_log->info("Send connection request to live feed "+ticker);
	qm_long header_id = bb_getheaderx(m_connection->connection(),
	                                  BHeaderENHANCEDSEARCH | EXTENDED_HEADER,
		                              0, 1, tik);
	BLBLIVEFEED rat(new blb_live_feed_type(ticker,header_id));
	m_request_monitor_id[header_id] = rat;
    return rat;
}


//    Create an Hystorical Data Request
template<class F, class LR, class HR, class L>
inline typename blb<F,LR,HR,L>::BLBHISTFEED
blb<F,LR,HR,L>::get_hist_feed(const qm_string& ticker, long startDate, long endDate,
							  const typename blb<F,LR,HR,L>::fieldlisttype& fields)  {
	QM_REQUIRE(m_connection->connection(),"Not connected to API. Connect please.");
	char* tik = (char*)ticker.c_str();
	//m_fieldList[0] = 1;
	//m_fieldList[0] = 2;
	//m_fieldList[0] = 3;
	//strcpy(m_secName, tik);
	long NF = fields.size();
	
	long rID = bb_mgethistoryx(
		// connection object
		m_connection->connection(),
		// number of securities
		1,
		// security keys (32 bytes each)
		//m_secName,
		tik,
		// key types, long*
		m_secTypeList,
		// Start date YYYYMMDD
		startDate,
		// eND date YYYYMMDD
		endDate,
		// number of fields ( <= 10 )
		NF,
		// array of Requested field ids
		fields.ptr(),
		// Various ORed flags
		BHistoryxDAILY);
		//						  BHistoryxDAILY | BHistoryxALLCALDAYS);

	QM_REQUIRE(rID>=0,"Error from history request. Bad request ID");

	BLBHISTFEED hf(new blb_hist_feed_type(ticker,rID));
	hf->fields.copy(fields);
	m_hist_ids[rID] = hf;
	return hf;
}



template<class F, class LR, class HR, class L>
inline typename blb<F,LR,HR,L>::BLBHISTFEED
blb<F,LR,HR,L>::get_data_feed(const qm_string& ticker,
							  const typename blb<F,LR,HR,L>::fieldlisttype& fields)  {
	QM_REQUIRE(m_connection->connection(),"Not connected to API. Connect please.");
	char* tik = (char*)ticker.c_str();
	long NF = fields.size();
	long rID = bb_getdatax(
		// connection object
		m_connection->connection(),
		// number of securities
		1,
		// key types, long*
		m_secTypeList,
		// security keys (32 bytes each)
		tik,
		// number of fields ( <= 10 )
		NF,
		// array of Requested field ids
		fields.ptr(),
		0,
		m_secTypeList,
		tik);

	QM_REQUIRE(rID>=0,"Error from static data request. Bad request ID");
	BLBHISTFEED hf(new blb_hist_feed_type(ticker,rID));
	hf->fields.copy(fields);
	m_hist_ids[rID] = hf;
	return hf;
}



//====================================================================
// Got the header, now start monitoring the ticks
//====================================================================
template<class F, class LR, class HR, class L>
inline typename blb<F,LR,HR,L>::BLBLIVEFEED
blb<F,LR,HR,L>::startTickMonitor(typename blb<F,LR,HR,L>::BLBLIVEFEED qp,
  							     typename blb<F,LR,HR,L>::bb_decoder_header_type* p)  {
	livedata* q = qp->get_data().get();

    q->set_bid(BB_PTOS(p->price_bid));
    q->set_ask(BB_PTOS(p->price_ask));
    q->set_last(BB_PTOS(p->price_last));
    q->set_open(BB_PTOS(p->open_interest));
    q->set_volume(BB_PTOS(p->volume_total));

    char* tik    = (char*)qp->ticker().c_str();
    qm_long rID  = bb_tickmntrx(m_connection->connection(), 1, tik, 1);
	qp->m_req_mon_id = rID;
	
	// Add a new tick id to the dictionary
    m_request_monitor_id[rID] = qp;
	return qp;
}

//==================================================================
// Receive response from header request
//==================================================================
template<class F, class LR, class HR, class L>
inline typename blb<F,LR,HR,L>::BLBLIVEFEED
blb<F,LR,HR,L>::DecodeHeader(typename blb<F,LR,HR,L>::bb_header_type* h)  {
    if(h->comm_header.num_items != 1) return BLBLIVEFEED();
    qm_long id = h->comm_header.request_id;
    id_container::const_iterator rat = m_request_monitor_id.find(id);

    QM_REQUIRE(rat != m_request_monitor_id.end(),"Received request to a header id not requested!!!");
	BLBLIVEFEED qp = rat->second;

    bb_decode_headerx_t* p = &h->sec_header[0];
    switch(p->status) {
      case -1: break; //m_log->critical(q->ticker() + " is an unknown security");   break;
      case -2: break; //m_log->critical(q->ticker() + " cannot get header");        break;
      case -3: break; //m_log->critical(q->ticker() + " is an invalid security");   break;
      case -4: break; //m_log->critical(q->ticker() + " security not in Database"); break;
	  case  0: return this->startTickMonitor(qp,p);
    }
    m_request_monitor_id.erase(id);
    return BLBLIVEFEED();
}


//=============================================================================================
//    Verify the request ID, then save the monitor IDs
//		This function is called after startTickMonitor
//=============================================================================================
template<class F, class LR, class HR, class L>
inline void blb<F,LR,HR,L>::HandleMonitor(typename blb<F,LR,HR,L>::bb_monid_type* m)  {

	if(m->comm_header.num_items != 1)  {
		//m_log->error("Monitor header with more than one item");
		return;
	}
	qm_long rID = m->comm_header.request_id;
	qm_long mID = m->mon_id[0];
	BLBLIVEFEED qp	= m_request_monitor_id[rID];
	if(qp) m_live_tick_id[mID] = qp;
}


//=========================================================================
//
// We just got some updates.  Make sure we've already got the header
// so we have something to update.  If not, just ignore the tick.
// Then, Loop through the ticks, apply each one to the corresponding 
// security header, then print out the updated header.
//
//=========================================================================
template<class F, class LR, class HR, class L>
inline typename blb<F,LR,HR,L>::LIVE_LIST
blb<F,LR,HR,L>::UpDateLiveData(typename blb<F,LR,HR,L>::bb_tick_type* t)  {

    int itms = t->comm_header.num_items;

	LIVE_LIST		ret(new live_list);
	if(itms <= 0) return ret;

	live_list*      pet = ret.get();

#	ifdef	USE_BOOST_THREAD
	//boost::mutex::scoped_lock scoped_lock(m_mutex);
#	endif	//	USE_BOOST_THREAD

	qm_long         idm;
	id_container    tmp;
	LIVEDATA		ld;
//
//. Now update the appropriate fields in the header, depending on the tick type
    for(int i=0;i<itms;i++)  {
		idm = t->tick_data[i].mon_id;
		BLBLIVEFEED qp = tmp[idm];
		if(!qp) {
			qp = m_live_tick_id[idm];
			if(!qp) continue;
			tmp[idm] = qp;
			pet->push_back(qp);
		}
		ld = qp->get_data();

		switch (t->tick_data[i].action)  {
			case bTickTRADE:          ld->set_last(t->tick_data[i].data.TRADE.price);     break;
			case bTickBID:            ld->set_bid(t->tick_data[i].data.BID.price);        break;
			case bTickASK:            ld->set_ask(t->tick_data[i].data.ASK.price);        break;
			case bTickOPEN_INTEREST : ld->set_open(t->tick_data[i].data.OPEN.price);      break;
			case bTickVOLUME        : ld->set_volume(t->tick_data[i].data.VOLUME.volume); break;
			default: continue;
		}
	}
    return ret;
}



template<class F, class LR, class HR, class L>
inline typename blb<F,LR,HR,L>::BLBHISTFEED
blb<F,LR,HR,L>::DecodeHistory(typename blb<F,LR,HR,L>::bb_history_type* t)  {
	qm_long id = t->comm_header.request_id;
	BLBHISTFEED qp = m_hist_ids[id];
	if(qp)  {
		m_hist_ids.erase(id);
		return this->fillData(qp,t);
	}
	else
		return qp;
}




template<class F, class LR, class HR, class L>
inline typename blb<F,LR,HR,L>::BLBHISTFEED
blb<F,LR,HR,L>::fillData(typename blb<F,LR,HR,L>::BLBHISTFEED qp, typename blb<F,LR,HR,L>::bb_history_type* t)  {

	typedef bb_decode_mhistory_t				   	  bb_decode_type;
	typedef bb_decode_history_t						  bb_single_history;

	long numKeys	 = t->num_of_securities;
	long totNumItems = t->comm_header.num_items;
	long numFields   = t->num_of_fields;
	long secStart    = numFields + 1;
	long   dte;
	double val;

	bb_single_history   *hist;

	if(numKeys != 1)  {
		//m_log->critical("Number of securities should be 1");
		return BLBHISTFEED();
	}

	histdata_type ffil;	  // Holder for field ids
	histdata_type data;   // Data holder
	histdata_type datad;  // holder for dates

	data.append(ffil);	// append field ids to data holder
	data.append(datad); // append dates to data holder

	// Pointer to start of Security Error Codes
	long  *pSecurityError  = &(t->mhistory_data[0]);

	// Pointer to start of number of points per field
	long *pNumPts          = &(t->mhistory_data[numKeys]);

	bb_decode_type *pData = (bb_decode_type*) t->mhistory_data[secStart];
	
	// Loop around fields
	for(int f=0;f<numFields;f++)  {
		unsigned npoins = pNumPts[f];
		histdata_type dataf;
		ffil.append(qp->fields.get_slow(f));
		data.append(dataf);
		hist = pData->mhist_data;

		// loop around data points
		for(unsigned i=0;i<npoins;i++)  {
			dte = hist[i].date;
			val = hist[i].value;

			if(f==0) datad.append(dte);

			if(val == BB_VAL_MISSING)
				dataf.append("#NA");
			else
				dataf.append(val);
		}
		pData += npoins;
	}
	qp->set_data(data);
	return qp;
}



template<class F, class LR, class HR, class L>
inline typename blb<F,LR,HR,L>::BLBHISTFEED
blb<F,LR,HR,L>::DecodeStaticData(bb_msg_fieldsx_t *t) {
    char *p;
	int lp;
	int i;
	int n;
    
	qm_long id = t->comm_header.request_id;
	BLBHISTFEED qp = m_hist_ids[id];
	if(qp)
		m_hist_ids.erase(id);
	else
		return qp;
	int iNumOfFields = t->NumFields;

	histdata_type data;   // Data holder
    /*
    ** Get the pointer to the first security fields into p.  The field_ptr array will
    ** have the pointers to the fields for each security in the order we 
    ** requested them.  For each security, we will get null-terminated 
    ** strings with the field data, one after another in the order we 
    ** requested the fields.
    */

	for (i=0; i<t->comm_header.num_items; i++) {
		p = t->field_ptr[i];

		for (n=0; n<iNumOfFields; n++) {
			qm_string sp(p);
			data.append(sp);
			lp = strlen(p)+1;
			//if (is_Bulk_field(piFieldList[n])) {
			//	printf ("\tField: 0x%X  Bulk Data:\n", piFieldList[n]);
			//	decodeBulkData (p);
			//}
			//else {
				//printf ("\tField: 0x%X \t=\t%s\n", piFieldList[n],p);
			//}
			p += lp;
		}
	}
	qp->set_data(data);
	return qp;
}




/*
template<class F, class LR, class HR, class L>
template<class P>
inline P blb<F,LR,HR,L>::liverates() const {
	P l;
	for(rate_container::const_iterator it=m_live_rates.begin();it!=m_live_rates.end();++it)  {
		l.append(it->second);
	}
	return l;
}
*/
 

#ifdef	BB_USING_DLL

template<class F, class LR, class HR, class L>
template<class D, class P>
inline P  blb<F,LR,HR,L>::fields()  {
	P l;
#ifdef WIN32
	if(!m_loaded_fields)  {
		int rcode = bb_load_datadictx(NULL);
		if(rcode == ExitFAILOPENFILE)  {
			//m_log->warning("Could not load bbfields.tbl using bb_load_datadictx()");
			return l;
		}
		else  {
			//m_log->info("Loaded bbfields.tbl into memory.");
			m_loaded_fields = true;
		}
	}
#else
	m_log->warning("Only available under windows");
	return l;
#endif
	for(int f = 0;f<MAX_Field;f++)  {
		D d;
		d["Id"]     = bbFieldArrayx[f].FieldId;
		d["Name"]   = bbFieldArrayx[f].FieldMnemonic;
		d["Format"] = bbFieldArrayx[f].FieldFormat;
		l.append(d);
	}
	return l;
}
#endif	//	BB_USING_DLL


