// Copyright 2016 MongoDB Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "catch.hpp"

#include <mongo_odm/util.hpp>

using bsoncxx::stdx::optional;

TEST_CASE("all_true struct contains true only if all boolean template parameters are true.",
          "[mongo_odm::all_true]") {
    REQUIRE((mongo_odm::all_true<false>::value) == false);
    REQUIRE((mongo_odm::all_true<false, true>::value) == false);
    REQUIRE((mongo_odm::all_true<true, false>::value) == false);
    REQUIRE((mongo_odm::all_true<true, false, true>::value) == false);
    REQUIRE((mongo_odm::all_true<true, true>::value) == true);
    REQUIRE((mongo_odm::all_true<true, true, true>::value) == true);
}

TEST_CASE("is_optional struct contains true only if template type parameter is an optional",
          "[mongo_odm::is_optional]") {
    REQUIRE(mongo_odm::is_optional<int>::value == false);
    REQUIRE(mongo_odm::is_optional<optional<int>>::value == true);
}

TEST_CASE(
    "remove_optional, when templated with an optional type, contains the underlying wrapped type",
    "[mongo_odm::remove_optional]") {
    REQUIRE((std::is_same<mongo_odm::remove_optional<int>::type, int>::value));
    REQUIRE((std::is_same<mongo_odm::remove_optional<std::string>::type, std::string>::value));
    REQUIRE((std::is_same<mongo_odm::remove_optional<optional<int>>::type, int>::value));
    REQUIRE((
        std::is_same<mongo_odm::remove_optional<optional<std::string>>::type, std::string>::value));
}