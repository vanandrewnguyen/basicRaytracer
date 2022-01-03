#include "lightBase.h"

// Constructor destructor
LightBase::LightBase() {

}

LightBase::~LightBase() {

}

// Function to compute illumination
bool LightBase::computeIlluminationContribution(const qbVector<double>& intersectPoint, const qbVector<double>& localNormal,
	const std::vector<std::shared_ptr<ObjectBase>>& objectList, const std::shared_ptr<ObjectBase>& currentObject,
	qbVector<double>& colour, double& intensity) {
	return false;
}