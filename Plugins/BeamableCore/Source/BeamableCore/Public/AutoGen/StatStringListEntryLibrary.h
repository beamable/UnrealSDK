#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/StatStringListEntry.h"

#include "StatStringListEntryLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStatStringListEntryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Json", DisplayName="StatStringListEntry To JSON String")
	static FString StatStringListEntryToJsonString(const UStatStringListEntry* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Make/Break", DisplayName="Make StatStringListEntry", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UStatStringListEntry* Make(FString K, FString V, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Make/Break", DisplayName="Break StatStringListEntry", meta=(NativeBreakFunc))
	static void Break(const UStatStringListEntry* Serializable, FString& K, FString& V);
};