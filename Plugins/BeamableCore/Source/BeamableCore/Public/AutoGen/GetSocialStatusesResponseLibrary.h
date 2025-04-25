#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetSocialStatusesResponse.h"

#include "GetSocialStatusesResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetSocialStatusesResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Json", DisplayName="GetSocialStatusesResponse To JSON String")
	static FString GetSocialStatusesResponseToJsonString(const UGetSocialStatusesResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Make/Break", DisplayName="Make GetSocialStatusesResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetSocialStatusesResponse* Make(TArray<USocial*> Statuses, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|Utils|Make/Break", DisplayName="Break GetSocialStatusesResponse", meta=(NativeBreakFunc))
	static void Break(const UGetSocialStatusesResponse* Serializable, TArray<USocial*>& Statuses);
};