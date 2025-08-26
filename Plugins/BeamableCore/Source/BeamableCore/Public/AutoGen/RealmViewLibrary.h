#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmView.h"

#include "RealmViewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="RealmView To JSON String")
	static FString RealmViewToJsonString(const URealmView* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make RealmView", meta=(DefaultToSelf="Outer", AdvancedDisplay="bArchived, bSharded, CustomerId, Parent, Secret, Children, Outer", NativeMakeFunc))
	static URealmView* Make(FString DisplayName, FString RealmId, FOptionalBool bArchived, FOptionalBool bSharded, FOptionalString CustomerId, FOptionalString Parent, FOptionalString Secret, FOptionalArrayOfString Children, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break RealmView", meta=(NativeBreakFunc))
	static void Break(const URealmView* Serializable, FString& DisplayName, FString& RealmId, FOptionalBool& bArchived, FOptionalBool& bSharded, FOptionalString& CustomerId, FOptionalString& Parent, FOptionalString& Secret, FOptionalArrayOfString& Children);
};