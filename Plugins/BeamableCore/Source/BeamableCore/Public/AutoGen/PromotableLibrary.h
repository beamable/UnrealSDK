#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Promotable.h"

#include "PromotableLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPromotableLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="Promotable To JSON String")
	static FString PromotableToJsonString(const UPromotable* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make Promotable", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPromotable* Make(FString Checksum, int64 CreatedAt, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break Promotable", meta=(NativeBreakFunc))
	static void Break(const UPromotable* Serializable, FString& Checksum, int64& CreatedAt);
};