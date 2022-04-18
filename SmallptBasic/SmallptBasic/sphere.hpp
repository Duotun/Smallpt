#pragma once

#pragma region
//includes and defines
#include "ray.hpp"
#define EPSILON_SPHERE 1E-4
#pragma endregion

namespace smallpt_basics {

	//for different reflections
	enum struct reflection_type : std::uint8_t {
		Diffuse = 0u,
		Specular,
		Refractive
	};

	//for the scene description, only composed of sphere
	class Sphere {
	public:
		double radius;
		Vector3 position;  //position of the origin
		Vector3 emission;
		Vector3 reflection;    
		reflection_type ref_type;
		explicit Sphere(double r, Vector3 o, Vector3 e, Vector3 f, reflection_type rf_t) noexcept
			: radius(r), position(std::move(o)), emission(std::move(e)), reflection(std::move(f)), ref_type(ref_type) {}
		
		 constexpr Sphere(const Sphere& sphere) noexcept = default;
		 constexpr Sphere(Sphere& sphere) noexcept = default;
		 ~Sphere() = default;

		 //copy operators
		 Sphere& operator=(const Sphere& sphere) = default;
		 Sphere& operator=(Sphere& sphere) = default;


		 // (o + t*d - p) . (o + t*d - p) - r*r = 0
			// <=> (d . d) * t^2 + 2 * d . (o - p) * t + (o - p) . (o - p) - r*r = 0
			// 
			// Discriminant check
			// (2 * d . (o - p))^2 - 4 * (d . d) * ((o - p) . (o - p) - r*r) <? 0
			// <=> (d . (o - p))^2 - (d . d) * ((o - p) . (o - p) - r*r) <? 0
			// <=> (d . op)^2 - 1 * (op . op - r*r) <? 0
			// <=> b^2 - (op . op) + r*r <? 0
			// <=> D <? 0
			//
			// Solutions
			// t = (- 2 * d . (o - p) +- 2 * sqrt(D)) / (2 * (d . d))
			// <=> t = dpo +- sqrt(D) and the magnitude of d is one
		 [[nodiscard]]  //check whether the current ray collides with the spheres
		 bool Intersect(const Ray& ray) const noexcept {

			 const Vector3 po = position - ray.m_o;   //  C - O
			 const double  dpo = ray.m_d.Dot(po);
			 const double det = dpo * dpo - po.Dot(po) + radius * radius;
			 if (det < 0.0) return false;

		 }
	};
}
