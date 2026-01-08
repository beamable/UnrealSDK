#include "AppleSignIn.h"

void UAppleSignIn::Login(APlayerController* PlayerController, FOnAppleEventComplete OnLoginSuccess,
	FOnAppleEventComplete OnLoginFail)
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get(IOS_SUBSYSTEM);
		
	if (!OnlineSub)
	{
		UE_LOG(LogTemp, Error, TEXT("OnlineSubsystem not found"));
		return;
	}

	IOnlineIdentityPtr Identity = OnlineSub->GetIdentityInterface();

	const int32 ControllerId = CastChecked<ULocalPlayer>(PlayerController->Player)->GetControllerId();
    
	Identity->AddOnLoginCompleteDelegate_Handle(
	ControllerId,
	FOnLoginCompleteDelegate::CreateLambda(
			[OnLoginSuccess, OnLoginFail](int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
			{
				if (bWasSuccessful)
				{
					UE_LOG(LogTemp, Warning, TEXT("Login Complete!"));
					OnLoginSuccess.ExecuteIfBound();
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Login failed: %s"), *Error);
					OnLoginFail.ExecuteIfBound();
				}
			}
		)
	);
	Identity->Login(ControllerId, FOnlineAccountCredentials{});
}

FString UAppleSignIn::GetAccessToken(APlayerController* PlayerController)
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get(IOS_SUBSYSTEM);
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();

	const int32 ControllerId = CastChecked<ULocalPlayer>(PlayerController->Player)->GetControllerId();
		
	TSharedPtr<const FUniqueNetId> UserId = Identity->GetUniquePlayerId(ControllerId);
	
	TSharedPtr<FUserOnlineAccount> UserOnlineAccount = Identity->GetUserAccount(*UserId);
	
	if (!UserOnlineAccount.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("[APPLE] User account is invalid")); 
	}

	// Getting the token from the online subsystem
	return *UserOnlineAccount->GetUserId()->ToString();
}
