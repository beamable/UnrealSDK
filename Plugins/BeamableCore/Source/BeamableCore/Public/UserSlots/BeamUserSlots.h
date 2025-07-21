// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"
#include "UserSlot.h"
#include "BeamBackend/SemanticTypes/BeamAccountId.h"
#include "BeamBackend/SemanticTypes/BeamGamerTag.h"
#include "BeamBackend/ReplacementTypes/BeamExternalIdentity.h"
#include "RequestTracker/BeamOperationHandle.h"
#include "BeamUserSlots.generated.h"

/**
 * @brief Semantic separation for ints representing an active Beamable User Idx.
 * These are never guaranteed to be the same across sessions.
 */
typedef int FBeamUserIdx;

USTRUCT(BlueprintType)
struct FUserSlotAuthData
{
	GENERATED_BODY()

	/**
	 * @brief The Access Token for the User signed into a User Slot.
	 */
	UPROPERTY(BlueprintReadWrite)
	FString AccessToken;

	/**
	 * @brief The Refresh Token for the User signed into a User Slot. Used to re-authenticate the user in case of token expiration.
	 */
	UPROPERTY(BlueprintReadWrite)
	FString RefreshToken;

	/**
	 * @brief The DateTime offset from IssuedAt in which the AccessToken will no longer be valid.
	 */
	UPROPERTY(BlueprintReadWrite)
	int64 ExpiresIn = -1;

	/**
	 * @brief The DateTime in which the AccessToken will no longer be valid.
	 */
	UPROPERTY(BlueprintReadWrite)
	int64 IssuedAt = -1;

	/**
	 * @brief The CustomerId whose scope this user exists in.
	 */
	UPROPERTY(BlueprintReadWrite)
	FBeamCid Cid;

	/**
	 * @brief The ProductId (Realm) into which this user is signed into.
	 */
	UPROPERTY(BlueprintReadWrite)
	FBeamPid Pid;

	/**
	 * @returns Whether or not this auth data is expired.
	 */
	bool IsExpired() const
	{
		const FDateTime Now = FDateTime::UtcNow();
		const FDateTime Expiration = FDateTime::FromUnixTimestamp(IssuedAt) + FTimespan::FromMilliseconds(ExpiresIn);
		return Now >= Expiration;
	}
};

USTRUCT(BlueprintType)
struct FUserSlotAccountData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FBeamAccountId AccountId;

	UPROPERTY(BlueprintReadWrite)
	FBeamGamerTag GamerTag;

	UPROPERTY(BlueprintReadWrite)
	FString Email;

	UPROPERTY(BlueprintReadWrite)
	TArray<FBeamExternalIdentity> ExternalIdentities;
};

UENUM(BlueprintType)
enum EUserSlotClearedReason
{
	USCR_Manual,
	USCR_FailedAuthentication,
	USCR_ExitPIE,
	USCR_OnlineSubsystem_NoLocalPlayer,
};

DECLARE_MULTICAST_DELEGATE_FourParams(FUserSlotClearedCodeHandler, const EUserSlotClearedReason&, const FUserSlot&, const FBeamRealmUser&, const UObject*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FUserSlotClearedHandler, const EUserSlotClearedReason&, Reason, const FUserSlot&, ClearedSlot, const FBeamRealmUser&, SlotContentsOnClear, const UObject*,
                                              TriggeringContext);

DECLARE_MULTICAST_DELEGATE_FourParams(FUserSlotAuthenticatedCodeHandler, const FUserSlot&, const FBeamRealmUser&, const FBeamOperationHandle&, const UObject*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FUserSlotAuthenticatedHandler, const FUserSlot&, SlotId, const FBeamRealmUser&, AuthenticatedUser, const FBeamOperationHandle&, OperationHandle, const UObject*,
                                              TriggeringContext);

/**
 * 
 */
UCLASS()
class BEAMABLECORE_API UBeamUserSlots : public UEngineSubsystem
{
	GENERATED_BODY()

	// Forward declaration of the Automated Testing class so we can make it a friend and make it easier to test internal state.
	// Also, mock request types declared for Automated Testing purposes.
	friend class FBeamUserSlotsSpec;

	friend class UBeamRuntime;
	friend class UBeamEditor;

private:
	/**
	 * @brief List of all currently authenticated users paired with the realms they are authenticated with.
	 * A user may be authenticated with multiple different CIDs at the same time and is implicitly authenticated with
	 * all child realms of the Root PID (project) they selected when logging in. 
	 */
	TArray<FBeamRealmUser> AuthenticatedUsers;

	/**
	 * @brief Just a mapping of declared User Slots and authenticated users.
	 * These are mostly here to allow people to refer to users by name: Player1 (Default Player), Player2.
	 * In our own Editor Module, we have a fixed UserSlot for the current editor session's user: MainDeveloperUser.
	 */
	TMap<FString, FBeamUserIdx> AuthenticatedUserMapping;


	/**
	 * @brief Gets the file path for the serialized auth data of the given user slot.
	 */
	static FString GetSavedSlotAuthFilePath(FString NamespacedSlotId);

	/**
	 * @brief Gets the file path for the serialized account data of the given user slot. 
	 */
	static FString GetSavedSlotAccountFilePath(FString NamespacedSlotId);

public:
	/** @brief Initializes the subsystem.  */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Cleans up the system.  */
	virtual void Deinitialize() override;


	static FString GetSavedSlotsDirectory();
	/**
		 * @brief Gets a FUserSlot from a NamespacedSlotId.
		 */
	static bool GetSlotIdFromNamespacedSlotId(FString NamespacedSlotId, FUserSlot& OutUserSlot);
	/**
	 * @brief Gets the file path for the serialized account data of the given user slot.
	 * To be used by other systems when saving data related to a slot.
	 */
	static FString GetSlotDataSavedFilePath(FString SlotDataType, FUserSlot SlotId, const UObject* CallingContext);

	/**
	 * @brief Checks to see an object is owned by a PIE instance.	  
	 */
	static bool IsPIEContext(const UObject* CallingContext);

	/**
	 * @brief Use this instead of FUserSlot.Equals/== if you wish to have multiple PIE support.
	 * Typically, you'll use this only on Global Handlers.
	 *
	 * @see GetNamespacedSlotId 	 
	 */
	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="SlotAContext, SlotBContext", ExpandBoolAsExecs="ReturnValue"))
	static bool IsSameSlot(FUserSlot SlotA, FUserSlot SlotB, const UObject* SlotAContext, const UObject* SlotBContext);

	/**
	 * @brief Gets a list of all known user slots across all PIE instances. When iterating the returned list inside runtime code, remember to call GetUserDataAtSlot to ensure that particular PIE instance has the slot.
	 */
	UFUNCTION(BlueprintPure, Category="Beam", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	TArray<FUserSlot> GetKnownSlots();

	/**
	 * @brief Tries to get the user currently  mapped to the given slot.	  
	 * @return True, if there is a user mapped. False, if no user mapped was found. 
	 */
	UFUNCTION(BlueprintPure, Category="Beam", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	bool GetUserDataAtSlot(FUserSlot SlotId, FBeamRealmUser& OutUserData, const UObject* CallingContext) const;

	/**
	 * @brief Tries to find the a FUserSlot, and its data, that contains the user with the given FBeamGamerTag.	  
	 * @return True, if there is a user mapped. False, if no user mapped was found. 
	 */
	bool GetUserDataWithGamerTag(const FBeamGamerTag& GamerTag, FBeamRealmUser& OutUserData, FUserSlot& OutUserSlot, FString& NamespacedSlotId) const;

	/**
	 * @brief Tries to get the user currently  mapped to the given slot.	  
	 * @return True, if there is a user mapped. False, if no user mapped was found. 
	 */
	UFUNCTION(BlueprintPure, Category="Beam")
	bool GetUserDataWithRefreshTokenAndPid(const FString& RefreshToken, const FBeamPid& Pid, FBeamRealmUser& OutUserData, FUserSlot& OutUserSlot, FString& NamespacedSlotId) const;

	/**
	 * @brief Sets the authentication data directly at a namespaced slot.
	 * Assumes the caller guarantees the given slot is already the correctly namespaced slot name.
	 */
	UFUNCTION()
	void SetAuthenticationDataAtNamespacedSlot(const FString& NamespacedSlotId, const FString& AccessToken, const FString& RefreshToken, const int64& IssuedAt, const int64& ExpiresIn,
	                                           const FBeamCid& Cid, const FBeamPid& Pid);

	/**
	 * @brief Sets, without saving, the given authentication token + realm data into the given user slot.
	 * THIS DOES NOT SERIALIZE THE USER INTO THAT SLOT --- IT'LL BE VALID ONLY FOR THE CURRENT SESSION'S DURATION.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(DefaultToSelf="CallingContext", AutoCreateRefTerm="Cid,Pid", AdvancedDisplay="CallingContext"))
	void SetAuthenticationDataAtSlot(FUserSlot SlotId, const FString& AccessToken, const FString& RefreshToken, const int64& IssuedAt, const int64& ExpiresIn, const FBeamCid& Cid, const FBeamPid& Pid,
	                                 const UObject* CallingContext);

	/**
	 * @brief Sets, without saving, the given GamerTag of the user into this slot. Must always be called on a user slot that has authentication data.
	 * This is because you need to be authenticated in order to get the user's gamer tag.	  	 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(AutoCreateRefTerm="GamerTag", DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	void SetGamerTagAtSlot(FUserSlot SlotId, const FBeamGamerTag& GamerTag, const UObject* CallingContext);


	/**
	 * @brief Sets, without saving, the given AccountId of the user into this slot. Must always be called on a user slot that has authentication data.
	 * This is because you need to be authenticated in order to get the user's gamer tag.	  	 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(AutoCreateRefTerm="AccountId", DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	void SetAccountIdAtSlot(FUserSlot SlotId, const FBeamAccountId& AccountId, const UObject* CallingContext);

	/**
	 * @brief Sets the email to the account data of an authenticated user slot. If it's not authenticated, the email information isn't stored.	  
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(AutoCreateRefTerm="Email", DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	void SetEmailAtSlot(FUserSlot SlotId, const FString& Email, const UObject* CallingContext);

	/**
	 * @brief Sets, without saving, the given PID into the auth data for this slot. If it's not authenticated, the PID is not set (use SetAuthenticationDataAtSlot instead).
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(AutoCreateRefTerm="Pid", DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	void SetPIDAtSlot(FUserSlot SlotId, const FBeamPid& Pid, const UObject* CallingContext);

	/**
	 * @brief Sets the email to the account data of an authenticated user slot. If it's not authenticated, the email information isn't stored.	  
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(AutoCreateRefTerm="Pid", DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	void SetExternalIdsAtSlot(const FUserSlot& SlotId, const TArray<FBeamExternalIdentity> ExternalIdentities, const UObject* CallingContext);

	/**
	 * @brief Invokes the global callback for when a user is authenticated. Used by BPs SignIn/Up/Out Flows in both editor and runtime.
	 * This means that it is ready to make authenticated requests as well as any request that requires a user's gamer tag.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	void TriggerUserAuthenticatedIntoSlot(FUserSlot SlotId, FBeamOperationHandle AuthOp, const UObject* CallingContext);


	/**
	 * @brief Saves whatever data is currently set in that given slot. 
	 * @returns TRUE, if the UserSlot was authenticated. FALSE, otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	bool SaveSlot(FUserSlot SlotId, const UObject* CallingContext);

	/**
	 * @brief Clears the user and realm data at the give slot id.
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	void ClearUserAtSlot(FUserSlot SlotId, const EUserSlotClearedReason& Reason = USCR_Manual, const bool& bShouldRemoveSavedData = false, const UObject* CallingContext = nullptr);

	UFUNCTION(BlueprintCallable, Category="Beam")
	void ClearAllCachedUserDataAtSlot(FUserSlot SlotId);

	void ClearAllCachedUserDataAtNamespacedSlot(FString NamespacedSlot);

	/**
		 * @brief Attempts to quickly authenticate a user with locally stored, serialized data.	  
		 * @return True, if there was a user authenticated at that slot. False, if no serialized user slot file was found or if the file does not contain a refresh token.  
		 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	bool IsUserSlotAuthenticated(FUserSlot SlotId, const UObject* CallingContext);

	/**
	 * Call to clear all slots that have the "PIE_" string in them. 
	 */
	UFUNCTION(BlueprintCallable)
	void DeleteUserSlotCacheForPIE();

	/**
	 * Returned by TryLoadSavedUserAtSlot when no slot was found.
	 */
	static inline int32 LoadSavedUserResult_Failed = 0;

	/**
	 * Returned by TryLoadSavedUserAtSlot when a slot was found and successfully signed in.
	 */
	static inline int32 LoadSavedUserResult_Success = 1;

	/**
	 * Returned by TryLoadSavedUserAtSlot when no slot was found, successfully signed in but the token was expired.
	 */
	static inline int32 LoadSavedUserResult_ExpiredToken = 2;

	/**
	 * @brief Attempts to quickly authenticate a user with locally stored, serialized data.	  
	 * @return True, if there was a user authenticated at that slot. False, if no serialized user slot file was found or if the file does not contain a refresh token.  
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	int32 TryLoadSavedUserAtSlotAndAuth(FUserSlot SlotId, UObject* CallingContext);

	/**
	 * @copydoc @link TryLoadSavedUserAtSlotAndAuth @endlink 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext", ExpandBoolAsExecs="ReturnValue"))
	int32 TryLoadSavedUserAtSlot(FUserSlot SlotId, FUserSlotAuthData& OutAuthData, FUserSlotAccountData& OutAccountData, UObject* CallingContext);

	/**
	 * @copydoc @link TryLoadSavedUserAtSlotAndAuth @endlink 
	 */
	int32 TryLoadSavedUserAtNamespacedSlot(FString NamespacedSlotId, FUserSlotAuthData& OutAuthData, FUserSlotAccountData& OutAccountData);


	/**
	 * @brief Get's a namespaced ID from the given Slot Id and the calling context.
	 * 
	 * @param SlotId The Slot ID you want to namespace.
	 * 
	 * @param CallingContext The UObject that is calling this. In the editor, we need this to determine if we are making the call from a PIE-owned UObject or not.
	 * If we are, we namespace the SlotId with "PIE_{PieInstance}_{SlotId}" so that we can automatically support multiple PIE instances running.
	 * This can be useful to fully test matchmaking into match flows from within the editor.
	 * 
	 * @return A namespaced Slot ID that takes into account the fact that there might be multiple PIE instances running at the same time.
	 */
	static FString GetNamespacedSlotId(FUserSlot SlotId, const UObject* CallingContext);

	static FString GetNamespacedSlotId(FUserSlot SlotId, int32 PIEInstance);

#if WITH_EDITOR
	/**
	 * Extracts the PIE Prefix (PIE_N_) from any given string. This is used to support Multiplayer PIE modes. 
	 */
	static void GetPiePrefix(const FString& Str, FString& PiePrefix);

	/**
	 * Removes the PIE Prefix (PIE_N_) from any given string. This is used to support Multiplayer PIE modes. 
	 */
	static void RemovePiePrefix(const FString& Str, FString& WithoutPiePrefix);
#endif

	/**
	______                           __               ______                                             __  
  / ____/___ _____ ___  ___  ____  / /___ ___  __   / ____/________ _____ ___  ___ _      ______  _____/ /__
 / / __/ __ `/ __ `__ \/ _ \/ __ \/ / __ `/ / / /  / /_  / ___/ __ `/ __ `__ \/ _ \ | /| / / __ \/ ___/ //_/
/ /_/ / /_/ / / / / / /  __/ /_/ / / /_/ / /_/ /  / __/ / /  / /_/ / / / / / /  __/ |/ |/ / /_/ / /  / ,<   
\____/\__,_/_/ /_/ /_/\___/ .___/_/\__,_/\__, /  /_/   /_/   \__,_/_/ /_/ /_/\___/|__/|__/\____/_/  /_/|_|  
						 /_/            /____/                                                              
	 */

	/**
	 * For integration with other implementations of Unreal's Online Subsystem --- this maps the indices of the array of @link UBeamCoreSettings::RuntimeUserSlots @endlink to
	 * Unreal's @link FUniqueNetIdRepl @endlink, @link ULocalPlayer @endlink and @link APlayerController @endlink objects.
	 */
	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FUniqueNetIdRepl GetUniqueNetIdForSlot(FUserSlot Slot, UObject* CallingContext);

	/**
	 * For integration with other implementations of Unreal's Online Subsystem --- this maps the indices of the array of @link UBeamCoreSettings::RuntimeUserSlots @endlink to
	 * Unreal's @link FUniqueNetIdRepl @endlink, @link ULocalPlayer @endlink and @link APlayerController @endlink objects.
	 */
	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	APlayerController* GetPlayerControllerForSlot(FUserSlot Slot, UObject* CallingContext);

	/**
	 * For integration with other implementations of Unreal's Online Subsystem --- this maps the indices of the array of @link UBeamCoreSettings::RuntimeUserSlots @endlink to
	 * Unreal's @link FUniqueNetIdRepl @endlink, @link ULocalPlayer @endlink and @link APlayerController @endlink objects.
	 */
	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	ULocalPlayer* GetLocalPlayerForSlot(FUserSlot Slot, UObject* CallingContext);

	/**
	 
  _    _                  _____ _       _      _____      _ _ _                _        
 | |  | |                / ____| |     | |    / ____|    | | | |              | |       
 | |  | |___  ___ _ __  | (___ | | ___ | |_  | |     __ _| | | |__   __ _  ___| | _____ 
 | |  | / __|/ _ \ '__|  \___ \| |/ _ \| __| | |    / _` | | | '_ \ / _` |/ __| |/ / __|
 | |__| \__ \  __/ |     ____) | | (_) | |_  | |___| (_| | | | |_) | (_| | (__|   <\__ \
  \____/|___/\___|_|    |_____/|_|\___/ \__|  \_____\__,_|_|_|_.__/ \__,_|\___|_|\_\___/																						
																						
	 */
private:
	void SaveSlot(FUserSlot SlotId, int32 PIEInstance, int64 GamerTag, const FString& AccessToken, const FString& RefreshToken, const int64& IssuedAt, const int64& ExpiresIn, const FBeamCid& Cid,
	              const FBeamPid& Pid);

	/**	 
	 * @brief A global handler delegate that'll be called when a UserSlot gets cleared.
	 * It'll have access to the data associated with that slot at the time when it was cleared out but the slot itself will be empty
	 * (as in, you can safely authenticate new users into that slot if you want to).
	 */
	UPROPERTY(BlueprintAssignable, Category="Beam")
	FUserSlotClearedHandler GlobalUserSlotClearedHandler;

	/**
	 * \copybrief GlobalUserSlotClearedHandler
	 * This only exists so that you can write code binding lambdas to this callback. All the same properties of the above are guaranteed
	 * (this is invoked before the BP-compatible handlers).
	 *
	 * PREFER USING THE BP-COMPATIBLE HANDLERS WHENEVER POSSIBLE!! THIS IS A QUALITY OF LIFE THING TO ENABLE FASTER ITERATION!
	 */
	FUserSlotClearedCodeHandler GlobalUserSlotClearedCodeHandler;


	/**	 
	 * @brief A global handler delegate that'll be called immediately before a UserSlot gets authenticated.
	 * It'll have access to the data associated with that slot. The slot itself has whatever data will be saved over.
	 */
	UPROPERTY(BlueprintAssignable, Category="Beam")
	FUserSlotAuthenticatedHandler GlobalUserSlotAuthenticatedHandler;

	/**
	 * \copybrief GlobalUserSlotClearedHandler
	 * This only exists so that you can write code binding lambdas to this callback. All the same properties of the above are guaranteed
	 * (this is invoked before the BP-compatible handlers).
	 *
	 * PREFER USING THE BP-COMPATIBLE HANDLERS WHENEVER POSSIBLE!! THIS IS A QUALITY OF LIFE THING TO ENABLE FASTER ITERATION!
	 */
	FUserSlotAuthenticatedCodeHandler GlobalUserSlotAuthenticatedCodeHandler;
};
