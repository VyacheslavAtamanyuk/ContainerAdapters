#pragma once

#include <iterator>

template <typename Iterator>
class take_view {
public:
    using iterator = Iterator;

    take_view(Iterator begin, Iterator end, size_t n): begin_(begin), end_(end) {
        Iterator temp = begin_;
        size_t counter = 0;

        if constexpr(std::random_access_iterator<Iterator>) {
            temp += ((n > std::distance(begin_, end_)) ? std::distance(begin_, end_): n);
        } else {
            while (temp != end_ && counter < n) {
                ++temp;
                ++counter;
            }
        }

        end_ = temp;
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