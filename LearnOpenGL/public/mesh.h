//#ifndef MESH_H 
//#define MESH_H 
//
//#include <glad/glad.h>
//
//#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
//
//#include <shader_m.h>
//
//#include <string>
//#include <fstream>
//#include <sstream>
//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//struct Vertex {
//	// position
//	glm::vec3 Position;
//	glm::vec3 Normal;
//	glm::vec2 TexCoords;
//	glm::vec3 Tangent;
//	glm::vec3 Bitangent;
//};
//
//struct Texture {
//	unsigned int id;
//	string type;
//	string path;
//};
//
//class Mesh {
//public:
//	vector<Vertex> m_Vertices;
//	vector<unsigned int> m_Indices;
//	vector<Texture> m_Textures;
//	unsigned int VAO;
//
//	Mesh(vector<Vertex> _Vertices, vector<unsigned int> _Indices, vector<Texture> _Texture)
//	{
//		this->m_Vertices = _Vertices;
//		this->m_Indices = _Indices;
//		this->m_Textures = _Texture;
//
//		setupMesh();
//	}
//
//	void Draw(Shader _Shader)
//	{
//		unsigned int _DiffuseNr = 1;
//		unsigned int _SpecularNr = 1;
//		unsigned int _NormalNr = 1;
//		unsigned int _HeightNr = 1;
//		for (unsigned int i = 0; i < m_Textures.size(); i++)
//		{
//			// needSee
//			glActiveTexture(GL_TEXTURE0 + i);
//
//			string _Number;
//			string _Name = m_Textures.type;
//
//			if (_Name == "texture_diffuse")
//				_Number = std::to_string(_DiffuseNr++);
//			else if (_Name == "texture_specular")
//				_Number = std::to_string(_SpecularNr++); // transfer unsigned int to stream
//			else if (_Name == "texture_normal")
//				_Number = std::to_string(_NormalNr++); // transfer unsigned int to stream
//			else if (_Name == "texture_height")
//				_Number = std::to_string(_HeightNr++); // transfer unsigned int to stream
//
//			glUniform1i(glGetUniformLocation(_Shader.ID, (_Name + _Number).c_str()), i);
//			// and finally bind the texture
//			glBindTexture(GL_TEXTURE_2D, m_Textures[i].id);
//		}
//
//		// draw mesh
//		glBindVertexArray(VAO);
//		glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
//		glBindVertexArray(0);
//
//		// always good practice to set everything back to defaults once configured.
//		glActiveTexture(GL_TEXTURE0);
//	}
//
//private:
//	unsigned int VBO, EBO;
//
//	void setupMesh()
//	{
//		// create buffers/arrays
//		glGenVertexArrays(1, &VAO);
//		glGenBuffers(1, &VBO);
//		glGenBuffers(1, &EBO);
//
//		glBindVertexArray(VAO);
//		// load data into vertex buffers
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		// A great thing about structs is that their memory layout is sequential for all its items.
//		// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
//		// again translates to 3/2 floats which translates to a byte array.
//		glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW);
//
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);
//
//		// set the vertex attribute pointers
//		// vertex Positions
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
//		// vertex normals
//		glEnableVertexAttribArray(1);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
//		// vertex texture coords
//		glEnableVertexAttribArray(2);
//		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
//		// vertex tangent
//		glEnableVertexAttribArray(3);
//		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
//		// vertex bitangent
//		glEnableVertexAttribArray(4);
//		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
//
//		glBindVertexArray(0);
//	}
//};
//
//#endif