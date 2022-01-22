#ifndef TEXBASE_H
#define TEXBASE_H

#include <memory>
#include "qbLinAlg/qbMatrix.h"
#include "qbLinAlg/qbVector.h"
#include "ray.h"

namespace Texture {
	class TextureBase {
	public:
		// Constructor destructor
		TextureBase();
		~TextureBase();

		// Functions
		// Returns 4D vector (RGBA)
		virtual qbVector<double> getColourAtUVCoord(const qbVector<double> &uvCoords);
		void setTransform(const qbVector<double> &translation, const double rotation, const qbVector<double>& scale);
		static qbVector<double> blend4DColoursTo3D(const std::vector<qbVector<double>>& inputColourList);
		qbVector<double> applyTransform(const qbVector<double> &inputVector);

	private:
		// Init transform matrix to identity matrix
		qbMatrix2<double> transformMatrix{ 3, 3, std::vector<double>{1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0} };
	};
}

#endif