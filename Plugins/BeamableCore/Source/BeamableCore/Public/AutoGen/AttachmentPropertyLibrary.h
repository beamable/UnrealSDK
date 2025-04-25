#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/AttachmentProperty.h"

#include "AttachmentPropertyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAttachmentPropertyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Json", DisplayName="AttachmentProperty To JSON String")
	static FString AttachmentPropertyToJsonString(const UAttachmentProperty* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Make AttachmentProperty", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UAttachmentProperty* Make(FString Name, FString Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Break AttachmentProperty", meta=(NativeBreakFunc))
	static void Break(const UAttachmentProperty* Serializable, FString& Name, FString& Value);
};