// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"
#include "BeamUserSlots.generated.h"

USTRUCT(BlueprintType)
struct FUserSlotSerializedData
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
	 * @brief The DateTime in which the AccessToken will no longer be valid.
	 */
	UPROPERTY(BlueprintReadWrite)
	int64 ExpiresIn;

	/**
	 * @brief The CustomerId whose scope this user exists in.
	 */
	UPROPERTY(BlueprintReadWrite)
	FString Cid;

	/**
	 * @brief The ProductId (Realm) into which this user is signed into.
	 */
	UPROPERTY(BlueprintReadWrite)
	FString Pid;
};

/**
 * 
 */
UCLASS()
class BEAMABLECORE_API UBeamUserSlots : public UEngineSubsystem
{
	GENERATED_BODY()

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
	TMap<FUserSlot, FBeamUserIdx> AuthenticatedUserMapping;

public:
	/** @brief Initializes the auto-increment Id and binds the ExecuteRequestDelegate to DefaultExecuteRequestImpl  */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/** Cleans up the system.  */
	virtual void Deinitialize() override;

	/**
	 * @brief Gets the file path for the serialized state of the given user slot.
	 */
	static FString GetSavedSlotPath(const FUserSlot& SlotId);

	/**
	 * @brief Tries to get the user currently  mapped to the given slot.	  
	 * @return True, if there is a user mapped. False, if no user mapped was found. 
	 */
	bool GetUserDataAtSlot(const FUserSlot& SlotId, FBeamRealmUser& OutUserData) const;

	/**
	 * @brief Tries to get the user currently  mapped to the given slot.	  
	 * @return True, if there is a user mapped. False, if no user mapped was found. 
	 */
	bool GetUserDataWithRefreshTokenAndPid(const FString& RefreshToken, const FString& Pid, FBeamRealmUser& OutUserData, FUserSlot& OutUserSlot) const;

	/**
	 * @brief Sets, without saving, the given authentication token + realm data into the given user slot.	  
	 */
	void SetUserAtSlot(const FUserSlot& SlotId, const FString& AccessToken, const FString& RefreshToken, const int64& ExpiresIn, const FString& Cid, const FString& Pid);

	/**
	 * @brief Sets AND serializes the given authentication token + realm data into the given user slot.
	 */
	void AuthenticateUserAtSlot(const FUserSlot& SlotId, const FString& AccessToken, const FString& RefreshToken, const int64& ExpiresIn, const FString& Cid, const FString& Pid);

	/**
	 * @brief Clears the user and realm data at the give slot id.
	 */
	void ClearUserAtSlot(const FUserSlot& SlotId);


	/**
	 * @brief Attempts to quickly authenticate a user with locally stored, serialized data.	  
	 * @return True, if there was a user authenticated at that slot. False, if no serialized user slot file was found or if the file does not contain a refresh token.  
	 */
	bool TryAuthenticateSavedUserAtSlot(const FUserSlot& SlotId);
};
