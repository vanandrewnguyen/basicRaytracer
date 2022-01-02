#ifndef CAMERA_H
#define CAMERA_H

#include "qbLinAlg/qbVector.h"
#include "ray.h"

class Camera {
public:
	Camera();

	// Functions 
	// Init Camera
	void setPos(const qbVector<double>& newPos);
	void setLookat(const qbVector<double>& newLookAt);
	void setUp(const qbVector<double>& upVec);
	void setLen(double newLen);
	void setHorSize(double newSize);
	void setAspect(double newAspect);

	// Getters
	qbVector<double> getPos();
	qbVector<double> getLookAt();
	qbVector<double> getUp();
	qbVector<double> getUVec();
	qbVector<double> getVVec();
	qbVector<double> getScreenCentre();
	double getLength();
	double getHorSize();
	double getAspect();

	// Rays
	bool createRay(float projectionScreenX, float projectionScreenY, Ray &cameraRay);

	// Update Camera
	void updateCameraGeometry();

private:
	qbVector<double> currCamPos{ 3 };
	qbVector<double> currCamLookAt{ 3 };
	qbVector<double> currCamUp{ 3 };
	double currCamLen;
	double currCamHorSize;
	double currCamAspectRatio;

private:
	qbVector<double> alignmentVector{ 3 };
	qbVector<double> projectionScreenU{ 3 };
	qbVector<double> projectionScreenV{ 3 };
	qbVector<double> projectionScreenCentre{ 3 };

};

#endif