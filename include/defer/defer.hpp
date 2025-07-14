#ifndef DEFER_INCLUDE_DEFER_DEFER_H
#define DEFER_INCLUDE_DEFER_DEFER_H

#if __cplusplus >= 202002L
#define DEFER_CPP20
#endif

#ifdef DEFER_CPP20
#include <concepts>
#else
#include <type_traits>
#endif

#include <utility>

#ifdef DEFER_CPP20
template <std::invocable<> Func>
#else
template <typename Func>
#endif
class DeferredCallback {
#ifndef DEFER_CPP20
  static_assert(std::is_invocable_v<Func>,
                "Func must be invocable with no arguments.");
#endif
public:
  explicit DeferredCallback(Func &&function) noexcept
      : callback(std::forward<Func>(function)) {}

  ~DeferredCallback() noexcept { callback(); }

  DeferredCallback(DeferredCallback &&other) noexcept
      : callback(std::move(other.callback)) {}

  DeferredCallback(const DeferredCallback &) = delete;
  DeferredCallback &operator=(const DeferredCallback &) = delete;
  DeferredCallback &operator=(DeferredCallback &&) = delete;

private:
  Func callback;
};

template <typename Func> [[nodiscard]] auto deferred(Func &&callback) noexcept {
  return DeferredCallback<std::decay_t<Func>>(std::forward<Func>(callback));
}

#define DEFER_UNIQUE_NAME(a, b) DEFER_CONCAT(a, b)
#define DEFER_CONCAT(a, b) a##b

#define defer_inline(code)                                                     \
  auto DEFER_UNIQUE_NAME(_deferred_, __LINE__) = deferred([&] { code });
#define defer(func)                                                            \
  auto DEFER_UNIQUE_NAME(_deferred_, __LINE__) = deferred(func);

#endif
