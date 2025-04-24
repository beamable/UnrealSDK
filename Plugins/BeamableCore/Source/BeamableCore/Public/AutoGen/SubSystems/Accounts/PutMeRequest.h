
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/AccountUpdate.h"
#include "BeamableCore/Public/AutoGen/AccountPlayerView.h"

#include "PutMeRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutMeRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UAccountUpdate* Body = {};

	// Beam Base Request Declaration
	UPutMeRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Accounts|Utils|Make/Break", DisplayName="Make PutMe",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="_ThirdParty,_Country,_Language,_GamerTagAssoc,_Token,_DeviceId,_UserName,_External,RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPutMeRequest* Make(bool _bHasThirdPartyToken, FOptionalString _ThirdParty, FOptionalString _Country, FOptionalString _Language, FOptionalGamerTagAssociation _GamerTagAssoc, FOptionalString _Token, FOptionalString _DeviceId, FOptionalString _UserName, FOptionalArrayOfBeamExternalIdentity _External, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutMeSuccess, FBeamRequestContext, Context, UPutMeRequest*, Request, UAccountPlayerView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutMeError, FBeamRequestContext, Context, UPutMeRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutMeComplete, FBeamRequestContext, Context, UPutMeRequest*, Request);

using FPutMeFullResponse = FBeamFullResponse<UPutMeRequest*, UAccountPlayerView*>;
DECLARE_DELEGATE_OneParam(FOnPutMeFullResponse, FPutMeFullResponse);
