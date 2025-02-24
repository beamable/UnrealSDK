// ================================ Copyright (c) Wildcard Alliance , All Rights Reserved. ================================


#include "DiscordSubsystem.h"
#include "DiscordSDK/Discord/core.h"

void UDiscordSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	TickDelegate = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UDiscordSubsystem::Tick), 0);
}

void UDiscordSubsystem::Deinitialize()
{
	FTSTicker::GetCoreTicker().RemoveTicker(TickDelegate);
	delete Core;
}

bool UDiscordSubsystem::Tick(float)
{
	if (Core)
		Core->RunCallbacks();
	return true;
}

void UDiscordSubsystem::ManualInitialize()
{
	if (State == discord::Initialized)
		return;
	
	UE_LOG(LogTemp, Display, TEXT("[Discord SDK] Initializing Discord SDK."));
	auto Result = discord::Core::Create(DiscordAppId, DiscordCreateFlags_Default, &Core);
	if (Result == discord::Result::Ok)
	{
		UE_LOG(LogTemp, Display, TEXT("[Discord SDK] Initialized Discord SDK."));
		Core->ApplicationManager().GetOAuth2Token([this](discord::Result Result, discord::OAuth2Token const& Token)
		{
			UE_LOG(LogTemp, Display, TEXT("[Discord SDK] Found Auth Token: %hd"), Result);
			OnAuthTokenReceived(Result, Token);
		});
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[Discord SDK] Failed To Initialize Discord SDK. %d"), Result);
		State = discord::Failed;
		FDiscordUserData UserData;
		OnDiscordInitialized.ExecuteIfBound(false, UserData, "Failed to initialize Discord SDK.\n Please ensure Discord is running.");
	}
}

FString UDiscordSubsystem::GetDiscordUserId() const
{
	check(State == discord::Initialized);
	return FString::Printf(TEXT("%lld"), CurrentUser->GetId());
}

FString UDiscordSubsystem::GetDiscordUserAuthToken() const
{
	check(State == discord::Initialized);
	return FString(ANSI_TO_TCHAR(CurrentToken.GetAccessToken()));
}


void UDiscordSubsystem::OnAuthTokenReceived(discord::Result Res, discord::OAuth2Token const& Token)
{
	if (Res != discord::Result::Ok)
	{
		UE_LOG(LogTemp, Error, TEXT("[Discord Integration] Failed to get discord OAuth Token"));
		State = discord::Failed;
		FDiscordUserData UserData;
		OnDiscordInitialized.ExecuteIfBound(false, UserData, "Failed to get discord OAuth Token");
	}
	else
	{
		Core->UserManager().OnCurrentUserUpdate.Connect([this, Token]()
		{
			OnUserUpdated(Token);
		});
	}
}

void UDiscordSubsystem::OnUserUpdated(discord::OAuth2Token Token)
{
	CurrentUser = new discord::User;
	Core->UserManager().GetCurrentUser(CurrentUser);
	FDiscordUserData UserData;
	
	if (CurrentUser)
	{
		// We only want to emit this once.
		if (State != discord::Initialized)
		{
			CurrentToken = Token;
			State        = discord::Initialized;

			UserData.UserId = FString::Printf(TEXT("%lld"), CurrentUser->GetId());
			UserData.Username = ANSI_TO_TCHAR(CurrentUser->GetUsername());
			UserData.Discriminator = ANSI_TO_TCHAR(CurrentUser->GetDiscriminator());
			UserData.Avatar = ANSI_TO_TCHAR(CurrentUser->GetAvatar());
			UserData.OAuthToken = ANSI_TO_TCHAR(Token.GetAccessToken());
			OnDiscordInitialized.ExecuteIfBound(true, UserData, "");
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[Discord Integration] Failed to get Discord User Info"));
		State = discord::Failed;
		OnDiscordInitialized.ExecuteIfBound(false, UserData, "Failed to get Discord User Info");
	}
}
