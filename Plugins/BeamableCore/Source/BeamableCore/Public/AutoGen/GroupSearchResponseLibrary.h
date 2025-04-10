#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GroupSearchResponse.h"

#include "GroupSearchResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGroupSearchResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Json", DisplayName="GroupSearchResponse To JSON String")
	static FString GroupSearchResponseToJsonString(const UGroupSearchResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Make GroupSearchResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGroupSearchResponse* Make(TArray<UGroup*> Groups, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Break GroupSearchResponse", meta=(NativeBreakFunc))
	static void Break(const UGroupSearchResponse* Serializable, TArray<UGroup*>& Groups);
};