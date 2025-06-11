#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventQueryResponse.h"

#include "EventQueryResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventQueryResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Json", DisplayName="EventQueryResponse To JSON String")
	static FString EventQueryResponseToJsonString(const UEventQueryResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Make EventQueryResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UEventQueryResponse* Make(TArray<UEventObjectData*> Events, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Make/Break", DisplayName="Break EventQueryResponse", meta=(NativeBreakFunc))
	static void Break(const UEventQueryResponse* Serializable, TArray<UEventObjectData*>& Events);
};