#pragma once

#include <stdexcept>
#include <string>

namespace Errors {
    inline std::logic_error immutable() {
        return std::logic_error("Immutable object");
    }

    inline std::out_of_range index_out_of_range() {
        return std::out_of_range("Index out of range");
    }

    inline std::invalid_argument invalid_argument(const std::string& message = "") {
        return std::invalid_argument("Invalid argument" + (message.empty() ? "" : ": " + message));
    }

    inline std::out_of_range empty_array() {
        return std::out_of_range("Empty array");
    }

    inline std::out_of_range empty_list() {
        return std::out_of_range("Empty list");
    }

    inline std::invalid_argument incompatible_types() {
        return std::invalid_argument("Incompatible types");
    }

    inline std::runtime_error empty_value() {
        return std::runtime_error("Empty value");
    }

    inline std::invalid_argument negative_size() {
        return std::invalid_argument("Negative size not allowed");
    }

    inline std::out_of_range invalid_indices() {
        return std::out_of_range("Invalid indices");
    }

    inline std::invalid_argument negative_count() {
        return std::invalid_argument("Negative count");
    }

    inline std::invalid_argument null_list() {
        return std::invalid_argument("Null list");
    }
}

