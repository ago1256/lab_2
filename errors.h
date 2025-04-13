#pragma once

#include <stdexcept>
#include <string>

namespace Errors {
    inline std::logic_error immutable() {
        return std::logic_error("неизменяемая последовательность");
    }

    inline std::out_of_range index_out_of_range() {
        return std::out_of_range("Неверно введен индекс");
    }

    inline std::invalid_argument invalid_argument() {
        return std::invalid_argument("Неверно введен аргумент");
    }

    inline std::out_of_range empty_array() {
        return std::out_of_range("Пустой массив");
    }

    inline std::out_of_range empty_list() {
        return std::out_of_range("Пустой список");
    }

    inline std::invalid_argument incompatible_types() {
        return std::invalid_argument("Несовместимые типы");
    }

    inline std::runtime_error empty_value() {
        return std::runtime_error("Пустое значение");
    }

    inline std::invalid_argument negative_size() {
        return std::invalid_argument("Отрицательный индекс");
    }

    inline std::out_of_range invalid_ind() {
        return std::out_of_range("Invalid index");
    }

    inline std::invalid_argument negative_count() {
        return std::invalid_argument("Negative count");
    }

    inline std::invalid_argument null_list() {
        return std::invalid_argument("Null list");
    }
}

