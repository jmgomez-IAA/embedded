/*
 * @file MessageBase.h
 * @brief Message Communication Base Class
 * @description Communication class definition for embedded system.
 * @author greenlean
 * @copyright Juan Manuel Gomez 2018 - Distribruted under Boost
 */

#ifndef _COMM_HK_2018_06_16_H_
#define _COMM_HK_2018_06_16_H_

#include "../MessageBase.h"

namespace comm 
{

  namespace msg
  {

    void init(void *void_ptr);

    class HouseKeeping : public MessageBase<TReadIterator, TWriteIterator, HouseKeeping>
    {
      
      using Base = Message<TReadIter, TWriteIter>;
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
	....
      };

      /**
       * @brief Write a Message
       * @param Message to transmit, ITerator, etc.
       * @return Communication Status, ErrorStatus enum.        
       */      
      virtual comm::ErrorStatus writeImpl(WriteIterator& iter, std::size_t len) const override 
      {
	....
      };

      virtual comm::ErrorStatus dispatchImpl(Handler& handler) override
      {
	....
	handler.handle(*this);
      };
 
    };

  }

}

#endif // _COMM_HK_2018_06_16_H_
