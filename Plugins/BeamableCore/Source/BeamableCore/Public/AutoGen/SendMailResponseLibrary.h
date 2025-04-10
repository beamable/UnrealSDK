#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SendMailResponse.h"

#include "SendMailResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USendMailResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Mail|4 - Json", DisplayName="SendMailResponse To JSON String")
	static FString SendMailResponseToJsonString(const USendMailResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|3 - Backend", DisplayName="Make SendMailResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="MailId, Outer", NativeMakeFunc))
	static USendMailResponse* Make(FOptionalInt64 MailId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|3 - Backend", DisplayName="Break SendMailResponse", meta=(NativeBreakFunc))
	static void Break(const USendMailResponse* Serializable, FOptionalInt64& MailId);
};