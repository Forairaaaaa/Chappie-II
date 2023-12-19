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
class SFixed;

template< unsigned Integer, unsigned Fraction >
class UFixed
{
public:
	static constexpr uintmax_t IntegerSize = Integer;
	static constexpr uintmax_t FractionSize = Fraction;
	static constexpr uintmax_t LogicalSize = IntegerSize + FractionSize;
	static constexpr uintmax_t Scale = UINTMAX_C(1) << FractionSize;

public:
	static_assert(LogicalSize <= FIXED_POINTS_DETAILS::BitSize<uintmax_t>::Value, "Platform does not have a native type large enough for UFixed.");

public:
	using IntegerType = FIXED_POINTS_DETAILS::LeastUInt<IntegerSize>;
	using FractionType = FIXED_POINTS_DETAILS::LeastUInt<FractionSize>;
	using InternalType = FIXED_POINTS_DETAILS::LeastUInt<LogicalSize>;

	static constexpr uintmax_t InternalSize = FIXED_POINTS_DETAILS::BitSize<InternalType>::Value;
	
	using ShiftType = FIXED_POINTS_DETAILS::LeastUInt<LogicalSize>;
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
	constexpr UFixed(const RawType & value);
	
public:
	constexpr UFixed();
	constexpr UFixed(const IntegerType & integer, const FractionType & fraction);
	constexpr UFixed(const char & value);
	constexpr UFixed(const unsigned char & value);
	constexpr UFixed(const signed char & value);
	constexpr UFixed(const unsigned short int & value);
	constexpr UFixed(const signed short int & value);
	constexpr UFixed(const unsigned int & value);
	constexpr UFixed(const signed int & value);
	constexpr UFixed(const unsigned long int & value);
	constexpr UFixed(const signed long int & value);
	constexpr UFixed(const unsigned long long int & value);
	constexpr UFixed(const signed long long int & value);
	constexpr UFixed(const double & value);
	constexpr UFixed(const float & value);
	constexpr UFixed(const long double & value);
	
public:
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
	constexpr explicit operator UFixed<IntegerOut, FractionOut>() const;

	template< unsigned IntegerOut, unsigned FractionOut >
	constexpr explicit operator SFixed<IntegerOut, FractionOut>() const;

	constexpr explicit operator SFixed<Integer - 1, Fraction>() const;

	static constexpr UFixed fromInternal(const InternalType & value);

	UFixed & operator ++();
	UFixed & operator --();
	UFixed & operator +=(const UFixed & other);
	UFixed & operator -=(const UFixed & other);
	UFixed & operator *=(const UFixed & other);
	UFixed & operator /=(const UFixed & other);
	
public:
	static constexpr UFixed Epsilon = UFixed::fromInternal(1);
	static constexpr UFixed MinValue = UFixed::fromInternal(0);
	static constexpr UFixed MaxValue = UFixed::fromInternal(~0);
	
	// 40 digits is probably enough for these
	static constexpr UFixed Pi = 3.1415926535897932384626433832795028841971;
	static constexpr UFixed E = 2.718281828459045235360287471352662497757;
	static constexpr UFixed Phi = 1.6180339887498948482045868343656381177203;
	static constexpr UFixed Tau = 6.2831853071795864769252867665590057683943;
};


//
// Free functions
//

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer * 2, Fraction * 2> multiply(const UFixed<Integer, Fraction> & left, const UFixed<Integer, Fraction> & right);


//
// Basic Logic Operations
//

template< unsigned Integer, unsigned Fraction >
constexpr bool operator ==(const UFixed<Integer, Fraction> & left, const UFixed<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr bool operator !=(const UFixed<Integer, Fraction> & left, const UFixed<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr bool operator <(const UFixed<Integer, Fraction> & left, const UFixed<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr bool operator >(const UFixed<Integer, Fraction> & left, const UFixed<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr bool operator <=(const UFixed<Integer, Fraction> & left, const UFixed<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr bool operator >=(const UFixed<Integer, Fraction> & left, const UFixed<Integer, Fraction> & right);

//
// Inter-size Logic Operations
//

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr bool operator ==(const UFixed<IntegerLeft, FractionLeft> & left, const UFixed<IntegerRight, FractionRight> & right);

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr bool operator !=(const UFixed<IntegerLeft, FractionLeft> & left, const UFixed<IntegerRight, FractionRight> & right);

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr bool operator <(const UFixed<IntegerLeft, FractionLeft> & left, const UFixed<IntegerRight, FractionRight> & right);

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr bool operator >(const UFixed<IntegerLeft, FractionLeft> & left, const UFixed<IntegerRight, FractionRight> & right);

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr bool operator <=(const UFixed<IntegerLeft, FractionLeft> & left, const UFixed<IntegerRight, FractionRight> & right);

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr bool operator >=(const UFixed<IntegerLeft, FractionLeft> & left, const UFixed<IntegerRight, FractionRight> & right);

//
// Basic Arithmetic Operations
//

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction> operator +(const UFixed<Integer, Fraction> & left, const UFixed<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction> operator -(const UFixed<Integer, Fraction> & left, const UFixed<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction> operator *(const UFixed<Integer, Fraction> & left, const UFixed<Integer, Fraction> & right);

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction> operator /(const UFixed<Integer, Fraction> & left, const UFixed<Integer, Fraction> & right);

//
// Inter-size Arithmetic Operations
//

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr auto operator +(const UFixed<IntegerLeft, FractionLeft> & left, const UFixed<IntegerRight, FractionRight> & right)
	-> FIXED_POINTS_DETAILS::LargerType< UFixed<IntegerLeft, FractionLeft>, UFixed<IntegerRight, FractionRight> >;

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr auto operator -(const UFixed<IntegerLeft, FractionLeft> & left, const UFixed<IntegerRight, FractionRight> & right)
	-> FIXED_POINTS_DETAILS::LargerType< UFixed<IntegerLeft, FractionLeft>, UFixed<IntegerRight, FractionRight> >;

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
constexpr auto operator *(const UFixed<IntegerLeft, FractionLeft> & left, const UFixed<IntegerRight, FractionRight> & right)
	-> FIXED_POINTS_DETAILS::LargerType< UFixed<IntegerLeft, FractionLeft>, UFixed<IntegerRight, FractionRight> >;

template< unsigned IntegerLeft, unsigned FractionLeft, unsigned IntegerRight, unsigned FractionRight >
inline constexpr auto operator /(const UFixed<IntegerLeft, FractionLeft> & left, const UFixed<IntegerRight, FractionRight> & right)
	-> FIXED_POINTS_DETAILS::LargerType< UFixed<IntegerLeft, FractionLeft>, UFixed<IntegerRight, FractionRight> >;
	
FIXED_POINTS_END_NAMESPACE

#include "UFixedMemberFunctions.h"
#include "UFixedFreeFunctions.h"