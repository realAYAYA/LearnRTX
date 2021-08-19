#ifndef MESH_H_
#define MESH_H_
#include<string>
#include<vector>

#include<gl/glew.h>
#include<glm/glm.hpp>

#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

namespace CppUtil {
	namespace OpenGL {
		struct Vertex {
			glm::vec3 Position;
			glm::vec3 Normal;
			glm::vec2 TexCoords;
		};

		struct TextureInfo {
			unsigned int id;
			std::string type;
			aiString path;
		};

		using std::vector;

		class Shader;
		
		class Mesh
		{
		public:
			Mesh() {};
			Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<TextureInfo> textures);
			~Mesh();			

			void Draw(Shader& shader);
			//void DrawArrays(Shader* shader, const glm::mat4& modelMat);
			//void DrawElements(Shader* shader);

			unsigned int GetVAO()const { return this->VAO; }
		private:
			unsigned int VAO;
			vector<Vertex> vertices;
			vector<unsigned int> indices;
			vector<TextureInfo> textures;

			void setupMesh();
		};

		class Interface {
		public:
			enum MeshType
			{
				ENUM_TYPE_MODEL,
				ENUM_TYPE_MESH,
				ENUM_TYPE_SKYBOX
			};
			virtual void Draw(Shader& shader) {}
		private:
			MeshType type;
		};

		class SimpleMesh:public Interface {
		public:
			enum Type// 数组存储形式
			{
				ENUM_FORMAT_PCT,// pos color texcoord
				ENUM_FORMAT_PNT,// pos normal texcoord
				ENUM_FORMAT_PN,// pos normal
				ENUM_FORMAT_PT,// pos texcoord
				ENUM_FORMAT_P,// only pos
			};
			SimpleMesh(const GLfloat _vertices[], const int size, Type type);
			SimpleMesh(const GLfloat _vertices[], const int size1, Type type, const GLuint _indices[], const int size2);

			virtual void Draw(Shader& shader)override;
		private:
			void setupMesh();

			bool IsValid;

			unsigned int VAO;
			vector<Vertex> vertices;
			vector<unsigned int> indices;
			vector<TextureInfo> textures;
			int drawCount;// 根据顶点数目决定绘制次数
			Type type;
		};
	}
}
#endif // !MESH_H_