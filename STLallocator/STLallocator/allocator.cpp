#include "stdafx.h"
#include <string>
#include "allocator.h"
#include <cstddef>
#include <stddef.h>
#include "MemoryPool.h"
#define __MAX_BYTES 128

using namespace std;
template<class _T>
class allocator {
	typedef void _Not_user_specialized;
	typedef _T value_type;
	typedef value_type *pointer;
	typedef const value_type *const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef true_type
		propagate_on_container_move_assignment;
	typedef true_type is_always_equal;
	pointer address(reference _Val) const _NOEXCEPT{
		return const_cost<reference>(address(static_cast<const_reference>(_Val)));
	} 
	const_pointer address(const_reference _Val) const _NOEXCEPT{
		return &_Val;
	} 
	pointer allocate(size_type _Count) {
		return static_cast<pointer>(pool.allocate(_Count * sizeof(_T)));
	}
	void deallocate(pointer _Ptr, size_type _Count){
		pool.deallocate(ptr, _Count);
	}
	
	template<class _Uty>
	void destroy(_Uty *_Ptr) {
		_Destroy(_Ptr);
	}
	template<class _Objty, class... _Types>
	void construct(_Objty *_Ptr, _Types&&... _Args) {
		::new ((void*)_Ptr) _Objty(::std::forward<_Types>(_Args)...);
	}
};
