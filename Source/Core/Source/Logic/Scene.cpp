//
// Created by mrjaqbq on 17.04.16.
//

#include "Scene.h"
#include "../Engine.h"
#include "RenderingSystem.h"

namespace Logic
{
	Scene::Scene(Core::Engine& engine, Memory::IMemoryBlock& memory, const char* name)
		: _memory(memory), Name(name), engine(engine)
	{
		Rendering = YAGE_CREATE_NEW(_memory, RenderingSystem)(engine, _memory);
	}

	Scene::~Scene()
	{
		Memory::Delete(_memory, Rendering);
	}

	void Scene::Draw(const Core::GameTime& time, Gfx::Renderer& renderer)
	{
		// TODO: in update or draw?
		// go through each of components
		// scheme <- mesh -> component
		// so using that we can access batch for scheme & material pair

		// this can be divided into threads
		Rendering->update(time, renderer);

		// what main classes do we have?
		// submesh, material, light, postprocess
		// should postprocess be related to scene?
		// component data is not relevant
		// they all pass what is necessary to material, submesh and uniform data anyway
		// what is important?
		// who knows which data should be collected?
		// shaders know their data
		// meshes know theirs also
		// gather meshes by pass id
		// gather lights
	}

	void Scene::Update(const Core::GameTime&)
	{

	}

	void Scene::Start()
	{

	}

	void Scene::End()
	{

	}
}
