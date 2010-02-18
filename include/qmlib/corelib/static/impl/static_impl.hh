

#ifndef		__STATIC_IMPL_HH__
#define		__STATIC_IMPL_HH__





QM_NAMESPACE


/*
inline const qm_string&    ccy::twolettercode() const {return m_twolettercode;}
inline const qm_string&    ccy::fixedCoupFred() const {return m_fixedCoupFreq;}
inline const qm_string&    ccy::floatCoupFred() const {return m_floatCoupFreq;}
inline qm_uns_char         ccy::order()         const {return m_order;}
inline qm_uns_char         ccy::rounding()      const {return m_rounding;}
inline qm_uns_char         ccy::cashDelay()     const {return m_cashdelay;}
inline qm_uns_char         ccy::swapDelay()     const {return m_swapdelay;}
inline const qm_string&    ccy::isocode()       const {return m_isocode;}
inline DC 		           ccy::fixedDC()       const {return daycounter::get(m_fixedDC);}
inline DC       		   ccy::floatDC()       const {return daycounter::get(m_floatDC);}
inline INDEX  			   ccy::rateIndex()	 	const {return index::get(m_defIndex);}
inline bool                ccy::iscurrency()    const {return m_iscurrency;}
inline const qm_string&    ccy::defaultTC()     const {return m_defaultTC;}
*/

    
inline period parsefrequency(const qm_string& freq, const period& te)  {
	if(freq.length() == 1) return charFrequencyToPeriod(freq[0]);
    qm_strings fs = qmstring::split(freq,";");
    QM_REQUIRE(fs.size() == 2,"Unrecognized frequency string "+freq);
    for(qm_strings::const_iterator it = fs.begin();it!=fs.end();++it)  {
    	qm_uns_int len = it->length();
        QM_REQUIRE(len >= 6,"Unrecognized frequency string "+freq);
        qm_uns_int ip = it->find_first_of("123456789");
        QM_REQUIRE(ip < len,"Unrecognized frequency string "+freq);
        period pe(it->substr(ip,len-ip-1));
        //
        if(it->find('>')<len)  {
          if(it->find('=')<len && te >= pe) return charFrequencyToPeriod((*it)[0]);
          else if(te > pe) return charFrequencyToPeriod((*it)[0]);
          else continue;
        }
        else if(it->find('<')<len)  {
          if(it->find('=')<len && te <= pe) return charFrequencyToPeriod((*it)[0]);
          else if(te < pe) return charFrequencyToPeriod((*it)[0]);
          else continue;
        }
        else QM_FAIL("Unrecognized frequency string "+freq);
    }
    QM_FAIL("Unrecognized frequency string "+freq);
}





namespace  {


/*
inline ccys generate_ccys()  {
	ccys cc("Day counter inline database");
	CCY 	cur;
    cur = CCY(new ccy("EUR","Euro",              "EU","TGT","A",               "Q(<=1y);S(>1y)",  modfoll,1,4,2,2,"30360","Act360","978","EUR-EURIBOR-TELERATE"));
    cc.add(cur->code(),cur);
    cur = CCY(new ccy("GBP","British Pound",     "BP","LON","A(<=1y);S(>1y)",  "Q(<=1y);S(>1y)",  modfoll,2,4,0,0,"Act365","Act365","826","GBP-LIBOR-BBA"));
    cc.add(cur->code(),cur);
    cur = CCY(new ccy("AUD","Australian Dollar", "AD","SID","Q(<=3y);S(>3y)",  "Q(<=3y);S(>3y)",  modfoll,3,4,0,0,"Act365","Act365","036","AUD-BBR-BBSW"));
    cc.add(cur->code(),cur);
    cur = CCY(new ccy("NZD","New Zealand Dollar","ND","AUC","S",               "Q",               modfoll,4,4,0,2,"Act365","Act365","554","NZD-BBR-FRA"));
    cc.add(cur->code(),cur);
    cur = CCY(new ccy("USD","U.S. Dollar",       "US","NY", "A(<=18M);S(>18M)","Q",               modfoll,5,0,2,2,"30360","Act360","840","USD-LIBOR-BBA"));
    cc.add(cur->code(),cur);
    cur = CCY(new ccy("CAD","Canadian Dollar",   "CD","TOR","S",               "Q",               modfoll,6,4,2,2,"Act365","Act365","124","CAD-BA-CDOR"));
    cc.add(cur->code(),cur);
    cur = CCY(new ccy("CHF","Swiss Franc",       "SZ","ZUR","A",               "Q(<=1Y);S(>1Y)",  modfoll,7,4,2,2,"30360","Act360","756","CHF-LIBOR-BBA"));
    cc.add(cur->code(),cur);
    cur = CCY(new ccy("NOK","Norwegian Krone",   "NK","OSL","A",               "S",               modfoll,8,4,2,2,"30360","Act360","578"));
    cc.add(cur->code(),cur);
    cur = CCY(new ccy("SEK","Swedish Krone",     "SK","STO","A",               "Q",               modfoll,9,4,2,2,"30360","Act360","752"));
    cc.add(cur->code(),cur);
    cur = CCY(new ccy("TRY","Turkish Lira",      "TL","IST","A",               "Q",              modfoll,19,4,0,0,"Act360","Act360","949"));
    cc.add(cur->code(),cur);
    cur = CCY(new ccy("JPY","Japanese Yen",      "JY","TOK","S",               "S",              modfoll,20,2,2,2,"Act365","Act360","392"));
    cc.add(cur->code(),cur);
	return cc;
}
*/

inline tcs generate_tcs()  {
	tcs db("Trading centre inline database");
	TC t;
	t = TC(new NewYork());
	db.add(t->code(),t);
	t = TC(new Target());
	db.add(t->code(),t);
	t = TC(new London());
	db.add(t->code(),t);
	t = TC(new Zurich());
	db.add(t->code(),t);
	t = TC(new Oslo());
	db.add(t->code(),t);
	t = TC(new Stockholm());
	db.add(t->code(),t);
	t = TC(new Copenhagen());
	db.add(t->code(),t);
	t = TC(new Reykjavik());
	db.add(t->code(),t);
	t = TC(new Tokyo());
	db.add(t->code(),t);
	t = TC(new Sidney());
	db.add(t->code(),t);
	t = TC(new Auckland());
	db.add(t->code(),t);
	t = TC(new Istanbul());
	db.add(t->code(),t);
	t = TC(new Johannesburg());
	db.add(t->code(),t);
	t = TC(new Moscow());
	db.add(t->code(),t);
	t = TC(new Toronto());
	db.add(t->code(),t);
	t = TC(new BuenosAires());
	db.add(t->code(),t);
	t = TC(new SaoPaulo());
	db.add(t->code(),t);
	t = TC(new MexicoCity());
	db.add(t->code(),t);
	return db;
}

/*
inline indices generate_indices() {
	indices db;
	INDEX id;
	id = INDEX(new index("EUR-EURIBOR-TELERATE","EUR-EURIBOR","TGT"));
	db.add(id->code(),id);
	id = INDEX(new index("GBP-LIBOR-BBA","GBP-LIBOR","LON"));
	db.add(id->code(),id);
	id = INDEX(new index("AUD-BBR-BBSW","GBP-LIBOR","LON"));
	db.add(id->code(),id);
	id = INDEX(new index("NZD-BBR-FRA","GBP-LIBOR","LON"));
	db.add(id->code(),id);
  	id = INDEX(new index("USD-LIBOR-BBA","USD-LIBOR","LON"));
  	db.add(id->code(),id);
  	id = INDEX(new index("CAD-BA-CDOR","USD-LIBOR","LON"));
  	db.add(id->code(),id);
  	id = INDEX(new index("CHF-LIBOR-BBA","CHF-LIBOR","LON"));
  	db.add(id->code(),id);
  	return db;
}


inline contracts generate_contracts()  {
    qm_string lif = "Euronext-Liffe";
    qm_string cme = "CME - Chicago Mercantile Exchange";
    qm_string nym = "NYMEX - New York Mercantile Exchange";
    qm_string tfx = "TFX - Tokyo Financial Exchange";
    
    contracts exs;
	CONTRACT ex;
	ex = CONTRACT(new exchange("ER","3M Euro (EURIBOR) Future","EUR","TGT",imm_3m_irfuture,lif,1000000,0.005,12.5,2));
	exs.add(ex->code(),ex);
	ex = CONTRACT(new exchange("ED","3M EuroDollar (LIBOR) Future","USD","NY",imm_3m_irfuture,cme,1000000,0.005,12.5,2));
	exs.add(ex->code(),ex);
	ex = CONTRACT(new exchange("L_","3M ShortSterling (LIBOR) Future","GBP","LON",imm_3m_irfuture,lif,500000,0.01,12.5,0));
	exs.add(ex->code(),ex);
	ex = CONTRACT(new exchange("ES","3M EuroSwiss (LIBOR) Future","CHF","LON",imm_3m_irfuture,lif,500000,0.01,12.5,2));
	exs.add(ex->code(),ex);
	return exs;
}


inline ccypairs generate_ccypairs()  {
	ccypairs cc("Currency Pairs inline database");
	CCYPAIR 	cur;
    cur = CCYPAIR(new ccypair("EUR","USD","Euro",2,"NY"));
    cc.add(cur->code(),cur);
    cur = CCYPAIR(new ccypair("GBP","USD","Cable",2,"NY,LON"));
    cc.add(cur->code(),cur);
    cur = CCYPAIR(new ccypair("USD","JPY","DollarYen",2,"NY"));
    cc.add(cur->code(),cur);
	return cc;
}
*/


static const tcs  		c_tcs  		 = generate_tcs();
//static const indices	c_indices 	 = generate_indices();
//static const ccys 		c_ccys 		 = generate_ccys();
//static const contracts 	c_contracts  = generate_contracts();
//static const ccypairs 	c_ccypairs   = generate_ccypairs();

}

inline TC tc::get(const qm_string& cod)  {
	return c_tcs.get(cod);
}

template<class L>
inline L tc::keys()  {
	return c_tcs.keys<L>();
}

/*
inline INDEX index::get(const qm_string& cod)  {
	return c_indices.get(cod);
}

template<class L>
inline L index::keys()  {
	return c_indices.keys<L>();
}


inline CONTRACT contract::get(const qm_string& cod)  {
	return c_contracts.get(cod);
}

template<class L>
inline L contract::keys()  {
	return c_contracts.keys<L>();
}


inline CCY ccy::get(const qm_string& cod)  {
	return c_ccys.get(cod);
}

template<class L>
inline L ccy::keys()  {
	return c_ccys.keys<L>();
}

inline CCYPAIR ccypair::get(const qm_string& cod)  {
	return c_ccypairs.get(cod);
}

template<class L>
inline L ccypair::keys()  {
	return c_ccypairs.keys<L>();
}


inline CCY contract::currency() const  {
  return ccy::get(m_cur);
}
*/
    
QM_NAMESPACE_END
 
 
#endif	//	__STATIC_IMPL_HH__
 
