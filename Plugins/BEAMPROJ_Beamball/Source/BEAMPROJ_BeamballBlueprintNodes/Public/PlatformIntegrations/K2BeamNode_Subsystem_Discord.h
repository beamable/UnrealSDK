#pragma once
#include "BeamFlow/K2BeamNode_Operation.h"
#include "BeamFlow/K2BeamNode_GetLocalState.h"
#include "BeamFlow/K2BeamNode_EventRegister.h"
#include "BeamFlow/K2BeamNode_EventUnregister.h"
#include "BeamFlow/K2BeamNode_EventUnregisterAll.h"
#include "BEAMPROJ_Beamball/Public/PlatformIntegrations/BeamableDiscord.h"


#include "K2BeamNode_Subsystem_Discord.generated.h"


//   ___                       _   _
//  / _ \ _ __   ___ _ __ __ _| |_(_) ___  _ __  ___
// | | | | '_ \ / _ \ '__/ _` | __| |/ _ \| '_ \/ __|
// | |_| | |_) |  __/ | | (_| | |_| | (_) | | | \__ \
//  \___/| .__/ \___|_|  \__,_|\__|_|\___/|_| |_|___/
//       |_|


#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_InitializeDiscord"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_InitializeDiscord : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Beamable Discord - Operation - Initialize Discord"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamableDiscord, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamableDiscord, InitializeDiscordOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamableDiscord::StaticClass(); }

	virtual bool IsNodeSafeToIgnore() const override { return false; }
};

#undef LOCTEXT_NAMESPACE


//  ______                          _
// |  ____|                        | |
// | |__    __   __   ___   _ __   | |_   ___
// |  __|   \ \ / /  / _ \ | '_ \  | __| / __|
// | |____   \ V /  |  __/ | | | | | |_  \__ \
// |______|   \_/    \___| |_| |_|  \__| |___/


#define LOCTEXT_NAMESPACE "UK2BeamNode_EventRegister_Discord"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_EventRegister_Discord : public UK2BeamNode_EventRegister
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Discord - Bind"); }

	virtual FString GetServiceName() const override { return "Discord"; };

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamableDiscord, GetSelf); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamableDiscord::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "UK2BeamNode_EventUnregister_Discord"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_EventUnregister_Discord : public UK2BeamNode_EventUnregister
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Discord - Unbind"); }

	virtual FString GetServiceName() const override { return "Discord"; };

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamableDiscord, GetSelf); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamableDiscord::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "UK2BeamNode_EventUnregisterAll_Discord"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_EventUnregisterAll_Discord : public UK2BeamNode_EventUnregisterAll
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Discord - Unbind All Events"); }

	virtual FString GetServiceName() const override { return "Discord"; };

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamableDiscord, GetSelf); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamableDiscord::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE


//  _                    _      ____  _        _
// | |    ___   ___ __ _| |    / ___|| |_ __ _| |_ ___
// | |   / _ \ / __/ _` | |    \___ \| __/ _` | __/ _ \
// | |__| (_) | (_| (_| | |     ___) | || (_| | ||  __/
// |_____\___/ \___\__,_|_|    |____/ \__\__,_|\__\___|


#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetDiscordData"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetDiscordData : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - BeamableDiscord - TryGetDiscordData"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamableDiscord, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamableDiscord, TryGetDiscordData); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamableDiscord::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE


#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetMatchmakingWhitelisted"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetMatchmakingWhitelisted : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - BeamableDiscord - TryGetMatchmakingWhitelisted"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamableDiscord, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamableDiscord, TryGetMatchmakingWhitelisted); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamableDiscord::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE
