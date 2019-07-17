#pragma once

#include <RamjetCore.h>

class Test3D : public Core::Rendering::Layer3D 
{
private:
	Core::Entities::Entity* m_Cube;
	Core::Entities::Entity* m_Sphere;
	Core::Entities::Entity* m_Plane;

	Core::Manager::Control_Manager* C_Manager;

	bool m_SetUniforms[2];
	float m_Rotation;
public:
	Test3D();
	~Test3D();

	void onInit(Core::Rendering::Renderer3D& renderer, Core::Rendering::Scene& scene) override;

	void onTick() override;
	void onUpdate() override;
	void onEvent() override;
};