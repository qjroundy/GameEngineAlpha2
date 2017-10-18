#include "Terrain.h"


Terrain::Terrain()
{
}


Terrain::~Terrain()
{
}

Terrain::Terrain
(
GLint gridX, 
GLint gridZ, 
Loader* loader, 
TerrainTexturePack* texturePack,
TerrainTexture* blendMap
)
:
_texturePack(texturePack),
_blendMap(blendMap)
{
	_x = static_cast<GLfloat>(gridX) * SIZE;
	_z = static_cast<GLfloat>(gridZ) * SIZE;
	_model = generateTerrain(loader);
}



GLfloat Terrain::x() {
	return _x;
}



GLfloat Terrain::z() {
	return _z;
}



RawModel* Terrain::model() {
	return _model;
}

TerrainTexturePack * Terrain::texturePack()
{
	return _texturePack;
}

TerrainTexture * Terrain::blendMap()
{
	return _blendMap;
}

RawModel* Terrain::generateTerrain(Loader* loader){
	GLuint count = VERTEX_COUNT * VERTEX_COUNT;

	vector<GLfloat>* vertices = new vector<GLfloat>{};
	vector<GLfloat>* normals = new vector<GLfloat>{};
	vector<GLfloat>* textureCoords = new vector<GLfloat>{};
	vector<GLint>* indices = new vector<GLint>{};

	vertices->resize(count * 3);
	normals->resize(count * 3);
	textureCoords->resize(count * 2);
	indices->resize(6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1));
	
	GLuint vertexPointer = 0;
	for (GLuint i = 0; i<VERTEX_COUNT; i++){
		for (GLuint j = 0; j<VERTEX_COUNT; j++){
			(*vertices)[vertexPointer * 3] = static_cast<GLfloat>(j) / (static_cast<GLfloat>(VERTEX_COUNT - 1) * SIZE);
			(*vertices)[vertexPointer * 3 + 1] = 0;
			(*vertices)[vertexPointer * 3 + 2] = static_cast<GLfloat>(i) / (static_cast<GLfloat>(VERTEX_COUNT - 1) * SIZE);
			(*normals)[vertexPointer * 3] = 0;
			(*normals)[vertexPointer * 3 + 1] = 1;
			(*normals)[vertexPointer * 3 + 2] = 0;
			(*textureCoords)[vertexPointer * 2] = static_cast<GLfloat>(j) / static_cast<GLfloat>(VERTEX_COUNT - 1);
			(*textureCoords)[vertexPointer * 2 + 1] = static_cast<GLfloat>(i) / static_cast<GLfloat>(VERTEX_COUNT - 1);
			vertexPointer++;
		}
	}
	
	int pointer = 0;
	for (int gz = 0; gz<VERTEX_COUNT - 1; gz++){
		for (int gx = 0; gx<VERTEX_COUNT - 1; gx++){
			int topLeft = (gz*VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			(*indices)[pointer++] = topLeft;
			(*indices)[pointer++] = bottomLeft;
			(*indices)[pointer++] = topRight;
			(*indices)[pointer++] = topRight;
			(*indices)[pointer++] = bottomLeft;
			(*indices)[pointer++] = bottomRight;
		}
	}
	return loader->loadToVao(vertices, textureCoords, normals, indices);
}


