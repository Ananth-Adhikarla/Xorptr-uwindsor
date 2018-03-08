
// This file has been provided as a template for you to do individual
// portion of your project. You will find instructions, hints/tips, etc.
// below as comments in the source code.


#include <iostream>
#include <bitset>

// If neither CXX_XOR_PROJECT_USE_UINTPTR_T not CXX_XOR_PROJECT_USE_REINTERPRET_CAST are defined,
// trigger compile-time error.
#if !defined (CXX_XOR_PROJECT_USE_UINTPTR_T) && !defined (CXX_XOR_PROJECT_USE_REINTERPRET_CAST)
#	error Must define one of CXX_XOR_PROJECT_USE_UINTPTR_T or CXX_XOR_PROJECT_USE_REINTERPRET_CAST
#endif

// If both CXX_XOR_PROJECT_USE_UINTPTR_T and CXX_XOR_PROJECT_USE_REINTERPRET_CAST are defined,
// trigger compile-time error.
#if defined (CXX_XOR_PROJECT_USE_UINTPTR_T) && defined(CXX_XOR_PROJECT_USE_REINTERPRET_CAST)
#	error Define only one of CXX_XOR_PROJECT_USE_UINTPTR_T or CXX_XOR_PROJECT_USE_REINTERPRET_CAST
#endif

// execute this code if CXX_XOR_PROJECT_USE_UINTPTR_T is defined
#ifdef CXX_XOR_PROJECT_USE_UINTPTR_T

	// A template is a blueprint or formula for creating a generic class
	// or function. In this case, we are creating a blueprint for a class.
	// "typname" and "class" are interchangable in the declaration of a type
	// template parameter.
	template <typename T>

	// The only difference between a class and a struct is that in a class
	// definition, the default access for members and base classes is private, 
	// while in a struct it is public.
	// ...actually, there is apparently one more difference. template<class T>
	// is allowed, but template<struct T> is not.
	struct xorptr_traits final
	{
		// pointer_type is an alias for T*, a pointer to type T
		using pointer_type = T*;

		// const_pointer_type is an alias for T const*, a pointer
		// to const T
		using const_pointer_type = T const*;

		// uintptr_t is an unsigned int capable of storing a pointer.
		// This is used to perform integer-specific operations on a pointer,
		// or to obscure the type of a pointer by providing it 
		// as an integer "handle".
		using xorptr_type = std::uintptr_t;

		// When no parameters are given, create xorptr with nullptr parameters
		static xorptr_type create() noexcept
		{
			return create(static_cast<T*>(nullptr), static_cast<T*>(nullptr));
		}

		// Function used when parameters are not const
		// Cast pointer values to uintptr_t, so that the ^ value may be used
		// on them (xor the addresses)
		static xorptr_type create(pointer_type p1, pointer_type p2) noexcept
		{
		 	// // cast both input parameters to uintptr_t
		 	// xorptr_type uip1 = reinterpret_cast<std::uintptr_t>(p1);
		 	// xorptr_type uip2 = reinterpret_cast<std::uintptr_t>(p2);

		 	// // // observe the values of uip1 and uip2 before xoring
		 	// std::cout << "before xoring: \n"
		 	//  		<< "uip1: " << uip1 << "\n"
		 	//  		<< "uip2: " << uip2 << "\n\n";

		 	// xorptr_type t = uip1 ^ uip2;

		 	//  // observe the values of uip1 and uip2 after xoring
		 	//  std::cout << "xor'd value: \n"
		 	//  		<< t << "\n\n";

		 	// return t;

			// reinterpret_cast does not compile to any CPU instructions.
		    // It is purely a compiler directive which instructs the compiler
		 	// to treat the sequence of bits as if it had the new type.
			return
		 		reinterpret_cast<xorptr_type>(p1)
		 		^ reinterpret_cast<xorptr_type>(p2)
		 	;
		}

		// Function used when parameters are const
		// Cast pointer values to uintptr_t, so that the ^ value may be used
		// on them (xor the addresses)
		// Return the xor'd pointer value while retaining the const-ness of
		// the input parameters
		static xorptr_type create(
			const_pointer_type p1, const_pointer_type p2) noexcept
		{
		 	// // cast both input parameters to uintptr_t
		 	// // reinterpret_cast does not compile to any CPU instructions.
		 	// // It is purely a compiler directive which instructs the compiler
		 	// // to treat the sequence of bits as if it had the new type.
		 	// xorptr_type uip1 = reinterpret_cast<std::uintptr_t>(p1);
		 	// xorptr_type uip2 = reinterpret_cast<std::uintptr_t>(p2);

		 	// // // observe the values of uip1 and uip2 before xoring
		 	// std::cout << "before xoring: \n"
		 	//  		<< "uip1: " << uip1 << "\n"
		 	//  		<< "uip2: " << uip2 << "\n\n";

		 	// xorptr_type t = uip1 ^ uip2;

		 	//  // observe the values of uip1 and uip2 after xoring
		 	//  std::cout << "xor'd value: \n"
		 	//  		<< t << "\n\n";

		 	// return t;

			return
		 		reinterpret_cast<xorptr_type>(p1)
		 		^ reinterpret_cast<xorptr_type>(p2)
		 	;
		}

		// Compute the xor of an xorptr and a pointer of any type.
		// Return the computed pointer value while retaining the const-ness
		// of the pointed-to value.
		static pointer_type extract(
		 	xorptr_type const& xp, pointer_type p) noexcept
		{
			// static_cast does an explicit type conversion.
			// The type must be a data type for which there is a know method
			// for converting the object to. Here, void* is used to ensure that
			// the conversion happens. void* can downcast to any pointer type, and
			// any pointer type can be upcasted to void* (sort of similar to Object
			// in Java)
		 	return
		 		static_cast<T*>(
		 			reinterpret_cast<void*>(xp ^ reinterpret_cast<xorptr_type>(p))
		 		)
		 	;
		}


		// Compute the xor of an xorptr and a const pointer of any type.
		// Return the computed pointer value while retaining the const-ness
		// of the pointed-to values.
		static const_pointer_type extract(
		 	xorptr_type const& xp, const_pointer_type p) noexcept
		{
		 	return
		 		static_cast<const_pointer_type>(
		 			reinterpret_cast<void const*>(xp ^ reinterpret_cast<xorptr_type>(p))
		 		)
		 	;
		}
	};	

// execute this code if CXX_XOR_PROJECT_USE_REINTERPRET_CAST is defined
#elif defined(CXX_XOR_PROJECT_USE_REINTERPRET_CAST)

	template <typename T>
	struct xorptr_traits final
	{
		// pointer_type is an alias for T*
		using pointer_type = T*;

		// const_pointer_type is an alias for T const*
		using const_pointer_type = T const*;

		// xorptr_type is an alias for void*
		using xorptr_type = void*;

		// Create an XOR-encoded pointer value of two nullptr values
		static xorptr_type create() noexcept 
		{
		 	return create(static_cast<T*>(nullptr), static_cast<T*>(nullptr));
		}

		 // Create an XOR-encoded pointer value of two non-const pointer values
		 static xorptr_type create(
		 	pointer_type p1, pointer_type p2
		) noexcept
		{
		 	// ucharptr is an alias for unsigned char*
		 	using ucharptr = unsigned char*;

		 	// Every access on a volatile object is treated as a visible side-effect
		 	// for the purposes of optimization. Any attempt to refer to a volatile
		 	// object through a reference or pointer to non-volatile type results
		 	// in undefined behaviour
		 	void* volatile vp1 = p1;
		 	void* volatile vp2 = p2;

		 	// ucp1 is an unsigned char* that points to vp1.
		 	// We are doing this so that we can manipulate the bits
		 	// at vp1 algebraically.
		 	ucharptr ucp1 = static_cast<ucharptr>(
		 						reinterpret_cast<void*>(
		 							const_cast<void**>(
		 								&vp1
		 							)
		 						)
		 					);

		 	// Same as above
		 	ucharptr ucp2 = static_cast<ucharptr>(
		 						reinterpret_cast<void*>(
		 							const_cast<void**>(
		 								&vp2
		 							)
		 						)
		 					);

		 // 	// obtaining and observing the values
		 // 	// pointed to by ucp1 and ucp2 before
		 // 	// xor takes place
		 // 	std::bitset<sizeof(void*)*8> w(*ucp1);
		 // 	std::bitset<sizeof(void*)*8> x(*ucp2);

		 // 	std::cout << "function: static xorptr_type create("
		 // 				 "\n\tconst_pointer_type p1, const_pointer_type p2"
		 // 				 "\n) noexcept\n\n";

			// std::cout << "before xor: \n";

		 // 	std::cout << "ucp1: " << w << "\n"
		 // 			  << "ucp2: " << x << "\n\n";

		 	// xor the bytes pointed to by ucp1 and ucp2 and 
		 	// back in object pointed to by ucp1.
		 	// Since ucp1 points to vp1, this changes the value
		 	// of vp1.
		 	for (unsigned i = 0; i < sizeof(void*); ++i) {
		 		ucp1[i] ^= ucp2[i];
		 	}

		 	// // obtaining and observing the values
		 	// // pointed to by ucp1 and ucp2 after
		 	// // xor takes place
		 	// std::bitset<sizeof(void*)*8> y(*ucp1);
		 	// std::bitset<sizeof(void*)*8> z(*ucp2);

		 	// std::cout << "after xor: \n";

		 	// std::cout << "ucp1: " << y << "\n"
		 	// 		  << "ucp2: " << z << "\n\n";

		 	// Cast vp1 to xorptr_type and return
		 	return static_cast<xorptr_type>(vp1);
		}

		 // Create an XOR-encoded pointer value of two const pointer values
		 // This method does the same thing as the previous one, except it
		 // takes const pointer parameters
		 static xorptr_type create(
		 	const_pointer_type p1, const_pointer_type p2
		) noexcept
		{
		 	using ucharptr = unsigned char*;
		 	void const* volatile vp1 = p1;
		 	void const* volatile vp2 = p2;

		 	ucharptr ucp1 = static_cast<ucharptr>(
		 						reinterpret_cast<void*>(
		 							const_cast<void**>(
		 								&vp1
		 							)
		 						)
		 					);

		 	ucharptr ucp2 = static_cast<ucharptr>(
		 						reinterpret_cast<void*>(
		 							const_cast<void**>(
		 								&vp2
		 							)
		 						)
		 					);

		 // 	// obtaining and observing the values
		 // 	// pointed to by ucp1 and ucp2 before
		 // 	// xor takes place
		 // 	std::bitset<sizeof(void*)*8> w(*ucp1);
		 // 	std::bitset<sizeof(void*)*8> x(*ucp2);

		 // 	std::cout << "function: static xorptr_type create("
		 // 				 "\n\tconst_pointer_type p1, const_pointer_type p2"
		 // 				 "\n) noexcept\n\n";

			// std::cout << "before xor: \n";

		 // 	std::cout << "ucp1: " << w << "\n"
		 // 			  << "ucp2: " << x << "\n\n";

		 	for (unsigned i = 0; i < sizeof(void*); ++i) {
		 		ucp1[i] ^= ucp2[i];
		 	}

		 	// // obtaining and observing the values
		 	// // pointed to by ucp1 and ucp2 after
		 	// // xor takes place
		 	// std::bitset<sizeof(void*)*8> y(*ucp1);
		 	// std::bitset<sizeof(void*)*8> z(*ucp2);

		 	// std::cout << "after xor: \n";

		 	// std::cout << "ucp1: " << y << "\n"
		 	// 		  << "ucp2: " << z << "\n\n";

		 	return const_cast<xorptr_type>(vp1);
		}

		// Compute the XOR of an XOR-encoded pointer with a normal pointer.
		 static pointer_type extract(
			 xorptr_type const& xp,
			 pointer_type p
		) noexcept
		{
		 	using ucharptr = unsigned char*;
		 	void* volatile vp1 = xp;
		 	void* volatile vp2 = p;

		 	// Variables used to manipulate vp1 and vp2
		 	ucharptr ucp1 = static_cast<ucharptr>(
		 						reinterpret_cast<void*>(
		 							const_cast<void**>(
		 								&vp1
		 							)
		 						)
		 					);

		 	ucharptr ucp2 = static_cast<ucharptr>(
		 						reinterpret_cast<void*>(
		 							const_cast<void**>(
		 								&vp2
		 							)
		 						)
		 					);

		 	// xor *ucp1 and *ucp2, store in *ucp1
		 	for (unsigned i = 0; i < sizeof(void*); ++i) {
		 		ucp1[i] ^= ucp2[i];
		 	}

		 	return static_cast<pointer_type>(vp1);
		}

		 // Compute the XOR of an XOR-encoded pointer with a const pointer
		 // NOTE: The result is a const pointer. See cast hints below.
		 static const_pointer_type extract(
			 xorptr_type const& xp,
			 const_pointer_type p
		) noexcept
		{
		 	using ucharptr = unsigned char*;
		 	void const* volatile vp1 = xp;
		 	void const* volatile vp2 = p;

		 	ucharptr ucp1 = static_cast<ucharptr>(
		 						reinterpret_cast<void*>(
		 							const_cast<void**>(
		 								&vp1
		 							)
		 						)
		 					);

		 	ucharptr ucp2 = static_cast<ucharptr>(
		 						reinterpret_cast<void*>(
		 							const_cast<void**>(
		 								&vp2
		 							)
		 						)
		 					);

		 	for (unsigned i = 0; i < sizeof(void*); ++i) {
		 		ucp1[i] ^= ucp2[i];
		 	}

		 	return static_cast<const_pointer_type>(vp1);
		}
	};
#endif

template <typename T>
class xorptr final
{
public:
	
	using traits_type = xorptr_traits<T>;
	using pointer_type = typename traits_type::pointer_type;
 	using const_pointer_type = typename traits_type::const_pointer_type;
private:

 	using xorptr_type = typename traits_type::xorptr_type;
 	xorptr_type xorptr_;
public:

	xorptr() noexcept:
		xorptr_{traits_type::create()}
	{}

	explicit xorptr(pointer_type ptr1, pointer_type ptr2) noexcept:
		xorptr_{traits_type::create(ptr1, ptr2)}
	{}

	explicit xorptr(
	const_pointer_type ptr1, const_pointer_type ptr2
	) noexcept:
		xorptr_{traits_type::create(ptr1, ptr2)}
	{}

	xorptr(xorptr const& xp) noexcept = default;

	xorptr(xorptr&& xp) noexcept = default;

	xorptr& operator =(xorptr const& xp) noexcept = default;

	xorptr& operator =(xorptr&& xp) noexcept = default;

	~xorptr() noexcept = default;

	pointer_type operator ^(pointer_type& b) const noexcept
	{
		return traits_type::extract(xorptr_, b);
	}

	const_pointer_type operator ^(const_pointer_type& b) const noexcept
	{
		return traits_type::extract(xorptr_, b);
	}
};
