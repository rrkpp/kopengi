/*
*	CShader_Raster.h - Regan Russell
*
*	Rasterizes post-processing FBOs and renders to screen.
*/

#ifndef _CSHADER_RASTER_H_
#define _CSHADER_RASTER_H_

class CShader_Raster : public CShader
{
public:
	CShader_Raster(std::string vs_path, std::string ps_path);
	~CShader_Raster();

	virtual void PreLink(GLuint ID);
	virtual void Activate();
	virtual void Update();
	virtual void Render();
};

#endif