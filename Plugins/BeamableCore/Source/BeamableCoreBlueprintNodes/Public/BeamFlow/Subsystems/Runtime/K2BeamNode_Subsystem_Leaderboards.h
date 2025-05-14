// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamFlow/K2BeamNode_GetLocalState.h"
#include "BeamFlow/K2BeamNode_Operation.h"
#include "BeamFlow/K2BeamNode_GetLocalStateForeach.h"
#include "Subsystems/Leaderboard/BeamLeaderboardsSubsystem.h"

#include "K2BeamNode_Subsystem_Leaderboards.generated.h"


//  _                    _      ____  _        _       
// | |    ___   ___ __ _| |    / ___|| |_ __ _| |_ ___ 
// | |   / _ \ / __/ _` | |    \___ \| __/ _` | __/ _ \
// | |__| (_) | (_| (_| | |     ___) | || (_| | ||  __/
// |_____\___/ \___\__,_|_|    |____/ \__\__,_|\__\___|

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetLeaderboard"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetLeaderboard : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Leaderboards - TryGetLeaderboard"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, TryGetLeaderboard); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLeaderboardsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetPlayerRankEntry"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetPlayerRankEntry : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Leaderboards - TryGetPlayerRankEntry"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, TryGetPlayerRankEntry); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLeaderboardsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalStateForeach_TryGetAllRankEntries"

UCLASS(meta=(BeamGetLocalStateForeach))
class UK2BeamNode_GetLocalStateForeach_TryGetAllRankEntries : public UK2BeamNode_GetLocalStateForeach
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Leaderboards - TryGetAllRankEntries"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, TryGetAllRankEntries); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLeaderboardsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalStateForeach_TryGetRankEntriesRange"

UCLASS(meta=(BeamGetLocalStateForeach))
class UK2BeamNode_GetLocalStateForeach_TryGetRankEntriesRange : public UK2BeamNode_GetLocalStateForeach
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Leaderboards - TryGetRankEntriesRange"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, TryGetRankEntriesRange); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLeaderboardsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetFocusRankEntries"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetFocusRankEntries : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Leaderboards - TryGetFocusRankEntries"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, TryGetFocusRankEntries); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLeaderboardsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryReleaseRankEntries"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryReleaseRankEntries : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Leaderboards - TryReleaseRankEntries"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, TryReleaseRankEntries); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLeaderboardsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryGetPlayerPageInfo"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryGetPlayerPageInfo : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Leaderboards - TryGetPlayerPageInfo"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, TryGetPlayerPageInfo); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLeaderboardsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalStateForeach_TryGetPageRankEntries"

UCLASS(meta=(BeamGetLocalStateForeach))
class UK2BeamNode_GetLocalStateForeach_TryGetPageRankEntries : public UK2BeamNode_GetLocalStateForeach
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Leaderboards - TryGetPageRankEntries"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, TryGetPageRankEntries); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLeaderboardsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE


#define LOCTEXT_NAMESPACE "K2BeamNode_GetLocalState_TryReleasePageRankEntries"

UCLASS(meta=(BeamGetLocalState))
class UK2BeamNode_GetLocalState_TryReleasePageRankEntries : public UK2BeamNode_GetLocalState
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Local State - Leaderboards - TryReleasePageRankEntries"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, GetSelf); }

	virtual FName GetFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, TryReleasePageRankEntries); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLeaderboardsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

//   ___                       _   _                 
//  / _ \ _ __   ___ _ __ __ _| |_(_) ___  _ __  ___ 
// | | | | '_ \ / _ \ '__/ _` | __| |/ _ \| '_ \/ __|
// | |_| | |_) |  __/ | | (_| | |_| | (_) | | | \__ \
//  \___/| .__/ \___|_|  \__,_|\__|_|\___/|_| |_|___/
//       |_|     

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchAssignmentOperation"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchAssignmentOperation : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Leaderboards - FetchAssignmentOperation"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, LeaderboardAssignmentOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLeaderboardsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchLeaderboardOperation"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchLeaderboardOperation : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Leaderboards - FetchLeaderboardOperation"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, FetchLeaderboardOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLeaderboardsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchLeaderboardPageOperation"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchLeaderboardPageOperation : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Leaderboards - FetchLeaderboardPageOperation"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, FetchLeaderboardPageOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLeaderboardsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchLeaderboardFocusPlayerOperation"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchLeaderboardFocusPlayerOperation : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Leaderboards - FetchLeaderboardFocusPlayerOperation"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, FetchLeaderboardFocusPlayerOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLeaderboardsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchAssignedLeaderboardOperation"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchAssignedLeaderboardOperation : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Leaderboards - FetchAssignedLeaderboardOperation"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, FetchAssignedLeaderboardOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLeaderboardsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchAssignedLeaderboardFocusPlayerOperation"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchAssignedLeaderboardFocusPlayerOperation : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Leaderboards - FetchAssignedLeaderboardFocusPlayerOperation"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, FetchAssignedLeaderboardFocusPlayerOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLeaderboardsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchPlayerLeaderboardsOperation"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchPlayerLeaderboardsOperation : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Leaderboards - FetchPlayerLeaderboardsOperation"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, FetchPlayerLeaderboardsOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLeaderboardsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchPlayerRankOperation"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchPlayerRankOperation : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Leaderboards - FetchPlayerRankOperation"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, FetchPlayerRankOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLeaderboardsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FetchFriendsRanksOperation"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FetchFriendsRanksOperation : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Leaderboards - FetchFriendsRanksOperation"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, FetchFriendsRanksOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLeaderboardsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_UpdateLeaderboardScoreOperation"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_UpdateLeaderboardScoreOperation : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Leaderboards - UpdateLeaderboardScoreOperation"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, UpdateLeaderboardScoreOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLeaderboardsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_IncrementLeaderboardScoreOperation"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_IncrementLeaderboardScoreOperation : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Leaderboards - IncrementLeaderboardScoreOperation"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, IncrementLeaderboardScoreOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLeaderboardsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE

#define LOCTEXT_NAMESPACE "K2BeamNode_Operation_FreezeLeaderboardOperation"

UCLASS(meta=(BeamFlowNode))
class UK2BeamNode_Operation_FreezeLeaderboardOperation : public UK2BeamNode_Operation
{
	GENERATED_BODY()

	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return LOCTEXT("Title", "Operation - Leaderboards - FreezeLeaderboardOperation"); }

	virtual FName GetSubsystemSelfFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, GetSelf); }

	virtual FName GetOperationFunctionName() const override { return GET_FUNCTION_NAME_CHECKED(UBeamLeaderboardsSubsystem, FreezeLeaderboardOperation); }

	virtual UClass* GetRuntimeSubsystemClass() const override { return UBeamLeaderboardsSubsystem::StaticClass(); }
};

#undef LOCTEXT_NAMESPACE
