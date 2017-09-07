/*
 * PoseStamped.h
 *
 *  Created on: 2016年9月23日
 *      Author: seeing
 */

#ifndef _DATATYPE_POSESTAMPED_H_
#define _DATATYPE_POSESTAMPED_H_

#include "DataBase.h"
#include "DataHeader.h"
#include "Pose.h"
#include "Serialization/Serialization.h"

namespace NS_DataType
{
  
  template<class ContainerAllocator>
    struct PoseStamped_: public DataBase
    {
      typedef PoseStamped_<ContainerAllocator> Type;
    public:
      PoseStamped_ ()
          : header (), pose ()
      {
      }
      ;

      PoseStamped_ (const ContainerAllocator& allocator)
          : header (allocator), pose (allocator)
      {
      }
      ;

      DataHeader_<ContainerAllocator> header;
      Pose_<ContainerAllocator> pose;

      typedef boost::shared_ptr<PoseStamped_<ContainerAllocator> > Ptr;
      typedef boost::shared_ptr<PoseStamped_<ContainerAllocator> const> ConstPtr;

    public:
      virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
      {
        NS_NaviCommon::OStream stream(write_ptr, 1000000000);

        return stream.getData();
      }

      virtual uint8_t *deserialize(uint8_t *read_ptr)
      {
        NS_NaviCommon::IStream stream(read_ptr, 1000000000);

        return stream.getData();
      }

      virtual uint32_t serializationLength() const
      {
        uint32_t size = 0;

        return size;
      }
    };
  
  typedef PoseStamped_<std::allocator<void> > PoseStamped;
  
  typedef boost::shared_ptr<PoseStamped> PoseStampedPtr;
  typedef boost::shared_ptr<PoseStamped const> PoseStampedConstPtr;

}

#endif /* _POSESTAMPED_H_ */