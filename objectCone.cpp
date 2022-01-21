#include "objectCone.h"
#include <cmath>
#include <array>

#define BIGNUMBER 100e6

ObjectCone::ObjectCone() {

}

ObjectCone::~ObjectCone() {

}

bool ObjectCone::testIntersection(const Ray& castRay, qbVector<double>& intersectionPoint,
	qbVector<double>& localNormal, qbVector<double>& localColour) {
	// Copy ray and apply backwards transform
	Ray backRay = transformMatrix.applyTransform(castRay, BCKTRANSFORM);

	// Copy vector and normalize
	qbVector<double> v = backRay.currVecAB;
	v.Normalize();

	// Get start point of the line 
	qbVector<double> p = backRay.currPointA;

	// Compute a, b, c
	/*
	Imagine you're looking at a canvas with xy coord, a side-on view of a cylinder would be a circle. Hence, using a point and vector to
	demonstrate a ray intersection you can assume l = p + t * v, x^2 + y^2 = r^2, hence equation x and y components;
	(p_x + t*v_x)^2 + (p_y + t*v_y)^2 = r^2
	Expanding and simplifying we get an equation of form a*t^2 + b*t + c = 0, where a, b, c = components below
	where p.getElement(0) = x component, p.getElement(1) = y component
	*/
	double a = std::pow(v.GetElement(0), 2.0) + std::pow(v.GetElement(1), 2.0) - std::pow(v.GetElement(2), 2.0);
	double b = 2.0 * (p.GetElement(0) * v.GetElement(0) + p.GetElement(1) * v.GetElement(1) - p.GetElement(2) * v.GetElement(2));
	double c = std::pow(p.GetElement(0), 2.0) + std::pow(p.GetElement(1), 2.0) - std::pow(p.GetElement(2), 2.0);

	// Finding determinant
	double numSqrt = sqrtf(std::pow(b, 2.0) - 4 * a * c);

	// Test intersection
	std::array<qbVector<double>, 3> poi; // 4 element array of type qbVector<double>
	std::array<double, 3> t;
	bool t1Valid, t2Valid, t3Valid; // one less valid check, since we only have 1 end cap

	if (numSqrt > 0.0) {
		// Is intersection, so compute values for t
		// This is the quadratic equation
		t.at(0) = (-b + numSqrt) / (2 * a);
		t.at(1) = (-b - numSqrt) / (2 * a);

		// Compute points of intersection
		poi.at(0) = backRay.currPointA + (v * t[0]);
		poi.at(1) = backRay.currPointA + (v * t[1]);

		// Check if any of these are valid
		// If t val is > 0.0 and first point of intersection.z has abs() < 1.0
		if ((t.at(0) > 0.0) && (poi.at(0).GetElement(2) > 0.0) && (poi.at(0).GetElement(2) < 1.0)) {
			t1Valid = true;
		} else {
			t1Valid = false;
			t.at(0) = BIGNUMBER;
		}

		if ((t.at(1) > 0.0) && (poi.at(1).GetElement(2) > 0.0) && (poi.at(1).GetElement(2) < 1.0)) {
			t2Valid = true;
		} else {
			t2Valid = false;
			t.at(1) = BIGNUMBER;
		}
	} else {
		t1Valid = false;
		t2Valid = false;
		t.at(0) = BIGNUMBER;
		t.at(1) = BIGNUMBER;
	}

	// Test end cap
	if (isFloatCloseEnough(v.GetElement(2), 0.0)) {
		t3Valid = false;
		t.at(2) = BIGNUMBER;
	} else {
		// Have intersection, so compute value of t (plane implementation)
		t.at(2) = (backRay.currPointA.GetElement(2) - 1.0) / -v.GetElement(2);

		// Compute point of intersection
		poi.at(2) = backRay.currPointA + t.at(2) * v;

		// Check valid int
		if ((t.at(2) > 0.0) && (sqrtf(std::pow(poi.at(2).GetElement(0), 2.0) + std::pow(poi.at(2).GetElement(1), 2.0)) < 1.0)) {
			t3Valid = true;
		} else {
			t3Valid = false;
			t.at(2) = BIGNUMBER;
		}
	}

	// If no valid intersections found then stop searching
	if (!t1Valid && !t2Valid && !t3Valid) {
		return false;
	}

	// Else, find smallest value of t
	int minIndex = 0;
	double minValue = BIGNUMBER;
	for (int i = 0; i < 3; i++) {
		if (t.at(i) < minValue) {
			// set and grab smallest value + index of t
			minValue = t.at(i);
			minIndex = i;
		}
	}

	// If minIndex == 0 || 1, then we have valid intersection with cylinder
	qbVector<double> validPoi = poi.at(minIndex);
	if (minIndex < 2) {
		// Transfirm int point back to world coord by using transform
		intersectionPoint = transformMatrix.applyTransform(validPoi, FWDTRANSFORM);

		// Get local normal
		qbVector<double> oldNormal{ 3 };
		qbVector<double> newNormal{ 3 };
		qbVector<double> localOrigin{ std::vector<double> {0.0, 0.0, 0.0} };
		qbVector<double> globalOrigin = transformMatrix.applyTransform(localOrigin, FWDTRANSFORM);
		double normVecX = validPoi.GetElement(0);
		double normVecY = validPoi.GetElement(1);
		double normVecZ = -sqrtf(pow(normVecX, 2.0) + pow(normVecY, 2.0)); // pythag for side view (trig)
		oldNormal.SetElement(0, normVecX);
		oldNormal.SetElement(1, normVecY);
		oldNormal.SetElement(2, normVecZ); // normal vec is perpendicular to base of cone
		newNormal = transformMatrix.applyTransform(oldNormal, FWDTRANSFORM) - globalOrigin;
		newNormal.Normalize();
		localNormal = newNormal;

		// Return base colour
		localColour = baseColour;
		return true;
	}
	else {
		// Otherwise check end caps
		if (!isFloatCloseEnough(v.GetElement(2), 0.0)) {
			// Check if inside disk (this is x^2 + y^2 < r^2, since unit cylinder)
			if (sqrtf(std::pow(validPoi.GetElement(0), 2.0) + std::pow(validPoi.GetElement(1), 2.0)) < 1.0) {
				// Transform int point back to world coord
				intersectionPoint = transformMatrix.applyTransform(validPoi, FWDTRANSFORM);

				// Get local normal
				qbVector<double> localOrigin{ std::vector<double> {0.0, 0.0, 0.0} };
				qbVector<double> normalVec{ std::vector<double> {0.0, 0.0, 0.0 + validPoi.GetElement(2)} }; // setting z normal to +-1
				qbVector<double> globalOrigin = transformMatrix.applyTransform(localOrigin, FWDTRANSFORM);
				localNormal = transformMatrix.applyTransform(normalVec, FWDTRANSFORM) - globalOrigin;
				localNormal.Normalize();

				// Return base colour
				localColour = baseColour;
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}

	return false;
}