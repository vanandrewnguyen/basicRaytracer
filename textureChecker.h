#ifndef TEXTUREMCHECKER_H
#define TEXTUREMCHECKER_H

#include "textureBase.h"

namespace Texture {
	class TextureChecker : public TextureBase {
	public:
		// Constructor destructor
		TextureChecker();
		virtual ~TextureChecker() override;

		// Functions 
		virtual qbVector<double> getColourAtUVCoord(const qbVector<double>& uvCoords) override;
		void setColour(const qbVector<double>& inputCol1, const qbVector<double> inputCol2);

	private:
		qbVector<double> colour1{ 4 };
		qbVector<double> colour2{ 4 };
	};
}

#endif