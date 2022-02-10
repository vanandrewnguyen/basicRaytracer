#ifndef TEXTURECELLULAR_H
#define TEXTURECELLULAR_H

#include "textureBase.h"
#include "noiseFunctions.h"

namespace Texture {
	class TextureCellular : public TextureBase {
	public:
		// Constructor destructor
		TextureCellular();
		virtual ~TextureCellular() override;

		// Functions 
		virtual qbVector<double> getColourAtUVCoord(const qbVector<double>& uvCoords) override;
		void setColour(const qbVector<double>& inputCol);

	private:
		qbVector<double> colour{ 4 };
	};
}

#endif