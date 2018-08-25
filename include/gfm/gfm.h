// Copyright 2018 Kurt Kanzenbach <kurt@kmk-computers.de>
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef _GFM_H_
#define _GFM_H_

#include <type_traits>

template<typename T>
static inline constexpr auto BIT(T x) noexcept
{
    return 1 << x;
}

template<typename T>
constexpr auto to_scalar(T value)
{
    return static_cast<std::underlying_type_t<T>>(value);
}

template<typename ENUM>
struct IsFlagEnum
{
    static const bool enable = false;
};

#define GFM_DECLARE_FLAG_MAP(ENUM)                 \
    template<>                                     \
    struct IsFlagEnum<ENUM>                        \
    {                                              \
        static const bool enable = true;           \
    };                                             \
                                                   \
    using ENUM ## Flags = GenericFlagMap<ENUM>     \

template<typename ENUM,
         typename = typename std::enable_if<IsFlagEnum<ENUM>::enable>::type>
inline constexpr auto operator*(ENUM val) noexcept
{
    return to_scalar<ENUM>(val);
}

template<typename ENUM,
         typename = typename std::enable_if<IsFlagEnum<ENUM>::enable>::type>
inline constexpr ENUM operator| (ENUM lhs, ENUM rhs) noexcept
{
    return static_cast<ENUM>(*lhs | *rhs);
}

template<typename ENUM,
         typename = typename std::enable_if<IsFlagEnum<ENUM>::enable>::type>
inline constexpr ENUM operator& (ENUM lhs, ENUM rhs) noexcept
{
    return static_cast<ENUM>(*lhs & *rhs);
}

template<typename ENUM,
         typename = typename std::enable_if<IsFlagEnum<ENUM>::enable>::type>
inline constexpr ENUM operator^ (ENUM lhs, ENUM rhs) noexcept
{
    return static_cast<ENUM>(*lhs ^ *rhs);
}

template<typename ENUM,
         typename = typename std::enable_if<IsFlagEnum<ENUM>::enable>::type>
inline constexpr ENUM& operator|= (ENUM& lhs, ENUM rhs) noexcept
{
    lhs = static_cast<ENUM>(*lhs | *rhs);
    return lhs;
}

template<typename ENUM,
         typename = typename std::enable_if<IsFlagEnum<ENUM>::enable>::type>
inline constexpr ENUM& operator&= (ENUM& lhs, ENUM rhs) noexcept
{
    lhs = static_cast<ENUM>(*lhs & *rhs);
    return lhs;
}

template<typename ENUM,
         typename = typename std::enable_if<IsFlagEnum<ENUM>::enable>::type>
inline constexpr ENUM& operator^= (ENUM& lhs, ENUM rhs) noexcept
{
    lhs = static_cast<ENUM>(*lhs ^ *rhs);
    return lhs;
}

template<typename ENUM,
         typename = typename std::enable_if<IsFlagEnum<ENUM>::enable>::type>
inline constexpr ENUM operator~ (ENUM rhs) noexcept
{
    return static_cast<ENUM>(~(*rhs));
}

template<typename ENUM,
         typename = typename std::enable_if<IsFlagEnum<ENUM>::enable>::type>
struct GenericFlagMap {
public:
    GenericFlagMap(ENUM val) :
        _val{*val}
    {}

    GenericFlagMap() :
        _val{0}
    {}

    virtual ~GenericFlagMap()
    {}

    explicit constexpr operator bool() const noexcept
    {
        return _val;
    }

    constexpr GenericFlagMap operator& (ENUM rhs) const noexcept
    {
        return _val & *rhs;
    }

    constexpr GenericFlagMap operator| (ENUM rhs) const noexcept
    {
        return _val | *rhs;
    }

    constexpr GenericFlagMap operator^ (ENUM rhs) const noexcept
    {
        return _val ^ *rhs;
    }

    constexpr GenericFlagMap& operator&= (ENUM rhs) noexcept
    {
        _val &= *rhs;
        return *this;
    }

    constexpr GenericFlagMap& operator|= (ENUM rhs) noexcept
    {
        _val |= *rhs;
        return *this;
    }

    constexpr GenericFlagMap& operator^= (ENUM rhs) noexcept
    {
        _val ^= *rhs;
        return *this;
    }

private:
    GenericFlagMap(std::underlying_type_t<ENUM> val) :
        _val{val}
    {}

    std::underlying_type_t<ENUM> _val;
};

#endif /* _GFM_H_ */
