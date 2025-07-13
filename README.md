# Defer
This single header repo implements a C++ version of Go's `defer`.

## How to use
### Lambda
```cpp
defer([=] {
    std::println("Hello world");
});
```

### Inline code
```cpp
// defer_inline will generate a lambda and capture variables by reference.
// If you need more control, use the `defer` macro and specify the capture type in the lambda
defer_inline(
    std::println("Hello world");
);
```

### Function pointer
```cpp
void do_something() {
    std::println("Hello world");
}

defer(&do_something);
```

