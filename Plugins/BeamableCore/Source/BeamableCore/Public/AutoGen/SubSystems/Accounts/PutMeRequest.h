
#pragma once

#include "CoreMinimal.h"
#include "BeamCoreTypes.h"

#include "AutoGen/AccountUpdate.h"
#include "AutoGen/AccountPlayerView.h"

#include "PutMeRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPutMeRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="")
	UAccountUpdate* Body;

	// Beam Base Request Declaration
	UPutMeRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, meta=(DefaultToSelf="Outer", AdvancedDisplay="_ThirdParty,_Country,_Language,_GamerTagAssoc,_Token,_DeviceId,_UserName,Outer"))
	static UPutMeRequest* MakePutMeRequest(FOptionalString _ThirdParty, bool _bHasThirdPartyToken, FOptionalString _Country, FOptionalString _Language, FOptionalGamerTagAssociation _GamerTagAssoc, FOptionalString _Token, FOptionalString _DeviceId, FOptionalString _UserName, UObject* Outer);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutMeSuccess, FBeamRequestContext, Context, UPutMeRequest*, Request, UAccountPlayerView*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPutMeError, FBeamRequestContext, Context, UPutMeRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPutMeComplete, FBeamRequestContext, Context, UPutMeRequest*, Request);

using FPutMeFullResponse = FBeamFullResponse<UPutMeRequest*, UAccountPlayerView*>;
DECLARE_DELEGATE_OneParam(FOnPutMeFullResponse, FPutMeFullResponse);