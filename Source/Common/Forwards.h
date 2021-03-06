#ifndef _FORWARDS_H_
#define _FORWARDS_H_

#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/function.hpp>

#include "../Time/Time.h"
#include "../Exception/Exception.h"
#include "Declare.h"

namespace NS_NaviCommon
{

  typedef boost::shared_ptr< void > VoidPtr;
  typedef boost::weak_ptr< void > VoidWPtr;
  typedef boost::shared_ptr< void const > VoidConstPtr;
  typedef boost::weak_ptr< void const > VoidConstWPtr;

  class Header;
  class Transport;
  typedef boost::shared_ptr< Transport > TransportPtr;
  class TransportTCP;
  typedef boost::shared_ptr< TransportTCP > TransportTCPPtr;
  class TransportUDP;
  typedef boost::shared_ptr< TransportUDP > TransportUDPPtr;
  class Connection;
  typedef boost::shared_ptr< Connection > ConnectionPtr;
  typedef std::set< ConnectionPtr > S_Connection;
  typedef std::vector< ConnectionPtr > V_Connection;
  class Publication;
  typedef boost::shared_ptr< Publication > PublicationPtr;
  typedef std::vector< PublicationPtr > V_Publication;
  class SubscriberLink;
  typedef boost::shared_ptr< SubscriberLink > SubscriberLinkPtr;
  typedef std::vector< SubscriberLinkPtr > V_SubscriberLink;
  class Subscription;
  typedef boost::shared_ptr< Subscription > SubscriptionPtr;
  typedef boost::weak_ptr< Subscription > SubscriptionWPtr;
  typedef std::list< SubscriptionPtr > L_Subscription;
  typedef std::vector< SubscriptionPtr > V_Subscription;
  typedef std::set< SubscriptionPtr > S_Subscription;
  class PublisherLink;
  typedef boost::shared_ptr< PublisherLink > PublisherLinkPtr;
  typedef std::vector< PublisherLinkPtr > V_PublisherLink;
  class ServicePublication;
  typedef boost::shared_ptr< ServicePublication > ServicePublicationPtr;
  typedef std::list< ServicePublicationPtr > L_ServicePublication;
  typedef std::vector< ServicePublicationPtr > V_ServicePublication;
  class ServiceServerLink;
  typedef boost::shared_ptr< ServiceServerLink > ServiceServerLinkPtr;
  typedef std::list< ServiceServerLinkPtr > L_ServiceServerLink;
  class Transport;
  typedef boost::shared_ptr< Transport > TransportPtr;
  class NodeHandle;
  typedef boost::shared_ptr< NodeHandle > NodeHandlePtr;

  class SingleSubscriberPublisher;
  typedef boost::function< void(const SingleSubscriberPublisher&) > SubscriberStatusCallback;

  class CallbackQueue;
  class CallbackQueueInterface;
  class CallbackInterface;
  typedef boost::shared_ptr< CallbackInterface > CallbackInterfacePtr;

  struct SubscriberCallbacks
  {
    SubscriberCallbacks(
        const SubscriberStatusCallback& connect = SubscriberStatusCallback(),
        const SubscriberStatusCallback& disconnect = SubscriberStatusCallback(),
        const VoidConstPtr& tracked_object = VoidConstPtr(),
        CallbackQueueInterface* callback_queue = 0)
        : connect_(connect), disconnect_(disconnect),
          callback_queue_(callback_queue)
    {
      has_tracked_object_ = false;
      if(tracked_object)
      {
        has_tracked_object_ = true;
        tracked_object_ = tracked_object;
      }
    }
    SubscriberStatusCallback connect_;
    SubscriberStatusCallback disconnect_;

    bool has_tracked_object_;
    VoidConstWPtr tracked_object_;
    CallbackQueueInterface* callback_queue_;
  };
  typedef boost::shared_ptr< SubscriberCallbacks > SubscriberCallbacksPtr;

  /**
   * \brief Structure passed as a parameter to the callback invoked by a Timer
   */
  struct TimerEvent
  {
    Time last_expected; ///< In a perfect world, this is when the last callback should have happened
    Time last_real;                ///< When the last callback actually happened

    Time current_expected; ///< In a perfect world, this is when the current callback should be happening
    Time current_real; ///< This is when the current callback was actually called (Time::now() as of the beginning of the callback)

    struct
    {
      Duration last_duration;           ///< How long the last callback ran for
    } profile;
  };
  typedef boost::function< void(const TimerEvent&) > TimerCallback;

  /**
   * \brief Structure passed as a parameter to the callback invoked by a WallTimer
   */
  /*
   struct WallTimerEvent
   {
   WallTime last_expected;                 ///< In a perfect world, this is when the last callback should have happened
   WallTime last_real;                     ///< When the last callback actually happened

   WallTime current_expected;              ///< In a perfect world, this is when the current callback should be happening
   WallTime current_real;                  ///< This is when the current callback was actually called (Time::now() as of the beginning of the callback)

   struct
   {
   WallDuration last_duration;           ///< How long the last callback ran for
   } profile;
   };
   typedef boost::function<void(const WallTimerEvent&)> WallTimerCallback;
   */

  class ServiceManager;
  typedef boost::shared_ptr< ServiceManager > ServiceManagerPtr;
  class TopicManager;
  typedef boost::shared_ptr< TopicManager > TopicManagerPtr;
  class ConnectionManager;
  typedef boost::shared_ptr< ConnectionManager > ConnectionManagerPtr;
  class XMLRPCManager;
  typedef boost::shared_ptr< XMLRPCManager > XMLRPCManagerPtr;
  class PollManager;
  typedef boost::shared_ptr< PollManager > PollManagerPtr;

}

#endif
