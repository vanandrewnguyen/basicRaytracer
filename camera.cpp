#include "camera.h"
#include "ray.h"
#include <math.h>

Camera::Camera() {
	currCamPos = qbVector<double>(std::vector<double> {0.0, -10.0, 0.0});
	currCamLookAt = qbVector<double>(std::vector<double> {0.0, 0.0, 0.0});
	currCamUp = qbVector<double>(std::vector<double> {0.0, 0.0, 1.0});

	currCamLen = 1.0;
	currCamHorSize = 1.0;
	currCamAspectRatio = 1.0;
}

// Set camera position
void Camera::setPos(const qbVector<double>& newPos) {
	currCamPos = newPos;
}

// Set camera Lookat vector (camera front)
void Camera::setLookat(const qbVector<double>& newLookAt) {
	currCamLookAt = newLookAt;

}

// Set camera up direction 
void Camera::setUp(const qbVector<double>& upVec) {
	currCamUp = upVec;
}

// Set camera length
void Camera::setLen(double newLen) {
	currCamLen = newLen;
}

// Set camera horizontal size
void Camera::setHorSize(double newSize) {
	currCamHorSize = newSize;
}

// Set camera aspect ratio
void Camera::setAspect(double newAspect) {
	currCamAspectRatio = newAspect;
}

// Get the camera position
qbVector<double> Camera::getPos() {
	return currCamPos;
}

// Get camera lookat vector
qbVector<double> Camera::getLookAt() {
	return currCamLookAt;
}

// Get camera up vector
qbVector<double> Camera::getUp() {
	return currCamUp;
}

// Get U vector (UV Coords)
qbVector<double> Camera::getUVec() {
	return projectionScreenU;
}

// Get V vector (UV Coords)
qbVector<double> Camera::getVVec() {
	return projectionScreenV;
}

// Get center of the output screen
qbVector<double> Camera::getScreenCentre() {
	return projectionScreenCentre;
}

double Camera::getLength() {
	return currCamLen;
}

double Camera::getHorSize() {
	return currCamHorSize;
}

double Camera::getAspect() {
	return currCamAspectRatio;
}

// Create a ray instance
bool Camera::createRay(float projectionScreenX, float projectionScreenY, Ray& cameraRay) {
	// Compute location of the screen in world coords
	qbVector<double> screenWorldA = projectionScreenCentre + (projectionScreenU * projectionScreenX);
	qbVector<double> screenWorldCoord = screenWorldA + (projectionScreenV * projectionScreenY);

	// Use this point to compute ray
	cameraRay.currPointA = currCamPos;
	cameraRay.currPointB = screenWorldCoord;
	cameraRay.currVecAB = screenWorldCoord - currCamPos;
	return true;
}

// Update the camera
void Camera::updateCameraGeometry() {
	// Compute vector from camera pos to lookAt pos
	alignmentVector = currCamLookAt - currCamPos;
	alignmentVector.Normalize();

	// Find UV Vectors
	// Right hand rule, the thumb is the up vector, the index is the lookat vector. 
	// On the screen, the U vec is perpendicular to both lookat and up, so it's the middle finger.
	// Cross that again and you'll get the V vector which makes up the 2D plane of the screen
	projectionScreenU = qbVector<double>::cross(alignmentVector, currCamUp);
	projectionScreenU.Normalize();
	projectionScreenV = qbVector<double>::cross(projectionScreenU, alignmentVector);
	projectionScreenV.Normalize();

	// Compute centre of the screen
	projectionScreenCentre = currCamPos + (currCamLen * alignmentVector);

	// Modify UV vectors to match aspect ratio (since they are both unit vectors)
	projectionScreenU = projectionScreenU * currCamHorSize;
	projectionScreenV = projectionScreenV * (currCamHorSize / currCamAspectRatio);
}