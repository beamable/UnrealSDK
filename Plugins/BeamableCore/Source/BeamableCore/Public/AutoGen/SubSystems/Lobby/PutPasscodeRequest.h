
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/JoinLobby.h"
#include "BeamableCore/Public/AutoGen/Lobby.h"

#include "PutPasscodeRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutPasscodeRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UJoinLobby* Body = {};

	// Beam Base Request Declaration
	UPutPasscodeRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Make PutPasscode",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_Passcode,_Tags,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutPasscodeRequest* Make(FOptionalString _Passcode, FOptionalArrayOfBeamTag _Tags, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutPasscodeSuccess, FBeamRequestContext, Context, UPutPasscodeRequest*, Request, ULobby*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutPasscodeError, FBeamRequestContext, Context, UPutPasscodeRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutPasscodeComplete, FBeamRequestContext, Context, UPutPasscodeRequest*, Request);

using FPutPasscodeFullResponse = FBeamFullResponse<UPutPasscodeRequest*, ULobby*>;
DECLARE_DELEGATE_OneParam(FOnPutPasscodeFullResponse, FPutPasscodeFullResponse);
