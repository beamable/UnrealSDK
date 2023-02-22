#pragma once

#include "BeamableCoreStyle.h"
#include "SlateBasics.h"
#include "EditorStyleSet.h"


class FBeamableCoreEditorCommands : public TCommands<FBeamableCoreEditorCommands>
{
public:

	FBeamableCoreEditorCommands()
		: TCommands<FBeamableCoreEditorCommands>
		( 
			TEXT("BeamableCoreEditor"), 
			NSLOCTEXT("Contexts", "BeamableCoreEditor", "Beamable Plugin"), 
			NAME_None,
			TEXT("BeamableCore")
		){}

	virtual void RegisterCommands() override;

public:

	TSharedPtr<FUICommandInfo> OpenBeamableWindowCommand;

	TSharedPtr<FUICommandInfo> CreateContentObjectInLocalManifest;
	TSharedPtr<FUICommandInfo> EditContentObjectInLocalManifest;
	
	TSharedPtr<FUICommandInfo> PublishManifest;	
};