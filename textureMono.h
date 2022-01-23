#ifndef TEXTUREMONO_H
#define TEXTUREMONO_H

#include "textureBase.h"

namespace Texture {
	class TextureMono : public TextureBase {
	public:
		// Constructor destructor
		TextureMono();
		virtual ~TextureMono() override;

		// Functions 
		virtual qbVector<double> getColourAtUVCoord(const qbVector<double>& uvCoords) override;
		void setColour(const qbVector<double> &inputCol);

	private:
		qbVector<double> colour{ 4 };
	};
}

#endif