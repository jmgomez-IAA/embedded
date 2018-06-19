/**
 * @breif Linux inter process communication using pipes.
 * @author Juan Manuel Gomez <greenlean@protonmail.com>
 * @copyrigth 
 */

#include <iostream>
#include <memory>
#include <if.h>

//#include <Message.h>
#include "./PipeMessage/PipeMessage.h"


/*
using MsgPtr = std::unique_ptr<Message>;
MsgPtr msg = processTransportData(...);
auto es = msg.read(...);
if (es != ErrorStatus::Success)
{
... //handle error
Handler handler;
msg->dispatch(handler);
}
*/

// Type definition.
//using LinReadIter = const std::vector<std::uint32_t>::iterator;
//using LinWriteIter = std::back_insert_iterator<std::vector<std::uint32_t>>;


//using LinPipeMessage = PipeMessage<LinReadIter, LinWriteIter>;


/**
 * @description Realiza una comunicacion empleando uint8.
 */
int main()
{

  uint8_t val;
  //Bufferes de datos.
  std::vector<std::uint32_t> input_buffer, output_buffer;
  //Iterador para recorrer los bufferes de datos.
  std::vector<std::uint32_t>::iterator ReadIterator;
  std::back_insert_iterator< std::vector<std::uint32_t> > WriteIterator(output_buffer);

  std::cout << "Test del canal: " << std::endl;
  for (int iter = 0; iter < 10; iter ++)
    {      

      comm::hw_if::write(static_cast<uint8_t>(iter));
      std::cout << "Write " << iter << " <--> ";

      val = comm::hw_if::read();
      std::cout << "Read " << static_cast<int>(val) << std::endl;
      input_buffer.push_back(val);
                  
    }

  //Creamos el message
  using TReadIterator = std::vector<std::uint32_t>::iterator;
  using TWriteIterator = std::vector<std::uint32_t>::iterator;
  //std::unique_ptr<comm::msg::Message> pmesg = comm::msg::PipeMessage mesg(1,3,10);
  //  std::unique_ptr<comm::msg::Message> pmesg = std::make_unique<comm::msg::PipeMessage>(1,3,10);
  comm::msg::PipeMessage mesg(1,3,10);
  comm::msg::Message *pmesg = &mesg;

  //mesg.ShowFields();

  comm::ErrorStatus ret;
  ret = pmesg->write(output_buffer, 2);

  if (ret == comm::ErrorStatus::Success)
    {
      std::cout << "Todo ok." << std::endl;
    }


  ret = pmesg->read(output_buffer, 2);
  if (ret == comm::ErrorStatus::Success)
    {
      //  mesg.ShowFields();
      std::cout << "Todo Ok 2." << std::endl;
    }

}