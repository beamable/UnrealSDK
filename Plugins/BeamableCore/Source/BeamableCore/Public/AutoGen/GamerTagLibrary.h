#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GamerTag.h"

#include "GamerTagLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGamerTagLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Json", DisplayName="GamerTag To JSON String")
	static FString GamerTagToJsonString(const UGamerTag* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Make GamerTag", meta=(DefaultToSelf="Outer", AdvancedDisplay="Alias, Added, User, Trials, Outer", NativeMakeFunc))
	static UGamerTag* Make(int64 Tag, FString Platform, FOptionalString Alias, FOptionalInt64 Added, FOptionalSessionUser User, FOptionalArrayOfCohortEntry Trials, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Break GamerTag", meta=(NativeBreakFunc))
	static void Break(const UGamerTag* Serializable, int64& Tag, FString& Platform, FOptionalString& Alias, FOptionalInt64& Added, FOptionalSessionUser& User, FOptionalArrayOfCohortEntry& Trials);
};