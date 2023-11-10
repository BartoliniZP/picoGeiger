#ifndef _CALLABLE_WRAPPER_HPP
#define _CALLABLE_WRAPPER_HPP
#include <optional>
#include <type_traits>
#include <utility>

/*
    Callable wrapper

    This header contains code that allows easy binding of different callables (Callable classes and not-empty-capture-list lambdas) to function pointers

    Author: Bartosz Kotowicz
 */

template <unsigned l, typename Callable>
static std::optional<Callable> callableHolder;
template <unsigned l, typename Callable>
decltype(auto) callableWrapper(Callable &&callable) {
    callableHolder<l, std::decay_t<Callable>>.emplace(std::forward<Callable>(callable));
    return [](auto... args) -> decltype(auto) { return callableHolder<l, std::decay_t<Callable>>.value()(std::forward<decltype(args)>(args)...); };
}

#define wrapper(...) callableWrapper<__LINE__>(__VA_ARGS__)  // limitation: cannot create two or more wrappers of same type callables in one line
#endif