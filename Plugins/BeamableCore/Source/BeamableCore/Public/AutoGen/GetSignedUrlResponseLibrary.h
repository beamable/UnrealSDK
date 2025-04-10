#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetSignedUrlResponse.h"

#include "GetSignedUrlResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetSignedUrlResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="GetSignedUrlResponse To JSON String")
	static FString GetSignedUrlResponseToJsonString(const UGetSignedUrlResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make GetSignedUrlResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetSignedUrlResponse* Make(FString Url, FString Body, FString Method, TArray<UGetLogsUrlHeader*> Headers, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break GetSignedUrlResponse", meta=(NativeBreakFunc))
	static void Break(const UGetSignedUrlResponse* Serializable, FString& Url, FString& Body, FString& Method, TArray<UGetLogsUrlHeader*>& Headers);
};