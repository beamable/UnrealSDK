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
	FBeamRankEntry OutlierRankEntry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBeamRankEntry> RankEntries;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FBeamGamerTag, int32> PlayerEntriesCache;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int64 BoardSize = 0;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateLeaderboard, FString, LeaderboardId);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateLeaderboardCode, FString);

/**
 * 
 */
UCLASS()
class BEAMABLECORERUNTIME_API UBeamLeaderboardsSubsystem : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

	UBeamLeaderboardsApi* LeaderboardsApi;

	TMap<FString, FBeamLeaderboardView> LeaderboardsCache;

	TMap<FString, FString> AssignmentLeaderboardCache;

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
	 * This is called each time the leaderboard is fetched.
	 */
	UPROPERTY(BlueprintAssignable)
	FOnUpdateLeaderboard OnUpdateLeaderboard;

	/**
	 * @copydoc OnUpdateLeaderboard
	 */
	FOnUpdateLeaderboardCode OnUpdateLeaderboardCode;

	/**
	 * @brief For partitioned or cohorted leaderboards get the local state for a specific child leaderboard the player is assigned to e. g. "leaderboards. my_partitioned_board" -> "leaderboards. my_partitioned_board#0" -- where #0 denotes the partition identifier
	 * If it is not a partitioned leaderboard it will only returns the leaderboard id.
	 * @param PartitionedLeaderboardId: The output for the partitioned leaderboard
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetAssignedLeaderboard(FUserSlot UserSlot, FString LeaderboardId, FString& PartitionedLeaderboardId);
	
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
	 * If it didn't find the focus entry it will return false.
	 *
	 * @param LeaderboardId: The target leaderboard id.
	 * @param StartEntriesSize: The entries that is in the range of the rank 1 to StartEntriesSize will be returned.
	 * @param Entries: The output for the start entries.
	 * @param FocusEntryGamerTag: The Focus entry gamer tage.
	 * @param FocusEntry: The output for the focus entry.
	 * @param LastEntriesSize: The entries that is in the range of the rank last rank entry to LastEntriesSize will be returned.
	 *
	 * @return Returns False if the user don't have the leaderboard state initialized or if it's not possible to retrieve the data.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetFocusRankEntries(FString LeaderboardId, int StartEntriesSize, FBeamGamerTag FocusEntryGamerTag, int LastEntriesSize, TArray<FBeamRankEntry>& Entries, FBeamRankEntry& FocusEntry);

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
	 * @brief Attempts releases all the local rank entries for a specific leaderboard.
	 *
	 * @param LeaderboardId: The target leaderboard id.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	void TryReleaseAllRankEntries(FString LeaderboardId);

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
	 * @brief Attempts to retrieve the page info of a player entry.
	 *
	 * Please make sure to fetch the information before try to get it.
	 *
	 * @param LeaderboardId: The target leaderboard id.

	 * @param PageSize: Tha page size for the leaderboard pagination.
	 * @param LastPageCached: The output for the number of the last cached page.
	 * @param FirstPageCached: The output for the number of the first cached page.
	 * @param TotalPages: The output for the total of pages in the leaderboard (not only the cached).
	 *
	 * @return Returns False if the user don't have the leaderboard state initialized or if it's not possible to retrieve the data.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetLeaderboardPageInfo(FString LeaderboardId, int PageSize, int& FirstPageCached, int& LastPageCached, int& TotalPages);


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
	 *
	 * @return Returns False if the user don't have the leaderboard state initialized or if it's not possible to retrieve the data.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool TryGetPageRankEntries(FString LeaderboardId, int PageSize, int Page, TArray<FBeamRankEntry>& RankEntries, int& CachedEntriesCount);

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

	/**
	 * @brief Check if the leaderboard page is cached.
	 *
	 * @param LeaderboardId: The target leaderboard id.
	 * @param PageSize: The max size of each page.
	 * @param Page: The target page to be checked.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool IsLeaderboardPageCached(FString LeaderboardId, int PageSize, int Page);


	// Operations

	/**
	 * @brief For partitioned or cohorted leaderboards Resolves the specific child leaderboard the player is assigned to e. g. "leaderboards. my_partitioned_board" -> "leaderboards. my_partitioned_board#0" -- where #0 denotes the partition identifier
	 * If it is not a partitioned leaderboard it will only return the leaderboard id.
	 * @param UserSlot: The target user slot to get the partitioned leaderboard
	 * @param Join: If the player should join a partitioned leaderboard
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchAssignedLeaderboardOperation(FUserSlot UserSlot, FString LeaderboardId, bool Join,
	                                                       FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc FetchAssignedLeaderboardOperation
	 */
	FBeamOperationHandle CPP_FetchAssignedLeaderboardOperation(FUserSlot UserSlot, FString LeaderboardId, bool Join,
	                                                           FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief This will fetch some entries in the beginning and in the end of the leaderboard and return a focus entry.
	 *
	 * It will be useful for the @link UBeamLeaderboardsSubsystem::TryGetFocusRankEntries @endlink usage.
	 *
	 * @param LeaderboardId: The target leaderboard id.
	 * @param StartEntriesSize: The entries that is in the range of the rank 1 to StartEntriesSize will be returned.
	 * @param FocusEntryGamerTag: The Focus entry gamer tage.
	 * @param LastEntriesSize: The entries that is in the range of the rank last rank entry to LastEntriesSize will be returned.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchFocusRankEntriesOperation(FUserSlot UserSlot, FString LeaderboardId, int StartEntriesSize, FBeamGamerTag FocusEntryGamerTag, int LastEntriesSize,
	                                                    FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc FetchFocusRankEntriesOperation
	 */
	FBeamOperationHandle CPP_FetchFocusRankEntriesOperation(FUserSlot UserSlot, FString LeaderboardId, int StartEntriesSize, FBeamGamerTag FocusEntryGamerTag, int LastEntriesSize,
	                                                        FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	* Get a view with rankings from a specific leaderboard.
	*
	* @param LeaderboardId: The target leaderboard id.
	* @param From: The Starting Rank you wish to have in the leaderboard.
	* @param Max: Number of ranks. Moves towards the lowest rank; as in, if from is 20 and max is 10, you'll get ranks 20~30.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchLeaderboardOperation(FUserSlot UserSlot, FString LeaderboardId, int From, int Max,
	                                               FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc FetchLeaderboardOperation
	 */
	FBeamOperationHandle CPP_FetchLeaderboardOperation(FUserSlot UserSlot, FString LeaderboardId, int From, int Max,
	                                                   FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * Fetch all the entries for a leaderboard for specific pages.
	 *
	 * This will help in case of pagination for leaderboards with a big amount of entries
	 *
	 * @param LeaderboardId: The specific leaderboard id.
	 * @param PageSize: The size of each page intended to have in the leaderboard (for the view)
	 * @param StartPage: The page to start fetch, that helps cases were you have a lot of pages and would like to fetch it on demand.
	 * @param LastPage: The last page to fetch.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchLeaderboardPageOperation(FUserSlot UserSlot, FString LeaderboardId, int PageSize, int StartPage, int LastPage,
	                                                   FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc FetchLeaderboardPageOperation
	 */
	FBeamOperationHandle CPP_FetchLeaderboardPageOperation(FUserSlot UserSlot, FString LeaderboardId, int PageSize, int StartPage, int LastPage,
	                                                       FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	* Get a view with rankings from a specific leaderboard.
	*
	* @param LeaderboardId: The target leaderboard id.
	* @param FocusPlayer: A user's GamerTag that'll be used as the middle RankEntry of the resulting LeaderBoardView.
	* Will take Diameter/2 from above the focus user and Diameter/2 from below the focus user.
	* It is inclusive. As in, if focus is at rank 50, and you pass in max as 10, you'll get ranks 40~61.
	* If there are not enough entries in the leaderboard either above or below you, the corresponding Diameter/2' will be truncated. 
	* @param Diameter: Explained in the Focus Player Param.
	* @param Outlier: A GamerTag whose rank entry is guaranteed to be included. Will be stored in @link FBeamLeaderboardView::OutlierRankEntry @endlink. 
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchLeaderboardFocusPlayerOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag FocusPlayer, int Diameter, FOptionalBeamGamerTag Outlier,
	                                                          FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc FetchLeaderboardFocusPlayerOperation
	 */
	FBeamOperationHandle CPP_FetchLeaderboardFocusPlayerOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag FocusPlayer, int Diameter, FOptionalBeamGamerTag Outlier,
	                                                              FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief Fetch the rank for array of players in a specific leaderboard
	 *
	 * @param LeaderboardId: The target leaderboard id.
	 * @param PlayersGamerTag: The array of players to retrieve the rank entries.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchPlayerRankOperation(FUserSlot UserSlot, FString LeaderboardId, TArray<FBeamGamerTag> PlayersGamerTag,
	                                              FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc FetchPlayerRankOperation
	 */
	FBeamOperationHandle CPP_FetchPlayerRankOperation(FUserSlot UserSlot, FString LeaderboardId, TArray<FBeamGamerTag> PlayersGamerTag,
	                                                  FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief: Fetch all the friends ranks in a specific leaderboard.
	 *
	 * @param LeaderboardId: The target leaderboard to fetch.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle FetchFriendsRanksOperation(FUserSlot UserSlot, FString LeaderboardId,
	                                                FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc FetchFriendsRanksOperation
	 */
	FBeamOperationHandle CPP_FetchFriendsRanksOperation(FUserSlot UserSlot, FString LeaderboardId,
	                                                    FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	 * @brief: Update the score for a player in a specific leaderboard.
	 *
	 * This call will override the current value of this player.
	 * 
	 * IMPORTANT: It's Only allowed in the client side if the leaderboard have Client Permissions.
	 *
	 * @param LeaderboardId: The target leaderboard id.
	 * @param PlayerGamerTag: The target player to change the score.
	 * @param Score: The value of the new score.
	 * @param Stats: Custom stats that can be added to the Rank Entry.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle UpdateLeaderboardScoreOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, FOptionalMapOfString Stats,
	                                                     FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc UpdateLeaderboardScoreOperation
	 */
	FBeamOperationHandle CPP_UpdateLeaderboardScoreOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, FOptionalMapOfString Stats,
	                                                         FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	* @brief: Increment the score for a player in a specific leaderboard.
	*
	* This will be an addition to the current value that exist in the leaderboard.
	* 
	* IMPORTANT: It's Only allowed in the client side if the leaderboard have Client Permissions.
	*
	* @param LeaderboardId: The target leaderboard id.
	* @param PlayerGamerTag: The target player to change the score.
	* @param Score: The value to increment in the new score.
	* @param Stats: Custom stats that can be added to the Rank Entry.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle IncrementLeaderboardScoreOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, FOptionalMapOfString Stats,
	                                                        FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc IncrementLeaderboardScoreOperation
	 */
	FBeamOperationHandle CPP_IncrementLeaderboardScoreOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, FOptionalMapOfString Stats,
	                                                            FBeamOperationEventHandlerCode OnOperationEvent);

	/**
	* @brief: Decrement the score for a player in a specific leaderboard.
	*
	* This will be an addition to the current value that exist in the leaderboard.
	* 
	* IMPORTANT: It's Only allowed in the client side if the leaderboard have Client Permissions.
	*
	* @param LeaderboardId: The target leaderboard id.
	* @param PlayerGamerTag: The target player to change the score.
	* @param Score: The value to Decrement in the new score.
	* @param Stats: Custom stats that can be added to the Rank Entry.
	*/
	UFUNCTION(BlueprintCallable, Category="Beam|Operation|Leaderboards",
		meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle DecrementLeaderboardScoreOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, FOptionalMapOfString Stats,
	                                                        FBeamOperationEventHandler OnOperationEvent);

	/**
	 * @copydoc DecrementLeaderboardScoreOperation
	 */
	FBeamOperationHandle CPP_DecrementLeaderboardScoreOperation(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, FOptionalMapOfString Stats,
	                                                            FBeamOperationEventHandlerCode OnOperationEvent);

protected:
	// Async Operations

	void FetchAssignedLeaderboard(FUserSlot UserSlot, FString LeaderboardId, bool Join, FBeamOperationHandle Op);

	void FetchLeaderboard(FUserSlot UserSlot, FString LeaderboardId, int From, int Max, FBeamOperationHandle Op);

	void FetchFocusRankEntries(FUserSlot UserSlot, FString LeaderboardId, int StartEntriesSize, FBeamGamerTag FocusEntryGamerTag, int LastEntriesSize, FBeamOperationHandle Op);

	void FetchLeaderboard(FUserSlot UserSlot, FString LeaderboardId, int PageSize, int StartPage, int LastPage, FBeamOperationHandle Op);

	void FetchLeaderboard(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag FocusPlayer, int Max, FOptionalBeamGamerTag Outlier, FBeamOperationHandle Op);

	void FetchPlayerRank(FUserSlot UserSlot, FString LeaderboardId, TArray<FBeamGamerTag> PlayersGamerTag, FBeamOperationHandle Op);

	void FetchFriendsRanks(FUserSlot UserSlot, FString LeaderboardId, FBeamOperationHandle Op);

	void UpdateLeaderboardScore(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, FOptionalMapOfString Stats, FBeamOperationHandle Op);

	void IncrementLeaderboardScore(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, FOptionalMapOfString Stats, FBeamOperationHandle Op);

	void DecrementLeaderboardScore(FUserSlot UserSlot, FString LeaderboardId, FBeamGamerTag PlayerGamerTag, double Score, FOptionalMapOfString Stats, FBeamOperationHandle Op);

	// Utils
	static int64 GetLeaderboardPage(int PageSize, long Rank);

	static int64 GetExpectedPageEntriesCount(int PageSize, int Page, long LeaderboardSize);

	static void GetLeaderboardPageRange(int PageSize, long Page, long& StartPageRank, long& LastPageRank);

	FBeamLeaderboardView GetLeaderboardView(ULeaderBoardView* LeaderBoard);

	FString GetAssignmentLeaderboardKey(FBeamGamerTag PlayerGamerTag, FString LeaderboardId);

	void UpdateLeaderboardCache(FBeamLeaderboardView LeaderboardView);

	void UpdatePlayerEntriesLeaderboardCache(const FString& LeaderboardId, const FBeamGamerTag& PlayerGamerTag);

	void UpdatePlayerEntriesLeaderboardCache(const FString& LeaderboardId);
};
