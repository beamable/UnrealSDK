
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/PlayerIdRequestBody.h"
#include "BeamableCore/Public/AutoGen/FriendshipStatus.h"

#include "PostBlockedRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostBlockedRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UPlayerIdRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostBlockedRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Friends|Utils|Make/Break", DisplayName="Make PostBlocked",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostBlockedRequest* Make(FBeamGamerTag _PlayerId, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostBlockedSuccess, FBeamRequestContext, Context, UPostBlockedRequest*, Request, UFriendshipStatus*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostBlockedError, FBeamRequestContext, Context, UPostBlockedRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostBlockedComplete, FBeamRequestContext, Context, UPostBlockedRequest*, Request);

using FPostBlockedFullResponse = FBeamFullResponse<UPostBlockedRequest*, UFriendshipStatus*>;
DECLARE_DELEGATE_OneParam(FOnPostBlockedFullResponse, FPostBlockedFullResponse);
