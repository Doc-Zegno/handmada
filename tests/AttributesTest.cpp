//
// Created by syzegno on 18.05.17.
//


#include <vector>
#include <memory>

#include <gtest/gtest.h>

#include "Attributes.h"

using namespace Handmada;


TEST(Attributes, CompareTo)
{
    auto a = makeAttribute("login", "user");
    auto b = makeAttribute("login", "user");
    ASSERT_EQ(a->compareTo(*b), 0);
    auto c = makeAttribute("login", "not a user");
    ASSERT_NE(a->compareTo(*c), 0);
    auto d = makeAttribute("age", 37);
    ASSERT_THROW(a->compareTo(*d), std::exception);
    auto e = makeAttribute("arbitrary value", 5984);
    ASSERT_TRUE(d->compareTo(*e) < 0);
    ASSERT_TRUE(e->compareTo(*d) > 0);
    auto f = makeAttribute("likes coffee", true);
    auto g = makeAttribute("something totally unrelated to coffee", false);
    ASSERT_NE(f->compareTo(*g), 0);
    ASSERT_THROW(f->compareTo(*d), std::exception);
}


TEST(Attributes, Clone)
{
    std::vector<std::unique_ptr<IAttribute>> attributes;
    attributes.push_back(makeAttribute("login", "user"));
    attributes.push_back(makeAttribute("age", 37));
    attributes.push_back(makeAttribute("drinks coffee", true));

    for (auto& attribute : attributes) {
        auto copy = attribute->clone();
        ASSERT_STREQ(attribute->name().c_str(), copy->name().c_str());
        ASSERT_NO_THROW(copy->compareTo(*attribute));
        ASSERT_EQ(copy->compareTo(*attribute), 0);
    }
}

