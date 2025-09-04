#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmConfigSaveRequestBody.h"

#include "RealmConfigSaveRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmConfigSaveRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="RealmConfigSaveRequestBody To JSON String")
	static FString RealmConfigSaveRequestBodyToJsonString(const URealmConfigSaveRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make RealmConfigSaveRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Config, Outer", NativeMakeFunc))
	static URealmConfigSaveRequestBody* Make(FOptionalMapOfString Config, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break RealmConfigSaveRequestBody", meta=(NativeBreakFunc))
	static void Break(const URealmConfigSaveRequestBody* Serializable, FOptionalMapOfString& Config);
};