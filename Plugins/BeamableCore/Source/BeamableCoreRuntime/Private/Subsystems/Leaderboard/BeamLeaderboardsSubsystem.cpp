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
	if (PlayerLeaderboardsCache.Contains(BeamRealmUser.GamerTag))
	{
		PlayerLeaderboardsCache.Remove(BeamRealmUser.GamerTag);
	}

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

bool UBeamLeaderboardsSubsystem::TryGetPlayerRankEntry(FString LeaderboardId, FBeamGamerTag Player, FBeamRankEntry& PlayerRankEntry)
{
	if (!PlayerLeaderboardsCache.Contains(Player))
	{
		return false;
	}
	// Get all the leaderboards that the player are in.
	auto PlayerLeaderboardsMap = PlayerLeaderboardsCache[Player];

	if (PlayerLeaderboardsMap.Contains(LeaderboardId))
	{
		PlayerRankEntry = PlayerLeaderboardsMap[LeaderboardId].PlayerRankEntryCache;
		return true;
	}

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

bool UBeamLeaderboardsSubsystem::TryGetPlayerPageInfo(FString LeaderboardId, FBeamGamerTag Player, int PageSize, FBeamRankEntry& PlayerRankEntry, int& PlayerPage)
{
	if (!LeaderboardsCache.Contains(LeaderboardId) || !PlayerLeaderboardsCache.Contains(Player))
	{
		return false;
	}

	auto LeaderboardView = LeaderboardsCache[LeaderboardId];
	auto PlayerLeaderboardsMap = PlayerLeaderboardsCache[Player];

	bool HasPlayerLeaderboard = false;
	if (PlayerLeaderboardsMap.Contains(LeaderboardId))
	{
		PlayerRankEntry = PlayerLeaderboardsMap[LeaderboardId].PlayerRankEntryCache;
		HasPlayerLeaderboard = true;
	}

	if (!HasPlayerLeaderboard)
	{
		return false;
	}

	PlayerPage = GetLeaderboardPage(PageSize, PlayerRankEntry.Rank);

	return false;
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

			if (!LeaderboardsCache.Contains(LeaderboardView.LeaderboardId))
			{
				LeaderboardsCache.Add(LeaderboardView.LeaderboardId, LeaderboardView);
			}
			else
			{
				LeaderboardsCache[LeaderboardView.LeaderboardId] = LeaderboardView;
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

void UBeamLeaderboardsSubsystem::FetchAssignedLeaderboard(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, FBeamGamerTag FocusPlayer, int Max, FOptionalBeamGamerTag Outlier,
                                                          FBeamOperationHandle Op)
{
	// Check if have any assigned leaderboard if don't so we assign one to this player and join then return the assigned leaderbaord
	if (!AssignmentLeaderboardCache.Contains(GetAssignmentLeaderboardKey(PlayerGamerTag, LeaderboardId)))
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

void UBeamLeaderboardsSubsystem::FetchPlayerRanks(FUserSlot UserSlot, FString LeaderboardId, TArray<FBeamGamerTag> PlayersGamerTag, FBeamOperationHandle Op)
{
	auto Handle = FOnGetRanksFullResponse::CreateLambda([this, Op](const FGetRanksFullResponse& Response)
	{
		if (Response.State == RS_Retrying) return;

		if (Response.State == RS_Success)
		{
			Response.SuccessData->
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
	auto Handle = FOnPutEntryFullResponse::CreateLambda([this, Op](const FPutEntryFullResponse& Response)
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

	auto Request = UPutEntryRequest::Make(LeaderboardId, Score, PlayerGamerTag.AsLong, FOptionalBool(false), FOptionalDouble(), FOptionalDouble(), FOptionalMapOfString(Stats), this, {});

	FBeamRequestContext Ctx;

	LeaderboardsApi->CPP_PutEntry(UserSlot, Request, Handle, Ctx, Op, this);
}

void UBeamLeaderboardsSubsystem::IncrementLeaderboardScore(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, TMap<FString, FString> Stats, FBeamOperationHandle Op)
{
	auto Handle = FOnPutEntryFullResponse::CreateLambda([this, Op](const FPutEntryFullResponse& Response)
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
	for (auto RankEntry : LeaderboardView.RankEntries)
	{
		if (RankEntry.PlayerGamerTag == PlayerGamerTag)
		{
			if (!PlayerLeaderboardsCache.Contains(RankEntry.PlayerGamerTag))
			{
				PlayerLeaderboardsCache.Add(RankEntry.PlayerGamerTag, {});
			}
			// Verify if there is any cached data for this player
			if (!PlayerLeaderboardsCache[RankEntry.PlayerGamerTag].Contains(LeaderboardView.LeaderboardId))
			{
				PlayerLeaderboardsCache[RankEntry.PlayerGamerTag].Add(LeaderboardView.LeaderboardId, {});
			}

			// Update the player cache with the new entry
			PlayerLeaderboardsCache[RankEntry.PlayerGamerTag][LeaderboardView.LeaderboardId] =
				FBeamPlayerLeaderboardView(LeaderboardView.LeaderboardId, RankEntry.PlayerGamerTag, RankEntry);
			break;
		}
	}
}
