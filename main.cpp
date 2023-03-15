#include <iostream>
#include <variant>

#include <fmt/core.h>
#include <fmt/std.h>

// NOLINTNEXTLINE
struct force_valueless_by_exception {
  force_valueless_by_exception() = default;

  // std::variant is only guaranteed to be valueless by exception
  // only if an exception is thrown during the move
  // initialization of the contained value during
  // move assignment
  // source:
  // https://en.cppreference.com/w/cpp/utility/variant/valueless_by_exception
  // NOLINTNEXTLINE
  [[noreturn]] force_valueless_by_exception(force_valueless_by_exception&&)
  {
    throw 3.14;
  }

  force_valueless_by_exception(const force_valueless_by_exception&) =
    default;
};

template <>
struct fmt::formatter<force_valueless_by_exception>
    : formatter<string_view> {
  template <typename FormatContext>
  auto format(const force_valueless_by_exception&,
              FormatContext& ctx) const
  {
    string_view str {"<force_valueless_by_exception>"};
    return formatter<string_view>::format(str, ctx);
  }
};

auto main() -> int
{

  std::variant<std::monostate, force_valueless_by_exception>
    test_variant {};

  fmt::print("{}\n", test_variant);

  try {
    force_valueless_by_exception forcer {};
    test_variant.emplace<force_valueless_by_exception>(std::move(forcer));
  } catch ( ... ) { }

  fmt::print("{}\n", test_variant);

  return 0;
}

