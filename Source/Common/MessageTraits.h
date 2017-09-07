#ifndef _MESSAGE_TRAITS_H_
#define _MESSAGE_TRAITS_H_

#include "../Time/Time.h"

#include <string>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include "MessageForward.h"

namespace NS_NaviCommon
{
  namespace _Std_data_
  {
    DECLARE_MESSAGE(Header);
  }
}

#define IMPLEMENT_SIMPLE_TOPIC_TRAITS(msg, md5sum, datatype, definition) \
  namespace NS_NaviCommon \
  { \
  template<> struct MD5Sum<msg> \
  { \
    static const char* value() { return md5sum; } \
    static const char* value(const msg&) { return value(); } \
  }; \
  template<> struct DataType<msg> \
  { \
    static const char* value() { return datatype; } \
    static const char* value(const msg&) { return value(); } \
  }; \
  template<> struct Definition<msg> \
  { \
    static const char* value() { return definition; } \
    static const char* value(const msg&) { return value(); } \
  }; \
  }

namespace NS_NaviCommon
{
  
  /**
   * \brief Base type for compile-type true/false tests.  Compatible with Boost.MPL.  classes inheriting from this type
   * are \b true values.
   */
  struct TrueType
  {
    static const bool value = true;
    typedef TrueType type;
  };
  
  /**
   * \brief Base type for compile-type true/false tests.  Compatible with Boost.MPL.  classes inheriting from this type
   * are \b false values.
   */
  struct FalseType
  {
    static const bool value = false;
    typedef FalseType type;
  };
  
  /**
   * \brief A simple datatype is one that can be memcpy'd directly in array form, i.e. it's a POD, fixed-size type and
   * sizeof(M) == sum(serializationLength(M:a...))
   */
  template<typename M>
    struct IsSimple: public FalseType
    {
    };
  /**
   * \brief A fixed-size datatype is one whose size is constant, i.e. it has no variable-length arrays or strings
   */
  template<typename M>
    struct IsFixedSize: public FalseType
    {
    };
  /**
   * \brief HasHeader informs whether or not there is a header that gets serialized as the first thing in the message
   */
  template<typename M>
    struct HasHeader: public FalseType
    {
    };
  
  /**
   * \brief Am I message or not
   */
  template<typename M>
    struct IsMessage: public FalseType
    {
    };
  
  /**
   * \brief Specialize to provide the md5sum for a message
   */
  template<typename M>
    struct MD5Sum
    {
      static const char*
      value ()
      {
        return M::__s_getMD5Sum ().c_str ();
      }
      
      static const char*
      value (const M& m)
      {
        return m.__getMD5Sum ().c_str ();
      }
    };
  
  /**
   * \brief Specialize to provide the datatype for a message
   */
  template<typename M>
    struct DataType
    {
      static const char*
      value ()
      {
        return M::__s_getDataType ().c_str ();
      }
      
      static const char*
      value (const M& m)
      {
        return m.__getDataType ().c_str ();
      }
    };
  
  /**
   * \brief Specialize to provide the definition for a message
   */
  template<typename M>
    struct Definition
    {
      static const char*
      value ()
      {
        return M::__s_getMessageDefinition ().c_str ();
      }
      
      static const char*
      value (const M& m)
      {
        return m.__getMessageDefinition ().c_str ();
      }
    };
  
  /**
   * \brief Header trait.  In the default implementation pointer()
   * returns &m.header if HasHeader<M>::value is true, otherwise returns NULL
   */
  template<typename M, typename Enable = void>
    struct Header
    {
      static _Std_data_::Header*
      pointer (M& m)
      {
        (void) m;
        return 0;
      }
      static _Std_data_::Header const*
      pointer (const M& m)
      {
        (void) m;
        return 0;
      }
    };
  
  template<typename M>
    struct Header<M, typename boost::enable_if<HasHeader<M> >::type>
    {
      static _Std_data_::Header*
      pointer (M& m)
      {
        return &m.header;
      }
      static _Std_data_::Header const*
      pointer (const M& m)
      {
        return &m.header;
      }
    };
  
  /**
   * \brief FrameId trait.  In the default implementation pointer()
   * returns &m.header.frame_id if HasHeader<M>::value is true, otherwise returns NULL.  value()
   * does not exist, and causes a compile error
   */
  template<typename M, typename Enable = void>
    struct FrameId
    {
      static std::string*
      pointer (M& m)
      {
        (void) m;
        return 0;
      }
      static std::string const*
      pointer (const M& m)
      {
        (void) m;
        return 0;
      }
    };
  
  template<typename M>
    struct FrameId<M, typename boost::enable_if<HasHeader<M> >::type>
    {
      static std::string*
      pointer (M& m)
      {
        return &m.header.frame_id;
      }
      static std::string const*
      pointer (const M& m)
      {
        return &m.header.frame_id;
      }
      static std::string
      value (const M& m)
      {
        return m.header.frame_id;
      }
    };
  
  /**
   * \brief TimeStamp trait.  In the default implementation pointer()
   * returns &m.header.stamp if HasHeader<M>::value is true, otherwise returns NULL.  value()
   * does not exist, and causes a compile error
   */
  template<typename M, typename Enable = void>
    struct TimeStamp
    {
      static Time*
      pointer (M& m)
      {
        (void) m;
        return 0;
      }
      static Time const*
      pointer (const M& m)
      {
        (void) m;
        return 0;
      }
    };
  
  template<typename M>
    struct TimeStamp<M, typename boost::enable_if<HasHeader<M> >::type>
    {
      static Time*
      pointer (typename boost::remove_const<M>::type &m)
      {
        return &m.header.stamp;
      }
      static Time const*
      pointer (const M& m)
      {
        return &m.header.stamp;
      }
      static Time
      value (const M& m)
      {
        return m.header.stamp;
      }
    };
  
  /**
   * \brief returns MD5Sum<M>::value();
   */
  template<typename M>
    inline const char*
    md5sum ()
    {
      return MD5Sum<
          typename boost::remove_reference<typename boost::remove_const<M>::type>::type>::value ();
    }
  
  /**
   * \brief returns DataType<M>::value();
   */
  template<typename M>
    inline const char*
    datatype ()
    {
      return DataType<
          typename boost::remove_reference<typename boost::remove_const<M>::type>::type>::value ();
    }
  
  /**
   * \brief returns Definition<M>::value();
   */
  template<typename M>
    inline const char*
    definition ()
    {
      return Definition<
          typename boost::remove_reference<typename boost::remove_const<M>::type>::type>::value ();
    }
  
  /**
   * \brief returns MD5Sum<M>::value(m);
   */
  template<typename M>
    inline const char*
    md5sum (const M& m)
    {
      return MD5Sum<
          typename boost::remove_reference<typename boost::remove_const<M>::type>::type>::value (
          m);
    }
  
  /**
   * \brief returns DataType<M>::value(m);
   */
  template<typename M>
    inline const char*
    datatype (const M& m)
    {
      return DataType<
          typename boost::remove_reference<typename boost::remove_const<M>::type>::type>::value (
          m);
    }
  
  /**
   * \brief returns Definition<M>::value(m);
   */
  template<typename M>
    inline const char*
    definition (const M& m)
    {
      return Definition<
          typename boost::remove_reference<typename boost::remove_const<M>::type>::type>::value (
          m);
    }
  
  /**
   * \brief returns Header<M>::pointer(m);
   */
  template<typename M>
    inline _Std_data_::Header*
    header (M& m)
    {
      return Header<
          typename boost::remove_reference<typename boost::remove_const<M>::type>::type>::pointer (
          m);
    }
  
  /**
   * \brief returns Header<M>::pointer(m);
   */
  template<typename M>
    inline _Std_data_::Header const*
    header (const M& m)
    {
      return Header<
          typename boost::remove_reference<typename boost::remove_const<M>::type>::type>::pointer (
          m);
    }
  
  /**
   * \brief returns FrameId<M>::pointer(m);
   */
  template<typename M>
    inline std::string*
    frameId (M& m)
    {
      return FrameId<
          typename boost::remove_reference<typename boost::remove_const<M>::type>::type>::pointer (
          m);
    }
  
  /**
   * \brief returns FrameId<M>::pointer(m);
   */
  template<typename M>
    inline std::string const*
    frameId (const M& m)
    {
      return FrameId<
          typename boost::remove_reference<typename boost::remove_const<M>::type>::type>::pointer (
          m);
    }
  
  /**
   * \brief returns TimeStamp<M>::pointer(m);
   */
  template<typename M>
    inline Time*
    timeStamp (M& m)
    {
      return TimeStamp<
          typename boost::remove_reference<typename boost::remove_const<M>::type>::type>::pointer (
          m);
    }
  
  /**
   * \brief returns TimeStamp<M>::pointer(m);
   */
  template<typename M>
    inline Time const*
    timeStamp (const M& m)
    {
      return TimeStamp<
          typename boost::remove_reference<typename boost::remove_const<M>::type>::type>::pointer (
          m);
    }
  
  /**
   * \brief returns IsSimple<M>::value;
   */
  template<typename M>
    inline bool
    isSimple ()
    {
      return IsSimple<
          typename boost::remove_reference<typename boost::remove_const<M>::type>::type>::value;
    }
  
  /**
   * \brief returns IsFixedSize<M>::value;
   */
  template<typename M>
    inline bool
    isFixedSize ()
    {
      return IsFixedSize<
          typename boost::remove_reference<typename boost::remove_const<M>::type>::type>::value;
    }
  
  /**
   * \brief returns HasHeader<M>::value;
   */
  template<typename M>
    inline bool
    hasHeader ()
    {
      return HasHeader<
          typename boost::remove_reference<typename boost::remove_const<M>::type>::type>::value;
    }

} // namespace ros

#endif // _MESSAGE_TRAITS_H_