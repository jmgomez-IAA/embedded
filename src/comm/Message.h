/*
 * @file Message.h
 * @brief Message Communication Base Class
 * @description Communication class definition for embedded system. The message interface may include the following operation:
 * - Retreive the message ID.
 * - Read (deserialize) the message contents into a buffer.
 * - Write (serialize) the message contents into a buffer.
 * - Calculate the serialization length of the message.
 * - Dispatch the message to an appropiate handling function.
 * - Check the validity of the message contents.
 * Some customization may be required and some functionalities may be skipped.
 * @return An enum class is create with the most frequente errors.
 * @author greenlean
 * @copyright Juan Manuel Gomez 2018 - Distribruted under Boost
 */

#ifndef _COMM_MSG_2018_06_16_H_
#define _COMM_MSG_2018_06_16_H_

namespace comm 
{

  enum class ErrorStatus
  {
    Success, 
      NotEnoughData,
      BufferOverflow, 
      InvalidMsgData
  };


  namespace msg
  {
    void init(void *void_ptr);

    /**
     * @brief Send any message...
     */
    /*    void sendMessage(const Message & msg)
    {
      msg.write(...);
    };
*/

    class Message
    {
    public:

      /**
       * @brief Read a Message from a received chunk.
       * @description Deserialize the message from the received chunk.
       * @param iter, is an iterator to traverse the chunk of data, each traits should be deserialized.
       * @return Communication Status, ErrorStatus enum.        
       */
      ErrorStatus read( std::vector<std::uint32_t> &channel, std::size_t len) 
      {
	return readImpl(channel, len);
      }

      /**
       * @brief Wite a Message to a chunk.
       * @description Serialize the data container of the message into chunk of data to transmit.
       * @param iter is an iterator to traverse the chunk of data, each traits should be set to a value.
       * @param len, is the len of the message.
       * @return Communication Status, ErrorStatus enum.        
       */
      ErrorStatus write(std::vector<std::uint32_t> &channel, std::size_t len) 
      { 
	return writeImpl(channel, len);
      }

      /**
       * @brief Dispath the message to the appropiate handling function.
       * @param  handler is the object in charge of sending the me message to the appropiate function.
       * @return 
       */
      /*
      void dispatch(Handler& handler)
      {
	return dispatchImpl(handler);
      }
*/
    protected:
      virtual ErrorStatus readImpl(std::vector<std::uint32_t>& channel, std::size_t len)  = 0; 
      virtual ErrorStatus writeImpl(std::vector<std::uint32_t>& channel, std::size_t len)  = 0;     
 
    private:

    };

  }
}

#endif //__COMM_MSG_2018_06_16_H_
