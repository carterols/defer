#ifndef DEFER_INCLUDE_DEFER_DEFER_H
#define DEFER_INCLUDE_DEFER_DEFER_H

#include <utility>

template <typename Func>
class DeferredCallback {
  public:
    DeferredCallback(Func&& function)
      : callback(std::forward<Func>(function))
      {}

    ~DeferredCallback() {
      callback();
    }
    
  private:
    Func callback;
};

template<typename Func>
DeferredCallback<Func> make_deferred_callback(Func&& callback) {
  return DeferredCallback(std::forward<Func>(callback));
}

#define DEFER_UNIQUE_NAME(a, b) DEFER_CONCAT(a, b)
#define DEFER_CONCAT(a, b) a##b

#define defer_inline(code) auto DEFER_UNIQUE_NAME(_deferred_, __LINE__) = make_deferred_callback([&]{ code });
#define defer(func) auto DEFER_UNIQUE_NAME(_deferred_, __LINE__) = make_deferred_callback(func);

#endif
