#include "AppleSignIn.h"

#include "OnlineSubsystem.h"
#include "Interfaces/OnlineIdentityInterface.h"

void UAppleSignIn::Login(APlayerController* PlayerController, FOnAppleEventComplete OnLoginSuccess, FOnAppleEventComplete OnLoginFail)
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get(IOS_SUBSYSTEM);
		
	if (!OnlineSub)
	{
		UE_LOG(LogTemp, Error, TEXT("OnlineSubsystem not found"));
		OnLoginFail.ExecuteIfBound();
		return;
	}
	
	IOnlineIdentityPtr Identity = OnlineSub->GetIdentityInterface();

	const int32 ControllerId = CastChecked<ULocalPlayer>(PlayerController->Player)->GetControllerId();
    
	Identity->AddOnLoginCompleteDelegate_Handle(
	ControllerId,
	FOnLoginCompleteDelegate::CreateLambda([OnLoginFail, OnLoginSuccess](int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
			{
				if (bWasSuccessful)
				{
					UE_LOG(LogTemp, Warning, TEXT("Login Complete New!"));
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

FString UAppleSignIn::GetUserId(APlayerController* PlayerController)
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get(IOS_SUBSYSTEM);
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();

	const int32 ControllerId = CastChecked<ULocalPlayer>(PlayerController->Player)->GetControllerId();

	UE_LOG(LogTemp, Warning, TEXT("PLAYER ID: %s"), *Identity->GetUniquePlayerId(ControllerId)->ToString());
	
	// Getting the token from the online subsystem
	return *Identity->GetUniquePlayerId(ControllerId)->ToString();
}
