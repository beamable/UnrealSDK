#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ImportFriendsRequestBody.h"

#include "ImportFriendsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UImportFriendsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Friends|4 - Json", DisplayName="ImportFriendsRequestBody To JSON String")
	static FString ImportFriendsRequestBodyToJsonString(const UImportFriendsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|3 - Backend", DisplayName="Make ImportFriendsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UImportFriendsRequestBody* Make(FString Source, FString Token, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Friends|3 - Backend", DisplayName="Break ImportFriendsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UImportFriendsRequestBody* Serializable, FString& Source, FString& Token);
};