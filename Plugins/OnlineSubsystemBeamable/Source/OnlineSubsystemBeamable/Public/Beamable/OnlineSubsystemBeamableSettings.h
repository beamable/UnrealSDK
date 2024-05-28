// ================================ Copyright (c) Wildcard Alliance , All Rights Reserved. ================================

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "OnlineSubsystemTypes.h"
#include "OnlineSubsystemBeamableSettings.generated.h"

/**
 * 
 */
UCLASS(config=Engine, defaultconfig, meta=(DisplayName="Beamable Online Subsystem"))
class ONLINESUBSYSTEMBEAMABLE_API UOnlineSubsystemBeamableSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	/**
	 * Whether we should automatically try to sign up with persist the Auth data for Runtime User Slots when we are in PIE.
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Identity")
	bool bAutoSignUpWhenLogin = true;

	/**
	 * After we sign up, we get that Beamable User's Stats.
	 * You can map any of these stats to properties that will be stored in the FUserOnlineAccountBeamable::UserAttributes automatically.	 	  
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Identity")
	TMap<FString, FString> StatsToLocalUserAttributeMapping =
	{
		{FString(USER_ATTR_ID), FString(USER_ATTR_ID)},
		{FString(USER_ATTR_ALIAS), FString(USER_ATTR_ALIAS)},
		{FString(USER_ATTR_EMAIL), FString(USER_ATTR_EMAIL)},
		{FString(USER_ATTR_REALNAME), FString(USER_ATTR_REALNAME)},
		{FString(USER_ATTR_DISPLAYNAME), FString(USER_ATTR_DISPLAYNAME)},
		{FString(USER_ATTR_PREFERRED_DISPLAYNAME), FString(USER_ATTR_PREFERRED_DISPLAYNAME)},
	};

	/**
	 * When mapping a Beamable Lobby to a OnlineSubsystem Session, we look for this key in ULobby::Data to configure the IP/Port settings of Session (FInternetAddr). 
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Session")
	FString LobbyDataHostKey = FString(TEXT("host"));

	/**
	 * When mapping a Beamable Lobby to a OnlineSubsystem Session, we look for this key in ULobby::Data to configure the IP/Port settings of Session (FInternetAddr). 
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Session")
	FString LobbyDataPortKey = FString(TEXT("port"));

	/**
	 * When mapping a Beamable Lobby to a OnlineSubsystem Session, we look for this key in ULobby's Players's Tags to configure the FOnlineSession::OwningUserName for the session. 
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Session")
	FString LobbyPlayerTagDisplayNameKey = FString(USER_ATTR_DISPLAYNAME);

	/**
	 * When mapping a Beamable Lobby to a OnlineSubsystem Session, we set the Lobby's passcode into this entry of the FSessionSettings for the FOnlineSession. 
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Session")
	FString LobbyPasscodeSettingsKey = FString(TEXT("passcode"));
};
