#ifndef TEXTUREPERLIN_H
#define TEXTUREPERLIN_H

#include "textureBase.h"
#include "noiseFunctions.h"

namespace Texture {
	class TexturePerlin : public TextureBase {
	public:
		// Constructor destructor
		TexturePerlin();
		virtual ~TexturePerlin() override;

		// Functions 
		virtual qbVector<double> getColourAtUVCoord(const qbVector<double>& uvCoords) override;
		void setColour(const qbVector<double>& inputCol);

	private:
		qbVector<double> colour{ 4 };
	};
}

#endif