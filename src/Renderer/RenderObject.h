#pragma once
#include "Material.h"
#include "Mesh.h"
namespace Lava {
	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
	struct RenderObject {
		Lava::Mesh m_mesh;
		Material* m_material;
	};
}