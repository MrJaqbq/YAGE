#ifndef YAGE_RTTI_MANAGER_H
#define YAGE_RTTI_MANAGER_H

#include <RTTI/RTTIRegister.h>
#include "Core/IManager.h"

namespace RTTI
{
    class Manager : public Core::IManager
    {
        MANAGER(Manager);

    public:
        explicit Manager(Core::Engine& engine, Memory::IMemoryBlock& memory);
		virtual ~Manager() = default;

        template <typename T>
        void PushLayer()
        {
            static_assert(std::is_base_of<ILayer, T>::value,
                "RTTI: Can load only ILayer derivatives!");

            auto* instance = YAGE_CREATE_NEW(Memory::GetDefaultBlock<Manager>(), T)();

            RTTI::GetRegister()->LoadLayer(instance);
        }
    };
}

#endif // YAGE_RTTI_MANAGER_H