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
 
#include "../FixedPoints.h" 
 
FIXED_POINTS_BEGIN_NAMESPACE
using UQ4x4 = UFixed<4, 4>;
using UQ8x8 = UFixed<8, 8>;
using UQ16x16 = UFixed<16, 16>;
using UQ32x32 = UFixed<32, 32>;

using UQ1x7 = UFixed<1, 7>;
using UQ1x15 = UFixed<1, 15>;
using UQ1x31 = UFixed<1, 31>;
using UQ1x63 = UFixed<1, 63>;
FIXED_POINTS_END_NAMESPACE