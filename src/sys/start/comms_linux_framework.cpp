/**
 * @breif Linux inter process communication using pipes.
 * @author Juan Manuel Gomez <greenlean@protonmail.com>
 * @copyrigth 
 */

#include <iostream>
#include <if.h>



//#include <Message.h>


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
using LinReadIter = const std::vector<std::uint32_t>::iterator;
using LinWriteIter = std::back_insert_iterator<std_vector<std::uint32_t>>;


using LinPipeMessage = PipeMessage<LinReadIter, LinWriteIter>;


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
  std::back_insert_iterator<std::vector<std::uint32_t>> WriteIterator;


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
  Message<ReadIterator, WriteIterator> msg;
  
  


  /*
  //Definitions of our data, transmit buffers.
  std::vector<std::uint8_t> outBuf;
  LinWriteIter iter = std::back_inserter(outBuf);

  LinPipeMessage msg;

  msg.write(iter, outBuf.max_size());
  auto writtenCount = outBuf.size();

*/
}
