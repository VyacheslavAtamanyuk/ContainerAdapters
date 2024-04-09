#pragma once

#include <iterator>

template <typename Iterator, bool HasKey, bool HasValue>
class KeysValuesIterator {
public:
    using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
    using return_type = std::conditional_t<HasKey, decltype(std::declval<Iterator>()->first), decltype(std::declval<Iterator>() ->second)>;
    using value_type = std::remove_reference<return_type>;
    using pointer = value_type*;
    using reference = value_type&;
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;

    KeysValuesIterator(Iterator it): it_(it) {}

    KeysValuesIterator& operator++() {
        ++it_;
        return *this;
    }

    KeysValuesIterator operator++(int) {
        KeysValuesIterator temp = *this;
        ++it_;
        return temp;
    }

    KeysValuesIterator& operator--() {
        --it_;
        return *this;
    }

    KeysValuesIterator operator--(int) {
        KeysValuesIterator temp = *this;
        --it_;
        return *this;
    }

    return_type operator*() const requires HasKey {
        return it_->first;
    }

    return_type operator*() const requires HasValue {
        return it_->second;
    }

    bool operator==(KeysValuesIterator other) const {
        return it_ == other.it_;
    }

    bool operator!=(KeysValuesIterator other) const {
        return it_ != other.it_;
    }

private:
    Iterator it_;
};

template <typename Iterator, bool HasKey, bool HasValue>
class keys_values_view {
public:
    using iterator = KeysValuesIterator<Iterator, HasKey, HasValue>;

    keys_values_view(Iterator begin, Iterator end): begin_(KeysValuesIterator<Iterator, HasKey, HasValue>(begin)), end_(KeysValuesIterator<Iterator, HasKey, HasValue>(end)) {}

    KeysValuesIterator<Iterator, HasKey, HasValue> begin() const {
        return begin_;
    }

    KeysValuesIterator<Iterator, HasKey, HasValue> end() const {
        return end_;
    }

private:
    KeysValuesIterator<Iterator, HasKey, HasValue> begin_;
    KeysValuesIterator<Iterator, HasKey, HasValue> end_;
};