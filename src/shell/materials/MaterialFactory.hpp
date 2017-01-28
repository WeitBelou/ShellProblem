#pragma once
#include "MaterialsGroup.hpp"
#include "src/shell/util/JsonUtil.hpp"

namespace MaterialFactory
{
MaterialsGroup create_materials(const json &materials_properties);
}


