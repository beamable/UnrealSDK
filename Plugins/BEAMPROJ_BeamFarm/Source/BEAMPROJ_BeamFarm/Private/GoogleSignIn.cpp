#include "GoogleSignIn.h"

#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineExternalUIInterface.h"

bool UGoogleSignIn::IsLoggedIn(int32 index)
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get(GOOGLE_SUBSYSTEM);
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();

	// Check if the current status for the login is logged in
	if (Identity.Get()->GetLoginStatus(index) != ELoginStatus::LoggedIn)
	{
		UE_LOG(LogTemp, Error, TEXT("[GOOGLE] User is not logged in"));
		return false;
	}
	return true;
}

FString UGoogleSignIn::GetAccessToken(APlayerController* PlayerController)
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get(GOOGLE_SUBSYSTEM);
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
	
	const int32 ControllerId = CastChecked<ULocalPlayer>(PlayerController->Player)->GetControllerId();
	
	if (!IsLoggedIn(ControllerId)) return "";
        
	TSharedPtr<const FUniqueNetId> UserId = Identity->GetUniquePlayerId(ControllerId);
	
	TSharedPtr<FUserOnlineAccount> UserOnlineAccount = Identity->GetUserAccount(*UserId);
	
	if (!UserOnlineAccount.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("[GOOGLE] User account is invalid")); 
	}

	// Getting the token from the online subsystem
	FString Token;
	UserOnlineAccount->GetAuthAttribute(AUTH_ATTR_ID_TOKEN, Token);
	return Token;
}

void UGoogleSignIn::Login(APlayerController* PlayerController, FOnGoogleEventComplete OnLoginSuccess, FOnGoogleEventComplete OnLoginFail)
{
	IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get(GOOGLE_SUBSYSTEM);
	if (!OnlineSub)
	{
		UE_LOG(LogTemp, Error, TEXT("OnlineSubsystem not found"));
		return;
	}

	// IMPORTANT: Login must happen HERE
	IOnlineIdentityPtr Identity = OnlineSub->GetIdentityInterface();
	
	const int32 ControllerId = CastChecked<ULocalPlayer>(PlayerController->Player)->GetControllerId();
	
	Identity->AddOnLoginCompleteDelegate_Handle(
		ControllerId,
		FOnLoginCompleteDelegate::CreateLambda(
				[Identity, OnLoginSuccess, OnLoginFail](int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error)
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
