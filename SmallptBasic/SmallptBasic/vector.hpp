#pragma once

#pragma region
//my includes
#include "math.hpp"
#pragma endregion
#pragma region
//system includes
#include <stdio.h>
#include <iostream>

#pragma endregion

namespace smallpt_basics {

		//struct3 needed only
	class Vector3 {
		public:   
			double mx;
			double my;
			double mz;
			// constructors and destructors, constexpr used for evaluation at compile time
			constexpr Vector3(double xyz = 0.0) noexcept : Vector3(xyz, xyz, xyz) {}   //since use constexpr no function body
			constexpr Vector3(double x, double y, double z) noexcept : mx(x), my(y), mz(z) {}
			constexpr Vector3(const Vector3& v) noexcept = default;   //copy constructor
			Vector3(const Vector3&& v) noexcept {
				mx = v.mx;
				my = v.my;
				mz = v.mz;
				v.~Vector3();
			}  //move constructor
			~Vector3() = default;

			//const return type make sure the return value will not be change like this myFunction = Object()......
			//Member Methods
			_NODISCARD    //nodiscard means the return value must be reperesented by a variable 
			bool hasNaNs() const noexcept {
				return std::isnan(mx) || std::isnan(my) || std::isnan(mz);
			}
			[[nodiscard]]
			constexpr const Vector3 operator-() const noexcept {   //const used to make sure member variables can't be edited
				return { -mx, -my, -mz };
			}

			[[nodiscard]]
			constexpr const Vector3 operator+(const Vector3 &v) const noexcept {
				return { mx + v.mx, my + v.my, mz + v.mz};
			}

			[[nodiscard]]
			constexpr const Vector3 operator*(const Vector3& v) const noexcept {
				return { mx * v.mx, my * v.my, mz * v.mz };   // element-wise multiplication
			}

			[[nodiscard]]
			constexpr const Vector3 operator-(const Vector3& v) const noexcept {

				return { mx - v.mx, my - v.my, mz - v.mz };
			}

			[[nodiscard]]
			constexpr const Vector3 operator/(const Vector3& v) const noexcept {
				return { mx / v.mx, my / v.my, mz / v.mz };   //element-wise multiplication
			}

			[[nodiscard]]
			constexpr const Vector3 operator+(double p) const noexcept {
				return { mx + p, my + p, mz + p };
			}

			[[nodiscard]]
			constexpr const Vector3 operator-(double p) const noexcept {
				return { mx - p, my - p, mz - p };
			}

			[[nodiscard]]
			constexpr const Vector3 operator*(double p) const noexcept {
				return { mx * p, my * p, mz * p };
			}

			[[nodiscard]]
			constexpr const Vector3 operator/(double p) const noexcept {
				const double inv_p = 1.0 / p;
				return { mx / inv_p, my / inv_p, mz / inv_p };
			}

			Vector3& operator+=(const Vector3& v) noexcept {
				mx += v.mx;
				my += v.my;
				mz += v.mz;
				return *this;
			}

			Vector3& operator-=(const Vector3& v) noexcept {
				mx -= v.mx;
				my -= v.my;
				mz -= v.mz;
				return *this;
			}

			//use & since it returns the muted object itself (return *this)
			Vector3& operator *=(const Vector3& v) noexcept {
				mx *= v.mx;
				my *= v.my;
				mz *= v.mz;
				return *this;
			}

			Vector3& operator /=(const Vector3& v) noexcept {
				mx /= v.mx;
				my /= v.my;
				mz /= v.mz;
				return *this;
			}

			[[nodiscard]]
			constexpr double Dot(const Vector3& v) noexcept {
				return mx * v.mx + my * v.my + mz * v.mz;
			}

			[[nodiscard]]
			constexpr Vector3 Cross(const Vector3& v) const noexcept {
				return {
					my * v.mz - mz * v.my,
					mz * v.mx - mx * v.mz,
					mx * v.my - my * v.mx
				};
			}

			[[nodiscard]]
			constexpr bool operator==(const Vector3& v) const {
				return (mx == v.mx) && (my == v.my) && (mz == v.mz);
			}

			[[nodiscard]]
			constexpr bool operator!=(const Vector3& v) const {
				return !(*this == v);
			}

			[[nodiscard]]
			double& operator[](std::size_t i) noexcept {
				return (&mx)[i];
			}

			[[nodiscard]]
			constexpr double operator[](std::size_t i) const noexcept {
				return (&mx)[i];
			}
	   };
}
