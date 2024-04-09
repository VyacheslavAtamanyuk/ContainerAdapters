#pragma once

#include <iterator>

template <typename Iterator, typename Functor>
class TransformIterator {
public:
    using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
    using return_type = decltype(std::declval<Functor>()(*std::declval<Iterator>()));
    using value_type = std::remove_reference<return_type>;
    using pointer = value_type*;
    using reference = value_type&;
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;

    TransformIterator(Iterator current, Functor functor): it_(current), functor_(functor) {}

    TransformIterator& operator++() {
        ++it_;
        return *this;
    }

    TransformIterator operator++(int) {
        TransformIterator temp = *this;
        ++it_;
        return temp;
    }

    TransformIterator& operator--() requires std::bidirectional_iterator<Iterator> {
        --it_;
        return *this;
    }

    TransformIterator operator--(int) requires std::bidirectional_iterator<Iterator> {
        TransformIterator temp = *this;
        --it_;
        return temp;
    }

    return_type operator*() const {
        return functor_(*it_);
    }

    bool operator==(TransformIterator other) const {
        return it_ == other.it_;
    }

    bool operator!=(TransformIterator other) const {
        return it_ != other.it_;
    }

private:
    Iterator it_;
    Functor functor_;
};

template <typename Iterator, typename Functor>
class transform_view {
public:
    using iterator = TransformIterator<Iterator, Functor>;

    transform_view(Iterator begin, Iterator end, Functor functor): begin_(TransformIterator(begin, functor)), end_(TransformIterator(end, functor)), functor_(functor) {}

    TransformIterator<Iterator, Functor> begin() const {
        return begin_;
    }

    TransformIterator<Iterator, Functor> end() const {
        return end_;
    }

private:
    TransformIterator<Iterator, Functor> begin_;
    TransformIterator<Iterator, Functor> end_;
    Functor functor_;
};
