#include <iostream>
#include <variant>

#include <fmt/core.h>
#include <fmt/std.h>

// NOLINTNEXTLINE
struct force_valueless_by_exception {
  force_valueless_by_exception() = default;

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
    example_variant {};

  fmt::print("{}\n", example_variant);

  try {
    force_valueless_by_exception forcer {};
    example_variant.emplace<force_valueless_by_exception>(
      std::move(forcer));
  } catch ( ... ) { }

  // variant is now valueless by exception
  fmt::print("{}\n", example_variant);

  return 0;
}

