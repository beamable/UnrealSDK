#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CreateRealmRequestBody.h"

#include "CreateRealmRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCreateRealmRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="CreateRealmRequestBody To JSON String")
	static FString CreateRealmRequestBodyToJsonString(const UCreateRealmRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make CreateRealmRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bSharded, Plan, Parent, Outer", NativeMakeFunc))
	static UCreateRealmRequestBody* Make(FString Name, FOptionalBool bSharded, FOptionalString Plan, FOptionalString Parent, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break CreateRealmRequestBody", meta=(NativeBreakFunc))
	static void Break(const UCreateRealmRequestBody* Serializable, FString& Name, FOptionalBool& bSharded, FOptionalString& Plan, FOptionalString& Parent);
};