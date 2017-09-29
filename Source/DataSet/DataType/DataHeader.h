#ifndef _DATATYPE_DATAHEADER_H_
#define _DATATYPE_DATAHEADER_H_

#include <string>
#include <vector>
#include "../../Time/Time.h"
#include "DataBase.h"
#include "../../Serialization/Serialization.h"

namespace NS_DataType
{
  template<class ContainerAllocator>
    struct DataHeader_: public DataBase
    {
      typedef DataHeader_<ContainerAllocator> Type;
    public:
      DataHeader_ ()
          : seq (0), stamp (), frame_id ()
      {
      }
      ;

      DataHeader_ (const ContainerAllocator& allocator)
          : seq (0), stamp (allocator), frame_id (allocator)
      {
      }
      ;

      unsigned long seq;
      NS_NaviCommon::Time stamp;

      std::basic_string<int8_t, std::char_traits<int8_t>,
          typename ContainerAllocator::template rebind<int8_t>::other> frame_id;

      typedef boost::shared_ptr<DataHeader_<ContainerAllocator> > Ptr;
      typedef boost::shared_ptr<DataHeader_<ContainerAllocator> const> ConstPtr;

    public:
      virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
      {
        NS_NaviCommon::OStream stream(write_ptr, 1000000000);
        NS_NaviCommon::serialize(stream, this->seq);
        NS_NaviCommon::serialize(stream, stamp);
        NS_NaviCommon::serialize(stream, frame_id);
        return stream.getData();
      }

      virtual uint8_t *deserialize(uint8_t *read_ptr)
      {
        NS_NaviCommon::IStream stream(read_ptr, 1000000000);
        NS_NaviCommon::deserialize(stream, seq);
        NS_NaviCommon::deserialize(stream, stamp);
        NS_NaviCommon::deserialize(stream, frame_id);
        return stream.getData();
      }

      virtual uint32_t serializationLength() const
      {
        uint32_t size = 0;
        size += NS_NaviCommon::serializationLength(seq);
        size += NS_NaviCommon::serializationLength(stamp);
        size += NS_NaviCommon::serializationLength(frame_id);
        return size;
      }
    };
  
  typedef DataHeader_<std::allocator<void> > DataHeader;
  
  typedef boost::shared_ptr<DataHeader> DataHeaderPtr;
  typedef boost::shared_ptr<DataHeader const> DataHeaderConstPtr;

} /* namespace NS_NaviCommon */

#endif /* _DATAHEADER_H_ */
