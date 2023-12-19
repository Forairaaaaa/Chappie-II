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
#include "UFixed.h"
#include "SFixed.h"

//
// Declaration
//

FIXED_POINTS_BEGIN_NAMESPACE

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction> floorFixed(const UFixed<Integer, Fraction> & value);

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction> floorFixed(const SFixed<Integer, Fraction> & value);

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction> ceilFixed(const UFixed<Integer, Fraction> & value);

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction> ceilFixed(const SFixed<Integer, Fraction> & value);

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction> roundFixed(const UFixed<Integer, Fraction> & value);

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction> roundFixed(const SFixed<Integer, Fraction> & value);

template< unsigned Integer, unsigned Fraction >
constexpr bool signbitFixed(const SFixed<Integer, Fraction> & value);

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction> absFixed(const SFixed<Integer, Fraction> & value);

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction> copysignFixed(const SFixed<Integer, Fraction> & x, const SFixed<Integer, Fraction> & y);

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction> nextafterFixed(const SFixed<Integer, Fraction> & from, const SFixed<Integer, Fraction> & to);

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction> nextafterFixed(const UFixed<Integer, Fraction> & from, const UFixed<Integer, Fraction> & to);

//
// Unsigned Random
//

#if !defined(FIXED_POINTS_NO_RANDOM)
template< unsigned Integer, unsigned Fraction >
UFixed<Integer, Fraction> randomUFixed();

template< unsigned Integer, unsigned Fraction >
UFixed<Integer, Fraction> randomUFixed(const UFixed<Integer, Fraction> & exclusiveUpperBound);

template< unsigned Integer, unsigned Fraction >
UFixed<Integer, Fraction> randomUFixed(const UFixed<Integer, Fraction> & inclusiveLowerBound, const UFixed<Integer, Fraction> & exclusiveUpperBound);
#endif

//
// Signed Random
//

#if !defined(FIXED_POINTS_NO_RANDOM)
template< unsigned Integer, unsigned Fraction >
SFixed<Integer, Fraction> randomSFixed();

template< unsigned Integer, unsigned Fraction >
SFixed<Integer, Fraction> randomSFixed(const SFixed<Integer, Fraction> & exclusiveUpperBound);

template< unsigned Integer, unsigned Fraction >
SFixed<Integer, Fraction> randomSFixed(const SFixed<Integer, Fraction> & inclusiveLowerBound, const SFixed<Integer, Fraction> & exclusiveUpperBound);
#endif

FIXED_POINTS_END_NAMESPACE

//
// Definition
//

FIXED_POINTS_BEGIN_NAMESPACE

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction> floorFixed(const UFixed<Integer, Fraction> & value)
{
	using OutputType = UFixed<Integer, Fraction>;
	using InternalType = typename OutputType::InternalType;
	return OutputType::fromInternal(static_cast<InternalType>(value.getInternal() & ~OutputType::FractionMask));
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction> floorFixed(const SFixed<Integer, Fraction> & value)
{
	using OutputType = SFixed<Integer, Fraction>;
	using InternalType = typename OutputType::InternalType;
	return OutputType::fromInternal(static_cast<InternalType>(value.getInternal() & ~OutputType::FractionMask));
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction> ceilFixed(const UFixed<Integer, Fraction> & value)
{	
	return UFixed<Integer, Fraction>((value.getFraction() == 0) ? value.getInteger() : (value.getInteger() + 1), 0);
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction> ceilFixed(const SFixed<Integer, Fraction> & value)
{
	return SFixed<Integer, Fraction>((value.getFraction() == 0) ? value.getInteger() : (value.getInteger() + 1), 0);
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction> roundFixed(const UFixed<Integer, Fraction> & value)
{
	using OutputType = UFixed<Integer, Fraction>;
	return (value.getFraction() >= OutputType(0.5).getFraction()) ? ceilFixed(value) : floorFixed(value);
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction> roundFixed(const SFixed<Integer, Fraction> & value)
{
	using OutputType = SFixed<Integer, Fraction>;
	return		
		signbitFixed(value) ?
		((value.getFraction() <= OutputType(0.5).getFraction()) ? floorFixed(value) : ceilFixed(value)) :
		((value.getFraction() >= OutputType(0.5).getFraction()) ? ceilFixed(value) : floorFixed(value));
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction> truncFixed(const UFixed<Integer, Fraction> & value)
{
	return UFixed<Integer, Fraction>(value.getInteger(), 0);
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction> truncFixed(const SFixed<Integer, Fraction> & value)
{
	using OutputType = SFixed<Integer, Fraction>;
	return 
		(value.getInternal() < 0) ?
		OutputType::fromInternal(value.getInternal() & ~OutputType::FractionMask) + OutputType(1, 0) :
		OutputType::fromInternal(value.getInternal() & ~OutputType::FractionMask);
}

template< unsigned Integer, unsigned Fraction >
constexpr bool signbitFixed(const SFixed<Integer, Fraction> & value)
{
	return (value.getInternal() < 0);
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction> absFixed(const SFixed<Integer, Fraction> & value)
{
	return (signbitFixed(value)) ? -value : value;
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction> copysignFixed(const SFixed<Integer, Fraction> & x, const SFixed<Integer, Fraction> & y)
{
	return (signbitFixed(x) != signbitFixed(y)) ? -x : x;
}

template< unsigned Integer, unsigned Fraction >
constexpr SFixed<Integer, Fraction> nextafterFixed(const SFixed<Integer, Fraction> & from, const SFixed<Integer, Fraction> & to)
{
	using ResultType = SFixed<Integer, Fraction>;
	return
		(from < to) ?
		ResultType::fromInternal(from.getInternal() + 1) :
		(from > to) ?
		ResultType::fromInternal(from.getInternal() - 1) :
		to;
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction> nextafterFixed(const UFixed<Integer, Fraction> & from, const UFixed<Integer, Fraction> & to)
{
	using ResultType = UFixed<Integer, Fraction>;
	return
		(from < to) ?
		ResultType::fromInternal(from.getInternal() + 1) :
		(from > to) ?
		ResultType::fromInternal(from.getInternal() - 1) :
		to;
}

//
// Unsigned Random
//

#if !defined(FIXED_POINTS_NO_RANDOM)
template< unsigned Integer, unsigned Fraction >
UFixed<Integer, Fraction> randomUFixed()
{
	using InternalType = typename UFixed<Integer, Fraction>::InternalType;
	return UFixed<Integer, Fraction>::fromInternal(FIXED_POINTS_DETAILS::RandomHelper<InternalType>::Random());
}

template< unsigned Integer, unsigned Fraction >
UFixed<Integer, Fraction> randomUFixed(const UFixed<Integer, Fraction> & exclusiveUpperBound)
{
	using InternalType = typename UFixed<Integer, Fraction>::InternalType;
	return UFixed<Integer, Fraction>::fromInternal(FIXED_POINTS_DETAILS::RandomHelper<InternalType>::Random() % exclusiveUpperBound.getInternal());
}

template< unsigned Integer, unsigned Fraction >
UFixed<Integer, Fraction> randomUFixed(const UFixed<Integer, Fraction> & inclusiveLowerBound, const UFixed<Integer, Fraction> & exclusiveUpperBound)
{
	using InternalType = typename UFixed<Integer, Fraction>::InternalType;
	return UFixed<Integer, Fraction>::fromInternal(inclusiveLowerBound.getInternal() + (FIXED_POINTS_DETAILS::RandomHelper<InternalType>::Random() % (exclusiveUpperBound.getInternal() - inclusiveLowerBound.getInternal())));
}
#endif

//
// Signed Random
//

#if !defined(FIXED_POINTS_NO_RANDOM)
template< unsigned Integer, unsigned Fraction >
SFixed<Integer, Fraction> randomSFixed()
{
	using InternalType = typename SFixed<Integer, Fraction>::InternalType;
	return SFixed<Integer, Fraction>::fromInternal(FIXED_POINTS_DETAILS::RandomHelper<InternalType>::Random());
}

template< unsigned Integer, unsigned Fraction >
SFixed<Integer, Fraction> randomSFixed(const SFixed<Integer, Fraction> & exclusiveUpperBound)
{
	using InternalType = typename SFixed<Integer, Fraction>::InternalType;
	return SFixed<Integer, Fraction>::fromInternal(FIXED_POINTS_DETAILS::RandomHelper<InternalType>::Random() % exclusiveUpperBound.getInternal());
}

template< unsigned Integer, unsigned Fraction >
SFixed<Integer, Fraction> randomSFixed(const SFixed<Integer, Fraction> & inclusiveLowerBound, const SFixed<Integer, Fraction> & exclusiveUpperBound)
{
	using InternalType = typename SFixed<Integer, Fraction>::InternalType;
	auto value = FIXED_POINTS_DETAILS::RandomHelper<InternalType>::Random();
	return SFixed<Integer, Fraction>::fromInternal(inclusiveLowerBound.getInternal() + (abs(value) % (exclusiveUpperBound.getInternal() - inclusiveLowerBound.getInternal())));
}
#endif

FIXED_POINTS_END_NAMESPACE
