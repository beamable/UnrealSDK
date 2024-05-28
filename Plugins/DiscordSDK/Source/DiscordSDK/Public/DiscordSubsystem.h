// ================================ Copyright (c) Wildcard Alliance , All Rights Reserved. ================================

#pragma once

#include "CoreMinimal.h"
#include "DiscordSDK/Discord/core.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "DiscordSubsystem.generated.h"



namespace discord
{
	enum DiscordSubsystemState
	{
		Initializing,
		Failed,
		Initialized
	};
}

USTRUCT(BlueprintType)
struct FDiscordUserData {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Discord")
	FString UserId;
	UPROPERTY(BlueprintReadOnly, Category = "Discord")
	FString Username;
	UPROPERTY(BlueprintReadOnly, Category = "Discord")
	FString Discriminator;
	UPROPERTY(BlueprintReadOnly, Category = "Discord")
	FString Avatar;
	UPROPERTY(BlueprintReadOnly, Category = "Discord")
	FString OAuthToken;
};

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FDiscordInitialied, bool, Success, FDiscordUserData&, UserData, FString, Error);

/**
 * Subsystem to expose discord stuff for ease of use.
 *
 * Also, to get the Discord SDK to compile in certain cases, you'll need to
 * replace the <Windows.h> includes in some discord files. Here's an explanation on how:
 * https://github.com/ryanjon2040/Discord-UE4#compile-error-when-using-as-engine-plugin
 */
UCLASS(Config=Game, DefaultConfig)
class DISCORDSDK_API UDiscordSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	discord::Core* Core{};
	discord::User* CurrentUser{};
	discord::OAuth2Token CurrentToken{};
	
	discord::DiscordSubsystemState State = discord::Initializing;

	FTSTicker::FDelegateHandle TickDelegate;
public:
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	bool         Tick(float X);
	
	void ManualInitialize();
		
	// Read-only stuff that can only be called if initialized is true;	
	FString GetDiscordUserId() const;
	FString GetDiscordUserAuthToken() const;

	UPROPERTY(Config)
	int64 DiscordAppId;

	FDiscordInitialied OnDiscordInitialized;
	
private:
	void OnAuthTokenReceived(discord::Result Res, discord::OAuth2Token const& Token);
	void OnUserUpdated(discord::OAuth2Token Token);

	
};
