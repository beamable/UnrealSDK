#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MyMailUpdate.h"

#include "MyMailUpdateLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMyMailUpdateLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - MyMailUpdate To JSON String")
	static FString MyMailUpdateToJsonString(const UMyMailUpdate* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make MyMailUpdate", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMyMailUpdate* Make(int64 Id, UUpdateMailRequestBody* Update, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break MyMailUpdate", meta=(NativeBreakFunc))
	static void Break(const UMyMailUpdate* Serializable, int64& Id, UUpdateMailRequestBody*& Update);
};