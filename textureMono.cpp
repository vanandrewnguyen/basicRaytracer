#include "textureMono.h"

Texture::TextureMono::TextureMono() {
	// Default is red
	colour = qbVector<double>{ std::vector<double>{1.0, 0.0, 0.0, 1.0} };
}

Texture::TextureMono::~TextureMono() {

}

qbVector<double> Texture::TextureMono::getColourAtUVCoord(const qbVector<double>& uvCoords) {
	// Since this is a flat texture (mono-colour) there needs no variation of colour, otherwise
	// you can do shaderToy eske things with uv coords, e.g. checkerboard, noise, etc. Fun stuff
	return colour;
}

void Texture::TextureMono::setColour(const qbVector<double>& inputCol) {
	colour = inputCol;
}