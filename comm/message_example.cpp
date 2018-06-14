/**
 * @brief Example of usage of message class with Templates.
 * @author Juan Manuel Gomez Lopez
 */

using EmbReadIter = const std::uint8_t*;
using EmbWriteIter = std::uint8_t*; 
using EmbMessage = Message<EmbReadIter, EmbWriteIter>
using EmbActualMessage1 = ActualMessage1<EmbReadIter, EmbWriteIter>
using EmbActualMessage2 = ActualMessage2<EmbReadIter, EmbWriteIter>

std::array<std::uint8_t, 1024> outBuf;
EmbWriteIter iter = &outBuf[0];

EmbActualMessage1 msg;
msg.write(iter, outBuf.size());
auto writtenCount = std::distance(&outBuf[0], iter); // iter was incremented
