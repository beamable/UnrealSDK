// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamFlow/K2BeamNode_EventRegister.h"
#include "BeamFlow/K2BeamNode_EventUnregister.h"
#include "BeamFlow/K2BeamNode_EventUnregisterAll.h"
#include "BeamFlow/K2BeamNode_GetLocalState.h"
#include "BeamFlow/K2BeamNode_GetLocalStateForeach.h"
#include "BeamFlow/K2BeamNode_Operation.h"
#include "Subsystems/Friends/BeamFriendsSubsystem.h"
#include "K2BeamNode_Subsystem_Friend.generated.h"

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


#define LOCTEXT_NAMESPACE "K2BeamNode_EventUnregisterAll_FriendsSubsystem"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_EventUnregisterAll_FriendsSubsystem : public UK2BeamNode_EventUnregisterAll
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Friends - Unbind All Events"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, GetSelf); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendsSubsystem::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_EventUnregister_FriendsSubsystem"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_EventUnregister_FriendsSubsystem : public UK2BeamNode_EventUnregister
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Friends - Unbind"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, GetSelf); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendsSubsystem::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_EventRegister_FriendsSubsystem"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_EventRegister_FriendsSubsystem : public UK2BeamNode_EventRegister
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Events - Friends - Bind"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, GetSelf); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendsSubsystem::StaticClass(); }
};
#undef LOCTEXT_NAMESPACE


//  _                    _      ____  _        _       
// | |    ___   ___ __ _| |    / ___|| |_ __ _| |_ ___ 
// | |   / _ \ / __/ _` | |    \___ \| __/ _` | __/ _ \
// | |__| (_) | (_| (_| | |     ___) | || (_| | ||  __/
// |_____\___/ \___\__,_|_|    |____/ \__\__,_|\__\___|

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetFriendPresenceState"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetFriendPresenceState : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Friends - TryGetFriendPresenceState"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, TryGetFriendPresenceState); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetPlayerFriendState"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetPlayerFriendState : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Friends - TryGetPlayerFriendState"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, TryGetPlayerFriendState); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetUserFriendState"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetUserFriendState : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Friends - TryGetUserFriendState"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, TryGetUserFriendState); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalStateForeach_TryGetUserFriendsInfo"

UCLASS(meta=(BeamGetLocalStateForeach))
class UK2BeamNode_GetLocalStateForeach_TryGetUserFriendsInfo : public UK2BeamNode_GetLocalStateForeach
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Friends - TryGetUserFriendsInfo"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, TryGetUserFriendsInfo); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalStateForeach_TryGetUserBlockedFriends"

UCLASS(meta=(BeamGetLocalStateForeach))
class UK2BeamNode_GetLocalStateForeach_TryGetUserBlockedFriends : public UK2BeamNode_GetLocalStateForeach
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Friends - TryGetUserBlockedFriends"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, TryGetUserBlockedFriends); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalStateForeach_TryGetUserReceivedInvites"

UCLASS(meta=(BeamGetLocalStateForeach))
class UK2BeamNode_GetLocalStateForeach_TryGetUserReceivedInvites : public UK2BeamNode_GetLocalStateForeach
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Friends - TryGetUserReceivedInvites"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, TryGetUserReceivedInvites); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalStateForeach_TryGetUserSentInvites"

UCLASS(meta=(BeamGetLocalStateForeach))
class UK2BeamNode_GetLocalStateForeach_TryGetUserSentInvites : public UK2BeamNode_GetLocalStateForeach
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Friends - TryGetUserSentInvites"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, TryGetUserSentInvites); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalStateForeach_TryGetPlayerReceivedInvites"

UCLASS(meta=(BeamGetLocalStateForeach))
class UK2BeamNode_GetLocalStateForeach_TryGetPlayerReceivedInvites : public UK2BeamNode_GetLocalStateForeach
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Friends - TryGetPlayerReceivedInvites"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, TryGetPlayerReceivedInvites); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalStateForeach_TryGetPlayerSentInvites"

UCLASS(meta=(BeamGetLocalStateForeach))
class UK2BeamNode_GetLocalStateForeach_TryGetPlayerSentInvites : public UK2BeamNode_GetLocalStateForeach
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Friends - TryGetPlayerSentInvites"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, TryGetPlayerSentInvites); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalStateForeach_TryGetPlayerFriendsInfo"

UCLASS(meta=(BeamGetLocalStateForeach))
class UK2BeamNode_GetLocalStateForeach_TryGetPlayerFriendsInfo : public UK2BeamNode_GetLocalStateForeach
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Friends - TryGetPlayerFriendsInfo"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, TryGetPlayerFriendsInfo); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalStateForeach_TryGetPlayerBlockedFriends"

UCLASS(meta=(BeamGetLocalStateForeach))
class UK2BeamNode_GetLocalStateForeach_TryGetPlayerBlockedFriends : public UK2BeamNode_GetLocalStateForeach
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Friends - TryGetPlayerBlockedFriends"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamFriendsSubsystem, TryGetPlayerBlockedFriends); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamFriendsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

//   ___                       _   _                 
//  / _ \ _ __   ___ _ __ __ _| |_(_) ___  _ __  ___ 
// | | | | '_ \ / _ \ '__/ _` | __| |/ _ \| '_ \/ __|
// | |_| | |_) |  __/ | | (_| | |_| | (_) | | | \__ \
//  \___/| .__/ \___|_|  \__,_|\__|_|\___/|_| |_|___/
//       |_|     

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchPlayerFriendState"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchPlayerFriendState : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override
	{
		return LOCTEXT("Title", "Operation - Friend - FetchPlayerFriendState");
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
		return LOCTEXT("Title", "Operation - Friend - FetchFriendsState");
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
		return LOCTEXT("Title", "Operation - Friend - FetchFriendPresenceStatus");
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
		return LOCTEXT("Title", "Operation - Friend - SendFriendInvite");
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
		return LOCTEXT("Title", "Operation - Friend - AcceptFriendInvite");
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
		return LOCTEXT("Title", "Operation - Friend - DeclineFriendInvite");
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
		return LOCTEXT("Title", "Operation - Friend - BlockPlayer");
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
		return LOCTEXT("Title", "Operation - Friend - UnblockPlayer");
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
		return LOCTEXT("Title", "Operation - Friend - RemoveFriend");
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
