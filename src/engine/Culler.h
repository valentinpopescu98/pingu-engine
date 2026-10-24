#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Mesh.h"
#include "Model.h"

class Culler
{
	public:
		static void FrontFaceCulling();
		static void BackFaceCulling();
		static bool MeshInFrustum(Camera& camera, Mesh& mesh);
		static bool ModelInFrustum(Camera& camera, Model& model);
    private:
		static void ComputeSphereData(Camera& camera);
		static int SphereInFrustum(Camera& camera, glm::vec3 spherePos, float radius);

		enum { OUTSIDE, INTERSECT, INSIDE };
		static glm::vec3 X, Y, Z; // Camera referential
		static float sphereFactorX, sphereFactorY; // Variables required to test spheres
		static float tang;
};