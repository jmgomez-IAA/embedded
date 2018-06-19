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

#include "../Message.h"

namespace comm 
{

  namespace msg
  {

    void init(void *void_ptr);

    template<typename TReadIter, typename TWriteIter>
    class PipeMessage : public Message<TReadIter, TWriteIter>
    {

    public:
      //      using Base = Message<TReadIter,TWriteIter>;
      //using ReadIterator = Base::ReadIterator;
      //using WriteIterator = Base::WriteIterator;
      using ReadIterator = TReadIter;
      using WriteIterator = TWriteIter;


      PipeMessage(std::uint32_t id, std::int32_t t, std::uint32_t h): MsgId(id), temp(t), humidity(h){};

      void ShowFields()
      {
	std::cout << "M: " << MsgId << "T: " << temp << "H: " << humidity << std::endl;
      }

      ~PipeMessage() {MsgId=0; temp=0; humidity=0;};

      /**
       * @brief Read a Message
       * @param Message to tran, ITerator, etc.
       * @return Communication Status, ErrorStatus enum.        
       */      
      virtual comm::ErrorStatus readImpl(ReadIterator &iter, std::size_t len)  override 
      {

	for(int i=0; i<len; ++i)
	  {
	    if (i==0)	     
	      MsgId = static_cast<std::uint32_t>(*iter);

	    if (i==1)	     
	      temp = static_cast<std::int32_t>(*iter);

	    if (i==2)	     
	      humidity = static_cast<std::int32_t>(*iter);

	    iter ++;
	  }
	
	return comm::ErrorStatus::Success;
      };

      /**
       * @brief Write a Message
       * @param Message to transmit, ITerator, etc.
       * @return Communication Status, ErrorStatus enum.        
       */      
      virtual comm::ErrorStatus writeImpl(WriteIterator &iter, std::size_t len) override 
      {

	(*iter) = MsgId;
	iter ++;
        (*iter) = temp;
	iter ++;
        (*iter) = humidity;
	iter++;

	return comm::ErrorStatus::Success;

      };

      /**
       * @brief Process the Message!!
       */
      /*
      virtual comm::ErrorStatus dispatchImpl(Handler& handler) override
      {
	//....
	//handler.handle(*this);
	
      };
*/
    private:
      //The data in the message is Temperatura, Humidity and Others
      std::uint32_t MsgId;
      std::int32_t temp;
      std::uint32_t humidity;
 
    };

  }
}

#endif //__COMM_MSG_2018_06_16_H_
