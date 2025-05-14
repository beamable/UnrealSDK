// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Leaderboard/BeamLeaderboardsSubsystem.h"

FBeamRankEntry::FBeamRankEntry(const FOptionalRankEntry& Rankgt): Rank(0), Score(0)
{
	if (!Rankgt.IsSet)
	{
		return;
	}

	FBeamRankEntry(Rankgt.Val);
}

FBeamRankEntry::FBeamRankEntry(URankEntry* RankEntry)
{
	Rank = RankEntry->Rank;

	if (RankEntry->Score.IsSet)
	{
		Score = RankEntry->Score.Val;
	}
	Stats = {};
	if (RankEntry->Stats.IsSet)
	{
		for (const auto RankEntryStat : RankEntry->Stats.Val)
		{
			Stats.Add(RankEntryStat->Name, RankEntryStat->Value);
		}
	}
	PlayerGamerTag = FBeamGamerTag(RankEntry->Gt);
}

void UBeamLeaderboardsSubsystem::InitializeWhenUnrealReady_Implementation(FBeamOperationHandle& ResultOp)
{
	LeaderboardsApi = GEngine->GetEngineSubsystem<UBeamLeaderboardsApi>();

	Super::InitializeWhenUnrealReady_Implementation(ResultOp);
}

void UBeamLeaderboardsSubsystem::OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser, const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp)
{
	if (!IsRunningDedicatedServer())
	{
		ResultOp = Runtime->RequestTrackerSystem->CPP_BeginSuccessfulOperation({}, GetName(), {}, {});
	}
	else
	{
		ResultOp = Runtime->RequestTrackerSystem->CPP_BeginSuccessfulOperation({}, GetName(), {}, {});
	}
}

void UBeamLeaderboardsSubsystem::OnUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser, FBeamOperationHandle& ResultOp)
{
	Super::OnUserSignedOut_Implementation(UserSlot, Reason, BeamRealmUser, ResultOp);
}

bool UBeamLeaderboardsSubsystem::TryGetLeaderboard(FString LeaderboardId, FBeamLeaderboardView& LeaderboardView)
{
	if (!LeaderboardsCache.Contains(LeaderboardId))
	{
		return false;
	}

	LeaderboardView = LeaderboardsCache[LeaderboardId];
	return true;
}

bool UBeamLeaderboardsSubsystem::TryGetPlayerRankEntry(FString LeaderboardId, FBeamGamerTag PlayerGamerTag, FBeamRankEntry& PlayerRankEntry)
{
	//Return last player if false
	if (!LeaderboardsCache.Contains(LeaderboardId))
	{
		return false;
	}

	// Get all the leaderboards that the player are in.

	if (LeaderboardsCache[LeaderboardId].FocusedEntries.Contains(PlayerGamerTag))
	{
		int32 RankIndex = LeaderboardsCache[LeaderboardId].FocusedEntries[PlayerGamerTag];
		PlayerRankEntry = LeaderboardsCache[LeaderboardId].RankEntries[RankIndex];
		return true;
	}

	PlayerRankEntry = FBeamRankEntry();
	PlayerRankEntry.Rank = LeaderboardsCache[LeaderboardId].BoardSize + 1;

	return false;
}

bool UBeamLeaderboardsSubsystem::TryGetAllRankEntries(FString LeaderboardId, TArray<FBeamRankEntry>& RankEntries)
{
	if (!LeaderboardsCache.Contains(LeaderboardId))
	{
		return false;
	}

	RankEntries = LeaderboardsCache[LeaderboardId].RankEntries;

	return true;
}

void UBeamLeaderboardsSubsystem::TryGetRankEntriesRange(FString LeaderboardId, int From, int Max, TArray<FBeamRankEntry>& RankEntries)
{
	if (!LeaderboardsCache.Contains(LeaderboardId))
	{
		return;
	}
	auto LeaderboardView = LeaderboardsCache[LeaderboardId];

	int32 LastRank = From + Max;
	int32 StartRank = From;

	RankEntries.Reset();
	for (int32 i = 0; i < LeaderboardView.RankEntries.Num(); i++)
	{
		if (LeaderboardView.RankEntries[i].Rank > LastRank)
		{
			break;
		}
		if (LeaderboardView.RankEntries[i].Rank >= StartRank)
		{
			RankEntries.Add(LeaderboardView.RankEntries[i]);
		}
	}
}

bool UBeamLeaderboardsSubsystem::TryGetFocusRankEntries(FString LeaderboardId, int StartEntriesSize, FBeamGamerTag FocusEntryGamerTag, int LastEntriesSize, TArray<FBeamRankEntry>& StartEntries,
                                                        FBeamRankEntry& FocusEntry,
                                                        TArray<FBeamRankEntry>& LastEntries)
{
	if (!LeaderboardsCache.Contains(LeaderboardId))
	{
		return false;
	}

	auto LeaderboardView = LeaderboardsCache[LeaderboardId];

	StartEntries.Reset();
	LastEntries.Reset();

	for (int32 i = 0; i < LeaderboardView.RankEntries.Num(); i++)
	{
		FBeamRankEntry Item = LeaderboardView.RankEntries[i];
		if (i < StartEntriesSize)
		{
			StartEntries.Add(Item);
		}

		if (FocusEntryGamerTag == Item.PlayerGamerTag)
		{
			FocusEntry = Item;
		}

		if (i > LeaderboardView.RankEntries.Num() - LastEntriesSize)
		{
			LastEntries.Add(Item);
		}
	}
	return true;
}

bool UBeamLeaderboardsSubsystem::TryReleaseRankEntries(FString LeaderboardId, int From, int Max)
{
	if (!LeaderboardsCache.Contains(LeaderboardId))
	{
		return false;
	}

	auto LeaderboardView = &LeaderboardsCache[LeaderboardId];
	LeaderboardView->RankEntries.RemoveAll([From, Max](FBeamRankEntry RankEntry)
	{
		return RankEntry.Rank >= From && RankEntry.Rank < From + Max;
	});

	return false;
}

bool UBeamLeaderboardsSubsystem::TryGetPlayerPageInfo(FString LeaderboardId, FBeamGamerTag PlayerGamerTag, int PageSize, FBeamRankEntry& PlayerRankEntry, int& PlayerPage)
{
	if (!LeaderboardsCache.Contains(LeaderboardId))
	{
		return false;
	}

	auto LeaderboardView = LeaderboardsCache[LeaderboardId];

	if (!LeaderboardView.FocusedEntries.Contains(PlayerGamerTag))
	{
		return false;
	}
	int32 RankIndex = LeaderboardView.FocusedEntries[PlayerGamerTag];

	PlayerRankEntry = LeaderboardsCache[LeaderboardId].RankEntries[RankIndex];

	PlayerPage = GetLeaderboardPage(PageSize, PlayerRankEntry.Rank);

	return true;
}

bool UBeamLeaderboardsSubsystem::TryGetPageRankEntries(FString LeaderboardId, int PageSize, int Page, TArray<FBeamRankEntry>& RankEntries, int& CachedEntriesCount, int& TotalPages)
{
	if (!LeaderboardsCache.Contains(LeaderboardId))
	{
		return false;
	}
	auto LeaderboardView = LeaderboardsCache[LeaderboardId];

	long StartRank;
	long EndRank;
	GetLeaderboardPageRange(PageSize, Page, StartRank, EndRank);

	RankEntries.Reset();

	for (auto RankEntry : LeaderboardView.RankEntries)
	{
		if (RankEntry.Rank >= StartRank && RankEntry.Rank <= EndRank)
		{
			RankEntries.Add(RankEntry);
		}
	}

	CachedEntriesCount = LeaderboardView.RankEntries.Num();

	TotalPages = std::ceil(LeaderboardView.BoardSize / PageSize);

	return true;
}

bool UBeamLeaderboardsSubsystem::TryReleasePageRankEntries(FString LeaderboardId, int PageSize, int Page)
{
	if (!LeaderboardsCache.Contains(LeaderboardId))
	{
		return false;
	}

	auto LeaderboardView = &LeaderboardsCache[LeaderboardId];

	long StartRank;
	long LastRank;
	GetLeaderboardPageRange(PageSize, PageSize, StartRank, LastRank);

	LeaderboardView->RankEntries.RemoveAll([StartRank, LastRank](FBeamRankEntry RankEntry)
	{
		return RankEntry.Rank >= StartRank && RankEntry.Rank <= LastRank;
	});

	return true;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::LeaderboardAssignmentOperation(FUserSlot UserSlot, FString LeaderboardId, bool Join, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchAssignment(UserSlot, LeaderboardId, Join, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::CPP_LeaderboardAssignmentOperation(FUserSlot UserSlot, FString LeaderboardId, bool Join, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchAssignment(UserSlot, LeaderboardId, Join, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::FetchLeaderboardOperation(FUserSlot UserSlot, FString LeaderboardId, int From, int Max, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchLeaderboard(UserSlot, LeaderboardId, From, Max, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::CPP_FetchLeaderboardOperation(FUserSlot UserSlot, FString LeaderboardId, int From, int Max, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchLeaderboard(UserSlot, LeaderboardId, From, Max, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::FetchLeaderboardPageOperation(FUserSlot UserSlot, FString LeaderboardId, int PageSize, int StartPage, int LastPage, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchLeaderboard(UserSlot, LeaderboardId, PageSize, StartPage, LastPage, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::CPP_FetchLeaderboardPageOperation(FUserSlot UserSlot, FString LeaderboardId, int PageSize, int StartPage, int LastPage, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchLeaderboard(UserSlot, LeaderboardId, PageSize, StartPage, LastPage, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::FetchLeaderboardFocusPlayerOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag FocusPlayer, int Max, FOptionalBeamGamerTag Outlier,
                                                                                      FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchLeaderboard(UserSlot, LeaderboardId, FocusPlayer, Max, Outlier, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::CPP_FetchLeaderboardFocusPlayerOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag FocusPlayer, int Max, FOptionalBeamGamerTag Outlier,
                                                                                          FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchLeaderboard(UserSlot, LeaderboardId, FocusPlayer, Max, Outlier, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::FetchAssignedLeaderboardOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, int From, int Max,
                                                                                   FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchAssignedLeaderboard(UserSlot, LeaderboardId, PlayerGamerTag, From, Max, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::CPP_FetchAssignedLeaderboardOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, int From, int Max,
                                                                                       FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchAssignedLeaderboard(UserSlot, LeaderboardId, PlayerGamerTag, From, Max, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::FetchAssignedLeaderboardFocusPlayerOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, FBeamGamerTag FocusPlayer, int Max,
                                                                                              FOptionalBeamGamerTag Outlier, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchAssignedLeaderboard(UserSlot, LeaderboardId, FocusPlayer, Max, Outlier, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::CPP_FetchAssignedLeaderboardFocusPlayerOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, FBeamGamerTag FocusPlayer, int Max,
                                                                                                  FOptionalBeamGamerTag Outlier, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchAssignedLeaderboard(UserSlot, LeaderboardId, FocusPlayer, Max, Outlier, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::FetchPlayerLeaderboardsOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchPlayerLeaderboards(UserSlot, PlayerGamerTag, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::CPP_FetchPlayerLeaderboardsOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchPlayerLeaderboards(UserSlot, PlayerGamerTag, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::FetchPlayerRankOperation(FUserSlot UserSlot, FString LeaderboardId, TArray<FBeamGamerTag> PlayersGamerTag, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchPlayerRank(UserSlot, LeaderboardId, PlayersGamerTag, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::CPP_FetchPlayerRankOperation(FUserSlot UserSlot, FString LeaderboardId, TArray<FBeamGamerTag> PlayersGamerTag, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchPlayerRank(UserSlot, LeaderboardId, PlayersGamerTag, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::FetchFriendsRanksOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchFriendsRanks(UserSlot, LeaderboardId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::CPP_FetchFriendsRanksOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchFriendsRanks(UserSlot, LeaderboardId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::UpdateLeaderboardScoreOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, TMap<FString, FString> Stats,
                                                                                 FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	UpdateLeaderboardScore(UserSlot, LeaderboardId, PlayerGamerTag, Score, Stats, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::CPP_UpdateLeaderboardScoreOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, TMap<FString, FString> Stats,
                                                                                     FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	UpdateLeaderboardScore(UserSlot, LeaderboardId, PlayerGamerTag, Score, Stats, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::IncrementLeaderboardScoreOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, TMap<FString, FString> Stats,
                                                                                    FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	IncrementLeaderboardScore(UserSlot, LeaderboardId, PlayerGamerTag, Score, Stats, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::CPP_IncrementLeaderboardScoreOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, TMap<FString, FString> Stats,
                                                                                        FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	IncrementLeaderboardScore(UserSlot, LeaderboardId, PlayerGamerTag, Score, Stats, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::FreezeLeaderboardOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FreezeLeaderboard(UserSlot, LeaderboardId, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::CPP_FreezeLeaderboardOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FreezeLeaderboard(UserSlot, LeaderboardId, Handle);
	return Handle;
}


void UBeamLeaderboardsSubsystem::FetchAssignment(FUserSlot UserSlot, FString LeaderboardId, bool Join, FBeamOperationHandle Op)
{
	auto Handle = FOnBasicLeaderboardsGetAssignmentFullResponse::CreateLambda([this, Op](const FBasicLeaderboardsGetAssignmentFullResponse& Response)
	{
		if (Response.State == RS_Retrying) return;

		if (Response.State == RS_Success)
		{
			FString InKey = GetAssignmentLeaderboardKey(Response.SuccessData->PlayerId, Response.SuccessData->LeaderboardId);
			if (!AssignmentLeaderboardCache.Contains(InKey))
			{
				AssignmentLeaderboardCache.Add(InKey, "");
			}
			Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
			return;
		}

		if (Response.State == RS_Error)
		{
			Runtime->RequestTrackerSystem->TriggerOperationError(Op, Response.ErrorData.message);
			return;
		}

		if (Response.State == RS_Cancelled)
		{
			Runtime->RequestTrackerSystem->TriggerOperationCancelled(Op, Response.ErrorData.message);
			return;
		}
	});

	auto Request = UBasicLeaderboardsGetAssignmentRequest::Make(LeaderboardId, FOptionalBool(Join), this, {});

	FBeamRequestContext Ctx;

	LeaderboardsApi->CPP_BasicLeaderboardsGetAssignment(UserSlot, Request, Handle, Ctx, Op, this);
}


void UBeamLeaderboardsSubsystem::FetchLeaderboard(FUserSlot UserSlot, FString LeaderboardId, int From, int Max, FBeamOperationHandle Op)
{
	auto Handle = FOnGetViewFullResponse::CreateLambda([this, Op](const FGetViewFullResponse& Response)
	{
		if (Response.State == RS_Retrying) return;

		if (Response.State == RS_Success)
		{
			auto LeaderboardView = GetLeaderboardView(Response.SuccessData->Lb);

			UpdateLeaderboardCache(LeaderboardView);

			Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
			return;
		}

		if (Response.State == RS_Error)
		{
			Runtime->RequestTrackerSystem->TriggerOperationError(Op, Response.ErrorData.message);
			return;
		}

		if (Response.State == RS_Cancelled)
		{
			Runtime->RequestTrackerSystem->TriggerOperationCancelled(Op, Response.ErrorData.message);
			return;
		}
	});

	auto Request = UGetViewRequest::Make(LeaderboardId, FOptionalInt32(Max), FOptionalInt64(), FOptionalBool(false), FOptionalInt32(From), FOptionalInt64(), FOptionalBool(false), this, {});

	FBeamRequestContext Ctx;

	LeaderboardsApi->CPP_GetView(UserSlot, Request, Handle, Ctx, Op, this);
}

void UBeamLeaderboardsSubsystem::FetchLeaderboard(FUserSlot UserSlot, FString LeaderboardId, int PageSize, int StartPage, int LastPage, FBeamOperationHandle Op)
{
	long StartPageStartRank;
	long StartPageLastRank;
	GetLeaderboardPageRange(PageSize, StartPage, StartPageStartRank, StartPageLastRank);

	long LastPageStartRank;
	long LastPageLastRank;
	GetLeaderboardPageRange(PageSize, LastPage, LastPageStartRank, LastPageLastRank);

	FetchLeaderboard(UserSlot, LeaderboardId, StartPageStartRank, LastPageLastRank - StartPageStartRank, Op);
}

void UBeamLeaderboardsSubsystem::FetchLeaderboard(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag FocusPlayer, int Max, FOptionalBeamGamerTag Outlier, FBeamOperationHandle Op)
{
	auto Handle = FOnGetViewFullResponse::CreateLambda([this, Op, FocusPlayer, LeaderboardId](const FGetViewFullResponse& Response)
	{
		if (Response.State == RS_Retrying) return;

		if (Response.State == RS_Success)
		{
			auto LeaderboardView = GetLeaderboardView(Response.SuccessData->Lb);

			UpdateLeaderboardCache(LeaderboardView);

			UpdatePlayerLeaderboardCache(LeaderboardView, FocusPlayer);

			Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
			return;
		}

		if (Response.State == RS_Error)
		{
			Runtime->RequestTrackerSystem->TriggerOperationError(Op, Response.ErrorData.message);
			return;
		}

		if (Response.State == RS_Cancelled)
		{
			Runtime->RequestTrackerSystem->TriggerOperationCancelled(Op, Response.ErrorData.message);
			return;
		}
	});

	FOptionalInt64 OutlierLong = Outlier.IsSet ? FOptionalInt64(Outlier.Val.AsLong) : FOptionalInt64();

	auto Request = UGetViewRequest::Make(LeaderboardId, FOptionalInt32(Max), FOptionalInt64(FocusPlayer.AsLong), FOptionalBool(false), FOptionalInt32(), OutlierLong, FOptionalBool(false), this, {});

	FBeamRequestContext Ctx;

	LeaderboardsApi->CPP_GetView(UserSlot, Request, Handle, Ctx, Op, this);
}

void UBeamLeaderboardsSubsystem::FetchAssignedLeaderboard(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, int From, int Max, FBeamOperationHandle Op)
{
	// Check if have any assigned leaderboard if don't so we assign one to this player and join then return the assigned leaderbaord
	if (!AssignmentLeaderboardCache.Contains(GetAssignmentLeaderboardKey(PlayerGamerTag, LeaderboardId)))
	{
		auto Handle = FOnBasicLeaderboardsGetAssignmentFullResponse::CreateLambda([this, UserSlot, LeaderboardId, From, Max, Op](const FBasicLeaderboardsGetAssignmentFullResponse& Response)
		{
			if (Response.State == RS_Retrying) return;

			if (Response.State == RS_Success)
			{
				FetchLeaderboard(UserSlot, LeaderboardId, From, Max, Op);
				return;
			}

			if (Response.State == RS_Error)
			{
				Runtime->RequestTrackerSystem->TriggerOperationError(Op, Response.ErrorData.message);
				return;
			}

			if (Response.State == RS_Cancelled)
			{
				Runtime->RequestTrackerSystem->TriggerOperationCancelled(Op, Response.ErrorData.message);
				return;
			}
		});

		auto Request = UBasicLeaderboardsGetAssignmentRequest::Make(LeaderboardId, FOptionalBool(true), this, {});

		FBeamRequestContext Ctx;

		LeaderboardsApi->CPP_BasicLeaderboardsGetAssignment(UserSlot, Request, Handle, Ctx, Op, this);
	}
	else
	{
		FetchLeaderboard(UserSlot, LeaderboardId, From, Max, Op);
	}
}

void UBeamLeaderboardsSubsystem::FetchAssignedLeaderboard(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag FocusPlayer, int Max, FOptionalBeamGamerTag Outlier,
                                                          FBeamOperationHandle Op)
{
	if (!AssignmentLeaderboardCache.Contains(GetAssignmentLeaderboardKey(FocusPlayer, LeaderboardId)))
	{
		auto Handle = FOnBasicLeaderboardsGetAssignmentFullResponse::CreateLambda([this, UserSlot, LeaderboardId, FocusPlayer, Max, Outlier, Op](const FBasicLeaderboardsGetAssignmentFullResponse& Response)
		{
			if (Response.State == RS_Retrying) return;

			if (Response.State == RS_Success)
			{
				FetchLeaderboard(UserSlot, LeaderboardId, FocusPlayer, Max, Outlier, Op);
				return;
			}

			if (Response.State == RS_Error)
			{
				Runtime->RequestTrackerSystem->TriggerOperationError(Op, Response.ErrorData.message);
				return;
			}

			if (Response.State == RS_Cancelled)
			{
				Runtime->RequestTrackerSystem->TriggerOperationCancelled(Op, Response.ErrorData.message);
				return;
			}
		});

		auto Request = UBasicLeaderboardsGetAssignmentRequest::Make(LeaderboardId, FOptionalBool(true), this, {});

		FBeamRequestContext Ctx;

		LeaderboardsApi->CPP_BasicLeaderboardsGetAssignment(UserSlot, Request, Handle, Ctx, Op, this);
	}
	else
	{
		FetchLeaderboard(UserSlot, LeaderboardId, FocusPlayer, Max, Outlier, Op);
	}
}

void UBeamLeaderboardsSubsystem::FetchPlayerLeaderboards(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag, FBeamOperationHandle Op)
{
	auto Handle = FOnGetPlayerFullResponse::CreateLambda([this, Op, PlayerGamerTag](const FGetPlayerFullResponse& Response)
	{
		if (Response.State == RS_Retrying) return;

		if (Response.State == RS_Success)
		{
			for (auto LeaderBoardView : Response.SuccessData->Lbs)
			{
				FBeamLeaderboardView BeamLeaderboardView = GetLeaderboardView(LeaderBoardView);

				UpdateLeaderboardCache(BeamLeaderboardView);

				UpdatePlayerLeaderboardCache(BeamLeaderboardView, PlayerGamerTag);
			}

			Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
			return;
		}

		if (Response.State == RS_Error)
		{
			Runtime->RequestTrackerSystem->TriggerOperationError(Op, Response.ErrorData.message);
			return;
		}

		if (Response.State == RS_Cancelled)
		{
			Runtime->RequestTrackerSystem->TriggerOperationCancelled(Op, Response.ErrorData.message);
			return;
		}
	});

	auto Request = UGetPlayerRequest::Make(PlayerGamerTag.AsLong, this, {});

	FBeamRequestContext Ctx;

	LeaderboardsApi->CPP_GetPlayer(UserSlot, Request, Handle, Ctx, Op, this);
}

void UBeamLeaderboardsSubsystem::FetchPlayerRank(FUserSlot UserSlot, FString LeaderboardId, TArray<FBeamGamerTag> PlayersGamerTag, FBeamOperationHandle Op)
{
	auto Handle = FOnGetRanksFullResponse::CreateLambda([this, Op, PlayersGamerTag](const FGetRanksFullResponse& Response)
	{
		if (Response.State == RS_Retrying) return;

		if (Response.State == RS_Success)
		{
			FBeamLeaderboardView LeaderboardView = GetLeaderboardView(Response.SuccessData->Lb);
			UpdateLeaderboardCache(LeaderboardView);

			for (auto PlayerGamerTag : PlayersGamerTag)
			{
				UpdatePlayerLeaderboardCache(LeaderboardView, PlayerGamerTag);
			}

			Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
			return;
		}

		if (Response.State == RS_Error)
		{
			Runtime->RequestTrackerSystem->TriggerOperationError(Op, Response.ErrorData.message);
			return;
		}

		if (Response.State == RS_Cancelled)
		{
			Runtime->RequestTrackerSystem->TriggerOperationCancelled(Op, Response.ErrorData.message);
			return;
		}
	});

	FString PlayerIds = "";

	for (auto GamerTag : PlayersGamerTag)
	{
		PlayerIds += GamerTag.AsString + ",";
	}

	PlayerIds = PlayerIds.LeftChop(1);

	auto Request = UGetRanksRequest::Make(LeaderboardId, PlayerIds, this, {});

	FBeamRequestContext Ctx;

	LeaderboardsApi->CPP_GetRanks(UserSlot, Request, Handle, Ctx, Op, this);
}

void UBeamLeaderboardsSubsystem::FetchFriendsRanks(FUserSlot UserSlot, FString LeaderboardId, FBeamOperationHandle Op)
{
	auto Handle = FOnObjectLeaderboardsGetFriendsByObjectIdFullResponse::CreateLambda([this, Op](const FObjectLeaderboardsGetFriendsByObjectIdFullResponse& Response)
	{
		if (Response.State == RS_Retrying) return;

		if (Response.State == RS_Success)
		{
			UpdateLeaderboardCache(GetLeaderboardView(Response.SuccessData->Lb));

			Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
			return;
		}

		if (Response.State == RS_Error)
		{
			Runtime->RequestTrackerSystem->TriggerOperationError(Op, Response.ErrorData.message);
			return;
		}

		if (Response.State == RS_Cancelled)
		{
			Runtime->RequestTrackerSystem->TriggerOperationCancelled(Op, Response.ErrorData.message);
			return;
		}
	});

	auto Request = UObjectLeaderboardsGetFriendsByObjectIdRequest::Make(LeaderboardId, this, {});

	FBeamRequestContext Ctx;

	LeaderboardsApi->CPP_GetFriends(UserSlot, Request, Handle, Ctx, Op, this);
}

void UBeamLeaderboardsSubsystem::UpdateLeaderboardScore(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, TMap<FString, FString> Stats, FBeamOperationHandle Op)
{
	auto Handle = FOnPutEntryFullResponse::CreateLambda([this, Op, UserSlot, LeaderboardId, PlayerGamerTag](const FPutEntryFullResponse& Response)
	{
		if (Response.State == RS_Retrying) return;

		if (Response.State == RS_Success)
		{
			FetchPlayerRank(UserSlot, LeaderboardId, {PlayerGamerTag}, Op);

			return;
		}

		if (Response.State == RS_Error)
		{
			Runtime->RequestTrackerSystem->TriggerOperationError(Op, Response.ErrorData.message);
			return;
		}

		if (Response.State == RS_Cancelled)
		{
			Runtime->RequestTrackerSystem->TriggerOperationCancelled(Op, Response.ErrorData.message);
			return;
		}
	});

	auto Request = UPutEntryRequest::Make(LeaderboardId, Score, PlayerGamerTag.AsLong, FOptionalBool(false), FOptionalDouble(), FOptionalDouble(), FOptionalMapOfString(Stats), this, {});

	FBeamRequestContext Ctx;

	LeaderboardsApi->CPP_PutEntry(UserSlot, Request, Handle, Ctx, Op, this);
}

void UBeamLeaderboardsSubsystem::IncrementLeaderboardScore(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, TMap<FString, FString> Stats, FBeamOperationHandle Op)
{
	auto Handle = FOnPutEntryFullResponse::CreateLambda([this, Op, UserSlot, LeaderboardId, PlayerGamerTag](const FPutEntryFullResponse& Response)
	{
		if (Response.State == RS_Retrying) return;

		if (Response.State == RS_Success)
		{
			FetchPlayerRank(UserSlot, LeaderboardId, {PlayerGamerTag}, Op);

			return;
		}

		if (Response.State == RS_Error)
		{
			Runtime->RequestTrackerSystem->TriggerOperationError(Op, Response.ErrorData.message);
			return;
		}

		if (Response.State == RS_Cancelled)
		{
			Runtime->RequestTrackerSystem->TriggerOperationCancelled(Op, Response.ErrorData.message);
			return;
		}
	});

	auto Request = UPutEntryRequest::Make(LeaderboardId, Score, PlayerGamerTag.AsLong, FOptionalBool(true), FOptionalDouble(), FOptionalDouble(), FOptionalMapOfString(Stats), this, {});

	FBeamRequestContext Ctx;

	LeaderboardsApi->CPP_PutEntry(UserSlot, Request, Handle, Ctx, Op, this);
}

void UBeamLeaderboardsSubsystem::FreezeLeaderboard(FUserSlot UserSlot, FString LeaderboardId, FBeamOperationHandle Op)
{
	auto Handle = FOnPutFreezeFullResponse::CreateLambda([this, Op](const FPutFreezeFullResponse& Response)
	{
		if (Response.State == RS_Retrying) return;

		if (Response.State == RS_Success)
		{
			Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
			return;
		}

		if (Response.State == RS_Error)
		{
			Runtime->RequestTrackerSystem->TriggerOperationError(Op, Response.ErrorData.message);
			return;
		}

		if (Response.State == RS_Cancelled)
		{
			Runtime->RequestTrackerSystem->TriggerOperationCancelled(Op, Response.ErrorData.message);
			return;
		}
	});

	auto Request = UPutFreezeRequest::Make(LeaderboardId, this, {});

	FBeamRequestContext Ctx;

	LeaderboardsApi->CPP_PutFreeze(UserSlot, Request, Handle, Ctx, Op, this);
}

long UBeamLeaderboardsSubsystem::GetLeaderboardPage(int PageSize, long Rank)
{
	return std::floor((Rank - 1) / static_cast<double>(PageSize)) + 1;
}

void UBeamLeaderboardsSubsystem::GetLeaderboardPageRange(int PageSize, long Page, long& StartPageRank, long& LastPageRank)
{
	// Removing the possibility of passing a number lower than 1
	Page = std::max(Page, static_cast<long>(1));

	StartPageRank = (PageSize * (Page - 1)) + 1;

	LastPageRank = PageSize * Page;
}

FBeamLeaderboardView UBeamLeaderboardsSubsystem::GetLeaderboardView(ULeaderBoardView* LeaderBoard)
{
	FBeamLeaderboardView LeaderboardView = {};

	LeaderboardView.BoardSize = LeaderBoard->BoardSize;
	LeaderboardView.PlayerRankEntry = FBeamRankEntry(LeaderBoard->Rankgt);
	LeaderboardView.LeaderboardId = LeaderBoard->LbId;

	LeaderboardView.RankEntries = {};
	for (auto RankEntry : LeaderBoard->Rankings)
	{
		LeaderboardView.RankEntries.Add(FBeamRankEntry(RankEntry));
	}

	return LeaderboardView;
}

FString UBeamLeaderboardsSubsystem::GetAssignmentLeaderboardKey(FBeamGamerTag PlayerGamerTag, FString LeaderboardId)
{
	return PlayerGamerTag.AsString + ":" + LeaderboardId;
}

void UBeamLeaderboardsSubsystem::UpdateLeaderboardCache(FBeamLeaderboardView LeaderboardView)
{
	if (!LeaderboardsCache.Contains(LeaderboardView.LeaderboardId))
	{
		LeaderboardsCache.Add(LeaderboardView.LeaderboardId, LeaderboardView);
	}
	else
	{
		LeaderboardsCache[LeaderboardView.LeaderboardId] = LeaderboardView;
	}
}

void UBeamLeaderboardsSubsystem::UpdatePlayerLeaderboardCache(FBeamLeaderboardView LeaderboardView, const FBeamGamerTag& PlayerGamerTag)
{
	FString LeaderboardId = LeaderboardView.LeaderboardId;
	int32 RankIndex = 0;

	for (auto RankEntry : LeaderboardView.RankEntries)
	{
		if (LeaderboardsCache[LeaderboardId].FocusedEntries.Contains(RankEntry.PlayerGamerTag))
		{
			LeaderboardsCache[LeaderboardId].FocusedEntries[RankEntry.PlayerGamerTag] = RankIndex;
		}
		else if (RankEntry.PlayerGamerTag == PlayerGamerTag)
		{
			LeaderboardsCache[LeaderboardId].FocusedEntries.Add(RankEntry.PlayerGamerTag, RankIndex);
		}
		RankIndex++;
	}
}
