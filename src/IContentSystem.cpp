/*
*	IContentSystem.cpp - Regan Russell
*
*	Content interface, handles content loading and memory
*	management associated with assets.
*/

#include "kopengi.h"

IContentSystem::IContentSystem()
{
	m_ErrorTexture = SOIL_load_OGL_texture("textures/engine/error.tga", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
}

IContentSystem::~IContentSystem()
{
	// Delete models
	m_ModelCache.clear();
}

CModel* IContentSystem::GetModel(std::string path)
{
	if (m_ModelCache[path] != NULL)
	{
		return m_ModelCache[path];
	}
	else
	{
		return LoadModel(path);
	}
}

// ========================================================================
// Credit to Lighthouse3D and their OpenGL tutorials for most of this code!
// http://www.lighthouse3d.com/cg-topics/code-samples/importing-3d-models-with-assimp/
// ========================================================================
CModel* IContentSystem::LoadModel(std::string filepath)
{
	const aiScene* data = m_Importer.ReadFile(filepath, aiProcess_Triangulate);
	CModel* out_model = new CModel();

	if (!data)
	{
		std::cout << "ERROR: Failed to load file: " << m_Importer.GetErrorString() << std::endl;
		return 0;
	}

	// Load textures
	std::map<std::string, GLuint> textures;
	for (unsigned int i = 0; i < data->mNumMaterials; i++)
	{
		int texIndex = 0;
		aiString path;

		aiReturn texFound = data->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
		while (texFound == AI_SUCCESS)
		{
			std::string pathData = path.data;
			textures[pathData] = GetTexture(pathData);
			texIndex++;
			texFound = data->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
		}
	}

	// Load mesh data
	for (unsigned int i = 0; i < data->mNumMeshes; i++)
	{
		const struct aiMesh* mesh = data->mMeshes[i];

		// Output mesh
		CMesh* outMesh = new CMesh();
		struct CMaterial outMaterial;

		// Convert faces
		unsigned int* faces;
		faces = (unsigned int*)malloc(sizeof(unsigned int) * mesh->mNumFaces * 3);
		unsigned int faceIndex = 0;

		for (unsigned int i2 = 0; i2 < mesh->mNumFaces; i2++)
		{
			const struct aiFace* face = &mesh->mFaces[i2];
			memcpy(&faces[faceIndex], face->mIndices, 3 * sizeof(float));
			faceIndex += 3;
		}

		outMesh->m_NumFaces = data->mMeshes[i]->mNumFaces;

		// Temp variables to save buffer IDs
		GLuint vertexBuffer = 0;
		GLuint texcoordBuffer = 0;
		GLuint normalBuffer = 0;
		GLuint indexBuffer = 0;

		// Index Buffer
		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->mNumFaces * 3, faces, GL_STATIC_DRAW);

		// Position Buffer
		if (mesh->HasPositions())
		{
			glGenBuffers(1, &vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->mNumVertices * 3, mesh->mVertices, GL_STATIC_DRAW);
		}

		// TexCoord Buffer
		if (mesh->HasTextureCoords(0))
		{
			// Fill the texCoords array with properly formatted texCoord data
			float* texCoords = (float*)malloc(sizeof(float) * 2 * mesh->mNumVertices);
			for (unsigned int i2 = 0; i2 < mesh->mNumVertices; i2++)
			{
				texCoords[i2 * 2] = mesh->mTextureCoords[0][i2].x;
				texCoords[i2 * 2 + 1] = mesh->mTextureCoords[0][i2].y;
			}

			glGenBuffers(1, &texcoordBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, texcoordBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->mNumVertices * 2, texCoords, GL_STATIC_DRAW);
		}

		// Normal Buffer
		if (mesh->HasNormals())
		{
			glGenBuffers(1, &normalBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->mNumVertices * 3, mesh->mNormals, GL_STATIC_DRAW);
		}

		// Save buffers to Mesh
		outMesh->m_VertexBuffer = vertexBuffer;
		outMesh->m_UVBuffer = texcoordBuffer;
		outMesh->m_NormalBuffer = normalBuffer;
		outMesh->m_IndexBuffer = indexBuffer;

		// Unbind buffers
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// Material uniform buffer
		struct aiMaterial* material = data->mMaterials[mesh->mMaterialIndex];

		// Get the OpenGL texture ID and save it
		aiString texPath;
		if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texPath) == AI_SUCCESS)
		{
			std::string pathData = texPath.data;
			GLuint texID = textures[pathData];
			outMesh->m_TextureIndex = texID;
			outMaterial.m_TextureCount = 1;
		}
		else
		{
			outMaterial.m_TextureCount = 0;
		}

		float color[4] = {0.5f, 0.5f, 0.5f, 1.0f};

		aiColor4D diffuse;
		if (aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse) == AI_SUCCESS)
		{
			color[0] = diffuse.r;
			color[1] = diffuse.g;
			color[2] = diffuse.b;
			color[3] = diffuse.a;
		}
		outMaterial.m_Diffuse = glm::vec4(color[0], color[1], color[2], color[3]);

		aiColor4D ambient;
		if (aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambient) == AI_SUCCESS)
		{
			color[0] = ambient.r;
			color[1] = ambient.g;
			color[2] = ambient.b;
			color[3] = ambient.a;
		}
		outMaterial.m_Ambient = glm::vec4(color[0], color[1], color[2], color[3]);

		aiColor4D specular;
		if (aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specular) == AI_SUCCESS)
		{
			color[0] = specular.r;
			color[1] = specular.g;
			color[2] = specular.b;
			color[3] = specular.a;
		}
		outMaterial.m_Specular = glm::vec4(color[0], color[1], color[2], color[3]);

		aiColor4D emissive;
		if (aiGetMaterialColor(material, AI_MATKEY_COLOR_EMISSIVE, &emissive) == AI_SUCCESS)
		{
			color[0] = emissive.r;
			color[1] = emissive.g;
			color[2] = emissive.b;
			color[3] = emissive.a;
		}
		outMaterial.m_Emissive = glm::vec4(color[0], color[1], color[2], color[3]);

		float shininess = 0.0;
		unsigned int max = 0;
		
		aiGetMaterialFloatArray(material, AI_MATKEY_SHININESS, &shininess, &max);
		outMaterial.m_Shininess = shininess;
		outMesh->SetMaterial(outMaterial);

		// Store our mesh in the output Model
		out_model->AddMesh(outMesh);
	}

	m_ModelCache[filepath] = out_model;
	return out_model;
}

GLuint IContentSystem::GetTexture(std::string path)
{
	if (m_TextureCache[path] != 0)
	{
		return m_TextureCache[path];
	}

	GLuint result = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

	if (result == 0)
	{
		std::cout << "ERROR: Failed to load file: " << path << std::endl;
		std::cout << ">> SOIL: " << SOIL_last_result() << std::endl;
		result = GetErrorTexture();
		return result;
	}

	m_TextureCache[path] = result;
	return result;
}

GLuint IContentSystem::GetErrorTexture()
{
	return m_ErrorTexture;
}
