// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamableCoreStyle.h"


class BEAMABLEUNREALEDITOR_API FBeamableUtilityCommands : public TCommands<FBeamableUtilityCommands>
{
public:
	FBeamableUtilityCommands()
		: TCommands<FBeamableUtilityCommands>
		(
			TEXT("BeamableUtilityEditor"),
			NSLOCTEXT("Contexts", "BeamableUtilityEditor", "Beamable Plugin Utility"),
			NAME_None,
			FBeamableCoreStyle::Get().GetStyleSetName()
		)
	{
	}

	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> SyncProj;
};
