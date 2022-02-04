#ifndef TEXTUREDOT_H
#define TEXTUREDOT_H

#include "textureBase.h"
#include "noiseFunctions.h"

namespace Texture {
	class TexturePolkaDot : public TextureBase {
	public:
		// Constructor destructor
		TexturePolkaDot();
		virtual ~TexturePolkaDot() override;

		// Functions 
		virtual qbVector<double> getColourAtUVCoord(const qbVector<double>& uvCoords) override;
		void setColour(const qbVector<double>& inputCol1, const qbVector<double> inputCol2);
		void setRad(float rad, float blur);

	private:
		qbVector<double> colour1{ 4 };
		qbVector<double> colour2{ 4 };
		float radius;
		float blurRad;
	};
}

#endif