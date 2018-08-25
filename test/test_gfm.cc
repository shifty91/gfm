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

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GFM

#include <boost/test/unit_test.hpp>
#include <gfm/gfm.h>

using namespace boost::unit_test;

enum class Blub: std::uint32_t {
    FLAG1 = BIT(0),
    FLAG2 = BIT(1),
    FLAG3 = BIT(2),
    FLAG4 = BIT(3),
};
GFM_DECLARE_FLAG_MAP(Blub);

BOOST_AUTO_TEST_CASE(EnumOperations)
{
    auto a = Blub::FLAG1 | Blub::FLAG2;
    BOOST_CHECK_EQUAL(*a, 0x03);

    auto b = Blub::FLAG4 & Blub::FLAG4;
    BOOST_CHECK_EQUAL(*b, 0x08);

    auto c = (Blub::FLAG3 | Blub::FLAG4) & Blub::FLAG3;
    BOOST_CHECK_EQUAL(*c, 0x04);

    auto d = Blub::FLAG4 & Blub::FLAG3;
    BOOST_CHECK_EQUAL(*d, 0x00);

    auto e = Blub::FLAG1 ^ Blub::FLAG2;
    BOOST_CHECK_EQUAL(*e, 0x03);

    auto f = Blub::FLAG1;
    f |= Blub::FLAG2;
    BOOST_CHECK_EQUAL(*f, 0x03);

    auto g = Blub::FLAG4;
    g &= Blub::FLAG4;
    BOOST_CHECK_EQUAL(*g, 0x08);

    auto h = Blub::FLAG3;
    h |= Blub::FLAG4;
    h &= Blub::FLAG3;
    BOOST_CHECK_EQUAL(*h, 0x04);

    auto i = Blub::FLAG4;
    i &= Blub::FLAG3;
    BOOST_CHECK_EQUAL(*i, 0x00);

    auto j = Blub::FLAG1;
    j ^= Blub::FLAG2;
    BOOST_CHECK_EQUAL(*j, 0x03);
}

BOOST_AUTO_TEST_CASE(FlagMap)
{
    BlubFlags flags;

    flags = Blub::FLAG1 | Blub::FLAG2 | Blub::FLAG3 | Blub::FLAG4;
    BOOST_CHECK(flags & Blub::FLAG1);
    BOOST_CHECK(flags & Blub::FLAG2);
    BOOST_CHECK(flags & Blub::FLAG3);
    BOOST_CHECK(flags & Blub::FLAG4);

    flags &= ~Blub::FLAG3;
    BOOST_CHECK(flags & Blub::FLAG1);
    BOOST_CHECK(flags & Blub::FLAG2);
    BOOST_CHECK(!(flags & Blub::FLAG3));
    BOOST_CHECK(flags & Blub::FLAG4);
}
