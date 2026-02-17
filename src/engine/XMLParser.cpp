#include "XMLParser.h"

void XmlParser::Init(const char* path, GLuint firstTextureID)
{
	this->firstTextureID = firstTextureID;

	pugi::xml_parse_result result = doc.load_file(path); // Load the XML file
	if (!result)
	{
		std::cout << "ERROR: Failed to load XML file '" << path << "': " << result.description() << std::endl;
	}
	scene = doc.child("scene"); // Create node for the scene
}

// Initialize all MODELS from the XML
void XmlParser::CreateModels(pugi::xml_node node, std::vector<Model>& modelLights, std::vector<Model>& modelObjects)
{
	for (pugi::xml_node entity : node.children())
	{
		std::string modelPath = entity.attribute("modelPath").value();
		std::string texturePath = entity.attribute("texturePath").value();

		float posX = std::stof(entity.child("position").attribute("x").value());
		float posY = std::stof(entity.child("position").attribute("y").value());
		float posZ = std::stof(entity.child("position").attribute("z").value());

		float rotX = std::stof(entity.child("rotation").attribute("x").value());
		float rotY = std::stof(entity.child("rotation").attribute("y").value());
		float rotZ = std::stof(entity.child("rotation").attribute("z").value());

		float scaleX = std::stof(entity.child("scale").attribute("x").value());
		float scaleY = std::stof(entity.child("scale").attribute("y").value());
		float scaleZ = std::stof(entity.child("scale").attribute("z").value());

		float colX = std::stof(entity.child("color").attribute("r").value());
		float colY = std::stof(entity.child("color").attribute("g").value());
		float colZ = std::stof(entity.child("color").attribute("b").value());

		std::string parentName = entity.parent().name();
		if (parentName == (std::string)"scene")
		{
			parent.position = glm::vec3(0.0f, 0.0f, 0.0f);
			parent.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
			parent.scale = glm::vec3(1.0f, 1.0f, 1.0f);
		}

		if (entity.attribute("texturePath").value() == (std::string)"")
		{
			if (entity.name() == (std::string)"light")
			{
				modelLights.push_back(Model());
				modelLights.back().Import(parent, modelPath,
					glm::vec3(posX, posY, posZ), glm::vec3(rotX, rotY, rotZ), glm::vec3(scaleX, scaleY, scaleZ), glm::vec3(colX, colY, colZ));
			}
			else if (entity.name() == (std::string)"object")
			{
				modelObjects.push_back(Model());
				modelObjects.back().Import(parent, modelPath,
					glm::vec3(posX, posY, posZ), glm::vec3(rotX, rotY, rotZ), glm::vec3(scaleX, scaleY, scaleZ), glm::vec3(colX, colY, colZ));
			}
		}
		else
		{
			if (entity.name() == (std::string)"light")
			{
				modelLights.push_back(Model());
				modelLights.back().Import(parent, modelPath, texturePath,
					glm::vec3(posX, posY, posZ), glm::vec3(rotX, rotY, rotZ), glm::vec3(scaleX, scaleY, scaleZ), glm::vec3(colX, colY, colZ));
				modelLights.back().CreateTextures(firstTextureID);
				firstTextureID += modelLights.back().nextTextureID;
			}
			else if (entity.name() == (std::string)"object")
			{
				modelObjects.push_back(Model());
				modelObjects.back().Import(parent, modelPath, texturePath,
					glm::vec3(posX, posY, posZ), glm::vec3(rotX, rotY, rotZ), glm::vec3(scaleX, scaleY, scaleZ), glm::vec3(colX, colY, colZ));
				modelObjects.back().CreateTextures(firstTextureID);
				firstTextureID += modelObjects.back().nextTextureID;
			}
		}

		pugi::xml_node childrenNode = entity.child("children");
		if (std::distance(childrenNode.children().begin(), childrenNode.children().end()) > 0)
		{
			if (entity.name() == (std::string)"light")
			{
				parent = modelLights.back();
			}
			else if (entity.name() == (std::string)"object")
			{
				parent = modelObjects.back();
			}

			CreateModels(childrenNode, modelLights, modelObjects);
		}
	}
}