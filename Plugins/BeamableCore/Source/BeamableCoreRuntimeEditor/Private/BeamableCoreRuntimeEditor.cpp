#include "BeamableCoreRuntimeEditor.h"

#define LOCTEXT_NAMESPACE "FBeamableCoreRuntimeEditorModule"

void FBeamableCoreRuntimeEditorModule::StartupModule()
{
	PIEAuthorizer = UBeamPIEModularFeature();
	IModularFeatures::Get().RegisterModularFeature(UBeamPIEModularFeature::GetModularFeatureName(), &PIEAuthorizer);
}

void FBeamableCoreRuntimeEditorModule::ShutdownModule()
{
	IModularFeatures::Get().UnregisterModularFeature(UBeamPIEModularFeature::GetModularFeatureName(), &PIEAuthorizer);
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FBeamableCoreRuntimeEditorModule, BeamableCoreRuntimeEditor)