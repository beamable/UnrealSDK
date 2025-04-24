#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MailSuccessResponse.h"

#include "MailSuccessResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMailSuccessResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Json", DisplayName="MailSuccessResponse To JSON String")
	static FString MailSuccessResponseToJsonString(const UMailSuccessResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Make MailSuccessResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMailSuccessResponse* Make(bool bResult, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Make/Break", DisplayName="Break MailSuccessResponse", meta=(NativeBreakFunc))
	static void Break(const UMailSuccessResponse* Serializable, bool& bResult);
};