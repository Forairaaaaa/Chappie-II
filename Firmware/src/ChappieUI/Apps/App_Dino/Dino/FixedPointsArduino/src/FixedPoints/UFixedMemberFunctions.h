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

FIXED_POINTS_BEGIN_NAMESPACE

//
// Constructors
//

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const RawType & value)
	: value(static_cast<InternalType>(value))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed()
	: value(0)
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const IntegerType & integer, const FractionType & fraction)
	: value((static_cast<InternalType>(integer) << FractionSize) | fraction)
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const char & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<char, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const unsigned char & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<unsigned char, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const signed char & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<signed char, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const unsigned short int & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<unsigned short int, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const signed short int & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<signed short int, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const unsigned int & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<unsigned int, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const signed int & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<signed int, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const unsigned long int & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<unsigned long int, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const signed long int & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<signed long int, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const unsigned long long int & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<unsigned long long int, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const signed long long int & value)
	: value(static_cast<InternalType>(static_cast< FIXED_POINTS_DETAILS::LargerType<signed long long int, InternalType> >(value) << FractionSize))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const double & value)
	: value(static_cast<InternalType>(value * static_cast<double>(Scale)))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const float & value)
	: value(static_cast<InternalType>(value * static_cast<float>(Scale)))
{
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::UFixed(const long double & value)
	: value(static_cast<InternalType>(value * static_cast<long double>(Scale)))
{
}

//
// Getters
//

template< unsigned Integer, unsigned Fraction >
constexpr typename UFixed<Integer, Fraction>::InternalType UFixed<Integer, Fraction>::getInternal() const
{
	return this->value;
}

template< unsigned Integer, unsigned Fraction >
constexpr typename UFixed<Integer, Fraction>::IntegerType UFixed<Integer, Fraction>::getInteger() const
{
	return static_cast<IntegerType>(this->value >> IntegerShift) & IntegerMask;
}

template< unsigned Integer, unsigned Fraction >
constexpr typename UFixed<Integer, Fraction>::FractionType UFixed<Integer, Fraction>::getFraction() const
{
	return static_cast<FractionType>(this->value >> FractionShift) & FractionMask;
}

//
// Cast Operators
//

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::operator char() const
{
	return this->getInteger();
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::operator unsigned char() const
{
	return this->getInteger();
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::operator signed char() const
{
	return this->getInteger();
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::operator unsigned short int() const
{
	return this->getInteger();
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::operator signed short int() const
{
	return this->getInteger();
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::operator unsigned int() const
{
	return this->getInteger();
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::operator signed int() const
{
	return this->getInteger();
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::operator unsigned long int() const
{
	return this->getInteger();
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::operator signed long int() const
{
	return this->getInteger();
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::operator unsigned long long int() const
{
	return this->getInteger();
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::operator signed long long int() const
{
	return this->getInteger();
}



template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::operator float() const
{
	return ((this->value & IdentityMask) * (1.0F / Scale));
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::operator double() const
{
	return ((this->value & IdentityMask) * (1.0 / Scale));
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::operator long double() const
{
	return ((this->value & IdentityMask) * (1.0L / Scale));
}

template< unsigned Integer, unsigned Fraction >
template< unsigned IntegerOut, unsigned FractionOut >
constexpr UFixed<Integer, Fraction>::operator UFixed<IntegerOut, FractionOut>() const
{
	using OutputType = UFixed<IntegerOut, FractionOut>;
	using OutputInternalType = typename OutputType::InternalType;
	using OutputShiftType = typename OutputType::ShiftType;
	
	using InputType = UFixed<Integer, Fraction>;
	using InputShiftType = typename InputType::ShiftType;
	
	return
	(FractionOut > FractionSize) ?
		OutputType::fromInternal(static_cast<OutputInternalType>(static_cast<OutputShiftType>(this->value) << ((FractionOut > FractionSize) ? (FractionOut - FractionSize) : 0))) :
	(FractionSize > FractionOut) ?
		OutputType::fromInternal(static_cast<OutputInternalType>(static_cast<InputShiftType>(this->value) >> ((FractionSize > FractionOut) ? (FractionSize - FractionOut) : 0))) :
		OutputType::fromInternal(this->value);
}

template< unsigned Integer, unsigned Fraction >
template< unsigned IntegerOut, unsigned FractionOut >
constexpr UFixed<Integer, Fraction>::operator SFixed<IntegerOut, FractionOut>() const
{
	using OutputType = SFixed<IntegerOut, FractionOut>;
	using IntermediaryType = UFixed<IntegerOut + 1, FractionOut>;

	return static_cast<OutputType>(static_cast<IntermediaryType>(*this));
}

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction>::operator SFixed<Integer - 1, Fraction>() const
{
	using OutputType = SFixed<Integer - 1, Fraction>;
	using OutputInternalType = typename OutputType::InternalType;
	
	return OutputType::fromInternal(static_cast<OutputInternalType>(this->value));
}

//
// Static Functions
//

template< unsigned Integer, unsigned Fraction >
constexpr UFixed<Integer, Fraction> UFixed<Integer, Fraction>::fromInternal(const typename UFixed<Integer, Fraction>::InternalType & value)
{
	return UFixed<Integer, Fraction>(RawType(value));
}

//
// Member Operators
//

template< unsigned Integer, unsigned Fraction >
UFixed<Integer, Fraction> & UFixed<Integer, Fraction>::operator ++()
{
	this->value += (static_cast<InternalType>(1) << FractionSize);
	return *this;
}

template< unsigned Integer, unsigned Fraction >
UFixed<Integer, Fraction> & UFixed<Integer, Fraction>::operator --()
{
	this->value -= (static_cast<InternalType>(1) << FractionSize);
	return *this;
}

//
// Compound Assignment Operators
//

template< unsigned Integer, unsigned Fraction >
UFixed<Integer, Fraction> & UFixed<Integer, Fraction>::operator +=(const UFixed<Integer, Fraction> & other)
{
	this->value += other.value;
	return *this;
}

template< unsigned Integer, unsigned Fraction >
UFixed<Integer, Fraction> & UFixed<Integer, Fraction>::operator -=(const UFixed<Integer, Fraction> & other)
{
	this->value -= other.value;
	return *this;
}

template< unsigned Integer, unsigned Fraction >
UFixed<Integer, Fraction> & UFixed<Integer, Fraction>::operator *=(const UFixed<Integer, Fraction> & other)
{
	using InternalType = typename UFixed<Integer, Fraction>::InternalType;
	using PrecisionType = typename UFixed<Integer * 2, Fraction * 2>::InternalType;
	const PrecisionType temp = (static_cast<PrecisionType>(this->value) * static_cast<PrecisionType>(other.value)) >> FractionSize;
	this->value = static_cast<InternalType>(temp);
	return *this;
}

template< unsigned Integer, unsigned Fraction >
UFixed<Integer, Fraction> & UFixed<Integer, Fraction>::operator /=(const UFixed<Integer, Fraction> & other)
{
	using InternalType = typename UFixed<Integer, Fraction>::InternalType;
	using PrecisionType = typename UFixed<Integer * 2, Fraction * 2>::InternalType;
	const PrecisionType temp = (static_cast<PrecisionType>(this->value) << FractionSize) / static_cast<PrecisionType>(other.value);
	this->value = static_cast<InternalType>(temp);
	return *this;
}

FIXED_POINTS_END_NAMESPACE