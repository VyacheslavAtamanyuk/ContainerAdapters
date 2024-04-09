#pragma once

#include "drop_view.h"
#include "take_view.h"
#include "reverse_view.h"
#include "filter_view.h"
#include "transform_view.h"
#include "keys_values_view.h"

template <typename T>
concept BasicContainer = requires {std::declval<T>().begin(); std::declval<T>().end(); std::forward_iterator<decltype(std::declval<T>().begin())>;};

template <typename T>
concept AssociativeContainer = requires {std::declval<T>().begin(); std::declval<T>().end(); std::bidirectional_iterator<decltype(std::declval<T>().begin())>;};

template <typename T>
concept ReversibleContainer = requires {std::declval<T>().begin(); std::declval<T>().end(); std::bidirectional_iterator<decltype(std::declval<T>().begin())>; std::make_reverse_iterator(std::declval<T>().begin());};

struct drop {
    drop(size_t n): n_(n) {}

    size_t n_;
};

struct take {
    take(size_t n): n_(n) {}

    size_t n_;
};

struct reverse {
    reverse() {}
};

template <typename Functor>
struct filter {
    filter(Functor functor): functor_(functor) {}

    Functor functor_;
};

template <typename Functor>
struct transform {
    transform(Functor functor): functor_(functor) {}

    Functor functor_;
};

struct keys {
    keys() {};
};

struct values {
    values() {};
};

template <BasicContainer T>
auto operator|(T&& some_container, drop pipeline) {
    return drop_view(some_container.begin(), some_container.end(), pipeline.n_);
}

template <BasicContainer T>
auto operator|(T&& some_container, take pipeline) {
    return take_view(some_container.begin(), some_container.end(), pipeline.n_);
}

template <ReversibleContainer T>
auto operator|(T&& some_container, reverse) {
    return reverse_view(some_container.begin(), some_container.end());
}

template <BasicContainer T, typename Functor>
auto operator|(T&& some_container, filter<Functor> pipeline) {
    return filter_view(some_container.begin(), some_container.end(), pipeline.functor_);
}

template <BasicContainer T, typename Functor>
auto operator|(T&& some_container, transform<Functor> functor) {
    return transform_view(some_container.begin(), some_container.end(), functor.functor_);
}

template <AssociativeContainer T>
auto operator|(T&& some_container, keys) {
    return keys_values_view<decltype(std::declval<T>().begin()), true, false>(some_container.begin(), some_container.end());
}

template <AssociativeContainer T>
auto operator|(T&& some_container, values) {
    return keys_values_view<decltype(std::declval<T>().begin()), false, true>(some_container.begin(), some_container.end());
}