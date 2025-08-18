#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "PIE/BeamPIEModularFeature.h"

class FBeamableCoreRuntimeEditorModule : public IModuleInterface
{
public:
    
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    
    UBeamPIEModularFeature PIEAuthorizer;
};
