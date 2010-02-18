



template<class F, class LR, class HR, class L>
inline typename blb<F,LR,HR,L>::BLBFEEDR
blb<F,LR,HR,L>::responce()  {

    struct   timeval timeout = {1, 0};
	if(!m_connection->connection()) return m_none;

	SOCKET	 bb_sock = m_connection->bb_sock;

//	build select masks with our socket in them
	FD_ZERO(&read_set);
	FD_ZERO(&exec_set);
	FD_SET((int) bb_sock, &read_set);
	FD_SET((int) bb_sock, &exec_set);
//
//
//..We care about the socket being readable or having an exception,
//..not about it being writeable, so the third paramter of select is null
	int rcode = select(bb_sock + 1, &read_set, 0, &exec_set, &timeout);
	if(rcode==0) return m_none;

#ifdef WIN32
	if(rcode == SOCKET_ERROR) QM_FAIL("Error from select.");
#else
    if(rcode == -1)
		m_log->error("Bloomberg Loop: error from select.");
#endif

	if(FD_ISSET((int)  bb_sock, &exec_set))
		QM_FAIL("Exeption on Bloomberg socket.");
	else  if(FD_ISSET((int) bb_sock, &read_set))
		return this->Decode();
	
	QM_FAIL("Unknown error in responce");
}


//=================================================
//
//   receive data from a Bloomberg API connection.
//   This routine should be called after select
//   indicates there is data on the socket.
//=================================================
template<class F, class LR, class HR, class L>
inline typename blb<F,LR,HR, L>::BLBFEEDR
blb<F,LR,HR,L>::Decode()  {
	void* in_use_buffer;
    int   size, code;
    
    bool  bDone = false;
	BLBFEEDRD   retl;
	BLBLIVEFEED lf;
	BLBHISTFEED hf;

    while(!bDone)  {
		size = bb_sizeof_nextmsg(m_connection->connection());

		if(size < 0)  {
			//m_log->warning("Error Receiving Data");
			break;
		}
		else if(size == BB_SVC_INCOMPLETE) {
			//m_log->warning("Incomplete Message in Receive");
			break;
		}

		//  if the message is larger than our buffer, allocate a temporary buffer
		m_buffer.Alloca(size);
		in_use_buffer = m_buffer;

		code = bb_rcvdata(m_connection->connection(), in_use_buffer, m_buffer.size());

		if(code < 0)  {
			//m_log->warning("Bloomberg API. Permission Problem.");
			break;
		}

		if(code<-1900)  {
			bDone = true;
			if(code==ExitFAILCONNECTION || code==ExitFAILRECEIVE)  {
				//m_log->warning("Error Receiving Data");
				break;
			}
		}
//
		switch(code) {


			//________________________________________ HISTORY
			case BB_SVC_MGETHISTORYX:  {
				hf = DecodeHistory((bb_history_type*)in_use_buffer);
				if(hf) retl.append(hf);
				break;
			}
			//case BB_SVC_GETHISTORYX:  {
			//	DecodeHistory((bb_msg_history_t*)in_use_buffer);
			//	break;
			//}

		    //________________________________________ STATIC DATA
			case BB_SVC_GETDATAX:  {
				hf = DecodeStaticData((bb_msg_fieldsx_t *)in_use_buffer);
			    if(hf) retl.append(hf);
				break;
			}


			//________________________________________ GOT HEADER FOR LIVE RATE
			case BB_SVC_GETHEADERX: {
				lf = DecodeHeader((bb_header_type*)in_use_buffer);
				if(lf) retl.append(lf);
				break;
			}

			case BB_SVC_TICKMONITOR:
			case BB_SVC_TICKMONITORX:
			case BB_SVC_TICKMONITOR_TYPED:
			case BB_SVC_TICKMONITOR_TYPEDX:
			case BB_SVC_TICKMONITOR_ENHANCED:  {
				HandleMonitor((bb_monid_type*)in_use_buffer);
				break;
			}

			case BB_SVC_TICKDATA: {
				LIVE_LIST ll = UpDateLiveData((bb_tick_type*)in_use_buffer);
				for(typename live_list::const_iterator it=ll->begin();it!=ll->end();++it)
					retl.append(*it);
				break;
			}

			case BB_SVC_STATUS:  {
//				    printf("STATUS Message...\n");
		        break;
			}

		 	case BB_SVC_CONNECTSUCCEEDED:  {
				//m_log->info("Successfully connected to Bloomberg API.");
				//SecurityConnection();
				break;
			}
//
			case BB_SVC_CONNECTFAILED: {
				//m_log->info("Connection to Bloomberg API Failed.");
				break;
			}

		    default:  {
				//m_log->warning("Unexpected message type.");
				break;
			}
	    }
    }
	return BLBFEEDR(new blbfeedr(retl));
}