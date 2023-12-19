# FixedPoints
A portable fixed point arithmetic library.

Some knowledge of how fixed point types are formatted is required to used this library to full effect.
No knowledge of how these operations are implemented is required to use them.

This library was written with Arduino in mind, as well as CPUs with limited floating point support.
However, given the templated nature of the library, it should still function on a wide variety of CPUs.

## Project Showcase

Here's a list of projects that use `FixedPoints`:

* [1943](https://github.com/filmote/Nineteen43) for the [Arduboy](https://arduboy.com/) by [@filmote](https://github.com/filmote)
* [XOD Powered Rechargeable Solar Lamp](http://www.instructables.com/id/XOD-powered-Rechargeable-Solar-Lamp/) by [Victorian DeLorean](http://www.instructables.com/member/Victorian%20DeLorean/)
* [Pod Manager](https://github.com/felipemanga/PodManager) for the [Arduboy](https://arduboy.com/) by [@felipemanga](https://github.com/felipemanga)

If you have a project that uses `FixedPoints` and would like your work to be showcased here,
please [raise an issue](https://github.com/Pharap/FixedPointsArduino/issues/new).

## Requirements:

- The Compiler must be C++11 compliant.
- The user should ideally be familar with the [Q number format](https://en.wikipedia.org/wiki/Q_(number_format)) for fixed points.

## Licence

This code uses the Apache 2.0 Licence.
This means:

- This code comes with _no warranty_.
  - The licensor and any contributors **cannot** be held liable for damages.
- If you use this code, modified or unmodified:
  - You **must** package a copy of LICENCE with your code.
  - You **must** package a copy of NOTICE with your code.
  - You are not required to distribute the source code.
- You **must not** use any trademarks owned by the licensor.
  - Unless you have specific permission to do so.
- You **may** modify the source code.
  - If you modify the code, you **must** state this fact prominently within the source file.
    - E.g. in a comment at the top of the source file.
  - You are under no obligation to distribute the source code of your modifications.
- You may incorporate any part of the code into another project.
  - That project **may** use a different licence.
  - That code **must** retain the Apache 2.0 licence notice, including the copyright notice.
  - If the code is modified, the modifications **may** be published under a different licence.
    - The Apache 2.0 licence still applies to unmodified portions.
    - The copyright and licence notices for the unmodified portions **must** still be prominently displayed.
    - It is advised that you do not do this, as it is highly unusual and untested in court.

## Conditional Compilation

These are symbols you can define prior to library inclusion to alter the behaviour of the library.

- `FIXED_POINTS_USE_NAMESPACE`: Define this to wrap all classes and functions in the namespace `FixedPoints`. Useful for preventing naming conflicts.
- `FIXED_POINTS_NO_RANDOM`: Define this to disable the random utility functions. Useful for systems that don't have access to `long random(void)` from avr-libc.

## FAQ

* Why can't I multiply `UQ32x32` or `SQ31x32` by another type?
  * Because it would require a 128-bit integer type to provide enough precision for accurate multiplication.

## Contents
This library supplies two core types and sixteen type aliases.

### Defines

- `FIXED_POINTS_NAMESPACE`: The namespace used by FixedPoints. This is empty unless `FIXED_POINTS_USE_NAMESPACE` is defined prior to inclusion.
- `FIXED_POINTS_DETAILS`: An infrastructure macro that should not be used in user code. It is safe to undefine this if it is causing problems.
- `FIXED_POINTS_BEGIN_NAMESPACE`: An infrastructure macro that should not be used in user code. It is safe to undefine this if it is causing problems.
- `FIXED_POINTS_END_NAMESPACE`: An infrastructure macro that should not be used in user code. It is safe to undefine this if it is causing problems.

### Core Types:
The core types are provided by `FixedPoints.h`.

- `UFixed<I, F>`: An unsigned fixed point type where I is the number of bits used for the integer part of the number and F is the number of bits used for the fractional part of the number.  
- `SFixed<I, F>`: An signed fixed point type where I is the number of bits used for the integer part of the number (excluding the implicit sign bit) and F is the number of bits used for the fractional part of the number.

### Aliases:
The common aliases are provided by `FixedPointsCommon.h`.

- `UQ4x4`: An alias for `UFixed<4, 4>`, an 8-bit unsigned fixed point in the Q4.4 format.
- `UQ8x8`: An alias for `UFixed<8, 8>`, a 16-bit unsigned fixed point in the Q8.8 format.
- `UQ16x16`: An alias for `UFixed<16, 16>`, a 32-bit unsigned fixed point in the Q16.16 format.
- `UQ32x32`: An alias for `UFixed<32, 32>`, a 64-bit unsigned fixed point in the Q32.32 format.
- `UQ1x7`: An alias for `UFixed<1, 7>`, an 8-bit unsigned fixed point in the Q1.7 format.
- `UQ1x15`: An alias for `UFixed<1, 15>`, a 16-bit unsigned fixed point in the Q1.15 format.
- `UQ1x31`: An alias for `UFixed<1, 31>`, a 32-bit unsigned fixed point in the Q1.31 format.
- `UQ1x63`: An alias for `UFixed<1, 63>`, a 64-bit unsigned fixed point in the Q1.63 format.
- `SQ3x4`: An alias for `SFixed<3, 4>`, an 8-bit signed fixed point in the Q3.4 format with implicit sign bit.
- `SQ7x8`: An alias for `SFixed<7, 8>`, a 16-bit signed fixed point in the Q7.8 format with implicit sign bit.
- `SQ15x16`: An alias for `SFixed<15, 16>`, a 32-bit signed fixed point in the Q15.16 format with implicit sign bit.
- `SQ31x32`: An alias for `SFixed<31, 32>`, a 64-bit signed fixed point in the Q31.32 format with implicit sign bit.
- `SQ1x6`: An alias for `SFixed<1, 6>`, an 8-bit signed fixed point in the Q1.6 format with implicit sign bit.
- `SQ1x14`: An alias for `SFixed<1, 14>`, a 16-bit signed fixed point in the Q1.14 format with implicit sign bit.
- `SQ1x30`: An alias for `SFixed<1, 30>`, a 32-bit signed fixed point in the Q1.30 format with implicit sign bit.
- `SQ1x62`: An alias for `SFixed<1, 62>`, a 64-bit signed fixed point in the Q1.62 format with implicit sign bit.

([About Q Format](https://en.wikipedia.org/wiki/Q_(number_format)).)

### Operators:

- `+`: Adds two `UFixed`s or two `SFixed`s
- `-`: Subtracts two `UFixed`s or two `SFixed`s
- `*`: Multiplies two `UFixed`s or two `SFixed`s
- `/`: Divides two `UFixed`s or two `SFixed`s
- `==`: Compares two `UFixed`s or two `SFixed`s
- `!=`: Compares two `UFixed`s or two `SFixed`s
- `<`: Compares two `UFixed`s or two `SFixed`s
- `<=`: Compares two `UFixed`s or two `SFixed`s
- `>`: Compares two `UFixed`s or two `SFixed`s
- `>=`: Compares two `UFixed`s or two `SFixed`s

### Free Functions:

- `floorFixed`: The floor operation.
- `ceilFixed`: The Ceiling operation
- `roundFixed`: Rounding operation.
- `truncFixed`: Truncation operation.
- `signbitFixed`: Returns `true` for signed numbers and `false` for unsigned numbers.
- `copysignFixed`: Returns a value with the magnitude of the first argument and the sign of the second argument.
- `multiply`: Multiplies two `UFixed`s or two `SFixed`s, returns a result that is twice the resolution of the input.

### Member Functions:

- `UFixed<I, F>::getInteger`: Gets the integer part of an unsigned fixed point.
- `UFixed<I, F>::getFraction`: Gets the fractional part of an unsigned fixed point.
- `UFixed<I, F>::getInternal`: Gets the internal representation of an unsigned fixed point.

- `SFixed<I, F>::getInteger`: Gets the integer part of a signed fixed point.
- `SFixed<I, F>::getFraction`: Gets the fractional part of a signed fixed point.
- `SFixed<I, F>::getInternal`: Gets the internal representation of a signed fixed point.

### Static Functions:

- `UFixed<I, F>::fromInternal`: Produces an unsigned fixed point number from its internal representation.
- `SFixed<I, F>::fromInternal`: Produces a signed fixed point number from its internal representation.

## Construction:

Note that both `UFixed<I, F>` and `SFixed<I, F>` are implicitly compile-time constructable from all integer and decimal literals.
This means that you may write code such as `UFixed<8, 8> value = 0.5;` without incurring a runtime cost for converting from `double` to `UFixed<8, 8>` because the constructor is `constexpr`.

`UFixed<I, F>` is constructable from:
- Any integer literal type, regardless of sign.
-- This constructs the fixed point as an integer with no fractional part.
-- A value that does not fit shall be truncated without warning. 
-- If a constant value is used, the fixed point shall be constructed at compile time.
- An unsigned integer part and an unsigned fractional part.
-- The integer part is of the smallest type capable of representing `I` bits.
-- The fractional part is of the smallest type capable of representing `F` bits.
-- If constant values are used, the fixed point shall be constructed at compile time.
- Any decimal literal type, regardless of sign.
-- This constructs the fixed point as a best approximation of the provided value.
-- A value that does not fit shall be truncated without warning. 
-- If a constant value is used, the fixed point shall be constructed at compile time.

`SFixed<I, F>` is constructable from:
- Any integer literal type, regardless of sign.
-- This constructs the fixed point as an integer with no fractional part.
-- A value that does not fit shall be truncated without warning. 
-- If a constant value is used, the fixed point shall be constructed at compile time.
- A signed integer part and an unsigned fractional part.
-- The integer part is of the smallest type capable of representing `I + 1` bits.
-- The fractional part is of the smallest type capable of representing `F` bits.
-- If constant values are used, the fixed point shall be constructed at compile time.
- Any decimal literal type, regardless of sign.
-- This constructs the fixed point as a best approximation of the provided value.
-- A value that does not fit shall be truncated without warning. 
-- If a constant value is used, the fixed point shall be constructed at compile time.

### Casts:

`UFixed<I, F>` is explicitly convertible to:
- `float`.
- `double`.
- The smallest unsigned type capable of holding its integer part. I.e. a type of at least `I` bits.
- Another `UFixed` type of a different scale. E.g. `UFixed<4, 4>` may be converted to `UFixed<8, 8>` and vice versa.

`SFixed<I, F>` is explicitly convertible to:
- `float`.
- `double`.
- The smallest signed type capable of holding its integer part. I.e. a type of at least `I + 1` bits.
- Another `SFixed` type of a different scale. E.g. `SFixed<3, 4>` may be converted to `SFixed<7, 8>` and vice versa.


