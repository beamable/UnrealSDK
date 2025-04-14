// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamFlow/K2BeamNode_GetLocalState.h"
#include "BeamFlow/K2BeamNode_Operation.h"
#include "Subsystems/Friends/BeamFriendsSubsystem.h"
#include "K2BeamNode_Operation_Friend.generated.h"

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_TryGetUserFriendState"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_Operation_TryGetUserFriendState : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Beam - Operation - Friends - GetUserFriendState");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, GetSelf);
	}

	virtual FName GetFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, TryGetUserFriendState);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchPlayerFriendState"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchPlayerFriendState : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Beam - Operation - Friend - FetchPlayerFriendState");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, FetchPlayerFriendStateOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE


#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchFriendsState"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchFriendsState : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Beam - Operation - Friend - FetchFriendsState");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, FetchFriendsStateOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchFriendPresenceStatus"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchFriendPresenceStatus : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Beam - Operation - Friend - FetchFriendPresenceStatus");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, FetchFriendPresenceStatusOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_SendFriendInvite"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_SendFriendInvite : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Beam - Operation - Friend - SendFriendInvite");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, SendFriendInviteOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_AcceptFriendInvite"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_AcceptFriendInvite : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Beam - Operation - Friend - AcceptFriendInvite");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, AcceptFriendInviteOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE


#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_DeclineFriendInvite"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_DeclineFriendInvite : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Beam - Operation - Friend - DeclineFriendInvite");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, DeclineFriendInviteOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE


#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_BlockPlayer"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_BlockPlayer : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Beam - Operation - Friend - BlockPlayer");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, BlockPlayerOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_UnblockPlayer"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_UnblockPlayer : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Beam - Operation - Friend - UnblockPlayer");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, UnblockPlayerOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendsSubsystem::StaticClass(); }
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
		return LOCTEXT("Title", "Beam - Operation - Friend - RemoveFriend");
	}

	virtual FName GetSubsystemSelfFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, GetSelf);
	}

	virtual FName GetOperationFunctionName() const override
	{
		return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, RemoveFriendOperation);
	}

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE
