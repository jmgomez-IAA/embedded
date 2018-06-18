
#include <iostream>
#include <vector>

//#include <Message>

namespace comm
{
  namespace hw_if
  {
    std::vector<uint8_t> channel;

    //  Message * processTransportData(std::vector<uint32_t>& chunk_of_data);

    void write(std::uint8_t value)
    {
      channel.push_back(value);   
    }

    std::uint8_t read()
    {    
      std::uint8_t value = channel.front();
      channel.erase(channel.begin());

      return value;
    }


  }
}
