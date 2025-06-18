#pragma once

#include "HathoraDemoMainMenu.h"
#include "BeamFlow/K2BeamNode_Operation.h"

#include "K2BeamNode_Subsystem_HathoraDemo.generated.h"

//   ___                       _   _                 
//  / _ \ _ __   ___ _ __ __ _| |_(_) ___  _ __  ___ 
// | | | | '_ \ / _ \ '__/ _` | __| |/ _ \| '_ \/ __|
// | |_| | |_) |  __/ | | (_| | |_| | (_) | | | \__ \
//  \___/| .__/ \___|_|  \__,_|\__|_|\___/|_| |_|___/
//       |_|     

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_UpdateHathoraPings"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_UpdateHathoraPings : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Hathora Demo - Update Hathora Pings"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UHathoraDemoMainMenu, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UHathoraDemoMainMenu, UpdateHathoraPingsOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UHathoraDemoMainMenu::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE
