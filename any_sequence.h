#pragma once
#include"sequence.h"

enum class Seq_type { INT, DOUBLE, STRING };

struct Any_sequence {
    void* ptr;
    Seq_type type;
};

