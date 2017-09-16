/*
 * Vector3.h
 *
 *  Created on: 2016年9月23日
 *      Author: seeing
 */

#ifndef _DATATYPE_VECTOR3_H_
#define _DATATYPE_VECTOR3_H_

#include <string>
#include <vector>
#include <ostream>
#include <boost/shared_ptr.hpp>
#include "DataBase.h"
#include "../../Serialization/Serialization.h"

namespace NS_DataType
{
  
  template<class ContainerAllocator>
    struct Vector3_: public DataBase
    {
      typedef Vector3_<ContainerAllocator> Type;

      Vector3_ ()
          : x (0.0), y (0.0), z (0.0)
      {
      }
      
      Vector3_ (const ContainerAllocator& _alloc)
          : x (0.0), y (0.0), z (0.0)
      {
      }
      
      typedef double _x_type, _y_type, _z_type;

      double x, y, z;

      typedef boost::shared_ptr<Vector3_<ContainerAllocator> > Ptr;
      typedef boost::shared_ptr<Vector3_<ContainerAllocator> const> ConstPtr;

    public:
      virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
      {
        NS_NaviCommon::OStream stream(write_ptr, 1000000000);
        NS_NaviCommon::serialize(stream, x);
        NS_NaviCommon::serialize(stream, y);
        NS_NaviCommon::serialize(stream, z);
        return stream.getData();
      }

      virtual uint8_t *deserialize(uint8_t *read_ptr)
      {
        NS_NaviCommon::IStream stream(read_ptr, 1000000000);
        NS_NaviCommon::deserialize(stream, x);
        NS_NaviCommon::deserialize(stream, y);
        NS_NaviCommon::deserialize(stream, z);
        return stream.getData();
      }

      virtual uint32_t serializationLength() const
      {
        uint32_t size = 0;
        size += NS_NaviCommon::serializationLength(x);
        size += NS_NaviCommon::serializationLength(y);
        size += NS_NaviCommon::serializationLength(z);
        return size;
      }
    };
  
  typedef Vector3_<std::allocator<void> > Vector3;
  
  typedef boost::shared_ptr<Vector3> Vector3Ptr;
  typedef boost::shared_ptr<Vector3 const> Vector3ConstPtr;

} /* namespace NS_NaviCommon */

#endif /* _VECTOR3_H_ */
