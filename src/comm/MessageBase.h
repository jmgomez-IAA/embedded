/*
 * @file MessageBase.h
 * @brief Message Communication Base Class
 * @description Communication class definition for embedded system.
 * @author greenlean
 * @copyright Juan Manuel Gomez 2018 - Distribruted under Boost
 */

#ifndef _COMM_MSGBASE_2018_06_16_H_
#define _COMM_MSGBASE_2018_06_16_H_

#include "../Message.h"

namespace comm 
{

  namespace msg
  {

    void init(void *void_ptr);

    template <typename TReadIterator, 
	      typename TWriteIterator, 
	      typename TDerived>
    class MessageBase : public Message<TReadIterator, TWriteIterator>
    {

    protected:
      virtual void dispatchImpl(Handler& handler) override
      {
	handler.handle( static_cast<TDerived&>(*this) );
      }
    }    

  }

}


#endif //_COMM_MSGBASE_2018_06_16_H_
