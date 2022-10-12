#include "BeamableCoreEditor.h"

#include "CustomPinFactory.h"

#define LOCTEXT_NAMESPACE "FBeamableCoreEditorModule"

void FBeamableCoreEditorModule::StartupModule()
{
	// create your factory and shared pointer to it.
	TSharedPtr<FCustomPinFactory> Factory = MakeShareable(new FCustomPinFactory());
	// and now register it.
	FEdGraphUtilities::RegisterVisualPinFactory(Factory);
}

void FBeamableCoreEditorModule::ShutdownModule()
{
    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FBeamableCoreEditorModule, BeamableCoreEditor)