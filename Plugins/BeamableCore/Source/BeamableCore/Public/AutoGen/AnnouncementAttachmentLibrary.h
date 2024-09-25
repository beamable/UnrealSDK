#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/AnnouncementAttachment.h"

#include "AnnouncementAttachmentLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UAnnouncementAttachmentLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - AnnouncementAttachment To JSON String")
	static FString AnnouncementAttachmentToJsonString(const UAnnouncementAttachment* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make AnnouncementAttachment", meta=(DefaultToSelf="Outer", AdvancedDisplay="Type, Properties, Outer", NativeMakeFunc))
	static UAnnouncementAttachment* Make(FString Symbol, int32 Count, FOptionalString Type, FOptionalArrayOfAttachmentProperty Properties, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break AnnouncementAttachment", meta=(NativeBreakFunc))
	static void Break(const UAnnouncementAttachment* Serializable, FString& Symbol, int32& Count, FOptionalString& Type, FOptionalArrayOfAttachmentProperty& Properties);
};