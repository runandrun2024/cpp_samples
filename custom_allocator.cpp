#include <iostream>
#include <vector>
#include <list>
#include <new>
#include <limits>
#include <cstdint>
#include <map>

template<typename _T_> struct DBMemAllocator
{
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using pointer = _T_*;
	using const_pointer = const _T_*;
	using reference = _T_&;
	using const_reference = const _T_&;
	using value_type =_T_;
	
	template<typename _U_> struct rebind
	{
		using other = DBMemAllocator<_U_>;
	};

	DBMemAllocator() noexcept {}
	DBMemAllocator(const DBMemAllocator&) noexcept {}
	DBMemAllocator(DBMemAllocator&&) noexcept {}

	template<typename _U_> DBMemAllocator(const DBMemAllocator<_U_>&) noexcept {}

	_T_* allocate(std::size_t i_num)
	{
		return reinterpret_cast<_T_*>(std::malloc(sizeof(_T_) * i_num));
	}

	void deallocate(_T_* i_p_target, std::size_t i_num)
	{
		static_cast<void>(i_num);
		std::free(i_p_target);
	}

	void construct(pointer p, const _T_& value)
	{
		new((void*)p) _T_(value);
	}

	void destroy(pointer p)
	{
		((_T_*)p)->~_T_();
	}

	pointer address(reference value) const { return &value; }
	const_pointer address(const_reference value) const { return &value; }

	size_type max_size() const throw()
	{
		return std::numeric_limits<size_t>::max() / sizeof(_T_);
	}
	
};

template <> class DBMemAllocator<void> {
public:
	using pointer = void*;
	using const_pointer = const void*;
	using value_type = void;

	template <typename U>
	struct rebind
	{
		typedef DBMemAllocator<U> other;
	};
};

template<typename _T_, typename _U_> bool operator==(const DBMemAllocator<_T_>&, const DBMemAllocator<_U_>)
{
	return true;
}

template<typename _T_, typename _U_> bool operator!=(const DBMemAllocator<_T_>&, const DBMemAllocator<_U_>)
{
	return false;
}


int main(int argc, char* argv[])
{
#if 0
	std::vector<int, DBMemAllocator<int>> v = {1, 2, 3};
	for (const auto ele : v)
		std::cout << ele << std::endl;
	
	std::list<int, DBMemAllocator<int>> ls = {4, 5, 6};
	for (const auto ele : ls)
		std::cout << ele << std::endl;
#endif

	using MapT = std::map<std::uintptr_t, int>;
	MapT map {};

	for (size_t i = 0; i < 10; ++i)
		map.insert(std::make_pair(std::uintptr_t{i}, i));

	map.erase(2);
	
	for (auto ele : map)
	{
		std::cout << ele.first << "," << ele.second << std::endl;
	}
	

	return 0;
}
