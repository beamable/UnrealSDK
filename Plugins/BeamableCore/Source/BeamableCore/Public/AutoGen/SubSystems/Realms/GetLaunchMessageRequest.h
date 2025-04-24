
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseRequestInterface.h"
#include "BeamBackend/BeamRequestContext.h"
#include "BeamBackend/BeamErrorResponse.h"
#include "BeamBackend/BeamFullResponse.h"

#include "BeamableCore/Public/AutoGen/LaunchMessageListResponse.h"

#include "GetLaunchMessageRequest.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UGetLaunchMessageRequest : public UObject, public IBeamBaseRequestInterface
{
	GENERATED_BODY()
	
public:

	// Path Params
	
	
	// Query Params
	

	// Body Params
	

	// Beam Base Request Declaration
	UGetLaunchMessageRequest() = default;

	virtual void BuildVerb(FString& VerbString) const override;
	virtual void BuildRoute(FString& RouteString) const override;
	virtual void BuildBody(FString& BodyString) const override;

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make GetLaunchMessage",  meta=(DefaultToSelf="RequestOwner", AdvancedDisplay="RequestOwner", AutoCreateRefTerm="CustomHeaders"))
	static UGetLaunchMessageRequest* Make(UObject* RequestOwner, TMap<FString, FString> CustomHeaders);
};

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetLaunchMessageSuccess, FBeamRequestContext, Context, UGetLaunchMessageRequest*, Request, ULaunchMessageListResponse*, Response);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGetLaunchMessageError, FBeamRequestContext, Context, UGetLaunchMessageRequest*, Request, FBeamErrorResponse, Error);

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetLaunchMessageComplete, FBeamRequestContext, Context, UGetLaunchMessageRequest*, Request);

using FGetLaunchMessageFullResponse = FBeamFullResponse<UGetLaunchMessageRequest*, ULaunchMessageListResponse*>;
DECLARE_DELEGATE_OneParam(FOnGetLaunchMessageFullResponse, FGetLaunchMessageFullResponse);
