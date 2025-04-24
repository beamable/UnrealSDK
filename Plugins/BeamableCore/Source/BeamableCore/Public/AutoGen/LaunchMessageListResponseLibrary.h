#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LaunchMessageListResponse.h"

#include "LaunchMessageListResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULaunchMessageListResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="LaunchMessageListResponse To JSON String")
	static FString LaunchMessageListResponseToJsonString(const ULaunchMessageListResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make LaunchMessageListResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULaunchMessageListResponse* Make(TArray<FString> Files, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break LaunchMessageListResponse", meta=(NativeBreakFunc))
	static void Break(const ULaunchMessageListResponse* Serializable, TArray<FString>& Files);
};