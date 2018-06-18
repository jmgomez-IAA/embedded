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

    class PipeMessage : public Message
    {

    public:

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
      virtual comm::ErrorStatus readImpl(std::vector<std::uint32_t> &channel, std::size_t len) override 
      {
	MsgId = channel.front();
	channel.erase(channel.begin());

	temp = channel.front();
	channel.erase(channel.begin());

	humidity = channel.front();
	channel.erase(channel.begin());
	
	return comm::ErrorStatus::Success;
      };

      /**
       * @brief Write a Message
       * @param Message to transmit, ITerator, etc.
       * @return Communication Status, ErrorStatus enum.        
       */      
      virtual comm::ErrorStatus writeImpl(std::vector<std::uint32_t> &channel, std::size_t len) override 
      {

	channel.push_back(MsgId);
	channel.push_back(temp);
	channel.push_back(humidity);

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
