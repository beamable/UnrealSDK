#pragma once

#include "CoreMinimal.h"

class BEAMABLECOREEDITOR_API FBeamableCoreEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
