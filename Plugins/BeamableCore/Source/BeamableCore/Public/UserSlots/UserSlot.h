#pragma once
#include "BeamBackend/BeamAuthToken.h"
#include "BeamBackend/BeamRealmHandle.h"


#include "UserSlot.generated.h"


/**
 * @brief Semantic separation for strings representing a Beamable User Slot.
 * These can be Empty ("Invalid"), Test ("Any Slot used for automated tests") or Registered ("Slots configured in the Project Settings > Beamable Core > User Slots").
 * This struct exist so that we can make the BP environment better. 
 */
USTRUCT(BlueprintType)
struct FUserSlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Beam")
	FString Name;

	explicit FUserSlot();

	FUserSlot(const FString& x);

	FUserSlot& operator=(const FString& x);

	bool operator==(const FUserSlot& Other) const;

	bool Equals(const FUserSlot& Other) const;

	operator FString();
};

FORCEINLINE uint32 GetTypeHash(const FUserSlot& UserSlot) { return GetTypeHash(UserSlot.Name); }

USTRUCT(BlueprintType, Category="Beam")
struct FBeamRealmUser
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category="Beam")
	FBeamRealmHandle RealmHandle;
	UPROPERTY(BlueprintReadWrite, Category="Beam")
	FBeamAuthToken AuthToken;
};
