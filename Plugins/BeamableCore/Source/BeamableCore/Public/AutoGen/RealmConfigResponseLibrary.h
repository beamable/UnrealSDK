#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmConfigResponse.h"

#include "RealmConfigResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmConfigResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - RealmConfigResponse To JSON String")
	static FString RealmConfigResponseToJsonString(const URealmConfigResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make RealmConfigResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URealmConfigResponse* Make(TMap<FString, FString> Config, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break RealmConfigResponse", meta=(NativeBreakFunc))
	static void Break(const URealmConfigResponse* Serializable, TMap<FString, FString>& Config);
};