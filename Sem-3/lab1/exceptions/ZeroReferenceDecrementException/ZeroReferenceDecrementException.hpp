#ifndef LAB1_ZERO_REFERENCE_DECREMENT_EXCEPTION_HPP
#define LAB1_ZERO_REFERENCE_DECREMENT_EXCEPTION_HPP

#include <exception_lib.hpp>

namespace kogan {

class ZeroReferenceDecrementException : public BaseException {
    void build_message() const override;
};

}  // namespace kogan

#endif