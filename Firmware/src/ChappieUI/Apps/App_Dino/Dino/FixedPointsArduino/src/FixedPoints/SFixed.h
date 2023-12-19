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

#include "Details.h"

FIXED_POINTS_BEGIN_NAMESPACE

//
// Declaration
//

template< unsigned Integer, unsigned Fraction >
class UFixed;

template< unsigned Integer, unsigned Fraction >
class SFixed
{
public:
	static constexpr uintmax_t IntegerSize = Integer + 1;
	static constexpr uintmax_t FractionSize = Fraction;
	static constexpr uintmax_t LogicalSize = IntegerSize + FractionSize;
	static constexpr uintmax_t Scale = UINTMAX_C(1) << FractionSize;

public:
	static_assert(LogicalSize <= FIXED_POINTS_DETAILS::BitSize<intmax_t>::Value, "Platform does not have a native type large enough for SFixed.");

public:
	using IntegerType = FIXED_POINTS_DETAILS::LeastInt<IntegerSize>;
	using FractionType = FIXED_POINTS_DETAILS::LeastUInt<FractionSize>;
	using InternalType = FIXED_POINTS_DETAILS::LeastInt<LogicalSize>;

	static constexpr uintmax_t InternalSize = FIXED_POINTS_DETAILS::BitSize<InternalType>::Value;
	
	using ShiftType = FIXED_POINTS_DETAILS::LeastInt<LogicalSize>;
	using MaskType = FIXED_POINTS_DETAILS::LeastUInt<LogicalSize>;
		
public:
	static constexpr ShiftType IntegerShift = FractionSize;
	static constexpr ShiftType FractionShift = 0;
	
	static constexpr MaskType IntegerMask = FIXED_POINTS_DETAILS::IdentityMask<IntegerSize>::Value;
	static constexpr MaskType FractionMask = FIXED_POINTS_DETAILS::IdentityMask<FractionSize>::Value;
	
	static constexpr MaskType IdentityMask = (IntegerMask << IntegerShift) | (FractionMask << FractionShift);
	
	static constexpr MaskType MidpointMask = FIXED_POINTS_DETAILS::MsbMask<FractionSize>::Value;
	static constexpr MaskType LesserMidpointMask = MidpointMask - 1;

protected:
	class RawType
	{
	private:
		const InternalType value;

	public:
		constexpr explicit RawType(const InternalType & value) : value(value) {}
		constexpr explicit operator InternalType() const { return this->value; }
	};

protected:
	InternalType value;

protected:
	constexpr SFixed(const RawType & value);

public:
	constexpr SFixed();
	constexpr SFixed(const IntegerType & integer, const FractionType & fraction);
	constexpr SFixed(const char & value);
	constexpr SFixed(const unsigned char & value);
	constexpr SFixed(const signed char & value);
	constexpr SFixed(const unsigned short int & value);
	constexpr SFixed(const signed short int & value);
	constexpr SFixed(const unsigned int & value);
	constexpr SFixed(const signed int & value);
	constexpr SFixed(const unsigned long int & value);
	constexpr SFixed(const signed long int & value);
	constexpr SFixed(const unsigned long long int & value);
	constexpr SFixed(const signed long long int & value);
	constexpr SFixed(const double & value);
	constexpr SFixed(const float & value);
	constexpr SFixed(const long double & value);

	constexpr InternalType getInternal() const;
	constexpr IntegerType getInteger() const;
	constexpr FractionType getFraction() const;

	constexpr explicit operator char() const;
	constexpr explicit operator unsigned char() const;
	constexpr explicit operator signed char() const;
	constexpr explicit operator unsigned short int() const;
	constexpr explicit operator signed short int() const;
	constexpr explicit operator unsigned int() const;
	constexpr explicit operator signed int() const;
	constexpr explicit operator unsigned long int() const;
	constexpr explicit operator signed long int() const;
	constexpr explicit operator unsigned long long int() const;
	constexpr explicit operator signed long long int() const;

	constexpr explicit operator float() const;
	constexpr explicit operator double() const;
	constexpr explicit operator long double() const;

	template< unsigned IntegerOut, unsigned FractionOut >
	constexpr explicit operator SFixed<IntegerOut, FractionOut>() const;

	template< unsigned IntegerOut, unsigned FractionOut >
	constexpr explicit operator UFixed<IntegerOut, FractionOut>() const;

	constexpr explicit operator UFixed<Integer + 1, Fraction>() const;

	static constexpr SFixed fromInternal(const InternalType & value);

	constexpr SFixed operator -() const;
	SFixed & operator ++();
	SFixed & operator --();
	SFixed & operator +=(const SFixed & other);
	SFixed & operator -=(const SFixed & other);
	SFixed & operator *=(const SFixed & other);
	SFixed & operator /=(const SFixed & other);
	
public:
	static constexpr SFixed Epsilon = SFixed::fromInternal(1);
	static constexpr SFixed MinValue = SFixed::fromInternal(FIXED_POINTS_DETAILS::MsbMask<InternalSize>::Value);
	static constexpr SFixed MaxValue = SFixed::fromInternal(~FIXED_POINTS_DETAILS::MsbMask<InternalSize>::Value);
	
	// 40 digits is probably enough for these
	static constexpr SFixed Pi = 3.1415926535897932384626433832795028841971;
	static constexpr SFixed E = 2.718281828459045235360287471352662497757;
	static constexpr SFixed Phi = 1.6180339887498948482045868343656381177203;
	static constexpr SFixed Tau = 6.2831853071795864769252867665590057683943;
};


//
// Free functions
//

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer * 2, Fraction * 2> multiply(const SFixed<Integer, Fraction> & left, const SFixed<Integer, Fraction> & right);

//
// Basic Logic Operations
//

template< unsigned Integer, unsigned Fraction >
constexpr bool operator ==(const SFixed<Integer, Fraction> & left, const SFixed<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr bool operator !=(const SFixed<Integer, Fraction> & left, const SFixed<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr bool operator <(const SFixed<Integer, Fraction> & left, const SFixed<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr bool operator >(const SFixed<Integer, Fraction> & left, const SFixed<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr bool operator <=(const SFixed<Integer, Fraction> & left, const SFixed<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr bool operator >=(const SFixed<Integer, Fraction> & left, const SFixed<Integer, Fraction> & right);

//
// Inter-size Logic Operations
//

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr bool operator ==(const SFixed<IntegerLeft, FractionLeft> & left, const SFixed<IntegerRight, FractionRight> & right);

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr bool operator !=(const SFixed<IntegerLeft, FractionLeft> & left, const SFixed<IntegerRight, FractionRight> & right);

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr bool operator <(const SFixed<IntegerLeft, FractionLeft> & left, const SFixed<IntegerRight, FractionRight> & right);

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr bool operator >(const SFixed<IntegerLeft, FractionLeft> & left, const SFixed<IntegerRight, FractionRight> & right);

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr bool operator <=(const SFixed<IntegerLeft, FractionLeft> & left, const SFixed<IntegerRight, FractionRight> & right);

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr bool operator >=(const SFixed<IntegerLeft, FractionLeft> & left, const SFixed<IntegerRight, FractionRight> & right);

//
// Basic Arithmetic Operations
//

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction> operator +(const SFixed<Integer, Fraction> & left, const SFixed<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction> operator -(const SFixed<Integer, Fraction> & left, const SFixed<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction> operator *(const SFixed<Integer, Fraction> & left, const SFixed<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction> operator /(const SFixed<Integer, Fraction> & left, const SFixed<Integer, Fraction> & right);

//
// Inter-size Arithmetic Operations
//

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr auto operator +(const SFixed<IntegerLeft, FractionLeft> & left, const SFixed<IntegerRight, FractionRight> & right)
	-> FIXED_POINTS_DETAILS::LargerType< SFixed<IntegerLeft, FractionLeft>, SFixed<IntegerRight, FractionRight> >;

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr auto operator -(const SFixed<IntegerLeft, FractionLeft> & left, const SFixed<IntegerRight, FractionRight> & right)
	-> FIXED_POINTS_DETAILS::LargerType< SFixed<IntegerLeft, FractionLeft>, SFixed<IntegerRight, FractionRight> >;

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr auto operator *(const SFixed<IntegerLeft, FractionLeft> & left, const SFixed<IntegerRight, FractionRight> & right)
	-> FIXED_POINTS_DETAILS::LargerType< SFixed<IntegerLeft, FractionLeft>, SFixed<IntegerRight, FractionRight> >;

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
inline constexpr auto operator /(const SFixed<IntegerLeft, FractionLeft> & left, const SFixed<IntegerRight, FractionRight> & right)
	-> FIXED_POINTS_DETAILS::LargerType< SFixed<IntegerLeft, FractionLeft>, SFixed<IntegerRight, FractionRight> >;
	
FIXED_POINTS_END_NAMESPACE

#include "SFixedMemberFunctions.h"
#include "SFixedFreeFunctions.h"