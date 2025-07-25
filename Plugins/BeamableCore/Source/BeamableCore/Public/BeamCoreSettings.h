// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BeamEnvironment.h"
#include "BeamBackend/BeamRealmHandle.h"
#include "BeamBackend/BeamRetryConfig.h"
#include "BeamBackend/ResponseCache/BeamCacheConfig.h"
#include "BeamCoreSettings.generated.h"

/**
 * 
 */
UCLASS(config=Engine, defaultconfig, meta=(DisplayName="Beamable Core"))
class BEAMABLECORE_API UBeamCoreSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UBeamCoreSettings();

	/* Soft path will be converted to content reference before use */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", AdvancedDisplay)
	TSoftObjectPtr<UBeamEnvironmentData> BeamableEnvironment;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", AdvancedDisplay)
	TArray<TSoftObjectPtr<UBeamEnvironmentData>> BeamablePossibleEnvironments;
	
	/**
	* @brief A RealmHandle struct defining the CustomerID and RealmID (CID, PID) that this build will target.
	* All authentication and non-authenticated requests are made against this realm.
	*
	* In the editor environment, this is the realm where you are currently pointed at.
	* You can use the realm swap drop-down to change this from a list of available realms after you've signed in.
	* This CAN NEVER BE EMPTY if you are signed in to Beamable.
	*
	* When you create an account or sign in to a customer for the first time in this project, we default you to that customer's Dev realm if this is ever empty.
	*/
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Request/Response")
	FBeamRealmHandle TargetRealm;

	/**
	 * @brief Whether we should run the global error handlers even if there was a handler provided at the callsite.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Request/Response")
	bool AlwaysRunGlobalErrorHandlers = true;

	/**
	 * @brief Whether we should log after running the Success callback --- by default we always log them if you provide no callback at the callsite.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Request/Response")
	bool AlwaysLogSuccessResponses = true;

	/**
	 * @brief Whether we should log after running the Error callback --- by default we always log them if you provide no callback at the callsite.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Request/Response")
	bool AlwaysLogErrorResponses = true;

	/**
	 * @brief Whether we should log after running the Complete callback --- by default we always log them if you provide no callback at the callsite.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Request/Response")
	bool AlwaysLogCompletedResponses = true;

	/**
	 * @brief The configuration for retrying requests.
	 * Setting the Max Attempt as -1 will make it an "infinite retry" though we don't recommend doing this from a design perspective.
	 * Setting more retry attempts than falloff values will default to the last possible falloff value after the attempts exceed the array length.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Request/Response")
	FBeamRetryConfig FallbackRetryConfiguration{{408}, {}, 10, {.5f, 1, 2, 4, 8}, 5};
		
	/**
	 * @brief The configuration for cache-ing all requests. Can be overriden via the API in @see UBeamResponseCache.
	 *
	 * By default, we don't cache any requests because request cache-ing is somewhat of a game-specific thing. You should never cache any requests that modify state
	 * (for the most part, only cache GET requests and you'll be fine). Also, incorrectly cache-ing things can be a source of hard to find bugs. As such, we recommend you use
	 * our metrics to identify which requests are being made the most in your regular play-sessions and start there.
	 *
	 * REMEMBER TO ONLY CACHE READ-ONLY REQUESTS!!!
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Request/Response")
	FBeamCacheConfig GlobalCacheConfiguration{Disabled, 600,};

	/**
	 * @brief The interval (in seconds) over which the Request Tracker system will run it's CleanUp functions.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Request/Response")
	float RequestTrackerCleanUpInterval = 300.0f;

	/**
	 * @brief These are the expected user slots for your game.
	 *
	 * INFO: Index 0 here is considered the "Owner Player" slot. Typically, this is what most games without local-multiplayer will care about.
	 * INFO: We have an option here to automatically authenticate into the "OwnerPlayer" slot. If it is turned off, please use the OnBeamableReady to call the FrictionlessAuth operation.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "User Slots")
	TArray<FString> RuntimeUserSlots{"Player0"};

	/**
	 * @brief These are the expected user slots for your editor environment. By default, you get logged into the "MainEditorDeveloper" UserSlot.
	 * User slots not registered here will not be allowed to be authenticated into outside EditorUtilityWidget/EditorUtilityBlueprints.
	 * Are only valid slots if they contain the word "Developer" in them.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="User Slots")
	TArray<FString> DeveloperUserSlots{"MainEditorDeveloper"};

	/**
	 * @brief Whether we should automatically sign in for the Owner Player. If you do not wish this to be true and want to control when you sign in to Beamable, you can disable this.
	 * If you disable it and want to replicate the default behaviour for whatever reason, simply call the Frictionless Authentication operation at the OnBeamableStarted of a "BootBeamableSubsystem"
	 * and you will get the same behaviour.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="User Slots")
	bool bAutomaticFrictionlessAuthForOwnerPlayer = true;

	/**
	 * @brief Whether we should persist the Auth data for Runtime User Slots when we are in PIE.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="User Slots")
	bool bPersistRuntimeSlotDataWhenInPIE = true;

	/**
	 * @brief When deserializing content that stores FGameplayTag, should we error out if we fail to convert that tag?
	 * If this is true, you must guarantee all tags in all content are always valid in your project/build.
	 * If this is false, non-existent tags will be deserialized as invalid.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Content")
	bool bErrorIfGameplayTagNotFound = false;

	/**
	* @brief The name of the folder that is inside the saved folder that all the cached content will go into on runtime.
	*/
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Content")
	FString CachedContentFolderName = "CachedContent";

	/**
	* @brief Cached content file name.
	*/
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Content")
	FString GlobalCachedContentFileName = "CC_Global";
	
	/**
	* @brief The name of the folder that is inside the saved folder that all the cached content will go into on runtime.
	*/
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Content")
	FString BakedContentFolderName = "BakedContent";

	/**
	* @brief Cached content file name.
	*/
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Content")
	FString GlobalBakedContentFileName = "BCC_Global";
	
	UFUNCTION(BlueprintCallable)
	FUserSlot GetOwnerPlayerSlot() const { return FUserSlot{RuntimeUserSlots[0]}; }

	/**
	 * When this is false, our code-generated Break nodes for IBeamJsonSerializableUObject implementations will assume that the object is NEVER null.
	 * If this is true, it'll silently be a no-op.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Json Serialization")
	bool bSilenceBreakGuardEnsures = false;

	/**
	 * Called in all IBeamJsonSerializableUObject.  
	 */
	bool BreakGuard(const IBeamJsonSerializableUObject* Serializable) const
	{
		if (bSilenceBreakGuardEnsures)
		{
			return Serializable != nullptr;		
		}
		
		return ensureAlwaysMsgf(Serializable, 
			TEXT("Trying to break a null Beam Json Serializable object. If you don't care and just want to skip nulls, you can disable this ensure globally at Project Settings -> Beamable Core -> bSilenceBreakGuardEnsures."));	
	}
};
