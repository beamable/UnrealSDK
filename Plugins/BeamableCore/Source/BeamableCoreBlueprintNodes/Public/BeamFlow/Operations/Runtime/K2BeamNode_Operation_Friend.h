// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamFlow/K2BeamNode_Operation.h"
#include "Subsystems/Friends/BeamFriendSubsystem.h"
#include "K2BeamNode_Operation_Friend.generated.h"


#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchPlayerFriendState"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchPlayerFriendState : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - FetchPlayerFriendState");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendSubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendSubsystem, FetchPlayerFriendStateOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE


#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchFriendsState"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchFriendsState : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - FetchFriendsState");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendSubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendSubsystem, FetchFriendsStateOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchFriendPresenceStatus"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchFriendPresenceStatus : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - FetchFriendPresenceStatus");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendSubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendSubsystem, FetchFriendPresenceStatusOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_SendFriendInvite"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_SendFriendInvite : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - SendFriendInvite");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendSubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendSubsystem, SendFriendInviteOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_AcceptFriendInvite"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_AcceptFriendInvite : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - AcceptFriendInvite");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendSubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendSubsystem, AcceptFriendInviteOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE


#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_DeclineFriendInvite"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_DeclineFriendInvite : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - DeclineFriendInvite");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendSubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendSubsystem, DeclineFriendInviteOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE


#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_BlockPlayer"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_BlockPlayer : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - BlockPlayer");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendSubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendSubsystem, BlockPlayerOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_UnblockPlayer"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_UnblockPlayer : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - UnblockPlayer");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendSubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendSubsystem, UnblockPlayerOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_RemoveFriend"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_RemoveFriend : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Party - RemoveFriend");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendSubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendSubsystem, RemoveFriendOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE
