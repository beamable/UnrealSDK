#pragma once

#include "BeamFlow/K2BeamNode_Operation.h"
#include "Subsystems/PIE/BeamPIE.h"

#include "K2BeamNode_Subsystem_BeamPIE.generated.h"

//  _                    _      ____  _        _       
// | |    ___   ___ __ _| |    / ___|| |_ __ _| |_ ___ 
// | |   / _ \ / __/ _` | |    \___ \| __/ _` | __/ _ \
// | |__| (_) | (_| (_| | |     ___) | || (_| | ||  __/
// |_____\___/ \___\__,_|_|    |____/ \__\__,_|\__\___|


#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_RequiresGameServerOrchestratorSetup"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_RequiresGameServerOrchestratorSetup : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - PIE - Require Orchestrator Setup"); }

	virtual FText GetKeywords() const override { return FText::FromString(Super::GetKeywords().ToString() + " PIE"); }

	virtual FString GetServiceName() const override { return "PIE"; };

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPIE, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPIE, PreparePIE_Advanced_RequiresGameServerOrchestratorSetup); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPIE::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_EasyEnableBeamPIE"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_EasyEnableBeamPIE : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - PIE - Easy Enable - Gameplay"); }

	virtual FText GetKeywords() const override { return FText::FromString(Super::GetKeywords().ToString() + " PIE"); }

	virtual FString GetServiceName() const override { return "PIE"; };

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPIE, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPIE, EasyEnableBeamPIE_Gameplay); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPIE::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE


//   ___                       _   _                 
//  / _ \ _ __   ___ _ __ __ _| |_(_) ___  _ __  ___ 
// | | | | '_ \ / _ \ '__/ _` | __| |/ _ \| '_ \/ __|
// | |_| | |_) |  __/ | | (_| | |_| | (_) | | | \__ \
//  \___/| .__/ \___|_|  \__,_|\__|_|\___/|_| |_|___/
//       |_|     


#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_PrepareThenTravelToPIE"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_PrepareThenTravelToPIE : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - PIE - Prepare then Travel"); }

	virtual FText GetKeywords() const override { return FText::FromString(Super::GetKeywords().ToString() + " PIE"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPIE, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPIE, PrepareThenTravelToPIEOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPIE::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_BeamInitPIE"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_BeamPreparePIE : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - PIE - Prepare"); }

	virtual FText GetKeywords() const override { return FText::FromString(Super::GetKeywords().ToString() + " PIE"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPIE, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPIE, PreparePIEOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPIE::StaticClass(); }

protected:
	virtual TArray<FName> GetOperationEventIds(EBeamOperationEventType Type) const override
	{
		TArray<FName> Ids = Super::GetOperationEventIds(Type);

		switch (Type)
		{
		case OET_SUCCESS:
			Ids.Add(UBeamPIE::GetOperationEventID_PIE_ClientLoggedIn());
			return Ids;
		}

		return Ids;
	};

	virtual TArray<FString> GetOperationEventIdTooltips(EBeamOperationEventType Type) const override
	{
		TArray<FString> Ids = Super::GetOperationEventIdTooltips(Type);

		switch (Type)
		{
		case OET_SUCCESS:
			Ids.Add(TEXT("Triggered when the player is logged in."));
			return Ids;
		}
		return Ids;
	}
};

#undef LOCTEXT_NAMESPACE
