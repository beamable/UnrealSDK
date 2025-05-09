// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/SubSystems/BeamLeaderboardsApi.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "BeamLeaderboardsSubsystem.generated.h"

USTRUCT(BlueprintType)
struct BEAMABLECORERUNTIME_API FBeamRankEntry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBeamGamerTag PlayerGamerTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 Rank;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Score;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FString> Stats;

	double GetDoubleStat(const FString& Name, double Default = 0)
	{
		if (Stats.Contains(Name) && Stats[Name].IsNumeric())
		{
			double StatValue = FCString::Atod(*Stats[Name]);
			return StatValue;
		}
		return Default;
	}

	FString GetStat(const FString& Name)
	{
		if (Stats.Contains(Name))
		{
			return Stats[Name];
		}
		return FString();
	}

	FBeamRankEntry() = default;

	explicit FBeamRankEntry(const FOptionalRankEntry& Rankgt);
	explicit FBeamRankEntry(URankEntry* RankEntry);
};

USTRUCT(BlueprintType)
struct BEAMABLECORERUNTIME_API FBeamLeaderboardView
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LeaderboardId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBeamRankEntry PlayerRankEntry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBeamRankEntry> RankEntries;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 BoardSize;
};

USTRUCT(BlueprintType)
struct BEAMABLECORERUNTIME_API FBeamPlayerLeaderboardView
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LeaderboardId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBeamGamerTag PlayerGamerTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBeamRankEntry PlayerRankEntryCache;

	FBeamPlayerLeaderboardView() = default;

	FBeamPlayerLeaderboardView(const FString& LeaderboardId, const FBeamGamerTag& PlayerGamerTag, const FBeamRankEntry& PlayerRankEntryCache)
		: LeaderboardId(LeaderboardId),
		  PlayerGamerTag(PlayerGamerTag),
		  PlayerRankEntryCache(PlayerRankEntryCache)
	{
	}
};


/**
 * 
 */
UCLASS()
class BEAMABLECORERUNTIME_API UBeamLeaderboardsSubsystem : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

	UBeamLeaderboardsApi* LeaderboardsApi;

	TMap<FString, FString> AssignmentLeaderboardCache;

	TMap<FBeamGamerTag, TMap<FString, FBeamPlayerLeaderboardView>> PlayerLeaderboardsCache;

	TMap<FString, FBeamLeaderboardView> LeaderboardsCache;

	virtual void InitializeWhenUnrealReady_Implementation(FBeamOperationHandle& ResultOp) override;

	virtual void OnUserSignedIn_Implementation(const FUserSlot& UserSlot, const FBeamRealmUser& BeamRealmUser,
	                                           const bool bIsOwnerUserAuth, FBeamOperationHandle& ResultOp) override;

	virtual void OnUserSignedOut_Implementation(const FUserSlot& UserSlot, const EUserSlotClearedReason Reason,
	                                            const FBeamRealmUser& BeamRealmUser,
	                                            FBeamOperationHandle& ResultOp) override;

public:
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamLeaderboardsSubsystem* GetSelf(const UObject* CallingContext)
	{
		return CallingContext->GetWorld()->GetGameInstance()->GetSubsystem<UBeamLeaderboardsSubsystem>();
	}


	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetLeaderboard(FString LeaderboardId, FBeamLeaderboardView& LeaderboardView);

	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetPlayerRankEntry(FString LeaderboardId, FBeamGamerTag Player, FBeamRankEntry& PlayerRankEntry);

	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetAllRankEntries(FString LeaderboardId, TArray<FBeamRankEntry>& RankEntries);

	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryReleaseRankEntries(FString LeaderboardId, int From, int Max);

	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetPlayerPageInfo(FString LeaderboardId, FBeamGamerTag Player, int PageSize, FBeamRankEntry& PlayerRankEntry, int& PlayerPage);

	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetPageRankEntries(FString LeaderboardId, int PageSize, int Page, TArray<FBeamRankEntry>& RankEntries, int& CachedEntriesCount, int& TotalPages);

	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryReleasePageRankEntries(FString LeaderboardId, int PageSize, int Page);

protected:
	// Async Operations

	void FetchAssignment(FUserSlot UserSlot, FString LeaderboardId, bool Join, FBeamOperationHandle Op);

	void FetchLeaderboard(FUserSlot UserSlot, FString LeaderboardId, int From, int Max, FBeamOperationHandle Op);

	void FetchLeaderboard(FUserSlot UserSlot, FString LeaderboardId, int PageSize, int StartPage, int LastPage, FBeamOperationHandle Op);

	void FetchLeaderboard(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag FocusPlayer, int Max, FOptionalBeamGamerTag Outlier, FBeamOperationHandle Op);

	void FetchAssignedLeaderboard(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, int From, int Max, FBeamOperationHandle Op);

	void FetchAssignedLeaderboard(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, FBeamGamerTag FocusPlayer, int Max, FOptionalBeamGamerTag Outlier, FBeamOperationHandle Op);

	void FetchPlayerLeaderboards(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag, FBeamOperationHandle Op);

	void FetchPlayerRanks(FUserSlot UserSlot, FString LeaderboardId, TArray<FBeamGamerTag> PlayersGamerTag, FBeamOperationHandle Op);

	void FetchFriendsRanks(FUserSlot UserSlot, FString LeaderboardId, FBeamOperationHandle Op);

	void UpdateLeaderboardScore(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, TMap<FString, FString> Stats, FBeamOperationHandle Op);

	void IncrementLeaderboardScore(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, TMap<FString, FString> Stats, FBeamOperationHandle Op);

	// Admin
	void FreezeLeaderboard(FUserSlot UserSlot, FString LeaderboardId, FBeamOperationHandle Op);

	// Utils

	long GetLeaderboardPage(int PageSize, long Rank);

	void GetLeaderboardPageRange(int PageSize, long Page, long& StartPageRank, long& LastPageRank);

	FBeamLeaderboardView GetLeaderboardView(ULeaderBoardView* LeaderBoard);

	FString GetAssignmentLeaderboardKey(FBeamGamerTag PlayerGamerTag, FString LeaderboardId);

	void UpdateLeaderboardCache(FBeamLeaderboardView LeaderboardView);

	void UpdatePlayerLeaderboardCache(FBeamLeaderboardView LeaderboardView, const FBeamGamerTag& PlayerGamerTag);
};
