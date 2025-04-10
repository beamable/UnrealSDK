#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RoleChangeRequestBody.h"

#include "RoleChangeRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URoleChangeRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Groups|Utils|Json", DisplayName="RoleChangeRequestBody To JSON String")
	static FString RoleChangeRequestBodyToJsonString(const URoleChangeRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Groups|Utils|Make/Break", DisplayName="Make RoleChangeRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="SubGroup, Outer", NativeMakeFunc))
	static URoleChangeRequestBody* Make(int64 GamerTag, FString Role, FOptionalInt64 SubGroup, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Groups|Utils|Make/Break", DisplayName="Break RoleChangeRequestBody", meta=(NativeBreakFunc))
	static void Break(const URoleChangeRequestBody* Serializable, int64& GamerTag, FString& Role, FOptionalInt64& SubGroup);
};