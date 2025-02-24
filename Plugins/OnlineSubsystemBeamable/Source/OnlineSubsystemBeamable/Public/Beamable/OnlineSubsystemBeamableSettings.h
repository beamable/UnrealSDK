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
	 * When logging in with a non-frictionless auth type, this defines whether we should automatically try to sign up (true) OR if we should just assume the account already exists and error if it doesn't (false).
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Identity")
	bool bAutoSignUpWhenLogin = true;

	/**
	 * When trying to attach an identity to an existing account, we need to decide whether we should:
	 * - Sign Out of the current account and into the one that has the attached identity. (true)
	 * - Simply error out and let the game-code handle this case. (false)
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category="Identity")
	bool bAutoLoginOnAttach = true;

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
