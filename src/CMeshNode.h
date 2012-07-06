/*
*	CMeshNode.h - Regan Russell
*
*	Node that holds static mesh data.
*/

#ifndef _CMESHNODE_H_
#define _CMESHNODE_H_

class CMeshNode : public ISceneNode
{
public:
	CMeshNode();
	~CMeshNode();

	void Draw(bool useShader = true);
	
	void SetModel(CModel* model);
	CModel* GetModel();

	void UpdateShader(CMesh* mesh = 0, CLight* light = 0);
	void SetShader(CShader* shader);
	CShader* GetShader();

	void SetMaterial(CMaterial* mat);
	CMaterial* GetMaterial();
	void ClearMaterial();

private:
	CModel* m_Model;
	CShader* m_Shader;
	CMaterial* m_Material;
};

#endif