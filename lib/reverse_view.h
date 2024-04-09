#pragma once

#include <iterator>

template <typename Iterator>
class reverse_view {
public:
    using iterator = std::reverse_iterator<Iterator>;

    reverse_view(Iterator begin, Iterator end): begin_(std::make_reverse_iterator(end)), end_(std::make_reverse_iterator(begin))  {}

    iterator begin() const {return begin_;};
    iterator end() const { return end_;};

private:
    iterator begin_;
    iterator end_;
};