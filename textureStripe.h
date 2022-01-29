#ifndef TEXTURESTRIPE_H
#define TEXTURESTRIPE_H

#include "textureBase.h"

namespace Texture {
	class TextureStripe : public TextureBase {
	public:
		// Constructor destructor
		TextureStripe();
		virtual ~TextureStripe() override;

		// Functions 
		virtual qbVector<double> getColourAtUVCoord(const qbVector<double>& uvCoords) override;
		void setColour(const qbVector<double>& inputCol1, const qbVector<double> inputCol2);

	private:
		qbVector<double> colour1{ 4 };
		qbVector<double> colour2{ 4 };
	};
}

#endif