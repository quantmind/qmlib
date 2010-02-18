


namespace  { 
  //
  //
# if defined(_MSC_VER) || defined(__BORLANDC__)
  // allow Visual Studio integration
  inline std::string format(
                     #ifdef QM_ERROR_LINES
                     const std::string& file, long line,
                     #else
                     const std::string&, long,
                     #endif
                     #ifdef QM_ERROR_FUNCTIONS
                     const std::string& function,
                     #else
                     const std::string&,
                     #endif
                     const std::string& message) {
    std::ostringstream msg;
#   ifdef QM_ERROR_FUNCTIONS
    if (function != "(unknown)") msg << function << ": ";
#   endif
#   ifdef QM_ERROR_LINES
    msg << "\n  " << file << "(" << line << "): \n";
#   endif QM_ERROR_LINES
    msg << message;
    return msg.str();
  }
# else
      // use gcc format (e.g. for integration with Emacs)
      std::string format(const std::string& file,
                         long line,
                         const std::string& function,
                         const std::string& message) {
        std::ostringstream msg;
        #ifdef QM_ERROR_LINES
        msg << "\n" << file << ":" << line << ": ";
        #endif
        #ifdef QM_ERROR_FUNCTIONS
        if (function != "(unknown)")
            msg << "In function `" << function << "': \n";
        #endif
        msg << message;
        return msg.str();
      }
# endif
  //
}


namespace boost {
  // must be defined by the user
  inline void assertion_failed(char const * expr, char const * function, char const * file, long line)  {
    throw std::runtime_error(format(file, line, function,
                                        "Boost assertion failed: " +
                                        std::string(expr)));
  }
}




QM_NAMESPACE

  inline Error::Error(const qm_string& file, long line, const qm_string& function, const qm_string& message)  {
    m_message = QM_SMART_PTR(qm_string)(new qm_string(format(file, line, function, message)));
  }


  inline const char* Error::what() const throw ()  {
    return m_message->c_str();
  }
}


