/**
 * @brief Common class from what custom messages inherits.
 * @author Juan Manuel Gomez Lopez
 */
template <typename TReadIter, typename TWriteIter>
class Message
{
public:
    using ReadIterator = TReadIter;
    using WriteIterator = TWriteIter;

    ErrorStatus read(ReadIterator& iter, std::size_t len) {
        return readImpl(iter, len);
    }

    ErrorStatus write(WriteIterator& iter, std::size_t len) const {
        return writeImpl(iter, len);
    }
    ...

protected:
    // Implements reading from the buffer functionality
    virtual ErrorStatus readImpl(ReadIterator& iter, std::size_t len) = 0; 

    // Implements writing to a buffer functionality
    virtual ErrorStatus writeImpl(WriteIterator& iter, std::size_t len) const = 0;
};

template <typename TReadIter, typename TWriteIter>
class ActualMessage1 : public Message<TReadIter, TWriteIter>
{
    using Base = Message<TReadIter, TWriteIter>;
public:
    using Base::ReadIterator;
    using Base::WriteIterator;
    ...

protected:
    virtual ErrorStatus readImpl(ReadIterator& iter, std::size_t len) override {...}; 
    virtual ErrorStatus writeImpl(WriteIterator& iter, std::size_t len) const override {...};
};
