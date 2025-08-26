#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RenameRealmRequestBody.h"

#include "RenameRealmRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URenameRealmRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="RenameRealmRequestBody To JSON String")
	static FString RenameRealmRequestBodyToJsonString(const URenameRealmRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make RenameRealmRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URenameRealmRequestBody* Make(FString NewName, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break RenameRealmRequestBody", meta=(NativeBreakFunc))
	static void Break(const URenameRealmRequestBody* Serializable, FString& NewName);
};