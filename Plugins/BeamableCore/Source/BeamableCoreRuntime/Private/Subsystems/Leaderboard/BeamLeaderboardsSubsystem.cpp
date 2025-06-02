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
	ResultOp = Runtime->RequestTrackerSystem->CPP_BeginSuccessfulOperation({}, GetName(), {}, {});
}

void UBeamLeaderboardsSubsystem::OnUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason, const FBeamRealmUser& BeamRealmUser, FBeamOperationHandle& ResultOp)
{
	Super::OnUserSignedOut_Implementation(UserSlot, Reason, BeamRealmUser, ResultOp);
}

bool UBeamLeaderboardsSubsystem::TryGetAssignedLeaderboard(FUserSlot UserSlot, FString LeaderboardId, FString& PartitionedLeaderboardId)
{
	FBeamRealmUser RealmUser;
	if (Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
	{
		FString LeaderboardAssignedKey = GetAssignmentLeaderboardKey(RealmUser.GamerTag, LeaderboardId);
		
		if (AssignmentLeaderboardCache.Contains(LeaderboardAssignedKey))
		{
			PartitionedLeaderboardId = AssignmentLeaderboardCache[LeaderboardAssignedKey];
			return true;
		}
	}
	return false;
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
	if (LeaderboardsCache[LeaderboardId].PlayerEntriesCache.Contains(PlayerGamerTag))
	{
		int32 RankIndex = LeaderboardsCache[LeaderboardId].PlayerEntriesCache[PlayerGamerTag];
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
	// Prevent to get a 0 rank instead of 1.
	From = FGenericPlatformMath::Max(1, From);
	auto LeaderboardView = LeaderboardsCache[LeaderboardId];

	int32 LastRank = From + Max;
	int32 StartRank = From;

	RankEntries.Reset();
	for (int32 i = 0; i < LeaderboardView.RankEntries.Num(); i++)
	{
		if (LeaderboardView.RankEntries[i].Rank >= LastRank)
		{
			// As the ranks are sorted all the time it's fetched if the rank is greater than the last rank we can break the loop.
			break;
		}
		if (LeaderboardView.RankEntries[i].Rank >= StartRank)
		{
			RankEntries.Add(LeaderboardView.RankEntries[i]);
		}
	}
}

bool UBeamLeaderboardsSubsystem::TryGetFocusRankEntries(FString LeaderboardId, int StartEntriesSize, FBeamGamerTag FocusEntryGamerTag, int LastEntriesSize, TArray<FBeamRankEntry>& Entries,
                                                        FBeamRankEntry& FocusEntry)
{
	if (!LeaderboardsCache.Contains(LeaderboardId))
	{
		return false;
	}

	auto LeaderboardView = LeaderboardsCache[LeaderboardId];

	Entries.Reset();

	bool FoundFocusEntry = false;


	for (int32 i = 0; i < LeaderboardView.RankEntries.Num(); i++)
	{
		bool IsStartEntry = false;
		FBeamRankEntry Item = LeaderboardView.RankEntries[i];

		if (i < StartEntriesSize && FocusEntryGamerTag != Item.PlayerGamerTag)
		{
			// Adding all the entries below the StartEntriesSize
			Entries.Add(Item);
			IsStartEntry = true;
		}

		if (FocusEntryGamerTag == Item.PlayerGamerTag)
		{
			FocusEntry = Item;
			FoundFocusEntry = true;
			Entries.Add(Item);
		}

		if (i >= LeaderboardView.RankEntries.Num() - LastEntriesSize && FocusEntryGamerTag != Item.PlayerGamerTag && !IsStartEntry)
		{
			// Adding all the entries below the above the Lenght - LastEntriesSize
			Entries.Add(Item);
		}
	}
	// If don't found any focus entry it will return false
	return FoundFocusEntry;
}

bool UBeamLeaderboardsSubsystem::TryReleaseRankEntries(FString LeaderboardId, int From, int Max)
{
	if (!LeaderboardsCache.Contains(LeaderboardId))
	{
		return false;
	}

	auto LeaderboardView = &LeaderboardsCache[LeaderboardId];

	// Remove all the entries in the range.
	LeaderboardView->RankEntries.RemoveAll([From, Max](FBeamRankEntry RankEntry)
	{
		return RankEntry.Rank >= From && RankEntry.Rank < From + Max;
	});

	UpdatePlayerEntriesLeaderboardCache(LeaderboardId);

	return false;
}

void UBeamLeaderboardsSubsystem::TryReleaseAllRankEntries(FString LeaderboardId)
{
	if (!LeaderboardsCache.Contains(LeaderboardId))
	{
		return;
	}

	auto LeaderboardView = &LeaderboardsCache[LeaderboardId];

	LeaderboardView->RankEntries.Reset();

	UpdatePlayerEntriesLeaderboardCache(LeaderboardId);
}

bool UBeamLeaderboardsSubsystem::TryGetPlayerPageInfo(FString LeaderboardId, FBeamGamerTag PlayerGamerTag, int PageSize, FBeamRankEntry& PlayerRankEntry, int& PlayerPage)
{
	if (!LeaderboardsCache.Contains(LeaderboardId))
	{
		return false;
	}

	auto LeaderboardView = LeaderboardsCache[LeaderboardId];

	// Check if the leaderboard view contains the player
	if (!LeaderboardView.PlayerEntriesCache.Contains(PlayerGamerTag))
	{
		return false;
	}

	int32 RankIndex = LeaderboardView.PlayerEntriesCache[PlayerGamerTag];

	PlayerRankEntry = LeaderboardsCache[LeaderboardId].RankEntries[RankIndex];

	PlayerPage = GetLeaderboardPage(PageSize, PlayerRankEntry.Rank);

	return true;
}

bool UBeamLeaderboardsSubsystem::TryGetLeaderboardPageInfo(FString LeaderboardId, int PageSize, int& FirstPageCached, int& LastPageCached, int& TotalPages)
{
	if (!LeaderboardsCache.Contains(LeaderboardId))
	{
		return false;
	}
	auto LeaderboardView = LeaderboardsCache[LeaderboardId];

	TotalPages = FGenericPlatformMath::CeilToInt(static_cast<float>(LeaderboardView.BoardSize) / static_cast<float>(PageSize));

	if (LeaderboardView.RankEntries.Num() > 0)
	{
		FBeamRankEntry _;
		// Get the last cached page from the utility method
		auto LastIndex = LeaderboardView.RankEntries.Num() - 1;
		TryGetPlayerPageInfo(LeaderboardId, LeaderboardView.RankEntries[LastIndex].PlayerGamerTag, PageSize, _, LastPageCached);

		// Get the first cached page from the utility method
		auto FirstIndex = 0;
		TryGetPlayerPageInfo(LeaderboardId, LeaderboardView.RankEntries[FirstIndex].PlayerGamerTag, PageSize, _, FirstPageCached);
	}
	else
	{
		return false;
	}

	return true;
}

bool UBeamLeaderboardsSubsystem::TryGetPageRankEntries(FString LeaderboardId, int PageSize, int Page, TArray<FBeamRankEntry>& RankEntries, int& CachedEntriesCount)
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
	// Find all the entries in the range of the start and the end rank.
	for (auto RankEntry : LeaderboardView.RankEntries)
	{
		if (RankEntry.Rank >= StartRank && RankEntry.Rank <= EndRank)
		{
			RankEntries.Add(RankEntry);
		}
	}

	CachedEntriesCount = LeaderboardView.RankEntries.Num();

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
	GetLeaderboardPageRange(PageSize, Page, StartRank, LastRank);

	// Remove all the entries for a specific page
	LeaderboardView->RankEntries.RemoveAll([StartRank, LastRank](FBeamRankEntry RankEntry)
	{
		return RankEntry.Rank >= StartRank && RankEntry.Rank <= LastRank;
	});


	UpdatePlayerEntriesLeaderboardCache(LeaderboardId);

	return true;
}

bool UBeamLeaderboardsSubsystem::IsLeaderboardPageCached(FString LeaderboardId, int PageSize, int Page)
{
	if (!LeaderboardsCache.Contains(LeaderboardId))
	{
		return false;
	}
	auto LeaderboardView = LeaderboardsCache[LeaderboardId];

	if (LeaderboardView.RankEntries.Num() > 0)
	{
		int FirstPageCached;
		int LastPageCached;
		int TotalPagesCached;
		TryGetLeaderboardPageInfo(LeaderboardId, PageSize, FirstPageCached, LastPageCached, TotalPagesCached);

		int CachedEntriesCount;
		TArray<FBeamRankEntry> RankEntries;
		TryGetPageRankEntries(LeaderboardId, PageSize, Page, RankEntries, CachedEntriesCount);

		int ExpectedEntriesAmount = GetExpectedPageEntriesCount(PageSize, Page, LeaderboardView.BoardSize);

		// To verify if the cache is valid it should be in the range of the cached pages
		// And also have the same amount of entries as the expected for the page
		if (TotalPagesCached > 0 && Page >= FirstPageCached && Page <= LastPageCached && RankEntries.Num() == ExpectedEntriesAmount)
		{
			return true;
		}
	}

	return false;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::FetchAssignedLeaderboardOperation(FUserSlot UserSlot, FString LeaderboardId, bool Join, FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchAssignedLeaderboard(UserSlot, LeaderboardId, Join, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::CPP_FetchAssignedLeaderboardOperation(FUserSlot UserSlot, FString LeaderboardId, bool Join, FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchAssignedLeaderboard(UserSlot, LeaderboardId, Join, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::FetchFocusRankEntriesOperation(FUserSlot UserSlot, FString LeaderboardId, int StartEntriesSize, FBeamGamerTag FocusEntryGamerTag, int LastEntriesSize,
                                                                                FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchFocusRankEntries(UserSlot, LeaderboardId, StartEntriesSize, FocusEntryGamerTag, LastEntriesSize, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::CPP_FetchFocusRankEntriesOperation(FUserSlot UserSlot, FString LeaderboardId, int StartEntriesSize, FBeamGamerTag FocusEntryGamerTag, int LastEntriesSize,
                                                                                    FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchFocusRankEntries(UserSlot, LeaderboardId, StartEntriesSize, FocusEntryGamerTag, LastEntriesSize, Handle);
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

FBeamOperationHandle UBeamLeaderboardsSubsystem::FetchLeaderboardFocusPlayerOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag FocusPlayer, int Diameter, FOptionalBeamGamerTag Outlier,
                                                                                      FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchLeaderboard(UserSlot, LeaderboardId, FocusPlayer, Diameter, Outlier, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::CPP_FetchLeaderboardFocusPlayerOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag FocusPlayer, int Diameter, FOptionalBeamGamerTag Outlier,
                                                                                          FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	FetchLeaderboard(UserSlot, LeaderboardId, FocusPlayer, Diameter, Outlier, Handle);
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

FBeamOperationHandle UBeamLeaderboardsSubsystem::UpdateLeaderboardScoreOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, FOptionalMapOfString Stats,
                                                                                 FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	UpdateLeaderboardScore(UserSlot, LeaderboardId, PlayerGamerTag, Score, Stats, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::CPP_UpdateLeaderboardScoreOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, FOptionalMapOfString Stats,
                                                                                     FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	UpdateLeaderboardScore(UserSlot, LeaderboardId, PlayerGamerTag, Score, Stats, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::IncrementLeaderboardScoreOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, FOptionalMapOfString Stats,
                                                                                    FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	IncrementLeaderboardScore(UserSlot, LeaderboardId, PlayerGamerTag, Score, Stats, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::CPP_IncrementLeaderboardScoreOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, FOptionalMapOfString Stats,
                                                                                        FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	IncrementLeaderboardScore(UserSlot, LeaderboardId, PlayerGamerTag, Score, Stats, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::DecrementLeaderboardScoreOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, FOptionalMapOfString Stats,
                                                                                    FBeamOperationEventHandler OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	DecrementLeaderboardScore(UserSlot, LeaderboardId, PlayerGamerTag, Score, Stats, Handle);
	return Handle;
}

FBeamOperationHandle UBeamLeaderboardsSubsystem::CPP_DecrementLeaderboardScoreOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, FOptionalMapOfString Stats,
                                                                                        FBeamOperationEventHandlerCode OnOperationEvent)
{
	const auto Handle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
	DecrementLeaderboardScore(UserSlot, LeaderboardId, PlayerGamerTag, Score, Stats, Handle);
	return Handle;
}

void UBeamLeaderboardsSubsystem::FetchAssignedLeaderboard(FUserSlot UserSlot, FString LeaderboardId, bool Join, FBeamOperationHandle Op)
{
	if (!IsUserSlotAuthenticated(UserSlot, __FUNCTION__, Op))
	{
		return;
	}
	auto Handle = FOnBasicLeaderboardsGetAssignmentFullResponse::CreateLambda([this, LeaderboardId, Op, UserSlot](const FBasicLeaderboardsGetAssignmentFullResponse& Response)
	{
		if (Response.State == RS_Retrying) return;

		if (Response.State == RS_Success)
		{
			FBeamRealmUser RealmUser;
			if (Runtime->UserSlotSystem->GetUserDataAtSlot(UserSlot, RealmUser, this))
			{
				FString LeaderboardAssignedKey = GetAssignmentLeaderboardKey(RealmUser.GamerTag, LeaderboardId);
				// This maps the player - leaderboard id to a partition leaderboard id.
				if (!AssignmentLeaderboardCache.Contains(LeaderboardAssignedKey))
				{
					AssignmentLeaderboardCache.Add(LeaderboardAssignedKey, Response.SuccessData->LeaderboardId);
				}
				Runtime->RequestTrackerSystem->TriggerOperationSuccess(Op, TEXT(""));
			}
			else
			{
				Runtime->RequestTrackerSystem->TriggerOperationError(Op, TEXT("Couldn't found a authenticated player for the given user slot"));
			}

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
			// Get the leaderboard view from the response
			auto LeaderboardView = GetLeaderboardView(Response.SuccessData->Lb);

			// Update the leaderbaord cache
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

void UBeamLeaderboardsSubsystem::FetchFocusRankEntries(FUserSlot UserSlot, FString LeaderboardId, int StartEntriesSize, FBeamGamerTag FocusEntryGamerTag, int LastEntriesSize, FBeamOperationHandle Op)
{
	auto FetchStartEntriesHandle = Runtime->RequestTrackerSystem->CPP_BeginOperation({UserSlot}, GetName(), FBeamOperationEventHandlerCode::CreateLambda(
		                                                                                 [this, Op, LeaderboardId, StartEntriesSize, UserSlot, LastEntriesSize, FocusEntryGamerTag](FBeamOperationEvent Evt)
		                                                                                 {
			                                                                                 if (Evt.EventType == OET_SUCCESS)
			                                                                                 {
				                                                                                 FBeamLeaderboardView LeaderboardView;
				                                                                                 if (TryGetLeaderboard(LeaderboardId, LeaderboardView))
				                                                                                 {
					                                                                                 auto FetchLastEntriesHandle = Runtime->RequestTrackerSystem->CPP_BeginOperation(
						                                                                                 {UserSlot}, GetName(), FBeamOperationEventHandlerCode::CreateLambda(
							                                                                                 [this, Op, LeaderboardId, StartEntriesSize, UserSlot, FocusEntryGamerTag](FBeamOperationEvent Evt)
							                                                                                 {
								                                                                                 if (Evt.EventType == OET_SUCCESS)
								                                                                                 {
									                                                                                 FetchPlayerRank(UserSlot, LeaderboardId, {FocusEntryGamerTag}, Op);
								                                                                                 }
								                                                                                 else
								                                                                                 {
									                                                                                 Runtime->RequestTrackerSystem->TriggerOperationError(Op, TEXT("Fail to get the target leaderboard."));
								                                                                                 }
							                                                                                 }));
					                                                                                 FetchLeaderboard(UserSlot, LeaderboardId, LeaderboardView.BoardSize - LastEntriesSize, LastEntriesSize,
					                                                                                                  FetchLastEntriesHandle);
				                                                                                 }
				                                                                                 else
				                                                                                 {
					                                                                                 Runtime->RequestTrackerSystem->TriggerOperationError(Op, TEXT("Fail to get the target leaderboard from cache."));
				                                                                                 }
			                                                                                 }
			                                                                                 else
			                                                                                 {
				                                                                                 Runtime->RequestTrackerSystem->TriggerOperationError(Op, TEXT("Fail to get the target leaderboard."));
			                                                                                 }
		                                                                                 }));

	FetchLeaderboard(UserSlot, LeaderboardId, 1, StartEntriesSize, FetchStartEntriesHandle);
}

void UBeamLeaderboardsSubsystem::FetchLeaderboard(FUserSlot UserSlot, FString LeaderboardId, int PageSize, int StartPage, int LastPage, FBeamOperationHandle Op)
{
	// Get the first and the last entry in a specific page (Start Page)
	long StartPageStartRank;
	long StartPageLastRank;
	GetLeaderboardPageRange(PageSize, StartPage, StartPageStartRank, StartPageLastRank);

	// Get the first and the last entry in a specific page (Last Page)
	long LastPageStartRank;
	long LastPageLastRank;
	GetLeaderboardPageRange(PageSize, LastPage, LastPageStartRank, LastPageLastRank);

	// Fetch the leaderboard entries from the first in the start page to then last in the last page.
	FetchLeaderboard(UserSlot, LeaderboardId, StartPageStartRank, LastPageLastRank - (StartPageStartRank - 1), Op);
}

void UBeamLeaderboardsSubsystem::FetchLeaderboard(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag FocusPlayer, int Max, FOptionalBeamGamerTag Outlier, FBeamOperationHandle Op)
{
	auto Handle = FOnGetViewFullResponse::CreateLambda([this, Op, FocusPlayer, LeaderboardId](const FGetViewFullResponse& Response)
	{
		if (Response.State == RS_Retrying) return;

		if (Response.State == RS_Success)
		{
			// Get the leaderboard view from the response
			auto LeaderboardView = GetLeaderboardView(Response.SuccessData->Lb);

			// Update the leaderboard cache
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

	FOptionalInt64 OutlierLong = Outlier.IsSet ? FOptionalInt64(Outlier.Val.AsLong) : FOptionalInt64();

	auto Request = UGetViewRequest::Make(LeaderboardId, FOptionalInt32(Max), FOptionalInt64(FocusPlayer.AsLong), FOptionalBool(false), FOptionalInt32(), OutlierLong, FOptionalBool(false), this, {});

	FBeamRequestContext Ctx;

	LeaderboardsApi->CPP_GetView(UserSlot, Request, Handle, Ctx, Op, this);
}

void UBeamLeaderboardsSubsystem::FetchPlayerRank(FUserSlot UserSlot, FString LeaderboardId, TArray<FBeamGamerTag> PlayersGamerTag, FBeamOperationHandle Op)
{
	auto Handle = FOnGetRanksFullResponse::CreateLambda([this, Op, PlayersGamerTag](const FGetRanksFullResponse& Response)
	{
		if (Response.State == RS_Retrying) return;

		if (Response.State == RS_Success)
		{
			// Create the leaderboard view from the response
			FBeamLeaderboardView LeaderboardView = GetLeaderboardView(Response.SuccessData->Lb);

			// Update the leaderboard cache
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

	FString PlayerIds = "";

	for (auto GamerTag : PlayersGamerTag)
	{
		PlayerIds += GamerTag.AsString + ",";
	}

	// Removing the remaining "," from the last item
	PlayerIds = PlayerIds.LeftChop(1);

	auto Request = UGetRanksRequest::Make(LeaderboardId, PlayerIds, this, {});

	FBeamRequestContext Ctx;

	LeaderboardsApi->CPP_GetRanks(UserSlot, Request, Handle, Ctx, Op, this);
}

void UBeamLeaderboardsSubsystem::FetchFriendsRanks(FUserSlot UserSlot, FString LeaderboardId, FBeamOperationHandle Op)
{
	if (!IsUserSlotAuthenticated(UserSlot, __FUNCTION__, Op))
	{
		return;
	}
	auto Handle = FOnObjectLeaderboardsGetFriendsByObjectIdFullResponse::CreateLambda([this, Op](const FObjectLeaderboardsGetFriendsByObjectIdFullResponse& Response)
	{
		if (Response.State == RS_Retrying) return;

		if (Response.State == RS_Success)
		{
			// Create the leaderboard view from the response
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

	auto Request = UObjectLeaderboardsGetFriendsByObjectIdRequest::Make(LeaderboardId, this, {});

	FBeamRequestContext Ctx;

	LeaderboardsApi->CPP_GetFriends(UserSlot, Request, Handle, Ctx, Op, this);
}

void UBeamLeaderboardsSubsystem::UpdateLeaderboardScore(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, FOptionalMapOfString Stats, FBeamOperationHandle Op)
{
	auto Handle = FOnPutEntryFullResponse::CreateLambda([this, Op, UserSlot, LeaderboardId, PlayerGamerTag](const FPutEntryFullResponse& Response)
	{
		if (Response.State == RS_Retrying) return;

		if (Response.State == RS_Success)
		{
			// We shouldn't update the leaderboard score, the user should fetch again this information if needed.
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

	auto Request = UPutEntryRequest::Make(LeaderboardId, Score, PlayerGamerTag.AsLong, FOptionalBool(false), FOptionalDouble(), FOptionalDouble(), Stats, this, {});

	FBeamRequestContext Ctx;

	LeaderboardsApi->CPP_PutEntry(UserSlot, Request, Handle, Ctx, Op, this);
}

void UBeamLeaderboardsSubsystem::IncrementLeaderboardScore(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, FOptionalMapOfString Stats, FBeamOperationHandle Op)
{
	auto Handle = FOnPutEntryFullResponse::CreateLambda([this, Op, UserSlot, LeaderboardId, PlayerGamerTag](const FPutEntryFullResponse& Response)
	{
		if (Response.State == RS_Retrying) return;

		if (Response.State == RS_Success)
		{
			// We shouldn't update the leaderboard score, the user should fetch again this information if needed.
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

	auto Request = UPutEntryRequest::Make(LeaderboardId, Score, PlayerGamerTag.AsLong, FOptionalBool(true), FOptionalDouble(), FOptionalDouble(), Stats, this, {});

	FBeamRequestContext Ctx;

	LeaderboardsApi->CPP_PutEntry(UserSlot, Request, Handle, Ctx, Op, this);
}

void UBeamLeaderboardsSubsystem::DecrementLeaderboardScore(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, FOptionalMapOfString Stats, FBeamOperationHandle Op)
{
	auto Handle = FOnPutEntryFullResponse::CreateLambda([this, Op, UserSlot, LeaderboardId, PlayerGamerTag](const FPutEntryFullResponse& Response)
	{
		if (Response.State == RS_Retrying) return;

		if (Response.State == RS_Success)
		{
			// We shouldn't update the leaderboard score, the user should fetch again this information if needed.
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

	auto Request = UPutEntryRequest::Make(LeaderboardId, -Score, PlayerGamerTag.AsLong, FOptionalBool(true), FOptionalDouble(), FOptionalDouble(), Stats, this, {});

	FBeamRequestContext Ctx;

	LeaderboardsApi->CPP_PutEntry(UserSlot, Request, Handle, Ctx, Op, this);
}

int64 UBeamLeaderboardsSubsystem::GetLeaderboardPage(int PageSize, long Rank)
{
	return FGenericPlatformMath::FloorToInt64((Rank - 1) / static_cast<double>(PageSize)) + 1;
}

int64 UBeamLeaderboardsSubsystem::GetExpectedPageEntriesCount(int PageSize, int Page, long LeaderboardSize)
{
	if (Page <= 0 || PageSize <= 0 || LeaderboardSize <= 0)
		return 0;

	int startIndex = (Page - 1) * PageSize;
	if (startIndex >= LeaderboardSize)
		return 0;

	return FGenericPlatformMath::Min(PageSize, LeaderboardSize - startIndex);
}

void UBeamLeaderboardsSubsystem::GetLeaderboardPageRange(int PageSize, long Page, long& StartPageRank, long& LastPageRank)
{
	// Removing the possibility of passing a number lower than 1
	Page = FGenericPlatformMath::Max(Page, static_cast<long>(1));

	StartPageRank = (PageSize * (Page - 1)) + 1;

	LastPageRank = PageSize * Page;
}

FBeamLeaderboardView UBeamLeaderboardsSubsystem::GetLeaderboardView(ULeaderBoardView* LeaderBoard)
{
	FBeamLeaderboardView LeaderboardView = {};

	LeaderboardView.BoardSize = LeaderBoard->BoardSize;
	LeaderboardView.OutlierRankEntry = FBeamRankEntry(LeaderBoard->Rankgt);
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

		UpdatePlayerEntriesLeaderboardCache(LeaderboardView.LeaderboardId);
	}
	else
	{
		auto LeaderboardViewReference = &LeaderboardsCache[LeaderboardView.LeaderboardId];
		LeaderboardViewReference->BoardSize = LeaderboardView.BoardSize;
		LeaderboardViewReference->OutlierRankEntry = LeaderboardView.OutlierRankEntry;

		TMap<int32, int64> LeaderboardCacheRank;

		for (auto RankEntry : LeaderboardViewReference->RankEntries)
		{
			LeaderboardCacheRank.Add(RankEntry.Rank, RankEntry.PlayerGamerTag.AsLong);
		}

		for (auto RankEntry : LeaderboardView.RankEntries)
		{
			// Check if there's duplicated ranks
			if (LeaderboardCacheRank.Contains(RankEntry.Rank) && LeaderboardCacheRank[RankEntry.Rank] != RankEntry.PlayerGamerTag.AsLong)
			{
				// Get the invalid entry index
				auto CachedInvalidEntryGamerTag = LeaderboardCacheRank[RankEntry.Rank];
				auto IndexInvalidEntry = LeaderboardViewReference->PlayerEntriesCache[CachedInvalidEntryGamerTag];

				// Replace the invalid entry by the new one and skip the rest of the code.
				LeaderboardViewReference->RankEntries[IndexInvalidEntry] = RankEntry;

				continue;
			}

			if (LeaderboardViewReference->PlayerEntriesCache.Contains(RankEntry.PlayerGamerTag))
			{
				auto Index = LeaderboardViewReference->PlayerEntriesCache[RankEntry.PlayerGamerTag];
				LeaderboardViewReference->RankEntries[Index] = RankEntry;
			}
			else
			{
				LeaderboardViewReference->RankEntries.Add(RankEntry);
			}
		}

		UpdatePlayerEntriesLeaderboardCache(LeaderboardView.LeaderboardId);
	}

	OnUpdateLeaderboard.Broadcast(LeaderboardView.LeaderboardId);
	OnUpdateLeaderboardCode.Broadcast(LeaderboardView.LeaderboardId);
}

void UBeamLeaderboardsSubsystem::UpdatePlayerEntriesLeaderboardCache(const FString& LeaderboardId, const FBeamGamerTag& PlayerGamerTag)
{
	if (!LeaderboardsCache.Contains(LeaderboardId))
	{
		UE_LOG(LogTemp, Error, TEXT("LeaderboardsCache not found for the %s you should fetch first the leaderboard before use it"), *LeaderboardId);
		return;
	}
	int32 RankIndex = 0;

	auto LeaderboardView = LeaderboardsCache[LeaderboardId];

	for (auto RankEntry : LeaderboardView.RankEntries)
	{
		if (LeaderboardsCache[LeaderboardId].PlayerEntriesCache.Contains(RankEntry.PlayerGamerTag))
		{
			LeaderboardsCache[LeaderboardId].PlayerEntriesCache[RankEntry.PlayerGamerTag] = RankIndex;
		}
		else if (RankEntry.PlayerGamerTag == PlayerGamerTag)
		{
			LeaderboardsCache[LeaderboardId].PlayerEntriesCache.Add(RankEntry.PlayerGamerTag, RankIndex);
		}
		RankIndex++;
	}
}

void UBeamLeaderboardsSubsystem::UpdatePlayerEntriesLeaderboardCache(const FString& LeaderboardId)
{
	if (!LeaderboardsCache.Contains(LeaderboardId))
	{
		UE_LOG(LogTemp, Error, TEXT("LeaderboardsCache not found for the %s you should fetch first the leaderboard before use it"), *LeaderboardId);
		return;
	}

	auto LeaderboardViewReference = &LeaderboardsCache[LeaderboardId];

	if (LeaderboardViewReference->RankEntries.Num() > 0)
	{
		// Sort the ranks 
		LeaderboardViewReference->RankEntries.Sort([](const FBeamRankEntry& A, const FBeamRankEntry& B)
		{
			return A.Rank < B.Rank;
		});
	}

	// Update the player cache
	for (auto RankIndex = 0; RankIndex < LeaderboardViewReference->RankEntries.Num(); RankIndex++)
	{
		auto RankEntry = LeaderboardViewReference->RankEntries[RankIndex];
		if (LeaderboardViewReference->PlayerEntriesCache.Contains(RankEntry.PlayerGamerTag))
		{
			LeaderboardViewReference->PlayerEntriesCache[RankEntry.PlayerGamerTag] = RankIndex;
		}
		else
		{
			LeaderboardViewReference->PlayerEntriesCache.Add(RankEntry.PlayerGamerTag, RankIndex);
		}
	}
}
