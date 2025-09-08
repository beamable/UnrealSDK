#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmAssociation.h"

#include "RealmAssociationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmAssociationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="RealmAssociation To JSON String")
	static FString RealmAssociationToJsonString(const URealmAssociation* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make RealmAssociation", meta=(DefaultToSelf="Outer", AdvancedDisplay="RealmId, PlayerId, Outer", NativeMakeFunc))
	static URealmAssociation* Make(FOptionalString RealmId, FOptionalInt64 PlayerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break RealmAssociation", meta=(NativeBreakFunc))
	static void Break(const URealmAssociation* Serializable, FOptionalString& RealmId, FOptionalInt64& PlayerId);
};