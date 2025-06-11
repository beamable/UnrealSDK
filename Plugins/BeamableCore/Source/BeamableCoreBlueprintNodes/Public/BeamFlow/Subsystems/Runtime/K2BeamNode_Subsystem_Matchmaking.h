// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamFlow/K2BeamNode_EventRegister.h"
#include "BeamFlow/K2BeamNode_EventUnregister.h"
#include "BeamFlow/K2BeamNode_EventUnregisterAll.h"
#include "BeamFlow/K2BeamNode_GetLocalState.h"
#include "BeamFlow/K2BeamNode_Operation.h"
#include "Subsystems/Matchmaking/BeamMatchmakingSubsystem.h"

#include "K2BeamNode_Subsystem_Matchmaking.generated.h"

/***
 *      ______                          _         
 *     |  ____|                        | |        
 *     | |__    __   __   ___   _ __   | |_   ___ 
 *     |  __|   \ \ / /  / _ \ | '_ \  | __| / __|
 *     | |____   \ V /  |  __/ | | | | | |_  \__ \
 *     |______|   \_/    \___| |_| |_|  \__| |___/
 *                                                
 *                                                
 */


#define LOCTEXT_NAMESPACE "K2BeamNode_EventRegister_MatchmakingSubsystem"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_EventRegister_MatchmakingSubsystem : public UK2BeamNode_EventRegister
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Matchmaking - Bind"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingSubsystem, GetSelf); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamMatchmakingSubsystem::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_EventUnregisterAll_MatchmakingSubsystem"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_EventUnregisterAll_MatchmakingSubsystem : public UK2BeamNode_EventUnregisterAll
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Matchmaking - Unbind All Events"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingSubsystem, GetSelf); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamMatchmakingSubsystem::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_EventUnregister_MatchmakingSubsystem"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_EventUnregister_MatchmakingSubsystem : public UK2BeamNode_EventUnregister
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Matchmaking - Unbind"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingSubsystem, GetSelf); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamMatchmakingSubsystem::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

//  _                    _      ____  _        _       
// | |    ___   ___ __ _| |    / ___|| |_ __ _| |_ ___ 
// | |   / _ \ / __/ _` | |    \___ \| __/ _` | __/ _ \
// | |__| (_) | (_| (_| | |     ___) | || (_| | ||  __/
// |_____\___/ \___\__,_|_|    |____/ \__\__,_|\__\___|

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_IsUserSlotInQueue"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_IsUserSlotInQueue : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Matchmaking - IsUserSlotInQueue"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingSubsystem, IsUserSlotInQueue); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamMatchmakingSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetTicketId"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetTicketId : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Matchmaking - TryGetTicketId"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingSubsystem, TryGetTicketId); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamMatchmakingSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetTicket"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetTicket : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Matchmaking - TryGetTicket"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingSubsystem, TryGetTicket); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamMatchmakingSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

//   ___                       _   _                 
//  / _ \ _ __   ___ _ __ __ _| |_(_) ___  _ __  ___ 
// | | | | '_ \ / _ \ '__/ _` | __| |/ _ \| '_ \/ __|
// | |_| | |_) |  __/ | | (_| | |_| | (_) | | | \__ \
//  \___/| .__/ \___|_|  \__,_|\__|_|\___/|_| |_|___/
//       |_|     

#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_TryJoinQueue"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation_TryJoinQueue : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Matchmaking - Join Queue"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingSubsystem, TryJoinQueueOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamMatchmakingSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_TryJoinQueueWithTags"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation_TryJoinQueueWithTags : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Matchmaking - Join Queue with Tags"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingSubsystem, TryJoinQueueWithTagsOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamMatchmakingSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "UK2BeamNode_Operation_TryLeaveQueue"

UCLASS(meta=(BeamFlowNode))
class BEAMABLECOREBLUEPRINTNODES_API UK2BeamNode_Operation_TryLeaveQueue : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Matchmaking - Leave Queue"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamMatchmakingSubsystem, TryLeaveQueueOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamMatchmakingSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE
