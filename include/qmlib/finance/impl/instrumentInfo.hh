


#ifndef	__INSTRUMENT_STRINGS_QM_HPP__
#define	__INSTRUMENT_STRINGS_QM_HPP__


QM_NAMESPACE2(finance)

template<> struct InstrumentInfo<deposit_>  {
	static qm_string name()     {return "deposit";}
	static const unsigned  priority = 3;
};
template<> struct InstrumentInfo<fra_>      {
	static qm_string name() {return "FRA";}
	static const unsigned  priority = 1;
};
template<> struct InstrumentInfo<swap_>     {
	static qm_string name() {return "swap";}
	static const unsigned  priority = 2;
};
template<> struct InstrumentInfo<irfuture_>     {
	static qm_string name() {return "IRF";}
	static const unsigned  priority = 0;
};
template<> struct InstrumentInfo<ois_>      {
	static qm_string name() {return "OIS";}
	static const unsigned  priority = 1;
};
template<> struct InstrumentInfo<option_>      {
	static qm_string name() {return "Option";}
};

QM_NAMESPACE_END2


QM_NAMESPACE

template<>
struct object_to_string_o<QM_FROM_NAMESPACE2(finance)isimplediscount>  {
	static qm_string get(const QM_FROM_NAMESPACE2(finance)isimplediscount& obj)  {
		return obj.simple_discount_string();
	}
};

QM_NAMESPACE_END


#endif	//	__INSTRUMENT_STRINGS_QM_HPP__

