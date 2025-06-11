
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/CreateLaunchMessageRequestBody.h"
#include "BeamableCore/Public/AutoGen/CommonResponse.h"

#include "PostLaunchMessageRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UPostLaunchMessageRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="", Category="Beam")
	UCreateLaunchMessageRequestBody* Body = {};

	// Beam Base Request Declaration
	UPostLaunchMessageRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make PostLaunchMessage",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UPostLaunchMessageRequest* Make(FString _Name, FString _Body, UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostLaunchMessageSuccess, FBeamRequestContext, Context, UPostLaunchMessageRequest*, Request, UCommonResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnPostLaunchMessageError, FBeamRequestContext, Context, UPostLaunchMessageRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPostLaunchMessageComplete, FBeamRequestContext, Context, UPostLaunchMessageRequest*, Request);

using FPostLaunchMessageFullResponse = FBeamFullResponse<UPostLaunchMessageRequest*, UCommonResponse*>;
DECLARE_DELEGATE_OneParam(FOnPostLaunchMessageFullResponse, FPostLaunchMessageFullResponse);
