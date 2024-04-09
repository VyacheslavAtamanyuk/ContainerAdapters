#pragma once

#include <iterator>

template <typename Iterator, typename Functor>
class FilterIterator {
public:
    using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    using pointer = typename std::iterator_traits<Iterator>::pointer;
    using reference = typename std::iterator_traits<Iterator>::reference;
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;

    FilterIterator(Iterator current, Iterator begin, Iterator end, Functor functor): it_(current), begin_(begin), end_(end), functor_(functor) {
        while (it_ != end && !functor(*it_)) {
            ++it_;
        }
    }

    FilterIterator<Iterator, Functor>& operator++() {
        do {
            ++it_;
        }
        while (it_ != end_ && !functor_(*it_));

        return *this;
    }

    FilterIterator<Iterator, Functor> operator++(int) {
        FilterIterator<Iterator, Functor> temp = *this;
        ++(*this);
        return temp;
    }

    FilterIterator<Iterator, Functor> operator--() requires std::bidirectional_iterator<Iterator> {
        auto finish = begin_;
        --finish;

        do {
            --it_;
        }
        while (it_ != finish && !functor_(*it_));

        return *this;
    }

    FilterIterator<Iterator, Functor> operator--(int) requires std::bidirectional_iterator<Iterator> {
        FilterIterator<Iterator, Functor> temp = *this;
        --(*this);
        return temp;
    }

    reference operator*() const {
        return *it_;
    }

    bool operator==(FilterIterator<Iterator, Functor> other) const {
        return it_ == other.it_;
    }

    bool operator!=(FilterIterator<Iterator, Functor> other) const {
        return it_ != other.it_;
    }

private:
    Iterator it_;
    Iterator begin_;
    Iterator end_;
    Functor functor_;
};


template <typename Iterator, typename Functor>
class filter_view {
public:
    using iterator = FilterIterator<Iterator, Functor>;

    filter_view(Iterator begin, Iterator end, Functor functor): begin_(FilterIterator(begin, begin, end, functor)), end_(FilterIterator(end, begin, end, functor)), functor_(functor) {}

    FilterIterator<Iterator, Functor> begin() const {
        return begin_;
    }

    FilterIterator<Iterator, Functor> end() const {
        return end_;
    }

private:
    FilterIterator<Iterator, Functor> begin_;
    FilterIterator<Iterator, Functor> end_;
    Functor functor_;
};