#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MailResponse.h"

#include "MailResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMailResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Json", DisplayName="MailResponse To JSON String")
	static FString MailResponseToJsonString(const UMailResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make MailResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Result, Outer", NativeMakeFunc))
	static UMailResponse* Make(FOptionalMessage Result, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Break MailResponse", meta=(NativeBreakFunc))
	static void Break(const UMailResponse* Serializable, FOptionalMessage& Result);
};