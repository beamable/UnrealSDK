#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmConfigResponse.h"

#include "RealmConfigResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmConfigResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="RealmConfigResponse To JSON String")
	static FString RealmConfigResponseToJsonString(const URealmConfigResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make RealmConfigResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Config, Outer", NativeMakeFunc))
	static URealmConfigResponse* Make(FOptionalMapOfString Config, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break RealmConfigResponse", meta=(NativeBreakFunc))
	static void Break(const URealmConfigResponse* Serializable, FOptionalMapOfString& Config);
};