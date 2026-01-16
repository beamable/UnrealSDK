#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/UpdateRealmRequestBody.h"

#include "UpdateRealmRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UUpdateRealmRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="UpdateRealmRequestBody To JSON String")
	static FString UpdateRealmRequestBodyToJsonString(const UUpdateRealmRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make UpdateRealmRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bArchiveStatus, bHiddenStatus, Outer", NativeMakeFunc))
	static UUpdateRealmRequestBody* Make(FOptionalBool bArchiveStatus, FOptionalBool bHiddenStatus, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break UpdateRealmRequestBody", meta=(NativeBreakFunc))
	static void Break(const UUpdateRealmRequestBody* Serializable, FOptionalBool& bArchiveStatus, FOptionalBool& bHiddenStatus);
};