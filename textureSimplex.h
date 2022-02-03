#ifndef TEXTURESIMPLEX_H
#define TEXTURESIMPLEX_H

#include "textureBase.h"
#include "noiseFunctions.h"

namespace Texture {
	class TextureSimplex : public TextureBase {
	public:
		// Constructor destructor
		TextureSimplex();
		virtual ~TextureSimplex() override;

		// Functions 
		virtual qbVector<double> getColourAtUVCoord(const qbVector<double>& uvCoords) override;
		void setColour(const qbVector<double>& inputCol1, const qbVector<double> inputCol2);
		
	private:
		qbVector<double> colour1{ 4 };
		qbVector<double> colour2{ 4 };
	};
}

#endif