#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MessageRequestBody.h"

#include "MessageRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMessageRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Mailbox|Utils|Json", DisplayName="MessageRequestBody To JSON String")
	static FString MessageRequestBodyToJsonString(const UMessageRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Mailbox|Utils|Make/Break", DisplayName="Make MessageRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Body, Pid, PlayerId, Channel, RealmId, Outer", NativeMakeFunc))
	static UMessageRequestBody* Make(FOptionalString Body, FOptionalBeamPid Pid, FOptionalBeamGamerTag PlayerId, FOptionalString Channel, FOptionalBeamPid RealmId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Mailbox|Utils|Make/Break", DisplayName="Break MessageRequestBody", meta=(NativeBreakFunc))
	static void Break(const UMessageRequestBody* Serializable, FOptionalString& Body, FOptionalBeamPid& Pid, FOptionalBeamGamerTag& PlayerId, FOptionalString& Channel, FOptionalBeamPid& RealmId);
};