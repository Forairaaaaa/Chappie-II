// Copyright 2017-2021 Pharap
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <Arduino.h>
#include <limits.h>
#include <stdint.h>

#if defined(FIXED_POINTS_USE_NAMESPACE)
#define FIXED_POINTS_NAMESPACE FixedPoints
#define FIXED_POINTS_BEGIN_NAMESPACE namespace FIXED_POINTS_NAMESPACE\
{
#define FIXED_POINTS_END_NAMESPACE }
#define FIXED_POINTS_DETAILS Details
#else
#define FIXED_POINTS_NAMESPACE
#define FIXED_POINTS_BEGIN_NAMESPACE
#define FIXED_POINTS_END_NAMESPACE
#define FIXED_POINTS_DETAILS FixedPointsDetails
#endif

#if !defined(__AVR__)
#define FIXED_POINTS_NO_RANDOM
#endif

// Pay no attention to the man behind the curtains

FIXED_POINTS_BEGIN_NAMESPACE
namespace FIXED_POINTS_DETAILS
{
	template< typename T >
	struct BitSize
	{
		BitSize() = delete;
		static constexpr auto Value = sizeof(T) * CHAR_BIT;
	};

	template< bool Condition, typename TTrue, typename TFalse >
	struct Conditional;

	template< typename TTrue, typename TFalse >
	struct Conditional< true, TTrue, TFalse > { using Type = TTrue; };

	template< typename TTrue, typename TFalse >
	struct Conditional< false, TTrue, TFalse > { using Type = TFalse; };
	
	template< bool Condition, typename TTrue, typename TFalse >
	using ConditionalT = typename Conditional<Condition, TTrue, TFalse >::Type;

	template< typename T, typename U >
	using LargerType = ConditionalT<(BitSize<T>::Value > BitSize<U>::Value), T, U>;

	template< typename T, typename U >
	using StrictLargerType = ConditionalT< (BitSize<T>::Value > BitSize<U>::Value), T, ConditionalT< (BitSize<U>::Value > BitSize<T>::Value), U, void > >;

	template< typename T, typename U >
	using SmallerType = ConditionalT<(BitSize<T>::Value < BitSize<U>::Value), T, U>;

	template< typename T, typename U >
	using StrictSmallerType = ConditionalT< (BitSize<T>::Value < BitSize<U>::Value), T, ConditionalT< (BitSize<U>::Value < BitSize<T>::Value), U, void > >;

	template< unsigned Bits, typename... Ts >
	struct LeastTypeHelper;

	template< unsigned Bits, typename T, typename... Ts >
	struct LeastTypeHelper<Bits, T, Ts... >
	{
		LeastTypeHelper() = delete;
		using Type = ConditionalT<(Bits <= BitSize<T>::Value), T, typename LeastTypeHelper<Bits, Ts...>::Type>;
	};

	template< unsigned Bits >
	struct LeastTypeHelper<Bits>
	{
		LeastTypeHelper() = delete;
		using Type = void;
	};


	template< unsigned Bits, typename... Ts >
	using LeastType = typename LeastTypeHelper<Bits, Ts...>::Type;

	template< unsigned Bits >
	struct LeastUIntDef
	{
		static_assert(Bits <= BitSize<uintmax_t>::Value, "No type large enough");
		LeastUIntDef() = delete;
		using Type = LeastType<Bits, uint_least8_t, uint_least16_t, uint_least32_t, uint_least64_t, uintmax_t>;
	};
	

	template< unsigned Bits >
	using LeastUInt = typename LeastUIntDef<Bits>::Type;

	template< unsigned Bits >
	struct LeastIntDef
	{
		static_assert(Bits <= BitSize<intmax_t>::Value, "No type large enough");
		LeastIntDef() = delete;
		using Type = LeastType<Bits, int_least8_t, int_least16_t, int_least32_t, int_least64_t, intmax_t>;
	};

	template< unsigned Bits >
	using LeastInt = typename LeastIntDef<Bits>::Type;

	template< unsigned Bits >
	struct MsbMask
	{
		MsbMask() = delete;
		static constexpr LeastUInt<Bits> Value = (1ull << (Bits - 1));
	};

	template< unsigned Bits >
	struct IdentityMask
	{
		IdentityMask() = delete;
		static constexpr LeastUInt<Bits> Value = 1 | (static_cast<LeastUInt<Bits>>(IdentityMask<Bits - 1>::Value) << 1);
	};

	template<>
	struct IdentityMask<0>
	{
		IdentityMask() = delete;
		static constexpr LeastUInt<0> Value = 0;
	};
	
#if !defined(FIXED_POINTS_NO_RANDOM)
	template< typename T >
	struct RandomHelper;
	
	template<>
	struct RandomHelper<uint8_t>
	{
		static inline uint8_t Random() { return static_cast<uint8_t>(random()); }
	};
	
	template<>
	struct RandomHelper<uint16_t>
	{
		static inline uint16_t Random() { return static_cast<uint16_t>(random()); }
	};
	
	template<>
	struct RandomHelper<uint32_t>
	{
		static inline uint32_t Random() { return static_cast<uint32_t>(random()); }
	};
	
	template<>
	struct RandomHelper<uint64_t>
	{
		static inline uint64_t Random() { return (static_cast<uint64_t>(random()) << 32) | static_cast<uint64_t>(random()); }
	};
	
	template<>
	struct RandomHelper<int8_t>
	{
		static inline int8_t Random() { return static_cast<int8_t>(random()); }
	};
	
	template<>
	struct RandomHelper<int16_t>
	{
		static inline int16_t Random() { return static_cast<int16_t>(random()); }
	};
	
	template<>
	struct RandomHelper<int32_t>
	{
		static inline int32_t Random() { return static_cast<int32_t>(random()); }
	};
	
	template<>
	struct RandomHelper<int64_t>
	{
		static inline int64_t Random() { return (static_cast<int64_t>(random()) << 32) | static_cast<int64_t>(random()); }
	};
#endif

	///////////////////////
	// Here be dragons!! //
	//                   //
	//     /\___/\  _    //
	//    ( O . O ) \\   //
	//     >  ^  <  //   //
	//    ( \   / )//    //
	//     u U U u       //
	//                   //
	//    Or cats?...    //
	//     ~Mwrow~       //
	///////////////////////
}
FIXED_POINTS_END_NAMESPACE
