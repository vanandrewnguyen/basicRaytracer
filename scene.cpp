#include "scene.h"

#include "materialBase.h"
#include "simpleMaterial.h"
#include "simpleRefractiveMaterial.h"

#include "textureChecker.h"
#include "textureStripe.h"
#include "textureMono.h"
#include "textureImage.h"
#include "textureSimplex.h"
#include "texturePerlin.h"
#include "texturePolkaDot.h"
#include "textureCellular.h"

#define PI 3.1416

Scene::Scene() {
	postProcessEffectIndex = 0;

	// CAMERA //
	// Set parameters
	currCamera.setPos(qbVector<double>{std::vector<double>{-3.0, -9.0, -1.0}}); // 0.0, -10.0, 0.0
	currCamera.setLookat(qbVector<double>{std::vector<double>{0.2, 0.0, 0.5}}); // 0.0, 0.0, 0.0
	currCamera.setUp(qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}});
	currCamera.setHorSize(0.25);
	currCamera.setAspect(16.0 / 9.0);
	currCamera.updateCameraGeometry();

	// AMBIENT LIGHT //
	MaterialBase::ambientCol = std::vector<double>{ 1.0, 1.0, 1.0 };
	MaterialBase::ambientLightIntensity = 0.1;

	// TEXTURES //
	auto floorTexture = std::make_shared<Texture::TextureCellular>(Texture::TextureCellular());
	floorTexture->setTransform(qbVector<double>{std::vector<double>{0.0, 0.0}}, 0.0, qbVector<double>{std::vector<double>{4.0, 4.0}});
	floorTexture->setColour(qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}});

	auto cylinderTexture = std::make_shared<Texture::TextureSimplex>(Texture::TextureSimplex());
	cylinderTexture->setTransform(qbVector<double>{std::vector<double>{0.0, 0.0}}, 0.0, qbVector<double>{std::vector<double>{1.0 * PI, 1.0}});
	cylinderTexture->setColour(qbVector<double>{std::vector<double>{0.905, 0.886, 0.513}}, qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}});

	auto sphereTexture = std::make_shared<Texture::TexturePerlin>(Texture::TexturePerlin());
	sphereTexture->setTransform(qbVector<double>{std::vector<double>{0.0, 0.0}}, 0.0, qbVector<double>{std::vector<double>{2.0, 2.0}});
	sphereTexture->setColour(qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}});

	auto coneTexture = std::make_shared<Texture::TexturePolkaDot>(Texture::TexturePolkaDot());
	coneTexture->setTransform(qbVector<double>{std::vector<double>{0.0, 0.0}}, 0.0, qbVector<double>{std::vector<double>{2.0 * PI, 2.0}});
	coneTexture->setColour(qbVector<double>{std::vector<double>{0.0, 0.1, 0.2}}, qbVector<double>{std::vector<double>{1.0, 0.0, 0.0}});
	coneTexture->setRad(0.3, 0.05);

	/*
	auto texBrick = std::make_shared<Texture::TextureImage>(Texture::TextureImage());
	texBrick->setTransform(qbVector<double>{std::vector<double>{0.0, 0.0}}, 0.0, qbVector<double>{std::vector<double>{1.0, 1.0}});
	texBrick->loadImage("texBrickWall.bmp");

	auto texBarrel = std::make_shared<Texture::TextureImage>(Texture::TextureImage());
	texBarrel->setTransform(qbVector<double>{std::vector<double>{0.0, 0.0}}, 0.0, qbVector<double>{std::vector<double>{1.0 * PI, 1.0}});
	texBarrel->loadImage("texBarrel.bmp");

	auto texPlaster = std::make_shared<Texture::TextureImage>(Texture::TextureImage());
	texPlaster->setTransform(qbVector<double>{std::vector<double>{0.0, 0.0}}, 0.0, qbVector<double>{std::vector<double>{1.0, 1.0}});
	texPlaster->loadImage("texPlasterWall.bmp");

	auto texSafetyCone = std::make_shared<Texture::TextureStripe>(Texture::TextureStripe());
	texSafetyCone->setTransform(qbVector<double>{std::vector<double>{0.0, 0.15}}, 0.0, qbVector<double>{std::vector<double>{1.6 * PI, 1.6}});
	texSafetyCone->setColour(qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}}, qbVector<double>{std::vector<double>{1.0, 0.65, 0.0}});
	*/

	// MATERIALS //
	/*
	auto matBrickWall = std::make_shared<SimpleMaterial>(SimpleMaterial());
	matBrickWall->baseColour = qbVector<double>{ std::vector<double>{1.0, 1.0, 1.0} };
	matBrickWall->reflectivity = 0.0;
	matBrickWall->shininess = 0.0;
	matBrickWall->assignTexture(texBrick);

	auto matPlasterWall = std::make_shared<SimpleMaterial>(SimpleMaterial());
	matPlasterWall->baseColour = qbVector<double>{ std::vector<double>{1.0, 1.0, 1.0} };
	matPlasterWall->reflectivity = 0.1;
	matPlasterWall->shininess = 2.0;
	matPlasterWall->assignTexture(texPlaster);

	auto matMetal = std::make_shared<SimpleMaterial>(SimpleMaterial());
	matMetal->baseColour = qbVector<double>{ std::vector<double>{0.25, 0.5, 0.8} };
	matMetal->reflectivity = 0.9;
	matMetal->shininess = 10.0;

	auto matBarrelMetal = std::make_shared<SimpleMaterial>(SimpleMaterial());
	matBarrelMetal->baseColour = qbVector<double>{ std::vector<double>{1.0, 0.6, 0.8} };
	matBarrelMetal->reflectivity = 0.2;
	matBarrelMetal->shininess = 5.0;
	matBarrelMetal->assignTexture(texBarrel);

	auto matConePlastic = std::make_shared<SimpleMaterial>(SimpleMaterial());
	matConePlastic->baseColour = qbVector<double>{ std::vector<double>{1.0, 0.6, 0.8} };
	matConePlastic->reflectivity = 0.25;
	matConePlastic->shininess = 10.0;
	matConePlastic->assignTexture(texSafetyCone);

	auto matGlass = std::make_shared<SimpleRefractiveMaterial>(SimpleRefractiveMaterial());
	matGlass->baseColour = qbVector<double>{ std::vector<double>{1.0, 1.0, 1.0} };
	matGlass->reflectivity = 0.2;
	matGlass->shininess = 16.0;
	matGlass->translucency = 0.8;
	matGlass->IOR = 1.500;
	*/
	auto matMetal = std::make_shared<SimpleMaterial>(SimpleMaterial());
	matMetal->baseColour = qbVector<double>{ std::vector<double>{0.25, 0.5, 0.8} };
	matMetal->reflectivity = 0.9;
	matMetal->shininess = 10.0;

	auto matMarble = std::make_shared<SimpleMaterial>(SimpleMaterial());
	matMarble->baseColour = qbVector<double>{ std::vector<double>{0.8, 0.5, 0.8} };
	matMarble->reflectivity = 0.0;
	matMarble->shininess = 0.0;
	matMarble->assignTexture(cylinderTexture);

	auto matNoise = std::make_shared<SimpleMaterial>(SimpleMaterial());
	matNoise->baseColour = qbVector<double>{ std::vector<double>{0.8, 0.5, 0.8} };
	matNoise->reflectivity = 0.0;
	matNoise->shininess = 0.0;
	matNoise->assignTexture(sphereTexture);

	auto matDot = std::make_shared<SimpleMaterial>(SimpleMaterial());
	matDot->baseColour = qbVector<double>{ std::vector<double>{0.8, 0.5, 0.8} };
	matDot->reflectivity = 0.0;
	matDot->shininess = 0.0;
	matDot->assignTexture(coneTexture);

	auto matFloor = std::make_shared<SimpleMaterial>(SimpleMaterial());
	matFloor->baseColour = qbVector<double>{ std::vector<double>{1.0, 1.0, 1.0} };
	matFloor->reflectivity = 0.25;
	matFloor->shininess = 5.0;
	matFloor->assignTexture(floorTexture);

	auto matRedWall = std::make_shared<SimpleMaterial>(SimpleMaterial());
	matRedWall->baseColour = qbVector<double>{ std::vector<double>{1.0, 0.0, 0.0} };
	matRedWall->reflectivity = 0.0;
	matRedWall->shininess = 5.0;

	auto matGreenWall = std::make_shared<SimpleMaterial>(SimpleMaterial());
	matGreenWall->baseColour = qbVector<double>{ std::vector<double>{0.0, 1.0, 0.0} };
	matGreenWall->reflectivity = 0.0;
	matGreenWall->shininess = 5.0; 

	// CONSTRUCTION //
	// Modify each sphere (using geometric transforms - translation, rotation, scaling)
	GeometricTransform matrixSphere1, matrixSphere2, matrixCone1, matrixCylinder1, matrixPlaneFloor, matrixPlaneCeil, matrixPlaneRight, matrixPlaneLeft, matrixPlaneBack, matrixPlaneMirror;


	objectList.push_back(std::make_shared<ObjectSphere>(ObjectSphere()));
	matrixSphere1.setTransform(qbVector<double>{std::vector<double>{-0.7, -0.1, 0.5}},
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});
	objectList.at(0)->setTransformMatrix(matrixSphere1);
	objectList.at(0)->baseColour = qbVector<double>{ std::vector<double>{1.0, 0.6, 0.6} };
	objectList.at(0)->assignMaterial(matNoise);

	// Floor
	objectList.push_back(std::make_shared<ObjectPlane>(ObjectPlane()));
	matrixPlaneFloor.setTransform(qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}},
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{1.5, 1.5, 1.5}});
	objectList.at(1)->setTransformMatrix(matrixPlaneFloor);
	objectList.at(1)->baseColour = qbVector<double>{ std::vector<double>{0.9, 0.9, 0.9} };
	objectList.at(1)->assignMaterial(matFloor);

	objectList.push_back(std::make_shared<ObjectCylinder>(ObjectCylinder()));
	matrixCylinder1.setTransform(qbVector<double>{std::vector<double>{0.5, 0.0, 0.4}},
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});
	objectList.at(2)->setTransformMatrix(matrixCylinder1);
	objectList.at(2)->baseColour = qbVector<double>{ std::vector<double>{1.0, 0.6, 0.6} };
	objectList.at(2)->assignMaterial(matMarble);

	objectList.push_back(std::make_shared<ObjectCone>(ObjectCone()));
	matrixCone1.setTransform(qbVector<double>{std::vector<double>{-0.1, -0.7, 0.5}},
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.4, 0.4, 0.5}});
	objectList.at(3)->setTransformMatrix(matrixCone1);
	objectList.at(3)->baseColour = qbVector<double>{ std::vector<double>{0.8, 0.5, 0.8} };
	objectList.at(3)->assignMaterial(matDot);

	// Grunge alleyway render
	/*
	objectList.push_back(std::make_shared<ObjectCylinder>(ObjectCylinder()));
	matrixCylinder1.setTransform(qbVector<double>{std::vector<double>{-0.5, 0.8, 0.5}},
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});
	objectList.at(0)->setTransformMatrix(matrixCylinder1);
	objectList.at(0)->baseColour = qbVector<double>{ std::vector<double>{1.0, 0.6, 0.6} };
	objectList.at(0)->assignMaterial(matBarrelMetal);

	objectList.push_back(std::make_shared<ObjectSphere>(ObjectSphere()));
	matrixSphere1.setTransform(qbVector<double>{std::vector<double>{0.2, -1.0, 0.6}},
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.25, 0.25, 0.25}});
	objectList.at(1)->setTransformMatrix(matrixSphere1);
	objectList.at(1)->baseColour = qbVector<double>{ std::vector<double>{0.8, 0.6, 0.6} };
	objectList.at(1)->assignMaterial(matMetal);

	objectList.push_back(std::make_shared<ObjectCone>(ObjectCone()));
	matrixCone1.setTransform(qbVector<double>{std::vector<double>{1.3, 0.2, 0.3}},
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.4, 0.4, 0.7}});
	objectList.at(2)->setTransformMatrix(matrixCone1);
	objectList.at(2)->baseColour = qbVector<double>{ std::vector<double>{0.8, 0.8, 0.8} };
	objectList.at(2)->assignMaterial(matConePlastic);

	objectList.push_back(std::make_shared<ObjectSphere>(ObjectSphere()));
	matrixSphere2.setTransform(qbVector<double>{std::vector<double>{-1.0, -1.5, 0.6}},
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.4, 0.4, 0.4}});
	objectList.at(3)->setTransformMatrix(matrixSphere2);
	objectList.at(3)->baseColour = qbVector<double>{ std::vector<double>{1.0, 0.6, 0.6} };
	objectList.at(3)->assignMaterial(matGlass);

	// Floor
	objectList.push_back(std::make_shared<ObjectPlane>(ObjectPlane()));
	matrixPlaneFloor.setTransform(qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}},
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{2.0, 1.5, 1.5}});
	objectList.at(4)->setTransformMatrix(matrixPlaneFloor);
	objectList.at(4)->baseColour = qbVector<double>{ std::vector<double>{0.9, 0.9, 0.9} };
	objectList.at(4)->assignMaterial(matPlasterWall);

	// Right
	objectList.push_back(std::make_shared<ObjectPlane>(ObjectPlane()));
	matrixPlaneRight.setTransform(qbVector<double>{std::vector<double>{2.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.0, 1.57, 0.0}},
		qbVector<double>{std::vector<double>{1.0, 1.5, 1.0}});
	objectList.at(5)->setTransformMatrix(matrixPlaneRight);
	objectList.at(5)->baseColour = qbVector<double>{ std::vector<double>{0.0, 1.0, 0.0} };
	objectList.at(5)->assignMaterial(matBrickWall);

	// Left
	objectList.push_back(std::make_shared<ObjectPlane>(ObjectPlane()));
	matrixPlaneLeft.setTransform(qbVector<double>{std::vector<double>{-2.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.0, -1.57, 0.0}},
		qbVector<double>{std::vector<double>{1.0, 1.5, 1.0}});
	objectList.at(6)->setTransformMatrix(matrixPlaneLeft);
	objectList.at(6)->baseColour = qbVector<double>{ std::vector<double>{1.0, 0.0, 0.0} };
	objectList.at(6)->assignMaterial(matPlasterWall);

	// Back
	objectList.push_back(std::make_shared<ObjectPlane>(ObjectPlane()));
	matrixPlaneBack.setTransform(qbVector<double>{std::vector<double>{0.0, 1.5, 0.0}},
		qbVector<double>{std::vector<double>{-1.57, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{2.0, 1.0, 1.0}});
	objectList.at(7)->setTransformMatrix(matrixPlaneBack);
	objectList.at(7)->baseColour = qbVector<double>{ std::vector<double>{1.0, 1.0, 1.0} };
	objectList.at(7)->assignMaterial(matPlasterWall);
	*/

	/*
	Cornell Box Setup
	
	// Construct sphere
	objectList.push_back(std::make_shared<ObjectCylinder>(ObjectCylinder()));
	matrixCylinder1.setTransform(qbVector<double>{std::vector<double>{0.5, 0.0, 0.4}},
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});
	objectList.at(0)->setTransformMatrix(matrixCylinder1);
	objectList.at(0)->baseColour = qbVector<double>{ std::vector<double>{1.0, 0.6, 0.6} };
	objectList.at(0)->assignMaterial(matPlastic);

	objectList.push_back(std::make_shared<ObjectSphere>(ObjectSphere()));
	matrixSphere1.setTransform(qbVector<double>{std::vector<double>{-0.7, -0.1, 0.7}},
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.3, 0.3, 0.3}});
	objectList.at(1)->setTransformMatrix(matrixSphere1);
	objectList.at(1)->baseColour = qbVector<double>{ std::vector<double>{1.0, 0.6, 0.6} };
	objectList.at(1)->assignMaterial(matMetal);

	objectList.push_back(std::make_shared<ObjectCone>(ObjectCone()));
	matrixCone1.setTransform(qbVector<double>{std::vector<double>{-0.2, 0.0, 0.75}},
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.25, 0.25, 0.25}});
	objectList.at(2)->setTransformMatrix(matrixCone1);
	objectList.at(2)->baseColour = qbVector<double>{ std::vector<double>{0.8, 0.5, 0.8} };

	// Construct plane
	// Right
	objectList.push_back(std::make_shared<ObjectPlane>(ObjectPlane()));
	matrixPlaneRight.setTransform(qbVector<double>{std::vector<double>{1.5, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.0, 1.57, 0.0}},
		qbVector<double>{std::vector<double>{1.0, 1.5, 1.0}});
	objectList.at(3)->setTransformMatrix(matrixPlaneRight);
	objectList.at(3)->baseColour = qbVector<double>{ std::vector<double>{0.0, 1.0, 0.0} }; 
	objectList.at(3)->assignMaterial(matGreenWall);

	// Left
	objectList.push_back(std::make_shared<ObjectPlane>(ObjectPlane()));
	matrixPlaneLeft.setTransform(qbVector<double>{std::vector<double>{-1.5, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{0.0, -1.57, 0.0}},
		qbVector<double>{std::vector<double>{1.0, 1.5, 1.0}});
	objectList.at(4)->setTransformMatrix(matrixPlaneLeft);
	objectList.at(4)->baseColour = qbVector<double>{ std::vector<double>{1.0, 0.0, 0.0} };
	objectList.at(4)->assignMaterial(matRedWall);

	// Floor
	objectList.push_back(std::make_shared<ObjectPlane>(ObjectPlane()));
	matrixPlaneFloor.setTransform(qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}},
		qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{1.5, 1.5, 1.5}});
	objectList.at(5)->setTransformMatrix(matrixPlaneFloor);
	objectList.at(5)->baseColour = qbVector<double>{ std::vector<double>{0.9, 0.9, 0.9} }; 
	objectList.at(5)->assignMaterial(matFloor);

	// Back
	objectList.push_back(std::make_shared<ObjectPlane>(ObjectPlane()));
	matrixPlaneBack.setTransform(qbVector<double>{std::vector<double>{0.0, 1.5, 0.0}},
		qbVector<double>{std::vector<double>{-1.57, 0.0, 0.0}},
		qbVector<double>{std::vector<double>{1.5, 1.0, 1.0}});
	objectList.at(6)->setTransformMatrix(matrixPlaneBack);
	objectList.at(6)->baseColour = qbVector<double>{ std::vector<double>{1.0, 1.0, 1.0} };
	objectList.at(6)->assignMaterial(matFloor);

	// Ceiling
	objectList.push_back(std::make_shared<ObjectPlane>(ObjectPlane()));
	matrixPlaneCeil.setTransform(qbVector<double>{std::vector<double>{0.0, 0.0, -1.0}},
		qbVector<double>{std::vector<double>{0.0, 3.14, 0.0}},
		qbVector<double>{std::vector<double>{1.5, 1.5, 1.5}});
	objectList.at(7)->setTransformMatrix(matrixPlaneCeil);
	objectList.at(7)->baseColour = qbVector<double>{ std::vector<double>{0.9, 0.9, 0.9} };
	objectList.at(7)->assignMaterial(matFloor);
	*/

	// POINT LIGHTING //
	// Construct point light
	lightList.push_back(std::make_shared<PointLight>(PointLight()));
	lightList.at(0)->lightLocation = qbVector<double>{ std::vector<double>{0.0, -2.0, -2.0} }; 
	lightList.at(0)->lightColour = qbVector<double>{ std::vector<double>{1.0, 0.95, 0.9} }; // 1.0, 1.0, 1.0
}

// Render function
bool Scene::render(Image& outputImage) {
	// Get dimensions of output image
	int sizeX = outputImage.getSizeX();
	int sizeY = outputImage.getSizeY();

	// Ray-tracing algorithm
	// Loop over each pixel in our image.
	Ray cameraRay;
	qbVector<double> intersectPoint{ 3 };
	qbVector<double> localNormal{ 3 };
	qbVector<double> localColour{ 3 };
	double xScalingFactor = 1.0 / (static_cast<double>(sizeX) / 2.0);
	double yScalingFactor = 1.0 / (static_cast<double>(sizeY) / 2.0);
	double minDist = 1e6;
	double maxDist = 0.0;
	for (int y = 0; y < sizeY; ++y) {
		// Display debugging progress
		std::cout << "Rendering line " << y << " / " << sizeY << "\r";
		std::cout.flush();

		for (int x = 0; x < sizeX; ++x) {
			// Normalise XY Coord
			double normX = (static_cast<double>(x) * xScalingFactor) - 1.0; // -1 -> 1
			double normY = (static_cast<double>(y) * yScalingFactor) - 1.0;

			// Generate ray
			currCamera.createRay(normX, normY, cameraRay);

			// Test for intersections with all objects in the scene (using loop, auto is meant to define the correct data type)
			std::shared_ptr<ObjectBase> closestObject;
			qbVector<double> closestIntersectionPoint{ 3 };
			qbVector<double> closestLocalNormal{ 3 };
			qbVector<double> closestLocalColour{ 3 };
			bool intersectionFound = castRay(cameraRay, closestObject, closestIntersectionPoint, closestLocalNormal, closestLocalColour);

			// Compute lighting for closest object
			if (intersectionFound) {
				// Check if object has material
				if (closestObject->hasMaterial) {
					// Use material to compute colour
					// Reset counter, since we need to reset for each object rendered
					MaterialBase::reflRayCount = 0;
					qbVector<double> colour = closestObject->objectMaterial->computeColour(objectList, lightList, closestObject,
						closestIntersectionPoint, closestLocalNormal, cameraRay);
					outputImage.setPixel(x, y, colour.GetElement(0), colour.GetElement(1), colour.GetElement(2));
				} else {
					// Use diffuse lighting
					qbVector<double> matColor = MaterialBase::computeDiffuseColour(objectList, lightList, closestObject, closestIntersectionPoint,
						closestLocalNormal, closestObject->baseColour);
					outputImage.setPixel(x, y, matColor.GetElement(0), matColor.GetElement(1), matColor.GetElement(2));
				}
			}
		}
	}
	std::cout << std::endl;
	return true;
}

bool Scene::castRay(Ray& castRay, std::shared_ptr<ObjectBase>& closestObject, qbVector<double>& closestIntersectionPoint,
	qbVector<double>& closestLocalNormal, qbVector<double>& closestLocalColour) {
	qbVector<double> intersectionPoint{ 3 };
	qbVector<double> localNormal{ 3 };
	qbVector<double> localColour{ 3 };
	double minDist = 1e6;
	bool intersectionFound = false;

	for (auto currentObject : objectList) {
		bool isIntersect = currentObject->testIntersection(castRay, intersectionPoint, localNormal, localColour);
		// Output pixel colour 
		if (isIntersect) {
			// Set flag to show we found an intersection
			intersectionFound = true;

			// Compute distance between camera and point of intersection
			double dist = (intersectionPoint - castRay.currPointA).norm(); // measure the distance, if it is less than any other then we keep reference

			// If this object is closer to the camera, store a reference 
			if (dist < minDist) {
				minDist = dist;
				closestObject = currentObject;
				closestIntersectionPoint = intersectionPoint;
				closestLocalNormal = localNormal;
				closestLocalColour = localColour;
			}
		}
	}
	return intersectionFound;
}

void Scene::applyPostProcessing(Image& inputImage, int effectIndex, int windowWidth, int windowHeight) {
	/*
	This acts much like a frame buffer in OpenGL, we are essentially manipulating the drawn pixels AFTER they are drawn and rendered to the screen.
	By looping through each pixel and assigning it a uv coord we can play with the surface and create some nice effects. 
	*/
	for (int y = 0; y < windowHeight; ++y) {
		for (int x = 0; x < windowWidth; ++x) {
			double u = (static_cast<double>(x) / (static_cast<double>(windowWidth) / 2.0)) - 1.0;
			double v = (static_cast<double>(y) / (static_cast<double>(windowHeight) / 2.0)) - 1.0;
			qbVector<double> UV{ std::vector<double>{u, v} };
			qbVector<double> outputCol{ 3 };

			// Pixelisation //
			// The effect we are making is pixelisation of the canvas, we floor the colours and grab the top left pixel colour to display
			/*
			float cellSize = 4;
			float pointX = floor(x / cellSize) * cellSize;
			float pointY = floor(y / cellSize) * cellSize;
			qbVector<double> inputCol = inputImage.getPixel(pointX, pointY);
			for (int i = 0; i <= 2; i++) {
				outputCol.SetElement(i, inputCol.GetElement(i));
			}
			inputImage.setPixel(x, y, outputCol.GetElement(0), outputCol.GetElement(1), outputCol.GetElement(2)); */

			// Vignette //
			// The effect we are doing is a standard vignette, UV is a number -1 -> 1 so we're using the length of u and v (as an inverse 1.0 -) 
			// to dampen the colour values further from the center (0, 0)
			/*
			float len = sqrtf(powf(u, 2.0) + powf(v, 2.0));	
			qbVector<double> inputCol = inputImage.getPixel(x, y);
			for (int i = 0; i <= 2; i++) {
				outputCol.SetElement(i, inputCol.GetElement(i) * (1.0 - len));
			}
			inputImage.setPixel(x, y, outputCol.GetElement(0), outputCol.GetElement(1), outputCol.GetElement(2)); */

			// Chromatic Abberation (Still buggy) //
			/*
			float intensity = 0.001;
			float len = intensity * sqrtf(powf(u, 2.0) + powf(v, 2.0));
			outputCol.SetElement(0, inputImage.getPixel(NoiseFunctions::clamp(x - len, 1, windowWidth - 1), y).GetElement(0));
			outputCol.SetElement(1, inputImage.getPixel(x, y).GetElement(1));
			outputCol.SetElement(2, inputImage.getPixel(NoiseFunctions::clamp(x + len, 1, windowWidth - 1), y).GetElement(2));
			inputImage.setPixel(x, y, outputCol.GetElement(0), outputCol.GetElement(1), outputCol.GetElement(2)); */

			// Gaussian Blur //
			/*
			float blurDir = 32.0;
			float quality = 3.0;
			float blurRad = 512.0;
			for (int i = 0; i <= 2; i++) {
				outputCol.SetElement(i, inputImage.getPixel(x, y).GetElement(i));
			}
			for (float d = 0.0; d < PI; d += PI / blurDir) {
				for (float q = 1.0 / quality; q <= 1.0; q += 1.0 / quality) {
					float pX = NoiseFunctions::clamp(x + (cos(d) * (blurRad / windowWidth) * q), 1, windowWidth - 1);
					float pY = NoiseFunctions::clamp(y + (sin(d) * (blurRad / windowHeight) * q), 1, windowHeight - 1);
					for (int i = 0; i <= 2; i++) {
						outputCol.SetElement(i, outputCol.GetElement(i) + inputImage.getPixel(pX, pY).GetElement(i));
					}
				}
			}
			for (int i = 0; i <= 2; i++) {
				outputCol.SetElement(i, outputCol.GetElement(i) / (quality * blurDir - (blurDir - 1.0)));
			}
			inputImage.setPixel(x, y, outputCol.GetElement(0), outputCol.GetElement(1), outputCol.GetElement(2)); */
		}
	}
}


/* diffuse lighting (old)

					// Compute intensity
					double intensity;
					qbVector<double> colour{ 3 };
					double red = 0.0;
					double green = 0.0;
					double blue = 0.0;
					bool validLight = false;
					bool lightFound = false;

					// For every light add to rgb values on the screen
					for (auto currentLight : lightList) {
						validLight = currentLight->computeIlluminationContribution(closestIntersectionPoint,
							closestLocalNormal, objectList, closestObject, colour, intensity);
						if (validLight) {
							lightFound = true;
							red += colour.GetElement(0) * intensity;
							green += colour.GetElement(1) * intensity;
							blue += colour.GetElement(2) * intensity;
						}
					}

					// Merge output intensity with object colour
					if (lightFound) {
						red *= closestLocalColour.GetElement(0);
						green *= closestLocalColour.GetElement(1);
						blue *= closestLocalColour.GetElement(2);
						// Output
						outputImage.setPixel(x, y, red, green, blue);
					}
*/