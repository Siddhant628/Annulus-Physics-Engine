#pragma once
#include <cstdint>

class Foo
{
public:
	Foo() = default;
	~Foo() = default;
private:
	static const std::int32_t mFoo;
};