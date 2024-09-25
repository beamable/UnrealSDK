#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/MessageRequestBody.h"

#include "MessageRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMessageRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - MessageRequestBody To JSON String")
	static FString MessageRequestBodyToJsonString(const UMessageRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make MessageRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Body, Cid, Pid, PlayerId, Channel, Outer", NativeMakeFunc))
	static UMessageRequestBody* Make(FOptionalString Body, FOptionalString Cid, FOptionalString Pid, FOptionalBeamGamerTag PlayerId, FOptionalString Channel, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break MessageRequestBody", meta=(NativeBreakFunc))
	static void Break(const UMessageRequestBody* Serializable, FOptionalString& Body, FOptionalString& Cid, FOptionalString& Pid, FOptionalBeamGamerTag& PlayerId, FOptionalString& Channel);
};