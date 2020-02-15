//#ifndef MODEL_H 
//#define MODEL_H 
//
//#include <glad/glad.h>
//
//#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
//#include <stb_image.h>
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//
//#include <mesh.h>
//#include <shader_m.h>
//
//#include <string>
//#include <fstream>
//#include <sstream>
//#include <iostream>
//#include <map>
//#include <vector>
//
//using namespace std;
//
//unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);
//
//class Model
//{
//public:
//	Model(char* _Path)
//	{
//		loadModel(_Path);
//	}
//
//	void Draw(Shader _Shader)
//	{
//		for (unsigned int i = 0; i < m_Meshes.size(); i++)
//		{
//			m_Meshes[i].Draw(_Shader);
//		}
//	}
//
//private:
//	vector<Mesh> m_Meshes;
//	string m_Directory;
//
//	void loadModel(string _Path)
//	{
//		Assimp::Importer _Importer;
//		const aiScene* _Scene = _Importer.ReadFile(_Path, aiProcess_Triangulate | aiProcess_FlipUVs);
//
//		if (!_Scene || _Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !_Scene->mRootNode)
//		{
//			cout << "ERROR::ASSIMP:: " << _Importer.GetErrorString() << endl;
//			return;
//		}
//		m_Directory = _Path.substr(0, _Path.find_last_of('/'));
//
//		processNode(_Scene->mRootNode, _Scene);
//	}
//
//	void processNode(aiNode* _Node, const aiScene* _Scene)
//	{
//		for (unsigned int i = 0; i < _Node->mNumMeshes; i++)
//		{
//			aiMesh* _Mesh = _Scene->mMeshes[_Node->mMeshes[i]];
//			m_Meshes.push_back(processMesh(_Mesh, _Scene));
//		}
//
//		for (unsigned int i = 0; i < _Node->mNumChildren; i++)
//		{
//			processNode(_Node->mChildren[i], _Scene);
//		}
//	}
//	Mesh processMesh(aiMesh* _Mesh, const aiScene* _Scene)
//	{
//		vector<Vertex> _Vertices;
//		vector<unsigned int> _Indices;
//		vector<Texture> _Textures;
//
//		for (unsigned int i = 0; i < _Mesh->mNumVertices; i++)
//		{
//			Vertex _Vertex;
//
//			glm::vec3 _Vector;
//			_Vector.x = _Mesh->mVertices[i].x;
//			_Vector.y = _Mesh->mVertices[i].y;
//			_Vector.z = _Mesh->mVertices[i].z;
//			_Vertex.Position = _Vector;
//
//			_Vector.x = _Mesh->mNormals[i].x;
//			_Vector.y = _Mesh->mNormals[i].y;
//			_Vector.z = _Mesh->mNormals[i].z;
//			_Vertex.Normal = _Vector;
//
//			if (_Mesh->mTextureCoords[0])
//			{
//				glm::vec2 vec2;
//				vec2.x = _Mesh->mTextureCoords[0][i].x;
//				vec2.y = _Mesh->mTextureCoords[0][i].y;
//				_Vertex.TexCoords = vec2;
//			}
//			else
//				_Vertex.TexCoords = glm::vec2(0.f, 0.f);
//
//			_Vertices.push_back(_Vertex);
//		}
//
//		for (unsigned int i = 0; i < _Mesh->mNumFaces; i++)
//		{
//			aiFace _Face = _Mesh->mFaces[i];
//			for (unsigned int j = 0; j < _Face.mNumIndices; j++)
//			{
//				_Indices.push_back(_Face.mIndices[j]);
//			}
//		}
//
//		aiMaterial* _Material = _Scene->mMaterials[_Mesh->mMaterialIndex];
//		vector<Texture> _DiffuseMaps = loadMaterialTextures(_Material, aiTextureType_DIFFUSE, "Texture_diffuse");
//		_Textures.insert(_Textures.end(), _DiffuseMaps.begin(), _DiffuseMaps.end());
//
//		vector<Texture> _SpecularMaps = loadMaterialTextures(_Material, aiTextureType_SPECULAR, "Texture_diffuse");
//		_Textures.insert(_Textures.end(), _SpecularMaps.begin(), _SpecularMaps.end());
//
//
//
//		return Mesh(_Vertices, _Indices, _Textures);
//	}
//	vector<Texture> loadMaterialTextures(aiMaterial* _Mat, aiTextureType _Type, string _TypeName)
//	{
//		vector<Texture> _Textures;
//		for (unsigned int i = 0; i < _Mat->GetTextureCount(_Type); i++)
//		{
//			aiString _Str;
//			_Mat->GetTexture((_Type, i, &_Str);
//			Texture _Texture;
//			_Texture.id = TextureFromFile(_Str.C_Str(), directory);
//			_Texture.type = _TypeName;
//			_Texture.path = str;
//			_Textures.push_back(_Texture);
//		}
//	}
//
//};
//
//#endif