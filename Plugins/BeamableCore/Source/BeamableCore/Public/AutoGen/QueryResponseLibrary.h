#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/QueryResponse.h"

#include "QueryResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UQueryResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="QueryResponse To JSON String")
	static FString QueryResponseToJsonString(const UQueryResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make QueryResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="QueryId, Outer", NativeMakeFunc))
	static UQueryResponse* Make(FOptionalString QueryId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break QueryResponse", meta=(NativeBreakFunc))
	static void Break(const UQueryResponse* Serializable, FOptionalString& QueryId);
};