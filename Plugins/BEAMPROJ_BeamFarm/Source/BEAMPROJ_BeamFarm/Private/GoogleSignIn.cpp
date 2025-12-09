#include "GoogleSignIn.h"

#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineSubsystem.h"

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

FString UGoogleSignIn::GetAccessToken(int32 index)
{
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get(GOOGLE_SUBSYSTEM);
	IOnlineIdentityPtr Identity = Subsystem->GetIdentityInterface();
        
	if (!IsLoggedIn(index)) return "";
        
	TSharedPtr<const FUniqueNetId> UserId = Identity->GetUniquePlayerId(index);
	
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