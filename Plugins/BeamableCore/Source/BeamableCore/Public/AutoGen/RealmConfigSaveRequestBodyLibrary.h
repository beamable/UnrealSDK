#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmConfigSaveRequestBody.h"

#include "RealmConfigSaveRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmConfigSaveRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - RealmConfigSaveRequestBody To JSON String")
	static FString RealmConfigSaveRequestBodyToJsonString(const URealmConfigSaveRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make RealmConfigSaveRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URealmConfigSaveRequestBody* Make(TMap<FString, FString> Config, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break RealmConfigSaveRequestBody", meta=(NativeBreakFunc))
	static void Break(const URealmConfigSaveRequestBody* Serializable, TMap<FString, FString>& Config);
};