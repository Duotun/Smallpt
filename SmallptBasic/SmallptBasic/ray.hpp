#pragma once

#pragma region
//includes 
#include "vector.hpp"
#pragma endregion

namespace smallpt_basics {

	//represent the ray as P(t) = O + tD
	class Ray {
	public: 
		Vector3 m_o, m_d;  //origin and direction 
		mutable double m_tmin, m_tmax;   // t for segments
		std::uint32_t m_depth;   //_t fixed width

		 explicit Ray(Vector3 o, Vector3 d, double tmin = 00, double tmax = std::numeric_limits<double>::infinity(),
			std::uint32_t depth = 0u) noexcept
			: m_o(std::move(o)),m_d(std::move(d)),m_tmin(tmin), m_tmax(tmax), m_depth(depth){};

		constexpr Ray(const Ray& ray) noexcept = default;
		constexpr Ray(Ray&& ray) noexcept= default;

		//operator declarations
		Ray& operator =(const Ray& ray) = default;
		Ray& operator =(Ray& ray) = default;

		//member methods
		[[nodiscard]]
		constexpr Vector3 operator()(double t)const noexcept {
			return m_o + t * m_d;
		}
	};

	inline std::ostream& operator <<(std::ostream& os, const Ray& r) {
		os << "o: " << r.m_o << std::endl;
		os << "d: " << r.m_d << std::endl;
	}
}