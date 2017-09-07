/*
 * Client.h
 *
 *  Created on: Sep 6, 2017
 *      Author: root
 */

#ifndef _DATASET_PUBLISHER_H_
#define _DATASET_PUBLISHER_H_

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include "DataSet.h"

namespace NS_DataSet
{

  using namespace boost::interprocess;

  template <typename DataType>
  class Publisher
  {
  public:
    Publisher (std::string name)
    {
      dataset_name = name;

      shared_memory_object oper_shm (open_only, dataset_name.c_str (), read_write);

      mapped_region region (oper_shm, read_write);

      void* region_addr = region.get_address ();

      operation = static_cast<DataSetOperation*> (region_addr);
    }

    virtual ~Publisher ()
    {

    }

  private:
    std::string dataset_name;

    DataSetOperation* operation;

  private:

    void* getSrv ()
    {
      std::string ds_shm_name = dataset_name + "_DS";

      shared_memory_object ds_shm (open_only, ds_shm_name.c_str (), read_write);

      mapped_region region (ds_shm, read_write);

      void* region_addr = region.get_address ();

      return region_addr;
    }

    void resize (size_t size)
    {
      std::string srv_shm_name = dataset_name + "_DS";

      shared_memory_object::remove (srv_shm_name.c_str ());

      shared_memory_object srv_shm (create_only, srv_shm_name.c_str (), read_write);

      srv_shm.truncate (size);

      operation->buf_len = size;
    }

  public:
    bool publish (DataType& ds)
    {
      if (!operation)
        return false;

      scoped_lock<interprocess_mutex> lock (operation->lock);

      operation->status = DATASET_PROCESSING;
      operation->req_cond.notify_all ();

      int try_times = 10;
      bool timeout = false;
      while (operation->status == DATASET_PROCESSING)
      {
        operation->req_cond.timed_wait (lock, (boost::get_system_time () + boost::posix_time::microseconds (100)));
        if (try_times-- < 0)
        {
          timeout = true;
          break;
        }
      }

      if (timeout)
      {
        return false;
      }

      if (operation->buf_len != ds.serializationLength ())
      {
        resize (ds.serializationLength ());
      }

      operation->buf_len = ds.serializationLength ();

      unsigned char* addr = (unsigned char*)getSrv ();

      ds.serialize ((unsigned char*)addr, operation->buf_len);

      return true;
    }
  };

}



#endif /* DATASET_PUBLISHER_H_ */