#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ObjectRequests.h"

#include "ObjectRequestsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UObjectRequestsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ObjectRequests To JSON String")
	static FString ObjectRequestsToJsonString(const UObjectRequests* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ObjectRequests", meta=(DefaultToSelf="Outer", AdvancedDisplay="PlayerId, Request, Outer", NativeMakeFunc))
	static UObjectRequests* Make(FOptionalInt64 PlayerId, FOptionalArrayOfObjectRequestBody Request, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ObjectRequests", meta=(NativeBreakFunc))
	static void Break(const UObjectRequests* Serializable, FOptionalInt64& PlayerId, FOptionalArrayOfObjectRequestBody& Request);
};