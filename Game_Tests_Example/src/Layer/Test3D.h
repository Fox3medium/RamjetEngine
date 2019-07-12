#pragma once

#include <App/Application.h>
#include <Utils/Maths/maths.h>

#include <Rendering/Renderer/Models/Model.h>

#include <Rendering/Renderer/Layers/Layer3D.h>
#include <Rendering/Renderer/Renderer3D.h>
#include <Managers/Managers.h>
#include <Utils/Log.h>

class Test3D : public Core::Rendering::Layer3D 
{
private:
	Core::Rendering::Mesh* m_Cube;
	Core::Rendering::MaterialInstance* m_CubeMat;
	Core::Rendering::MaterialInstance* m_SphereMat;

	Core::Manager::Control_Manager* C_Manager;

	bool m_SetUniforms[2];
	float m_Rotation;
public:
	Test3D();
	~Test3D();

	void onInit(Core::Rendering::Renderer3D& renderer, Core::Rendering::Scene& scene) override;

	void onTick() override;
	void onUpdate() override;
	bool onEvent() override;
};