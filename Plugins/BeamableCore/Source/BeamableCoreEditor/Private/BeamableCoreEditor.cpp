#include "BeamableCoreEditor.h"

#include "BeamableCoreGraphWidgetFactory.h"

#define LOCTEXT_NAMESPACE "FBeamableCoreEditorModule"

void FBeamableCoreEditorModule::StartupModule()
{
	// create your factories and shared pointer to them.
	TSharedPtr<FBeamableCorePinFactory> PinFactory = MakeShareable(new FBeamableCorePinFactory());
	TSharedPtr<FBeamableCoreGraphNodeFactory> NodeFactory = MakeShareable(new FBeamableCoreGraphNodeFactory());

	// and now register them.
	FEdGraphUtilities::RegisterVisualPinFactory(PinFactory);
	FEdGraphUtilities::RegisterVisualNodeFactory(NodeFactory);
}

void FBeamableCoreEditorModule::ShutdownModule()
{
    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FBeamableCoreEditorModule, BeamableCoreEditor)