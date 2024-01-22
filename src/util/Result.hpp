//
// Created by User on 1/22/2024.
//

#ifndef NEBULA_MAIN_RESULT_HPP
#define NEBULA_MAIN_RESULT_HPP

#include <variant>
#include <string>
#include <stdexcept>

template <typename T, typename E>
class Result {
public:
    enum class Tag { Ok, Err };

private:
    std::variant<T, E> value;
    Tag tag;

public:
    Result(const T& val) : value(val), tag(Tag::Ok) {}

    Result(const E& err) : value(err), tag(Tag::Err) {}

    bool isOk() const {
        return tag == Tag::Ok;
    }

    bool isErr() const {
        return tag == Tag::Err;
    }

    const T& unwrap() const {
        if (isOk()) {
            return std::get<T>(value);
        } else {
            throw std::runtime_error("Called unwrap() on an Err result");
        }
    }

    const E& unwrapErr() const {
        if (isErr()) {
            return std::get<E>(value);
        } else {
            throw std::runtime_error("Called unwrapErr() on an Ok result");
        }
    }
};
#endif //NEBULA_MAIN_RESULT_HPP
