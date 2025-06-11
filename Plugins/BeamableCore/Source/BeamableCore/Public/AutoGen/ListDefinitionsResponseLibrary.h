#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ListDefinitionsResponse.h"

#include "ListDefinitionsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UListDefinitionsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Json", DisplayName="ListDefinitionsResponse To JSON String")
	static FString ListDefinitionsResponseToJsonString(const UListDefinitionsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Make ListDefinitionsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UListDefinitionsResponse* Make(TArray<UAnnouncementDto*> Content, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Break ListDefinitionsResponse", meta=(NativeBreakFunc))
	static void Break(const UListDefinitionsResponse* Serializable, TArray<UAnnouncementDto*>& Content);
};