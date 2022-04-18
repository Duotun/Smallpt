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
			constexpr double Dot(const Vector3& v) const noexcept {
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

			[[nodiscard]]
			constexpr double Min() const noexcept {
				return std::min(mx, std::min(my, mz));
			}

			[[nodiscard]]
			constexpr double Max() const noexcept {
				return std::max(mx, std::max(my, mz));
			}

			[[nodiscard]]   //length^2 in 3D
			constexpr double Magnitude_squared() const noexcept {
				return mx*mx+my*my+mz*mz;
			}

			[[nodiscard]]   //length in 3D
			constexpr double Magnitude() const noexcept {
				return std::sqrt(Magnitude_squared());
			}

			void Normalize() noexcept {
				const double p = 1.0 / Magnitude();
				mx *= p;
				my *= p;
				mz *= p;
			}
	   };

	   /////////////////////
	   //Vector3 Utilities for easy use
	   /////////////////////
	   std::ostream& operator<<(std::ostream& os, const Vector3& v)
	   {
		   os << '[' << v.mx << ' ' << v.my << ' ' << v.mz << ']';
		   return os;
	   }

	   [[nodiscard]]
	   constexpr  Vector3 operator+(double a, const Vector3& v) noexcept {
		   return { v.mx + a, v.my + a, v.mz + a };
	   }

	   [[nodiscard]]
	   constexpr  Vector3 operator-(double a, const Vector3& v) noexcept {
		   return { v.mx - a, v.my - a, v.mz - a };
	   }

	   [[nodiscard]]
	   constexpr  Vector3 operator*(double a, const Vector3& v) noexcept {
		   return { v.mx * a, v.my * a, v.mz * a };
	   }

	   [[nodiscard]]
	   constexpr  Vector3 operator/(double a, const Vector3& v) noexcept {
		   return { v.mx / a, v.my / a, v.mz / a };
	   }

	   [[nodiscard]]
	   inline const Vector3 Sqrt(const Vector3& v) noexcept {
		   return {
			   std::sqrt(v.mx),
			   std::sqrt(v.my),
			   std::sqrt(v.mz)
		   };
	   }

	   [[nodiscard]]
	   inline const Vector3 Pow(const Vector3& v, double p) noexcept {
		   return {
			   std::pow(v.mx, p),
			   std::pow(v.my, p),
			   std::pow(v.mz, p)
		   };
	   }

	   [[nodiscard]]
	   inline const Vector3 Abs(const Vector3& v) noexcept {
		   return {
			   std::abs(v.mx),
			   std::abs(v.my),
			   std::abs(v.mz)
		   };
	   }

	   [[nodiscard]]
	   inline const Vector3 Min(const Vector3& v1, const Vector3& v2) noexcept {
		   return {
			   std::min(v1.mx, v2.mx),
			   std::min(v1.my, v2.my),
			   std::min(v1.mz, v2.mz)
		   };
	   }

	   [[nodiscard]]
	   inline const Vector3 Max(const Vector3& v1, const Vector3& v2) noexcept {
		   return {
			   std::max(v1.mx, v2.mx),
			   std::max(v1.my, v2.my),
			   std::max(v1.mz, v2.mz)
		   };
	   }

	   // simple precision support
	   [[nodiscard]]
	   inline const Vector3 Round(const Vector3& v) noexcept {
		   return {
			   std::round(v.mx),
			   std::round(v.my),
			   std::round(v.mz)
		   };
	   }

	   [[nodiscard]]
	   inline const Vector3 Ceil(const Vector3& v) noexcept {
		   return {
			   std::ceil(v.mx),
			   std::ceil(v.my),
			   std::ceil(v.mz)
		   };
	   }

	   [[nodiscard]]
	   inline const Vector3 Truncate(const Vector3& v) noexcept {
		   return {
			   std::trunc(v.mx),
			   std::trunc(v.my),
			   std::trunc(v.mz)
		   };
	   }

	   [[nodiscard]]
	   constexpr const Vector3 Clamp(const Vector3& v, double low = 0.0, double high = 1.0) noexcept {
		   return{
			   std::clamp(v.mx, low, high),
			   std::clamp(v.my, low, high),
			   std::clamp(v.mz, low, high),
		   };

	   }

	   [[nodiscard]]
	   constexpr const Vector3 Lerp(const Vector3& v1, const Vector3& v2, double p) noexcept {
		   return v1 * p + v2 * (1.0 - p);
	   }

	   [[nodiscard]]
	   inline const Vector3 Normalize(const Vector3& v) noexcept {
		   const double p = 1.0 / v.Magnitude();
		   return p * v;
	   }

}
