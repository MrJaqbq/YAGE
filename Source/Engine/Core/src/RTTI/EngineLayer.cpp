#include "EngineLayer.h"
#include "Core/RTTI/RTTIEngineLoader.h"
#include <Utils/MemoryBlock.h>

namespace RTTI
{
    EngineLayer::EngineLayer(Memory::IMemoryBlock& memory)
        : Classes(memory), Enums(memory)
    {

    }

    EngineLayer::~EngineLayer()
    {
        Unload();
    }

    bool EngineLayer::OnLoad()
    {
        if (_loaded)
            return false;

        // Call generated method
        Meta::Engine::RegisterClasses(*this);

        _loaded = true;

        return true;
    }

    bool EngineLayer::OnUnload()
    {
        _loaded = false;

        Classes.clear();
        Enums.clear();

        return true;
    }

    void EngineLayer::RegisterType(ClassInfo* clazz)
    {
        if (_loaded)
            return;

        Classes.add(clazz);
    }

    void EngineLayer::RegisterType(EnumInfo* enumz)
    {
        if (_loaded)
            return;

        Enums.add(enumz);
    }
}