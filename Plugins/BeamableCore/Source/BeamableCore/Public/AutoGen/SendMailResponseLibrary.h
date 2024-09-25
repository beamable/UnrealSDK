#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/SendMailResponse.h"

#include "SendMailResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USendMailResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - SendMailResponse To JSON String")
	static FString SendMailResponseToJsonString(const USendMailResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make SendMailResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="MailId, Outer", NativeMakeFunc))
	static USendMailResponse* Make(FOptionalInt64 MailId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break SendMailResponse", meta=(NativeBreakFunc))
	static void Break(const USendMailResponse* Serializable, FOptionalInt64& MailId);
};