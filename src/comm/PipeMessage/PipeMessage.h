/*
 * @file PipeMessage.h
 * @brief Example of message using minimal inheritance.
 * @description Communication class definition for linux, using pipes..
 * @author greenlean
 * @copyright Juan Manuel Gomez 2018 - Distribruted under Boost
 */

#ifndef _COMM_MSGPIPE_2018_06_16_H_
#define _COMM_MSGPIPE_2018_06_16_H_


#include <iostream>
#include <tuple>

#include "../Message.h"

namespace comm 
{

  namespace msg
  {

    void init(void *void_ptr);

    template <typename TReadIter, typename TWriteIter>
    class PipeMessage : public Message<TReadIter, TWriteIter>
    {
      using Base = Message<TReadIterm, TWriteIter>;
      using Channel = std::vector<std::uint8_t>;

    public:
      using Base::ReadIterator;
      using Base::WriteIterator;

    protected:
      /**
       * @brief Write a Message
       * @param Message to tran, ITerator, etc.
       * @return Communication Status, ErrorStatus enum.        
       */      
      virtual comm::ErrorStatus readImpl(ReadIterator& iter, std::size_t len) override 
      {

	//std::in32_t myId, myTemp, myHumidity;
	std::int32_t val;
	//char mychar;
	//std::tie (myId, myTemp, myHumidity) = m_fields;  // unpack elements
	//std::tie (std::ignore, std::ignore, myint, mychar) = bar;  // unpack (with ignore)

	for(int i=0; i< len; ++i)
	  {
	    val = (*iter);
	  }

      };

      /**
       * @brief Write a Message
       * @param Message to transmit, ITerator, etc.
       * @return Communication Status, ErrorStatus enum.        
       */      
      virtual comm::ErrorStatus writeImpl(WriteIterator& iter, std::size_t len) const override 
      {
	for(int i=0; i<len; ++i)
	  {
	    (*iter) = i;
	    iter ++;
	  }
      };

      /**
       * @brief Process the Message!!
       */
      virtual comm::ErrorStatus dispatchImpl(Handler& handler) override
      {
	//....
	handler.handle(*this);
      };

    private:
      //The data in the message is Temperatura, Humidity and Others
      std::tuple<std::uint32_t, std::uint32_t,std::uint32_t> m_fields;
 
    };

  }
}

#endif //__COMM_MSG_2018_06_16_H_
