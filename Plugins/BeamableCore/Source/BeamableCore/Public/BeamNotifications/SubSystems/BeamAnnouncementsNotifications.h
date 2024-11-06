#pragma once


#include "BeamNotifications/BeamNotifications.h"
#include "Serialization/BeamJsonSerializable.h"
#include "UserSlots/UserSlot.h"
#include "BeamAnnouncementsNotifications.generated.h"


USTRUCT(BlueprintType)
struct BEAMABLECORE_API FAnnouncementRefreshNotificationMessage : public FBeamBaseNotificationMessage
{
	GENERATED_BODY()

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};

DECLARE_DELEGATE_OneParam(FOnAnnouncementRefreshNotificationCode, FAnnouncementRefreshNotificationMessage);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnAnnouncementRefreshNotification, FAnnouncementRefreshNotificationMessage, Evt);

UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamAnnouncementsNotifications : public UEngineSubsystem
{
	GENERATED_BODY()

	static const inline FString CTX_KEY_Content_Refresh = TEXT("announcements.refresh");

	UPROPERTY()
	UBeamNotifications* Notifications;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	UFUNCTION(BlueprintCallable, DisplayName="Subscribe - Announcement Refresh", Category="Beam", meta=(DefaultToSelf="ContextObject"))
	void SubscribeToAnnouncementRefresh(const FUserSlot& Slot, const FName& SocketName, const FOnAnnouncementRefreshNotification& Handler, UObject* ContextObject) const;

	FDelegateHandle CPP_SubscribeToAnnouncementRefresh(const FUserSlot& Slot, const FName& SocketName, const FOnAnnouncementRefreshNotificationCode& Handler, UObject* ContextObject) const;
};
