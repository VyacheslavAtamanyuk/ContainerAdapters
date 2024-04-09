#pragma once

#include <iterator>

template <typename Iterator>
class drop_view {
public:
    using iterator = Iterator;

    drop_view(Iterator begin, Iterator end, size_t n): begin_(begin), end_(end) {
        if constexpr(std::random_access_iterator<Iterator>) {
            begin_ += ((n > std::distance(begin_, end_)) ? std::distance(begin_, end_): n);
        } else {
            size_t counter = 0;

            while (begin_ != end_ && counter < n) {
                ++begin_;
                ++counter;
            }
        }
    }

    Iterator begin() const {
        return begin_;
    }

    Iterator end() const {
        return end_;
    }

private:
    Iterator begin_;
    Iterator end_;
};