#pragma once

#include "BeamableCoreStyle.h"
#include "SlateBasics.h"
#include "EditorStyleSet.h"


class BEAMABLECORERUNTIMEEDITOR_API FBeamableCoreEditorCommands : public TCommands<FBeamableCoreEditorCommands>
{
public:

	FBeamableCoreEditorCommands()
		: TCommands<FBeamableCoreEditorCommands>
		( 
			TEXT("BeamableCoreEditor"), 
			NSLOCTEXT("Contexts", "BeamableCoreEditor", "Beamable Plugin"), 
			NAME_None,
			FBeamableCoreStyle::Get().GetStyleSetName()
		){}

	virtual void RegisterCommands() override;

public:

	TSharedPtr<FUICommandInfo> OpenBeamableWindowCommand;

	TSharedPtr<FUICommandInfo> CreateContentObjectInLocalManifest;
	TSharedPtr<FUICommandInfo> EditContentObjectInLocalManifest;
	
	TSharedPtr<FUICommandInfo> PublishManifest;
	TSharedPtr<FUICommandInfo> DownloadManifest;
};