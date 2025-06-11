
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/PlayerIdRequestBody.h"
#include "BeamableCore/Public/AutoGen/FriendshipStatus.h"

#include "DeleteBlockedRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UDeleteBlockedRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UPlayerIdRequestBody* Body = {};

	// Beam Base Request Declaration
	UDeleteBlockedRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Friends|Utils|Make/Break", DisplayName="Make DeleteBlocked",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UDeleteBlockedRequest* Make(FBeamGamerTag _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteBlockedSuccess, FBeamRequestContext, Context, UDeleteBlockedRequest*, Request, UFriendshipStatus*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnDeleteBlockedError, FBeamRequestContext, Context, UDeleteBlockedRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteBlockedComplete, FBeamRequestContext, Context, UDeleteBlockedRequest*, Request);

using FDeleteBlockedFullResponse = FBeamFullResponse<UDeleteBlockedRequest*, UFriendshipStatus*>;
DECLARE_DELEGATE_OneParam(FOnDeleteBlockedFullResponse, FDeleteBlockedFullResponse);
