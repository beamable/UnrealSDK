#pragma once
/**
 * @brief Semantic separation for longs representing a Beamable Request Id.
 * Every request sent out from any of the UBeam***Api subsystems gets one of these.
 */
typedef int64 FBeamRequestId;

#ifdef BEAM_ENABLE_BEAMABLE_OSS

class IOnlineSubsystem;

// Defines here are meant to be used with the OnlineSubsystemBeamable plugin.
namespace BeamOSS
{
	// This is the string for the NamedInterface we expect to exist.
#ifndef OSS_BEAMABLE_GAME_INSTANCE
#define OSS_BEAMABLE_GAME_INSTANCE() FString(TEXT("BEAM_UE_GameInstance"))
#endif

// Use this for FOnlineAccountCredentials::Type, for signing up with Email/Password 
#ifndef OSS_BEAMABLE_IDENTITY_TYPE_SIGNUP_EMAIL
#define OSS_BEAMABLE_IDENTITY_TYPE_SIGNUP_EMAIL() FString(TEXT("signup_email"))
#endif

// Use this for FOnlineAccountCredentials::Type, for Email/Password 
#ifndef OSS_BEAMABLE_IDENTITY_TYPE_EMAIL
#define OSS_BEAMABLE_IDENTITY_TYPE_EMAIL() FString(TEXT("email"))
#endif

// Use this for FOnlineAccountCredentials::Type, for federated identity via microservice
#ifndef OSS_BEAMABLE_IDENTITY_TYPE_FEDERATED
#define OSS_BEAMABLE_IDENTITY_TYPE_FEDERATED(ServiceName, Namespace) FString::Printf(TEXT("extern_%s/%s"), *ServiceName, *Namespace)
#endif


	/**
	* When using Beamable's OSS, call this to set up the OnlineSubsystem with what Beamable needs.
	*/
	BEAMABLECORE_API void InitializeOnlineSubsystemBeamable(IOnlineSubsystem* OnlineSubsystemInterface, UGameInstance* GameInstance);

	BEAMABLECORE_API FString GetIdentityTypeSignUpEmail();

	BEAMABLECORE_API FString GetIdentityTypeEmail();

	BEAMABLECORE_API FString GetIdentityTypeFederated(FString ServiceName, FString Namespace);
}
#endif
