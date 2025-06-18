#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FBEAMPROJ_HathoraDemoBpModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
