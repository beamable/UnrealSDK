#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmConfigChangeRequestBody.h"

#include "RealmConfigChangeRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmConfigChangeRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - RealmConfigChangeRequestBody To JSON String")
	static FString RealmConfigChangeRequestBodyToJsonString(const URealmConfigChangeRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make RealmConfigChangeRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Deletes, Upserts, Outer", NativeMakeFunc))
	static URealmConfigChangeRequestBody* Make(FOptionalArrayOfString Deletes, FOptionalMapOfString Upserts, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break RealmConfigChangeRequestBody", meta=(NativeBreakFunc))
	static void Break(const URealmConfigChangeRequestBody* Serializable, FOptionalArrayOfString& Deletes, FOptionalMapOfString& Upserts);
};