#pragma once
#include "BeamBackend/BeamAuthToken.h"
#include "BeamBackend/BeamRealmHandle.h"
#include "BeamBackend/ReplacementTypes/BeamExternalIdentity.h"
#include "BeamBackend/SemanticTypes/BeamAccountId.h"
#include "BeamBackend/SemanticTypes/BeamGamerTag.h"


#include "UserSlot.generated.h"


/**
 * @brief Semantic separation for strings representing a Beamable User Slot.
 * These can be Empty ("Invalid"), Test ("Any Slot used for automated tests") or Registered ("Slots configured in the Project Settings > Beamable Core > User Slots").
 * This struct exist so that we can make the BP environment better. 
 */
USTRUCT(BlueprintType)
struct BEAMABLECORE_API FUserSlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	FString Name;

	explicit FUserSlot();

	FUserSlot(const FString& x);

	FUserSlot& operator=(const FString& x);

	/**
	 * @brief If you want multiple, slotUse this instead of FUserSlot.Equals/== if you wish to have multiple PIE support.
	 *
	 * @see GetNamespacedSlotId 	 
	 */
	bool operator==(const FUserSlot& Other) const;

	bool Equals(const FUserSlot& Other) const;

	operator FString();

	bool IsTestSlot() const { return Name.Contains("Test"); }
};

FORCEINLINE uint32 GetTypeHash(const FUserSlot& UserSlot) { return GetTypeHash(UserSlot.Name); }

/**
 * @brief Data structure representing a single signed-in user to a specific realm.
 */
USTRUCT(BlueprintType, Category="Beam")
struct FBeamRealmUser
{
	GENERATED_BODY()

	/**
	 * @brief The user's GamerTag. Used by a number of APIs to uniquely identify the user. 
	 */
	UPROPERTY(BlueprintReadOnly, Category="Beam")
	FBeamAccountId AccountId;

	/**
	 * @brief The user's GamerTag. Used by a number of APIs to uniquely identify the user. 
	 */
	UPROPERTY(BlueprintReadOnly, Category="Beam")
	FBeamGamerTag GamerTag;

	/**
	 * @brief The user's email, if any. Mostly used in editor code.
	 */
	UPROPERTY(BlueprintReadOnly, Category="Beam")
	FString Email;

	/**
	 * @brief The realm this user is currently authenticated into.
	 */
	UPROPERTY(BlueprintReadOnly, Category="Beam")
	FBeamRealmHandle RealmHandle;

	/**
	 * @brief The authentication token for this user.
	 */
	UPROPERTY(BlueprintReadOnly, Category="Beam")
	FBeamAuthToken AuthToken;

	/**
	 * @brief The list of all External Identities attached to this user.
	 */
	UPROPERTY(BlueprintReadOnly, Category="Beam")
	TArray<FBeamExternalIdentity> ExternalIdentities;
};
