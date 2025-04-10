#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Query.h"

#include "QueryLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UQueryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="Query To JSON String")
	static FString QueryToJsonString(const UQuery* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make Query", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UQuery* Make(FString QueryId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break Query", meta=(NativeBreakFunc))
	static void Break(const UQuery* Serializable, FString& QueryId);
};