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
    template<typename TReadIter, typename TWriteIter>
    class Message
    {
    public:

      using ReadIterator = TReadIter;  //std::vector<std::uint32_t>::iterator iter;
      using WriteIterator = TWriteIter;

      /**
       * @brief Read a Message from a received chunk.
       * @description Deserialize the message from the received chunk.
       * @param iter, is an iterator to traverse the chunk of data, each traits should be deserialized.
       * @return Communication Status, ErrorStatus enum.        
       */
      ErrorStatus read( ReadIterator& iter, std::size_t len) 
      {
	return readImpl(iter, len);
      }

      /**
       * @brief Wite a Message to a chunk.
       * @description Serialize the data container of the message into chunk of data to transmit.
       * @param iter is an iterator to traverse the chunk of data, each traits should be set to a value.
       * @param len, is the len of the message.
       * @return Communication Status, ErrorStatus enum.        
       */
      ErrorStatus write( WriteIterator& iter, std::size_t len) 
      { 
	return writeImpl(iter, len);
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
      virtual ErrorStatus readImpl(ReadIterator& iter, std::size_t len)  = 0; 
      virtual ErrorStatus writeImpl(WriteIterator& iter, std::size_t len) = 0;     
 
    };

  }
}

#endif //__COMM_MSG_2018_06_16_H_
