#ifndef YAGE_RTTI_FIELD_INFO_H
#define YAGE_RTTI_FIELD_INFO_H

#include "Defines.h"

namespace RTTI
{
    class TypeInfo;

    class FieldInfo : public MetaInfo
    {
        friend class ClassInfo;

    protected:
        FieldInfo(Utils::CompileString& name, TypeInfo* type)
            : MetaInfo(name), BaseType(type)
        { }

        TypeInfo*         BaseType;
        ValueType::TYPE   ValueType;
        AccessType::TYPE  AccessType;
    };
}

#endif // !YAGE_RTTI_FIELD_INFO_H