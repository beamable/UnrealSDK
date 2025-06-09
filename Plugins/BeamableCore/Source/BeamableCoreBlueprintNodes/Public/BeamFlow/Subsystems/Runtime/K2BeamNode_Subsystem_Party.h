// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamFlow/K2BeamNode_EventRegister.h"
#include "BeamFlow/K2BeamNode_EventUnregister.h"
#include "BeamFlow/K2BeamNode_EventUnregisterAll.h"
#include "BeamFlow/K2BeamNode_GetLocalState.h"
#include "BeamFlow/K2BeamNode_GetLocalStateForeach.h"
#include "BeamFlow/K2BeamNode_Operation.h"
#include "Subsystems/Party/BeamPartySubsystem.h"
#include "K2BeamNode_Subsystem_Party.generated.h"

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

#define LOCTEXT_NAMESPACE "K2BeamNode_EventUnregisterAll_PartySubsystem"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_EventUnregisterAll_PartySubsystem : public UK2BeamNode_EventUnregisterAll
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Party - Unbind All Events"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_EventUnregister_PartySubsystem"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_EventUnregister_PartySubsystem : public UK2BeamNode_EventUnregister
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Party - Unbind"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_EventRegister_PartySubsystem"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_EventRegister_PartySubsystem : public UK2BeamNode_EventRegister
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Party - Bind"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

//  _                    _      ____  _        _       
// | |    ___   ___ __ _| |    / ___|| |_ __ _| |_ ___ 
// | |   / _ \ / __/ _` | |    \___ \| __/ _` | __/ _ \
// | |__| (_) | (_| (_| | |     ___) | || (_| | ||  __/
// |_____\___/ \___\__,_|_|    |____/ \__\__,_|\__\___|

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_IsPlayerInAParty"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_IsPlayerInAParty : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Party - IsPlayerInAParty"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, IsPlayerInAParty); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_IsInAParty"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_IsInAParty : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Party - IsInAParty"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, IsInAParty); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_IsThePartyLeader"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_IsThePartyLeader : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Party - IsThePartyLeader"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, IsThePartyLeader); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetUserPartyState"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetUserPartyState : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Party - TryGetUserPartyState"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, TryGetUserPartyState); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalStateForeach_GetUserPartyPlayerStates"

UCLASS(meta=(BeamGetLocalStateForeach))
class UK2BeamNode_GetLocalStateForeach_GetUserPartyPlayerStates : public UK2BeamNode_GetLocalStateForeach
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Party - GetUserPartyPlayerStates"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetUserPartyPlayerStates); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetPlayerPartyState"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetPlayerPartyState : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Party - TryGetPlayerPartyState"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, TryGetPlayerPartyState); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetPartyState"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetPartyState : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Party - TryGetPartyState"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, TryGetPartyState); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalStateForeach_TryGetUserInvitesState"

UCLASS(meta=(BeamGetLocalStateForeach))
class UK2BeamNode_GetLocalStateForeach_TryGetUserInvitesState : public UK2BeamNode_GetLocalStateForeach
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Party - TryGetUserInvitesState"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, TryGetUserInvitesState); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

//   ___                       _   _                 
//  / _ \ _ __   ___ _ __ __ _| |_(_) ___  _ __  ___ 
// | | | | '_ \ / _ \ '__/ _` | __| |/ _ \| '_ \/ __|
// | |_| | |_) |  __/ | | (_| | |_| | (_) | | | \__ \
//  \___/| .__/ \___|_|  \__,_|\__|_|\___/|_| |_|___/
//       |_|     

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_CreateParty"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_CreateParty : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - CreateParty");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, CreatePartyOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_JoinParty"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_JoinParty : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - JoinParty");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, JoinPartyOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE


#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_JoinPlayerParty"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_JoinPlayerParty : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - JoinPlayerParty");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, JoinPlayerPartyOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE


#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_LeaveParty"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_LeaveParty : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - LeaveParty");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, LeavePartyOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_InvitePlayer"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_InvitePlayer : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - InvitePlayer");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, InvitePlayerToPartyOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE


#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_InvitePlayerToMyParty"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_InvitePlayerToMyParty : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - InvitePlayerToMyParty");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, InvitePlayerToMyPartyOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_DeclinePlayerInvite"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_DeclinePlayerInvite : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - DeclinePlayerInvite");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, DeclinePlayerPartyInviteOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE


#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_DeclinePartyInvite"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_DeclinePartyInvite : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - DeclinePartyInvite");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, DeclinePartyInviteOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchPartyState"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchPartyState : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - FetchPartyState");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, FetchPartyStateOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchPlayerPartyState"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchPlayerPartyState : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - FetchPlayerPartyState");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, FetchPlayerPartyStateOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchPartyInvites"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchPartyInvites : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - FetchPartyInvites");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, FetchPartyInvitesOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_UpdatePartyMeta"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_UpdateParty : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - Update Party Meta");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, UpdatePartyMetaOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_UpdateMyPartyMeta"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_UpdateMyPartyMeta : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - UpdateParty");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, UpdateMyPartyMetaOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_PartyKickPlayer"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_PartyKickPlayer : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - KickPlayer");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, KickPlayerOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_KickPlayerFromMyParty"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_KickPlayerFromMyParty : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - Kick Player From My Party");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, KickPlayerFromMyPartyOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_PromotePlayerToLeader"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_PromotePlayerToLeader : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - PromotePlayerToLeader");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, PromotePlayerToLeaderOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_PromotePlayerAsMyPartyLeader"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_PromotePlayerAsMyPartyLeader : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - Promote Player As My Party Leader");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, PromotePlayerToMyPartyLeaderOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_CancelSentPartyInvite"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_CancelSentPartyInvite : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - CancelSentPartyInvite");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, CancelSentPartyInviteOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_CancelPlayerPartyInvite"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_CancelPlayerPartyInvite : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - CancelPlayerPartyInvite");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, CancelPlayerPartyInviteOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamPartySubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE
