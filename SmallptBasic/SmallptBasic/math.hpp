#pragma once

#pragma region
// includes
#include <limits>
#include <cstdint>
#include <cmath>
#include <algorithm>    //to use clamp function

#pragma endregion

//provide pi and basic conversions for 0-255 color + simple gamma correction
namespace smallpt_basics {

	constexpr double pi = 3.14159265358979323846;

	[[nodiscard]]
	inline std::uint8_t ColorConversion(double color, double gamma = 2.2) noexcept {

		const double color = std::pow(color, 1.0 / gamma);
		return static_cast<std::uint8_t>(std::clamp(255.0 * color, 0.0, 255.0));
	}
}