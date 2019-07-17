#pragma once
//
// Core Header File
//


 // APPLICATION
#include <App/Application.h>
#include <Init/Window.h>

// AUDIO
#include <Audio/Sound.h>
#include <Managers/Sound_Manager.h>

// DEBUG UI
#include <Debug/DebugLayer.h>
#include <Debug/DebugMenu.h>
#include <Debug/Items/DebugMenuAction.h>
#include <Debug/Items/DebugMenuItem.h>

// ENTITY
#include <Rendering/Entity/Entity.h>
#include <Rendering/Entity/Component/Component.h>
#include <Rendering/Entity/Component/MeshComponent.h>
#include <Rendering/Entity/Component/ModelComponent.h>
#include <Rendering/Entity/Component/TransformComponent.h>

//RENDERER
#include <Rendering/Renderer/Renderer2D.h>
#include <Rendering/Renderer/Renderer3D.h>
#include <Rendering/Renderer/Batch2DRenderer.h>
#include <Rendering/Renderer/ForwardRenderer.h>
#include <Rendering/Renderer/Models/IRenderable.h>
#include <Rendering/Renderer/Renderable2D.h>
#include <Rendering/Renderer/RenderCommand.h>

// BUFFER
#include <Rendering/Renderer/Buffers/Buffer.h>
#include <Rendering/Renderer/Buffers/IndexBuffer.h>
#include <Rendering/Renderer/Buffers/VertexArray.h>
#include <Rendering/Renderer/Buffers/FrameBuffer.h>
#include <Rendering/Renderer/Buffers/BufferLayout.h>

// FONT CONSOLE AND DEBUG
#include <Rendering/Renderer/Font/Font.h>
#include <Managers/Font_Manager.h>
#include <Rendering/Renderer/Models/Label.h>
#include <Utils/Log.h>

// MESH
#include <Rendering/Renderer/Models/Sprite.h>
#include <Rendering/Renderer/Models/Mesh.h>
#include <Rendering/Renderer/Models/Model.h>
#include <Managers/Mesh_Manager.h>

// MATERIAL
#include <Rendering/Renderer/Texture/Mask.h>
#include <Rendering/Renderer/Texture/Texture.h>
#include <Rendering/Material/Material.h>
#include <Managers/Texture_Manager.h>

// SCENE AND CONTROL
#include <Rendering/Scene/Scene.h>
#include <Rendering/Camera/Camera.h>
#include <Rendering/Camera/FPS_Camera.h>
#include <Managers/Control_Manager.h>
#include <Managers/Scene_Manager.h>

// LAYER AND GROUPS
#include <Rendering/Renderer/Layers/Layer.h>
#include <Rendering/Renderer/Layers/Layer2D.h>
#include <Rendering/Renderer/Layers/Layer3D.h>
#include <Rendering/Renderer/Groups/Group.h>
#include <Managers/Layer_Manager.h>

// POST FX
#include <Rendering/Renderer/PostFX/PostFX.h>
#include <Rendering/Renderer/PostFX/PostFXPass.h>

// SHADER
#include <Rendering/Renderer/Shader/Shader.h>
#include <Rendering/Renderer/Shader/ShaderUniform.h>
#include <Managers/Shader_Manager.h>

// MATHS
#include <Utils/Maths/AABB.h>
#include <Utils/Maths/mat4.h>
#include <Utils/Maths/maths_func.h>
#include <Utils/Maths/Quaternion.h>
#include <Utils/Maths/Rectangle.h>
#include <Utils/Maths/tvec2.h>
#include <Utils/Maths/vec2.h>
#include <Utils/Maths/vec3.h>
#include <Utils/Maths/vec4.h>

// STRING
#include <Utils/String.h>
#include <Utils/StringUtils.h>

// UTILS
#include <Utils/Fileutils.h>
#include <Utils/ImageLoader.h>
#include <Utils/Timer.h>