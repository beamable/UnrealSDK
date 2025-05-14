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
	int64 Rank = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Score = 0.0;

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
	TMap<FBeamGamerTag, int32> FocusedEntries;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 BoardSize = 0;
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

	/**
	 * @brief Attempts to retrieve the local leaderboard state for a specific leaderboard.
	 *
	 * Please make sure to fetch the information before try to get it.
	 *
	 * @param LeaderboardId: The target leaderboard id.
	 * @param LeaderboardView: The leaderboard output state.
	 *
	 * @return Returns False if the user don't have the leaderboard state initialized or if it's not possible to retrieve the data.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetLeaderboard(FString LeaderboardId, FBeamLeaderboardView& LeaderboardView);

	/**
	 * @brief Attempts to retrieve the local player state for a specific leaderboard.
	 *
	 * Please make sure to fetch the information before try to get it.
	 *
	 * @param LeaderboardId: The target leaderboard id.
	 * @param PlayerGamerTag: The target player gamer tag.
	 * @param PlayerRankEntry: The output player entry to get from the leaderboard.
	 *
	 * @return Returns False if the user don't have the leaderboard state initialized or if it's not possible to retrieve the data.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetPlayerRankEntry(FString LeaderboardId, FBeamGamerTag PlayerGamerTag, FBeamRankEntry& PlayerRankEntry);

	/**
	 * @brief Attempts to retrieve the local all the rank entries for a specific leaderboard.
	 *
	 * Please make sure to fetch the information before try to get it.
	 *
	 * @param LeaderboardId: The target leaderboard id.
	 * @param RankEntries: The output rank entries.
	 *
	 * @return Returns False if the user don't have the leaderboard state initialized or if it's not possible to retrieve the data.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetAllRankEntries(FString LeaderboardId, TArray<FBeamRankEntry>& RankEntries);

	/**
	 * @brief Attempts to retrieve the local all the rank entries for a specific leaderboard.
	 *
	 * Please make sure to fetch the information before try to get it.
	 *
	 * @param LeaderboardId: The target leaderboard id.
	 * @param From: The start rank to get (Inclusive).
	 * @param Max: The amount of entries (Inclusive). Obs: If you fetch less than the max amount it will return the possible entries.
	 * @param RankEntries: The output rank entries.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	void TryGetRankEntriesRange(FString LeaderboardId, int From, int Max, TArray<FBeamRankEntry>& RankEntries);


	/**
	 * @brief This is a utility that cover a case of get some entries from the beginning and ending of the leaderboard. And show the position of the player in between.
	 *
	 * Please make sure to fetch the information before try to get it.
	 *
	 * @param LeaderboardId: The target leaderboard id.
	 * @param StartEntriesSize: The entries that is in the range of the rank 1 to StartEntriesSize will be returned.
	 * @param StartEntries: The output for the start entries.
	 * @param FocusEntryGamerTag: The Focus entry gamer tage.
	 * @param FocusEntry: The output for the focus entry.
	 * @param LastEntriesSize: The entries that is in the range of the rank last rank entry to LastEntriesSize will be returned.
	 * @param LastEntries: The output for the last entries.
	 *
	 * @return Returns False if the user don't have the leaderboard state initialized or if it's not possible to retrieve the data.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetFocusRankEntries(FString LeaderboardId, int StartEntriesSize, FBeamGamerTag FocusEntryGamerTag, int LastEntriesSize, TArray<FBeamRankEntry>& StartEntries, FBeamRankEntry& FocusEntry,
	                            TArray<FBeamRankEntry>& LastEntries);
	
	/**
	 * @brief Attempts release the local rank entries for a specific leaderboard in a given range.
	 *
	 * @param LeaderboardId: The target leaderboard id.
	 * @param From: The start rank to get (Inclusive).
	 * @param Max: The amount of entries (Inclusive). Obs: If you fetch less than the max amount it will return the possible entries.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryReleaseRankEntries(FString LeaderboardId, int From, int Max);


	/**
	 * @brief Attempts to retrieve the page info of a player entry.
	 *
	 * Please make sure to fetch the information before try to get it.
	 *
	 * @param LeaderboardId: The target leaderboard id.
	 * @param PlayerGamerTag: the target player gamer tag.
	 * @param PageSize: Tha page size for the leaderboard pagination.
	 * @param PlayerRankEntry: The output of the player rank entry.
	 * @param PlayerPage: The output for which page the player currently are.
	 *
	 * @return Returns False if the user don't have the leaderboard state initialized or if it's not possible to retrieve the data.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetPlayerPageInfo(FString LeaderboardId, FBeamGamerTag PlayerGamerTag, int PageSize, FBeamRankEntry& PlayerRankEntry, int& PlayerPage);

	/**
	 * @brief Attempts to retrieve all the entries for a specific leaderboard page.
	 *
	 * Please make sure to fetch the information before try to get it.
	 *
	 * @param LeaderboardId: The target leaderboard id.
	 * @param PageSize: the size of each leaderboard page.
	 * @param Page: The target page to retrive the entries.
	 * @param RankEntries: The output of all entries for the page.
	 * @param CachedEntriesCount: The output for the current cached entries.
	 * @param TotalPages: The output for the total of pages in the leaderboard (not only the cached).
	 *
	 * @return Returns False if the user don't have the leaderboard state initialized or if it's not possible to retrieve the data.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetPageRankEntries(FString LeaderboardId, int PageSize, int Page, TArray<FBeamRankEntry>& RankEntries, int& CachedEntriesCount, int& TotalPages);

	/**
	 * @brief Attempts to release all the entries for a specific leaderboard page.
	 *
	 * Please make sure to fetch the information before try to get it.
	 *
	 * @param LeaderboardId: The target leaderboard id.
	 * @param PageSize: the size of each leaderboard page.
	 * @param Page: The target page to release the entries.
	 *
	 * @return Returns False if the user don't have the leaderboard state initialized or if it's not possible to retrieve the data.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryReleasePageRankEntries(FString LeaderboardId, int PageSize, int Page);


	// Operations
	
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle LeaderboardAssignmentOperation(FUserSlot UserSlot, FString LeaderboardId, bool Join,
	                                                    FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc LeaderboardAssignmentOperation
	 */
	FBeamOperationHandle CPP_LeaderboardAssignmentOperation(FUserSlot UserSlot, FString LeaderboardId, bool Join,
	                                                        FBeamOperationEventHandlerCode OnOperationEvent);

	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchLeaderboardOperation(FUserSlot UserSlot, FString LeaderboardId, int From, int Max,
	                                               FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc FetchLeaderboardOperation
	 */
	FBeamOperationHandle CPP_FetchLeaderboardOperation(FUserSlot UserSlot, FString LeaderboardId, int From, int Max,
	                                                   FBeamOperationEventHandlerCode OnOperationEvent);

	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchLeaderboardPageOperation(FUserSlot UserSlot, FString LeaderboardId, int PageSize, int StartPage, int LastPage,
	                                                   FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc FetchLeaderboardPageOperation
	 */
	FBeamOperationHandle CPP_FetchLeaderboardPageOperation(FUserSlot UserSlot, FString LeaderboardId, int PageSize, int StartPage, int LastPage,
	                                                       FBeamOperationEventHandlerCode OnOperationEvent);

	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchLeaderboardFocusPlayerOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag FocusPlayer, int Max, FOptionalBeamGamerTag Outlier,
	                                                          FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc FetchLeaderboardFocusPlayerOperation
	 */
	FBeamOperationHandle CPP_FetchLeaderboardFocusPlayerOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag FocusPlayer, int Max, FOptionalBeamGamerTag Outlier,
	                                                              FBeamOperationEventHandlerCode OnOperationEvent);

	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchAssignedLeaderboardOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, int From, int Max,
	                                                       FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc FetchAssignedLeaderboardOperation
	 */
	FBeamOperationHandle CPP_FetchAssignedLeaderboardOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, int From, int Max,
	                                                           FBeamOperationEventHandlerCode OnOperationEvent);

	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchAssignedLeaderboardFocusPlayerOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, FBeamGamerTag FocusPlayer, int Max, FOptionalBeamGamerTag Outlier,
	                                                                  FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc FetchAssignedLeaderboardFocusPlayerOperation
	 */
	FBeamOperationHandle CPP_FetchAssignedLeaderboardFocusPlayerOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, FBeamGamerTag FocusPlayer, int Max, FOptionalBeamGamerTag Outlier,
	                                                                      FBeamOperationEventHandlerCode OnOperationEvent);

	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchPlayerLeaderboardsOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
	                                                      FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc FetchPlayerLeaderboardsOperation
	 */
	FBeamOperationHandle CPP_FetchPlayerLeaderboardsOperation(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag,
	                                                          FBeamOperationEventHandlerCode OnOperationEvent);

	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchPlayerRankOperation(FUserSlot UserSlot, FString LeaderboardId, TArray<FBeamGamerTag> PlayersGamerTag,
	                                              FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc FetchPlayerRankOperation
	 */
	FBeamOperationHandle CPP_FetchPlayerRankOperation(FUserSlot UserSlot, FString LeaderboardId, TArray<FBeamGamerTag> PlayersGamerTag,
	                                                  FBeamOperationEventHandlerCode OnOperationEvent);

	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchFriendsRanksOperation(FUserSlot UserSlot, FString LeaderboardId,
	                                                FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc FetchFriendsRanksOperation
	 */
	FBeamOperationHandle CPP_FetchFriendsRanksOperation(FUserSlot UserSlot, FString LeaderboardId,
	                                                    FBeamOperationEventHandlerCode OnOperationEvent);

	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle UpdateLeaderboardScoreOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, TMap<FString, FString> Stats,
	                                                     FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc UpdateLeaderboardScoreOperation
	 */
	FBeamOperationHandle CPP_UpdateLeaderboardScoreOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, TMap<FString, FString> Stats,
	                                                         FBeamOperationEventHandlerCode OnOperationEvent);

	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle IncrementLeaderboardScoreOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, TMap<FString, FString> Stats,
	                                                        FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc IncrementLeaderboardScoreOperation
	 */
	FBeamOperationHandle CPP_IncrementLeaderboardScoreOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, TMap<FString, FString> Stats,
	                                                            FBeamOperationEventHandlerCode OnOperationEvent);

	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FreezeLeaderboardOperation(FUserSlot UserSlot, FString LeaderboardId,
	                                                FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc IncrementLeaderboardScoreOperation
	 */
	FBeamOperationHandle CPP_FreezeLeaderboardOperation(FUserSlot UserSlot, FString LeaderboardId,
	                                                    FBeamOperationEventHandlerCode OnOperationEvent);

protected:
	// Async Operations

	void FetchAssignment(FUserSlot UserSlot, FString LeaderboardId, bool Join, FBeamOperationHandle Op);

	void FetchLeaderboard(FUserSlot UserSlot, FString LeaderboardId, int From, int Max, FBeamOperationHandle Op);

	void FetchLeaderboard(FUserSlot UserSlot, FString LeaderboardId, int PageSize, int StartPage, int LastPage, FBeamOperationHandle Op);

	void FetchLeaderboard(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag FocusPlayer, int Max, FOptionalBeamGamerTag Outlier, FBeamOperationHandle Op);

	void FetchAssignedLeaderboard(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, int From, int Max, FBeamOperationHandle Op);

	void FetchAssignedLeaderboard(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag FocusPlayer, int Max, FOptionalBeamGamerTag Outlier, FBeamOperationHandle Op);

	void FetchPlayerLeaderboards(FUserSlot UserSlot, FBeamGamerTag PlayerGamerTag, FBeamOperationHandle Op);

	void FetchPlayerRank(FUserSlot UserSlot, FString LeaderboardId, TArray<FBeamGamerTag> PlayersGamerTag, FBeamOperationHandle Op);

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
