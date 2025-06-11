#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/FederationInfo.h"

#include "FederationInfoLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UFederationInfoLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Json", DisplayName="FederationInfo To JSON String")
	static FString FederationInfoToJsonString(const UFederationInfo* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Make FederationInfo", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UFederationInfo* Make(FString Service, FString Namespace, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Break FederationInfo", meta=(NativeBreakFunc))
	static void Break(const UFederationInfo* Serializable, FString& Service, FString& Namespace);
};