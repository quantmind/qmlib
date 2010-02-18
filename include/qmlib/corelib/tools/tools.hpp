//
//  \file
//  @defgroup tools
//
#ifndef __BASIC_TOOLS_QM_H__
#define __BASIC_TOOLS_QM_H__
//
//
#include <qmlib/corelib/tools/string.hpp>
#include <boost/type_traits.hpp>
#include <boost/numeric/conversion/cast.hpp>
//
//
QM_NAMESPACE

template<class T>
inline void fastcopy(const T& from, T& to) {to = from;}


/// Object function template for type conversion
template<class From, class To>
struct convert  {
	convert(const From& from, To& to) {
		// Assume numeric cast
		to = boost::numeric_cast(from);
	}
};

template<class T> struct convert<T,T>  {
	convert(const T& from, T& to) {
		to = from;
	}
};

	
  //
  template<class T>
  class qm_simplearray  {
    T*       m_buffer;
    qm_Size  m_size;
    //
    void Dispose()
    {
      if(m_buffer) delete [] m_buffer;
      m_buffer = 0;
      m_size   = 0;
    }
  public:
    qm_simplearray(qm_Size siz = 0):m_buffer(0),m_size(0){Alloca(siz);}
    ~qm_simplearray(){Dispose();}
    //
    void Alloca(qm_Size siz)
    {
      if(siz != this->size())
      {
        Dispose();
        m_buffer = new T[siz];
        QM_REQUIRE(m_buffer,"buffer cannot be allocated: out of memory");
        m_size   = siz;
      }
    }
    //
    qm_Size size() const {return m_size;}
    operator T* () {return m_buffer;}
  };



/*
  class qm_buffer  {
  public:

    qm_buffer(qm_Size siz = 0):m_buffer(0),m_size(0){Alloca(siz);}
    virtual ~qm_buffer(){Dispose();}
    //
    void Alloca(qm_Size siz)
    {
      if(siz > this->size())
      {
        Dispose();
        m_buffer = malloc(siz);
        QM_REQUIRE(m_buffer,"buffer cannot be allocated: out of memory");
        m_size   = siz;
      }
    }
    //
    qm_Size size() const {return m_size;}
    operator void* () {return m_buffer;}

  private:
    void*    m_buffer;
    qm_Size  m_size;
    //
    void Dispose()
    {
      if(m_buffer) free(m_buffer);
      m_buffer = 0;
      m_size   = 0;
    }
  };
*/
  //
  //
  template<class To,class From>
  inline To* dynamicCast(From* ptr)
  {
    try {
      return dynamic_cast<To*>(ptr);
    }
    catch(...)
    {
      QM_FAIL("Could not cast the pointer");
    }
  }
  //
  //
  //
  //
  /*
  template<class D>
  class object_to_list  {
  public:
    //
    template <class L>
    L get_list() const
    {
      L lis;
      const D& c = static_cast<const D&>(*this);
      for(D::const_iterator it = c.begin();it!=c.end();++it)
        lis.append(*it);
      return lis;
    }
  };
  //
  //
  //
  template<class C>
  qm_list ContainerToList(const C& co)
  {
    qm_list list;
    for(C::const_iterator it = co.begin();it!=co.end();++it)
      list.append(*it);
    return list;
  }
  */
  	//
    //
    template <class T>
    struct Sample
    {
    public:
      T          Value;
      qm_real    Weight;
      Sample():Weight(1){}
      Sample(const T& value, qm_real weight) : Value(value), Weight(weight) {}
    };
    //
    //
    //

    /*
    template<class D>
    inline D GetDictionary(const qm_strings& keys, const qm_strings& vals)
    {
      D dic;
      qm_strings::const_iterator iv=vals.begin();
      for(qm_strings::const_iterator it=keys.begin();it!=keys.end();++it)
      {
        if(iv->length() > 0) dic[*it] = *iv;
        ++iv;
      }
      return dic;
    }
    */
//
//
QM_NAMESPACE_END
//
//
#endif // __BASIC_TOOLS_QM_H__
//
