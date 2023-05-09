#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/StatStringListEntry.h"

#include "StatStringListEntryLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStatStringListEntryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - StatStringListEntry To JSON String")
	static FString StatStringListEntryToJsonString(const UStatStringListEntry* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make StatStringListEntry", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UStatStringListEntry* Make(FString K, FString V, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break StatStringListEntry", meta=(NativeBreakFunc))
	static void Break(const UStatStringListEntry* Serializable, FString& K, FString& V);
};