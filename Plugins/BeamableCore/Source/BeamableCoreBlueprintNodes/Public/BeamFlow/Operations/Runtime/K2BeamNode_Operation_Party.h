// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamFlow/K2BeamNode_Operation.h"
#include "Subsystems/Party/BeamPartySubsystem.h"
#include "K2BeamNode_Operation_Party.generated.h"


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

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_UpdateParty"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_UpdateParty : public UK2BeamNode_Operation
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
		return GET_FUNCTION_NAME_CHECKED(UBeamPartySubsystem, UpdatePartyOperation);
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
