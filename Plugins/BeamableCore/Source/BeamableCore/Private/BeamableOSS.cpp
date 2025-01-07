#include "BeamableOSS.h"

#include "OnlineSubsystem.h"
#include "UserSlots/BeamUserSlots.h"

#ifdef BEAM_ENABLE_BEAMABLE_OSS

void BeamOSS::InitializeOnlineSubsystemBeamable(IOnlineSubsystem* OnlineSubsystemInterface, UGameInstance* GameInstance)
{
	FString RawName = OSS_BEAMABLE_GAME_INSTANCE();
	OnlineSubsystemInterface->SetNamedInterface(FName(RawName), GameInstance);
}

// SignUps

FString BeamOSS::GetIdentityTypeFrictionless()
{
	FString Type = OSS_BEAMABLE_IDENTITY_TYPE_FRICTIONLESS();
	return Type;
}

FString BeamOSS::GetIdentityTypeSignUpEmail()
{
	FString Type = OSS_BEAMABLE_IDENTITY_TYPE_SIGNUP_EMAIL();
	return Type;
}

FString BeamOSS::GetIdentityTypeSignUpFederated(FString ServiceName, FString FederationId)
{
	FString Type = OSS_BEAMABLE_IDENTITY_TYPE_SIGNUP_FEDERATED(ServiceName, FederationId);
	return Type;
}

// Logins

FString BeamOSS::GetIdentityTypeEmail()
{
	FString Type = OSS_BEAMABLE_IDENTITY_TYPE_EMAIL();
	return Type;
}

FString BeamOSS::GetIdentityTypeFederated(FString ServiceName, FString FederationId)
{
	FString Type = OSS_BEAMABLE_IDENTITY_TYPE_FEDERATED(ServiceName, FederationId);
	return Type;
}

// Attachs

FString BeamOSS::GetIdentityTypeAttachEmail()
{
	FString Type = OSS_BEAMABLE_IDENTITY_TYPE_ATTACH_EMAIL();
	return Type;
}

FString BeamOSS::GetIdentityTypeAttachFederated(FString ServiceName, FString FederationId)
{
	FString Type = OSS_BEAMABLE_IDENTITY_TYPE_ATTACH_FEDERATED(ServiceName, FederationId);
	return Type;
}
#endif
