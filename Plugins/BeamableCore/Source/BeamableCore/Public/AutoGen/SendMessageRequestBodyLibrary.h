#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SendMessageRequestBody.h"

#include "SendMessageRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USendMessageRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - SendMessageRequestBody To JSON String")
	static FString SendMessageRequestBodyToJsonString(const USendMessageRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make SendMessageRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USendMessageRequestBody* Make(FString RoomId, FString Content, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break SendMessageRequestBody", meta=(NativeBreakFunc))
	static void Break(const USendMessageRequestBody* Serializable, FString& RoomId, FString& Content);
};