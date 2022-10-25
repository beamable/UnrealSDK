
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/SendMessageResponse.h"

#include "SendMessageResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USendMessageResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - SendMessageResponse To JSON String")
	static FString SendMessageResponseToJsonString(const USendMessageResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make SendMessageResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USendMessageResponse* Make(UChatV2ObjectMessage* Message, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break SendMessageResponse", meta=(NativeBreakFunc))
	static void Break(const USendMessageResponse* Serializable, UChatV2ObjectMessage*& Message);
};