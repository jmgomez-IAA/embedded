/*
 * @file Handler.h
 * @brief Dispatch  Messages Base Class
 * @description Handler class to dispatch messages for embedded system.
 * @author greenlean
 * @copyright Juan Manuel Gomez 2018 - Distribruted under Boost
 */

#ifndef _COMM_HANDLER_2018_06_16_H_
#define _COMM_HANDLER_2018_06_16_H_

namespace comm 
{

  namespace msg
  {

    class Handler 
    {
    public:
      dispatch(Message &msg);
    };
  }

}

#endif //_COMM_HANDLER_2018_06_16_H_
