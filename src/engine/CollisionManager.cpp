#include "CollisionManager.h"

void CollisionManager::Uncollide(std::vector<Mesh>& meshObjects, std::vector<Model>& modelObjects)
{
	UncollideMeshToMesh(meshObjects);
	UncollideModelToModel(modelObjects);
	UncollideMeshToModel(meshObjects, modelObjects);
	UncollideModelToMesh(modelObjects, meshObjects);
}

void CollisionManager::UncollideMeshToMesh(std::vector<Mesh>& meshObjects)
{
	for (int i = 0; i < meshObjects.size() - 1; i++)
	{
		for (int j = i + 1; j < meshObjects.size(); j++)
		{
			float firstRadius = Utils::Get3DObjectLongestSide(meshObjects[i].scale.x, meshObjects[i].scale.y, meshObjects[i].scale.z) / 2;
			float secondRadius = Utils::Get3DObjectLongestSide(meshObjects[j].scale.x, meshObjects[j].scale.y, meshObjects[j].scale.z) / 2;

			float distance = glm::sqrt(
				glm::pow((meshObjects[i].position.x - meshObjects[j].position.x), 2) +
				glm::pow((meshObjects[i].position.y - meshObjects[j].position.y), 2) +
				glm::pow((meshObjects[i].position.z - meshObjects[j].position.z), 2));

			if (distance <= firstRadius + secondRadius)
			{
				glm::vec3 diff = meshObjects[i].position - meshObjects[j].position;
				if (diff == glm::vec3(0.0f)) diff = glm::vec3(1.0f, 0.0f, 0.0f);
				meshObjects[i].position = meshObjects[j].position + glm::normalize(diff) * (firstRadius + secondRadius);
			}
		}
	}
}

void CollisionManager::UncollideModelToModel(std::vector<Model>& modelObjects)
{
	for (int i = 0; i < modelObjects.size() - 1; i++)
	{
		for (int j = i + 1; j < modelObjects.size(); j++)
		{
			float firstRadius = Utils::Get3DObjectLongestSide(modelObjects[i].scale.x, modelObjects[i].scale.y, modelObjects[i].scale.z) / 2;
			float secondRadius = Utils::Get3DObjectLongestSide(modelObjects[j].scale.x, modelObjects[j].scale.y, modelObjects[j].scale.z) / 2;

			float distance = glm::sqrt(
				glm::pow((modelObjects[i].position.x - modelObjects[j].position.x), 2) +
				glm::pow((modelObjects[i].position.y - modelObjects[j].position.y), 2) +
				glm::pow((modelObjects[i].position.z - modelObjects[j].position.z), 2));

			if (distance <= firstRadius + secondRadius)
			{
				glm::vec3 diff = modelObjects[i].position - modelObjects[j].position;
				if (diff == glm::vec3(0.0f)) diff = glm::vec3(1.0f, 0.0f, 0.0f);
				modelObjects[i].position = modelObjects[j].position + glm::normalize(diff) * (firstRadius + secondRadius);
			}
		}
	}
}

void CollisionManager::UncollideMeshToModel(std::vector<Mesh>& meshObjects, std::vector<Model>& modelObjects)
{
	for (int i = 0; i < meshObjects.size(); i++)
	{
		for (int j = 0; j < modelObjects.size(); j++)
		{
			float firstRadius = Utils::Get3DObjectLongestSide(meshObjects[i].scale.x, meshObjects[i].scale.y, meshObjects[i].scale.z) / 2;
			float secondRadius = Utils::Get3DObjectLongestSide(modelObjects[j].scale.x, modelObjects[j].scale.y, modelObjects[j].scale.z) / 2;

			float distance = glm::sqrt(
				glm::pow((meshObjects[i].position.x - modelObjects[j].position.x), 2) +
				glm::pow((meshObjects[i].position.y - modelObjects[j].position.y), 2) +
				glm::pow((meshObjects[i].position.z - modelObjects[j].position.z), 2));

			if (distance <= firstRadius + secondRadius)
			{
				glm::vec3 diff = meshObjects[i].position - modelObjects[j].position;
				if (diff == glm::vec3(0.0f)) diff = glm::vec3(1.0f, 0.0f, 0.0f);
				meshObjects[i].position = modelObjects[j].position + glm::normalize(diff) * (firstRadius + secondRadius);
			}
		}
	}
}

void CollisionManager::UncollideModelToMesh(std::vector<Model>& modelObjects, std::vector<Mesh>& meshObjects)
{
	for (int i = 0; i < modelObjects.size(); i++)
	{
		for (int j = 0; j < meshObjects.size(); j++)
		{
			float firstRadius = Utils::Get3DObjectLongestSide(modelObjects[i].scale.x, modelObjects[i].scale.y, modelObjects[i].scale.z) / 2;
			float secondRadius = Utils::Get3DObjectLongestSide(meshObjects[j].scale.x, meshObjects[j].scale.y, meshObjects[j].scale.z) / 2;

			float distance = glm::sqrt(
				glm::pow((modelObjects[i].position.x - meshObjects[j].position.x), 2) +
				glm::pow((modelObjects[i].position.y - meshObjects[j].position.y), 2) +
				glm::pow((modelObjects[i].position.z - meshObjects[j].position.z), 2));

			if (distance <= firstRadius + secondRadius)
			{
				glm::vec3 diff = modelObjects[i].position - meshObjects[j].position;
				if (diff == glm::vec3(0.0f)) diff = glm::vec3(1.0f, 0.0f, 0.0f);
				modelObjects[i].position = meshObjects[j].position + glm::normalize(diff) * (firstRadius + secondRadius);
			}
		}
	}
}
